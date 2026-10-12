// Standalone canonical-LIR FFI adapter. Uses the same platform ABI engine as VM.
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
lymarrt_value argument(Word value,Word kind,lymarrt_type target) {
    lymarrt_value out{};out.type=target;
    if(target==LYMARRT_TYPE_F32) out.val.f32=lymar_aot_to_float(value,kind);
    else if(target==LYMARRT_TYPE_F64) out.val.f64=lymar_aot_to_float(value,kind);
    else if(target==LYMARRT_TYPE_PTR || target==LYMARRT_TYPE_CSTRING) out.val.ptr=reinterpret_cast<void*>(lymar_aot_ffi_pointer(value,kind));
    else {auto number=lymar_aot_to_integer(value,kind);switch(target) {
        case LYMARRT_TYPE_I8: out.val.i8=number;break;case LYMARRT_TYPE_U8:out.val.u8=number;break;
        case LYMARRT_TYPE_I16:out.val.i16=number;break;case LYMARRT_TYPE_U16:out.val.u16=number;break;
        case LYMARRT_TYPE_I32:out.val.i32=number;break;case LYMARRT_TYPE_U32:out.val.u32=number;break;
        case LYMARRT_TYPE_I64:out.val.i64=number;break;case LYMARRT_TYPE_U64:out.val.u64=number;break;
        default:throw std::runtime_error("Invalid FFI argument type");}}
    return out;
}
Word result(const lymarrt_value& value,Word& kind) {
    kind=0;
    switch(value.type) {
        case LYMARRT_TYPE_I8:return value.val.i8;case LYMARRT_TYPE_U8:return value.val.u8;
        case LYMARRT_TYPE_I16:return value.val.i16;case LYMARRT_TYPE_U16:return value.val.u16;
        case LYMARRT_TYPE_I32:return value.val.i32;case LYMARRT_TYPE_U32:return value.val.u32;
        case LYMARRT_TYPE_I64:return value.val.i64;case LYMARRT_TYPE_U64:return value.val.u64;
        case LYMARRT_TYPE_F32:kind=1;return lymar_aot_box_float(value.val.f32);
        case LYMARRT_TYPE_F64:kind=1;return lymar_aot_box_float(value.val.f64);
        case LYMARRT_TYPE_CSTRING: {
            kind=1;if(!value.val.ptr) return lymar_aot_nil();
            auto* text=static_cast<const char*>(value.val.ptr);auto length=std::strlen(text);
            auto object=lymar_aot_alloc(25+length);Word header[3]={11,length,length};
            std::memcpy(reinterpret_cast<void*>(object),header,24);std::memcpy(reinterpret_cast<void*>(object+24),text,length+1);return object;
        }
        case LYMARRT_TYPE_PTR:kind=1;return lymar_aot_ffi_wrap(reinterpret_cast<Word>(value.val.ptr));
        case LYMARRT_TYPE_VOID:kind=1;return lymar_aot_nil();
        default:throw std::runtime_error("Invalid FFI return type");
    }
}
void callback(void* context,const lymarrt_value* args,size_t count,lymarrt_value* out) {
    auto& state=*static_cast<Callback*>(context);
    if(count!=state.function.arguments.size()) throw std::runtime_error("Callback arity mismatch");
    std::vector<lymarrt_value> values;values.reserve(count);
    for(size_t index=0;index<count;++index) {
        Word kind=0;auto value=result(args[index],kind);
        values.push_back(argument(value,kind,state.function.arguments[index]));
        lymar_aot_arg_set(index,state.function.arguments[index]==LYMARRT_TYPE_F64?0:kind);
    }
    lymarrt_value returned{};
    if(!lymarrt_ffi_call(state.function.address,state.function.result,state.function.arguments.data(),values.data(),count,&returned))
        throw std::runtime_error("Native callback invocation failed");
    Word kind=0;auto value=result(returned,kind);
    if(state.function.result==LYMARRT_TYPE_I64) kind=lymar_aot_return_pointer();
    if(state.result==LYMARRT_TYPE_VOID) { *out={};out->type=LYMARRT_TYPE_VOID; }
    else *out=argument(value,kind,state.result);
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
    if(handle) {if(!libraries.count(handle)) libraries.emplace(handle,std::make_shared<Library>(handle));register_shutdown();}lymar_aot_ffi_result_kind(1);
    return lymar_aot_ffi_wrap(reinterpret_cast<Word>(handle));
}
Word lymar_aot_library_symbol(Word handle,Word name) {
    std::lock_guard guard(mutex);auto* library=reinterpret_cast<void*>(lymar_aot_ffi_pointer(handle,1));
    auto found=libraries.find(library);lymar_aot_ffi_result_kind(1);
    if(found==libraries.end()) return lymar_aot_nil();
    auto* pointer=lymarrt_symbol_lookup(library,lymar_aot_ffi_string(name));
    if(pointer) found->second->symbols.push_back(pointer);return lymar_aot_ffi_wrap(reinterpret_cast<Word>(pointer));
}
void lymar_aot_library_close(Word handle) {
    std::lock_guard guard(mutex);auto* library=reinterpret_cast<void*>(lymar_aot_ffi_pointer(handle,1));
    auto found=libraries.find(library);if(found==libraries.end()) return;
    for(auto* pointer:found->second->symbols) lymar_aot_ffi_invalidate(reinterpret_cast<Word>(pointer));
    lymar_aot_ffi_invalidate(reinterpret_cast<Word>(library));libraries.erase(found);
}
Word lymar_aot_foreign_call(Word function,Word values,Word kinds,Word types,Word count,Word return_type,Word function_kind) {
    std::unique_lock guard(mutex);auto* pointer=reinterpret_cast<void*>(lymar_aot_ffi_pointer(function,function_kind));
    if(!pointer) {lymar_aot_ffi_result_kind(1);return lymar_aot_nil();}
    auto* words=reinterpret_cast<Word*>(values);auto* flags=reinterpret_cast<Word*>(kinds);auto* ids=reinterpret_cast<Word*>(types);
    std::vector<lymarrt_type> signature;std::vector<lymarrt_value> arguments;
    for(Word index=0;index<count;++index) {signature.push_back(type(ids[index]));arguments.push_back(argument(words[index],flags[index],signature.back()));}
    // Opaque C may invoke any registered callback, including on another
    // thread. Pin executable code and userdata, then release the registry
    // lock before entering C so a callback can safely re-enter FFI.
    std::vector<std::shared_ptr<Callback>> callback_pins;
    std::vector<std::shared_ptr<Library>> library_pins;
    for(const auto& entry:callbacks) callback_pins.push_back(entry.second);
    for(const auto& entry:libraries) library_pins.push_back(entry.second);
    guard.unlock();
    lymarrt_value returned{};
    if(!lymarrt_ffi_call(pointer,type(return_type,true),signature.data(),arguments.data(),count,&returned)) {lymar_aot_ffi_result_kind(1);return lymar_aot_nil();}
    Word kind=0;auto value=result(returned,kind);lymar_aot_ffi_result_kind(kind);return value;
}
Word lymar_aot_foreign_call_list(Word function,Word values,Word return_type,Word types,Word function_kind) {
    auto count=lymar_aot_ffi_list_size(values),type_count=lymar_aot_ffi_list_size(types);
    std::vector<Word> words,flags,ids;
    for(Word index=0;index<count;++index) {
        auto value=lymar_aot_ffi_list_item(values,index),kind=lymar_aot_ffi_list_kind(values,index);
        words.push_back(value);flags.push_back(kind);
        if(index<type_count) ids.push_back(lymar_aot_to_integer(lymar_aot_ffi_list_item(types,index),lymar_aot_ffi_list_kind(types,index)));
        else ids.push_back(lymar_aot_ffi_infer_type(value,kind));
    }
    return lymar_aot_foreign_call(function,reinterpret_cast<Word>(words.data()),reinterpret_cast<Word>(flags.data()),reinterpret_cast<Word>(ids.data()),count,return_type,function_kind);
}
Word lymar_aot_callback_create(Word name,Word arguments,Word return_type) {
    std::lock_guard guard(mutex);auto text=std::string(lymar_aot_ffi_string(name));auto found=functions.find(text);
    if(found==functions.end()) {std::fprintf(stderr,"[ffi] callback_create: function '%s' is not registered\n",text.c_str());lymar_aot_ffi_result_kind(1);return lymar_aot_nil();}
    auto count=lymar_aot_ffi_list_size(arguments);
    if(count!=found->second.arguments.size() || count>64) throw std::runtime_error("Callback parameter count mismatch");
    std::vector<lymarrt_type> signature;
    for(Word index=0;index<count;++index) signature.push_back(type(lymar_aot_ffi_list_item(arguments,index)));
    auto context=std::make_shared<Callback>(found->second,type(return_type,true));
    auto handle=lymarrt_callback_create(callback,context.get(),signature.data(),count,context->result);
    if(handle>0) {context->handle=handle;callbacks[handle]=std::move(context);register_shutdown();}lymar_aot_ffi_result_kind(0);return handle;
}
Word lymar_aot_callback_pointer(Word handle) {std::lock_guard guard(mutex);lymar_aot_ffi_result_kind(1);return lymar_aot_ffi_wrap(reinterpret_cast<Word>(lymarrt_callback_get_ptr(handle)));}
void lymar_aot_callback_destroy(Word handle) {
    std::lock_guard guard(mutex);auto found=callbacks.find(handle);if(found==callbacks.end()) return;
    lymar_aot_ffi_invalidate(reinterpret_cast<Word>(lymarrt_callback_get_ptr(handle)));callbacks.erase(found);
}
}
