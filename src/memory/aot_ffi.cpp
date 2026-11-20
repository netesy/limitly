// Standalone canonical-LIR FFI adapter. Uses the same platform ABI engine as VM.
#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#endif
#include "aot_ffi_values.hh"
#include "../runtime/lymarrt/lymarrt.h"
#include <cstring>
#include <cstdio>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <stdexcept>
namespace {
using Word=uint64_t;
std::recursive_mutex mutex;
struct Function { void* address; std::vector<lymarrt_type> arguments; lymarrt_type result; };
struct Callback {
    Function function; lymarrt_type result; int64_t handle=0;
    Callback(Function f,lymarrt_type r):function(std::move(f)),result(r) {}
    ~Callback() {if(handle>0) lymarrt_callback_destroy(handle);}
};
struct Library {
    void* handle; std::vector<void*> symbols;
    explicit Library(void* h):handle(h) {}
    ~Library() {lymarrt_library_close(handle);}
};
std::map<std::string,Function> functions;
std::map<int64_t,std::shared_ptr<Callback>> callbacks;
std::map<void*,std::shared_ptr<Library>> libraries;
void register_shutdown() {
    struct Shutdown {
        ~Shutdown() {
            callbacks.clear();
            libraries.clear();
        }
    };
    static Shutdown shutdown;
}
lymarrt_type type(Word id,bool result=false) {
    if(id>LYMARRT_TYPE_VOID || (!result && id==LYMARRT_TYPE_VOID)) throw std::runtime_error("Invalid FFI type ID");
    return static_cast<lymarrt_type>(id);
}
lymarrt_value argument(Word value,lymarrt_type target) {
    lymarrt_value out{};out.type=target;
    if(target==LYMARRT_TYPE_F32) out.val.f32=lymar_aot_to_float(value);
    else if(target==LYMARRT_TYPE_F64) out.val.f64=lymar_aot_to_float(value);
    else if(target==LYMARRT_TYPE_PTR || target==LYMARRT_TYPE_CSTRING) out.val.ptr=reinterpret_cast<void*>(lymar_aot_ffi_pointer(value));
    else {auto number=lymar_aot_to_integer(value);switch(target) {
        case LYMARRT_TYPE_I8: out.val.i8=number;break;case LYMARRT_TYPE_U8:out.val.u8=number;break;
        case LYMARRT_TYPE_I16:out.val.i16=number;break;case LYMARRT_TYPE_U16:out.val.u16=number;break;
        case LYMARRT_TYPE_I32:out.val.i32=number;break;case LYMARRT_TYPE_U32:out.val.u32=number;break;
        case LYMARRT_TYPE_I64:out.val.i64=number;break;case LYMARRT_TYPE_U64:out.val.u64=number;break;
        default:throw std::runtime_error("Invalid FFI argument type");}}
    return out;
}
// Result words are self-describing LmValue words: integers become SMIs,
// floats/strings/pointers become heap objects, nil/void become VAL_NIL.
Word result(const lymarrt_value& value) {
    switch(value.type) {
        case LYMARRT_TYPE_I8:return lymar_aot_tag_int(value.val.i8);
        case LYMARRT_TYPE_U8:return lymar_aot_tag_int(value.val.u8);
        case LYMARRT_TYPE_I16:return lymar_aot_tag_int(value.val.i16);
        case LYMARRT_TYPE_U16:return lymar_aot_tag_int(value.val.u16);
        case LYMARRT_TYPE_I32:return lymar_aot_tag_int(value.val.i32);
        case LYMARRT_TYPE_U32:return lymar_aot_tag_int(value.val.u32);
        case LYMARRT_TYPE_I64:return lymar_aot_tag_int(value.val.i64);
        case LYMARRT_TYPE_U64:return lymar_aot_tag_int(static_cast<int64_t>(value.val.u64));
        case LYMARRT_TYPE_F32:return lymar_aot_box_float(value.val.f32);
        case LYMARRT_TYPE_F64:return lymar_aot_box_float(value.val.f64);
        case LYMARRT_TYPE_CSTRING: {
            if(!value.val.ptr) return lymar_aot_nil();
            auto* text=static_cast<const char*>(value.val.ptr);auto length=std::strlen(text);
            auto object=lymar_aot_alloc(25+length);Word header[3]={11,length,length};
            std::memcpy(reinterpret_cast<void*>(object),header,24);std::memcpy(reinterpret_cast<void*>(object+24),text,length+1);return object;
        }
        case LYMARRT_TYPE_PTR:return lymar_aot_ffi_wrap(reinterpret_cast<Word>(value.val.ptr));
        case LYMARRT_TYPE_VOID:return lymar_aot_nil();
        default:throw std::runtime_error("Invalid FFI return type");
    }
}
// --- GPU stage dispatch (software-emulation oracle, mirrors backend/vm/ops/gpu.cpp) ---
// gpu task functions are registered by name at startup; gpu_dispatch resolves
// the callable's name string, then invokes the function once per thread with
// the thread-context globals set, exactly like the register-VM emulation.
struct GpuEntry { Function function; Word stage, tx, ty, tz, max_vertices, max_primitives; };
std::map<std::string,GpuEntry> gpu_functions;
Word gpu_local_id[3]={0,0,0}, gpu_group_id[3]={0,0,0};
Word gpu_thread_dims[3]={1,1,1}, gpu_num_groups[3]={0,0,0};
Word gpu_mesh_vertices_=0, gpu_mesh_primitives_=0;

bool gpu_heap_read(Word ptr,Word offset,void* out,Word size) {
    return lymar_aot_heap_read(ptr,offset,out,size)==size;
}
Word gpu_field(Word ptr,Word offset) {
    Word value=0; gpu_heap_read(ptr,offset,&value,8); return value;
}
// Extracts the canonical function-name string from a callable value:
// type 11 is a name string; type 3 is a closure tuple whose first element is
// the name string (same shapes gpu_extract_callable_name handles in the VM).
std::string gpu_callable_name(Word value) {
    Word type=0;
    if(!gpu_heap_read(value,0,&type,8)) return "";
    type&=0xffffffff;
    auto string_chars=[&](Word str,std::string& out)->bool {
        Word header[3]={0};
        if(!gpu_heap_read(str,0,header,24) || (header[0]&0xffffffff)!=11) return false;
        Word length=header[1];
        if(length>4096) return false;
        out.resize(length);
        return length==0 || gpu_heap_read(str,24,out.data(),length);
    };
    if(type==11) { std::string out; return string_chars(value,out)?out:""; }
    if(type==3) {
        Word name=gpu_field(gpu_field(value,8),0);
        std::string out;
        if(string_chars(name,out)) return out;
    }
    return "";
}
// [x,y,z] list in the canonical AOT layout: 32-byte {1,data,count,capacity}
// header plus an element slot array, matching _builtin_list_with_capacity.
Word gpu_vec3(Word x,Word y,Word z) {
    auto pointer=lymar_aot_alloc(32);
    auto data=lymar_aot_alloc(24);
    Word header[4]={1,data,3,3};
    std::memcpy(reinterpret_cast<void*>(pointer),header,32);
    lymar_aot_edge(pointer+8,data);
    Word values[3]={x,y,z};
    for(Word index=0;index<3;++index) {
        std::memcpy(reinterpret_cast<void*>(data+index*8),&values[index],8);
        lymar_aot_edge(data+index*8,values[index]);
    }
    return pointer;
}
Word gpu_coords(int which) {
    Word coords[3];
    if(which==0) {
        for(int i=0;i<3;++i) coords[i]=gpu_group_id[i]*gpu_thread_dims[i]+gpu_local_id[i];
    } else {
        const Word* source=which==1?gpu_local_id:which==2?gpu_group_id:gpu_num_groups;
        for(int i=0;i<3;++i) coords[i]=source[i];
    }
    return gpu_vec3(coords[0],coords[1],coords[2]);
}
void callback(void* context,const lymarrt_value* args,size_t count,lymarrt_value* out) {
    auto& state=*static_cast<Callback*>(context);
    if(count!=state.function.arguments.size()) throw std::runtime_error("Callback arity mismatch");
    std::vector<lymarrt_value> values;values.reserve(count);
    for(size_t index=0;index<count;++index)
        values.push_back(argument(result(args[index]),state.function.arguments[index]));
    lymarrt_value returned{};
    if(!lymarrt_ffi_call(state.function.address,state.function.result,state.function.arguments.data(),values.data(),count,&returned))
        throw std::runtime_error("Native callback invocation failed");
    if(state.result==LYMARRT_TYPE_VOID) { *out={};out->type=LYMARRT_TYPE_VOID; }
    else *out=argument(result(returned),state.result);
}
}
extern "C" {
void lymar_aot_ffi_register(const char* name,void* address,Word count,Word floating,Word float_return) {
    std::lock_guard guard(mutex);
    Function function{address,{},float_return?LYMARRT_TYPE_F64:LYMARRT_TYPE_I64};
    for(Word index=0;index<count;++index) function.arguments.push_back((floating&(Word(1)<<index))?LYMARRT_TYPE_F64:LYMARRT_TYPE_I64);
    functions[lymar_aot_ffi_string(reinterpret_cast<Word>(name))]=std::move(function);
}
Word lymar_aot_library_open(Word path) {
    std::lock_guard guard(mutex);auto* handle=lymarrt_library_open(lymar_aot_ffi_string(path));
    if(handle) {if(!libraries.count(handle)) libraries.emplace(handle,std::make_shared<Library>(handle));register_shutdown();}return lymar_aot_ffi_wrap(reinterpret_cast<Word>(handle));
}
Word lymar_aot_library_symbol(Word handle,Word name) {
    std::lock_guard guard(mutex);auto* library=reinterpret_cast<void*>(lymar_aot_ffi_pointer(handle));
    auto found=libraries.find(library);
    if(found==libraries.end()) return lymar_aot_nil();
    auto* pointer=lymarrt_symbol_lookup(library,lymar_aot_ffi_string(name));
    if(pointer) found->second->symbols.push_back(pointer);return lymar_aot_ffi_wrap(reinterpret_cast<Word>(pointer));
}
void lymar_aot_library_close(Word handle) {
    std::lock_guard guard(mutex);auto* library=reinterpret_cast<void*>(lymar_aot_ffi_pointer(handle));
#ifdef _WIN32
    if (!library || library == GetModuleHandleA(NULL)) return;
#else
    if (!library) return;
#endif
    auto found=libraries.find(library);if(found==libraries.end()) return;
    for(auto* pointer:found->second->symbols) lymar_aot_ffi_invalidate(reinterpret_cast<Word>(pointer));
    lymar_aot_ffi_invalidate(reinterpret_cast<Word>(library));libraries.erase(found);
}
// Shared foreign-call implementation. `layouts`/`num_layouts` describe
// struct-by-value arguments (packed native bytes + element type list),
// mirroring the VM's lymarrt_ffi_call_ex path.
static Word foreign_call_impl(Word function,Word* words,Word* ids,Word count,Word return_type,
                              const lymarrt_struct_layout* layouts,size_t num_layouts) {
    std::unique_lock guard(mutex);
    auto* pointer=reinterpret_cast<void*>(lymar_aot_ffi_pointer(function));
    if(!pointer) return lymar_aot_nil();
    std::vector<lymarrt_type> signature;std::vector<lymarrt_value> arguments;
    for(Word index=0;index<count;++index) {signature.push_back(type(ids[index]));arguments.push_back(argument(words[index],signature.back()));}
    // Opaque C may invoke any registered callback, including on another
    // thread. Pin executable code and userdata, then release the registry
    // lock before entering C so a callback can safely re-enter FFI.
    std::vector<std::shared_ptr<Callback>> callback_pins;
    std::vector<std::shared_ptr<Library>> library_pins;
    for(const auto& entry:callbacks) callback_pins.push_back(entry.second);
    for(const auto& entry:libraries) library_pins.push_back(entry.second);
    guard.unlock();
    lymarrt_value returned{};
    auto okcall=lymarrt_ffi_call_ex(pointer,type(return_type,true),signature.data(),arguments.data(),count,layouts,num_layouts,&returned);
    if(!okcall) return lymar_aot_nil();
    return result(returned);
}
Word lymar_aot_foreign_call(Word function,Word values,Word types,Word count,Word return_type) {
    return foreign_call_impl(function,reinterpret_cast<Word*>(values),reinterpret_cast<Word*>(types),count,return_type,nullptr,0);
}
Word lymar_aot_foreign_call_list(Word function,Word values,Word return_type,Word types) {
    auto count=lymar_aot_ffi_list_size(values),type_count=lymar_aot_ffi_list_size(types);
    std::vector<Word> words,ids;
    std::vector<lymarrt_struct_layout> layouts;
    for(Word index=0;index<count;++index) {
        auto value=lymar_aot_ffi_list_item(values,index);
        words.push_back(value);
        if(index<type_count) {
            auto titem=lymar_aot_ffi_list_item(types,index);
            // A types entry that is itself a list is a struct-by-value
            // descriptor: [TYPE_STRUCT, elem_type_id, ...] (VM parity with
            // the register-VM foreign_call param-type handling).
            Word hdr=0;
            bool is_list=lymar_aot_heap_read(titem,0,&hdr,8) && (hdr&0xffffffff)==1;
            if(is_list) {
                auto n=lymar_aot_ffi_list_size(titem);
                if(n>=2 && n-1<=LYMARRT_MAX_STRUCT_ELEMS &&
                   lymar_aot_to_integer(lymar_aot_ffi_list_item(titem,0))==13) {
                    lymarrt_struct_layout lay{};lay.arg_index=(uint32_t)index;lay.count=(uint32_t)(n-1);
                    bool ok=true;
                    for(uint32_t e=0;e<lay.count;++e) {
                        auto et=lymar_aot_to_integer(lymar_aot_ffi_list_item(titem,e+1));
                        if(et<0 || et>(int64_t)LYMARRT_TYPE_PTR) {ok=false;break;}
                        lay.types[e]=static_cast<lymarrt_type>(et);
                    }
                    if(ok) {layouts.push_back(lay);ids.push_back(LYMARRT_TYPE_PTR);continue;}
                }
            }
            ids.push_back(lymar_aot_to_integer(titem));
        }
        else ids.push_back(lymar_aot_ffi_infer_type(value));
    }
    return foreign_call_impl(function,words.data(),ids.data(),count,return_type,layouts.data(),layouts.size());
}
Word lymar_aot_callback_create(Word name,Word arguments,Word return_type) {
    std::lock_guard guard(mutex);auto text=std::string(lymar_aot_ffi_string(name));auto found=functions.find(text);
    if(found==functions.end()) {std::fprintf(stderr,"[ffi] callback_create: function '%s' is not registered\n",text.c_str());return lymar_aot_nil();}
    auto count=lymar_aot_ffi_list_size(arguments);
    if(count!=found->second.arguments.size() || count>64) throw std::runtime_error("Callback parameter count mismatch");
    std::vector<lymarrt_type> signature;
    for(Word index=0;index<count;++index) signature.push_back(type(lymar_aot_to_integer(lymar_aot_ffi_list_item(arguments,index))));
    auto context=std::make_shared<Callback>(found->second,type(return_type,true));
    auto handle=lymarrt_callback_create(callback,context.get(),signature.data(),count,context->result);
    if(handle>0) {context->handle=handle;callbacks[handle]=std::move(context);register_shutdown();}return handle;
}
Word lymar_aot_callback_pointer(Word handle) {std::lock_guard guard(mutex);return lymar_aot_ffi_wrap(reinterpret_cast<Word>(lymarrt_callback_get_ptr(handle)));}
void lymar_aot_callback_destroy(Word handle) {
    std::lock_guard guard(mutex);auto found=callbacks.find(handle);if(found==callbacks.end()) return;
    lymar_aot_ffi_invalidate(reinterpret_cast<Word>(lymarrt_callback_get_ptr(handle)));callbacks.erase(found);
}

// Registers a gpu stage entry point for name-based lookup. Same calling
// convention metadata as lymar_aot_ffi_register plus stage kind (1=task,
// 2=vertex, 3=pixel, 4=mesh), workgroup dims, and mesh output limits.
void lymar_aot_gpu_register(const char* name,void* address,Word count,Word floating,Word float_return,Word stage,Word tx,Word ty,Word tz,Word max_vertices,Word max_primitives) {
    std::lock_guard guard(mutex);
    Function function{address,{},float_return?LYMARRT_TYPE_F64:LYMARRT_TYPE_I64};
    for(Word index=0;index<count;++index) function.arguments.push_back((floating&(Word(1)<<index))?LYMARRT_TYPE_F64:LYMARRT_TYPE_I64);
    gpu_functions[lymar_aot_ffi_string(reinterpret_cast<Word>(name))]=GpuEntry{function,stage,tx,ty,tz,max_vertices,max_primitives};
}
Word lymar_aot_gpu_thread_id() { return gpu_coords(0); }
Word lymar_aot_gpu_local_id() { return gpu_coords(1); }
Word lymar_aot_gpu_group_id() { return gpu_coords(2); }
Word lymar_aot_gpu_num_groups() { return gpu_coords(3); }
// Workgroup barriers are implicit in single-threaded emulation (VM parity).
Word lymar_aot_gpu_sync(Word) { return lymar_aot_nil(); }
Word lymar_aot_gpu_set_mesh_counts(Word vertices,Word primitives) {
    gpu_mesh_vertices_=lymar_aot_to_integer(vertices);
    gpu_mesh_primitives_=lymar_aot_to_integer(primitives);
    return lymar_aot_nil();
}
Word lymar_aot_gpu_dispatch(Word task,Word gx,Word gy,Word gz,Word args) {
    std::lock_guard<std::recursive_mutex> guard(mutex);
    auto fail=[&](const char* message) {
        std::fprintf(stderr,"[gpu] %s\n",message);
        return lymar_aot_nil();
    };
    std::string name=gpu_callable_name(task);
    if(name.empty()) return fail("gpu_dispatch: first argument must be a gpu task function");
    auto found=gpu_functions.find(name);
    if(found==gpu_functions.end()) {
        // Callable names may carry module qualification the registry key
        // lacks (or vice versa); fall back to an unambiguous suffix match.
        for(auto candidate=gpu_functions.begin();candidate!=gpu_functions.end();++candidate) {
            const std::string& key=candidate->first;
            bool suffix=key.size()>name.size() && key.compare(key.size()-name.size(),name.size(),name)==0 &&
                        key[key.size()-name.size()-1]=='.';
            bool prefix=name.size()>key.size() && name.compare(name.size()-key.size(),key.size(),key)==0 &&
                         name[name.size()-key.size()-1]=='.';
            if(suffix||prefix) { found=candidate; break; }
        }
    }
    if(found==gpu_functions.end()) {
        char message[600];std::snprintf(message,sizeof(message),"gpu_dispatch: unknown gpu task '%s'",name.c_str());
        return fail(message);
    }
    auto& entry=found->second;
    if(entry.stage!=1)
        return fail("gpu_dispatch: target is not a gpu task stage");
    int64_t grid_x=static_cast<int64_t>(lymar_aot_to_integer(gx));
    int64_t grid_y=static_cast<int64_t>(lymar_aot_to_integer(gy));
    int64_t grid_z=static_cast<int64_t>(lymar_aot_to_integer(gz));
    if(grid_x<=0||grid_y<=0||grid_z<=0) return fail("gpu_dispatch: grid dimensions must be positive");
    // Unpack the trailing argument list (VM parity: non-list non-nil value is
    // a single argument; nil means no arguments).
    std::vector<Word> arg_words;
    Word list_header=0;
    bool is_list=gpu_heap_read(args,0,&list_header,8) && (list_header&0xffffffff)==1;
    if(is_list) {
        Word count=0;
        try{count=lymar_aot_ffi_list_size(args);}catch(...){count=0;}
        for(Word index=0;index<count;++index) arg_words.push_back(lymar_aot_ffi_list_item(args,index));
    } else if(args!=2) arg_words.push_back(args);
    // Marshal arguments to the registered signature, padding missing params.
    // Integer params decode the tagged LmValue word to its integer payload;
    // float params are true F64 ABI values — the callee's machine signature
    // expects a double in the FP register, not a tagged word.
    const size_t arity=entry.function.arguments.size();
    std::vector<lymarrt_type> signature=entry.function.arguments;
    std::vector<lymarrt_value> values(arity);
    for(size_t index=0;index<arity;++index) {
        Word word=index<arg_words.size()?arg_words[index]:0;
        if(signature[index]==LYMARRT_TYPE_F64) {
            values[index].type=LYMARRT_TYPE_F64;
            // List elements carry floats in two representations: boxed heap
            // objects (literals) and raw f64 bit patterns (const-folded
            // values). Unbox the former, bitcast the latter.
            Word hdr=0;
            bool boxed=(word&7)==0 && word>4096 && gpu_heap_read(word,0,&hdr,8) && (hdr&0xffffffff)==9;
            if(boxed) {
                values[index].val.f64=lymar_aot_to_float(word);
            } else {
                std::memcpy(&values[index].val.f64,&word,sizeof(double));
            }
        } else {
            values[index].type=LYMARRT_TYPE_I64;
            values[index].val.i64=static_cast<int64_t>(lymar_aot_to_integer(word));
        }
    }
    // Save outer thread context for nested dispatch (VM parity).
    Word saved_local[3],saved_group[3],saved_dims[3],saved_groups[3];
    std::memcpy(saved_local,gpu_local_id,sizeof(saved_local));
    std::memcpy(saved_group,gpu_group_id,sizeof(saved_group));
    std::memcpy(saved_dims,gpu_thread_dims,sizeof(saved_dims));
    std::memcpy(saved_groups,gpu_num_groups,sizeof(saved_groups));
    const Word tx=entry.tx?entry.tx:1, ty=entry.ty?entry.ty:1, tz=entry.tz?entry.tz:1;
    gpu_thread_dims[0]=tx;gpu_thread_dims[1]=ty;gpu_thread_dims[2]=tz;
    gpu_num_groups[0]=grid_x;gpu_num_groups[1]=grid_y;gpu_num_groups[2]=grid_z;
    try {
        for(int64_t gz_i=0;gz_i<grid_z*tz;++gz_i)
            for(int64_t gy_i=0;gy_i<grid_y*ty;++gy_i)
                for(int64_t gx_i=0;gx_i<grid_x*tx;++gx_i) {
                    gpu_local_id[0]=gx_i%tx;gpu_local_id[1]=gy_i%ty;gpu_local_id[2]=gz_i%tz;
                    gpu_group_id[0]=gx_i/tx;gpu_group_id[1]=gy_i/ty;gpu_group_id[2]=gz_i/tz;
                    lymarrt_value ignored{};
                    // Lymar functions return a tagged i64 word regardless of
                    // the LIR return type (floats come back boxed).
                    lymarrt_ffi_call(entry.function.address,LYMARRT_TYPE_I64,
                                     signature.data(),values.data(),arity,&ignored);
                }
    } catch (...) {
        std::memcpy(gpu_local_id,saved_local,sizeof(saved_local));
        std::memcpy(gpu_group_id,saved_group,sizeof(saved_group));
        std::memcpy(gpu_thread_dims,saved_dims,sizeof(saved_dims));
        std::memcpy(gpu_num_groups,saved_groups,sizeof(saved_groups));
        throw;
    }
    std::memcpy(gpu_local_id,saved_local,sizeof(saved_local));
    std::memcpy(gpu_group_id,saved_group,sizeof(saved_group));
    std::memcpy(gpu_thread_dims,saved_dims,sizeof(saved_dims));
    std::memcpy(gpu_num_groups,saved_groups,sizeof(saved_groups));
    return lymar_aot_nil();
}
}
