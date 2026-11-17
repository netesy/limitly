#include <cstdint>
#include <cstddef>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string_view>
#include <cstring>
#include <cmath>
using V=uint64_t;
#ifdef _WIN32
#define LM_EXPORT __declspec(dllexport)
#else
#define LM_EXPORT __attribute__((visibility("default")))
#endif
struct Api { uint32_t version; uint32_t size;
V(*helper)(void*,uint32_t,V,V,V,const char*,const V*,size_t);
V(*integer)(int64_t); V(*floating)(double); int64_t(*read_int)(V); double(*read_float)(V);
int(*equal)(V,V); int(*compare)(V,V); bool(*truthy)(V); const char*(*string_data)(V); };
extern "C" LM_EXPORT uint32_t lymar_module_abi_version() { return 1; }
constexpr uint32_t HBuiltin=38, HAdd=0, HSub=1, HMul=2, HDiv=3, HMod=4, HFloat=9, HPairNew=26, HPairSet=28, HPairGet=27;

struct N {
  V value=2ULL;
  union { double scalar=0; V fields[2]; };
  bool unboxed=false;
  // Only specialized, read-only internal pair returns use this storage.
  // Heap/escaped tuples retain their original tagged representation.
  bool pair=false;
  N()=default;
  N(V v):value(v){}
  bool small() const {return !unboxed && (value&7ULL)==1ULL;}
  int64_t integer() const {return static_cast<int64_t>(value)>>3;}
  bool float_box() const {
    if(unboxed || !value || (value&7ULL)) return false;
    uint32_t type; std::memcpy(&type,reinterpret_cast<const void*>(value),sizeof(type));
    return type==HFloat;
  }
  bool floating() const {return unboxed || float_box();}
  bool numeric() const {return small() || floating();}
  double number(const Api* api) const {
    return unboxed?scalar:small()?static_cast<double>(integer()):api->read_float(value);
  }
  void cache_float(const Api* api) {
    if(!unboxed && float_box()) {scalar=api->read_float(value);unboxed=true;}
  }
  V boxed(const Api* api,void* ctx) const {
    if(unboxed && !value) {
      // A use may occur in a nested lexical region. Do not retain its
      // temporary box in the numeric register after that region exits.
      V box=api->floating(scalar); V args[]={box};
      api->helper(ctx,HBuiltin,2ULL,2ULL,2ULL,"_builtin_track",args,1);
      return box;
    }
    return value;
  }
};
static inline N native_pair() {N n; n.value=0; n.pair=true; n.fields[0]=2ULL; n.fields[1]=2ULL; return n;}
static inline void native_pair_set(const Api* api,void* ctx,N& pair,int64_t index,const N& child) {
  if(pair.pair && index>=0 && index<2 && child.small()) {
    pair.fields[index]=child.value; return;
  }
  if(pair.pair) {
    // An unknown/non-immediate field requires the real ownership graph.
    pair.value=api->helper(ctx,HPairNew,17ULL,2ULL,2ULL,nullptr,nullptr,0);
    for(int64_t i=0;i<2;++i)
      api->helper(ctx,HPairSet,pair.value,(static_cast<V>(i)<<3)|1ULL,pair.fields[i],nullptr,nullptr,0);
    pair.pair=false;
  }
  api->helper(ctx,HPairSet,pair.value,(static_cast<V>(index)<<3)|1ULL,child.boxed(api,ctx),nullptr,nullptr,0);
}
static inline __attribute__((always_inline)) N real(const Api* api,void* ctx,double x) {
  // Materialize NaNs so pointer-equality behavior of existing boxed values
  // remains observable through copies, erasure and equality.
  if(std::isnan(x)) {
    V v=api->floating(x); V args[]={v};
    api->helper(ctx,HBuiltin,2ULL,2ULL,2ULL,"_builtin_track",args,1);
    return N(v);
  }
  N n; n.value=0; n.scalar=x; n.unboxed=true; return n;
}
static inline __attribute__((always_inline)) N arithmetic(const Api* api,void* ctx,uint32_t op,const N& a,const N& b,bool allow_fast) {
  // These guards establish the actual runtime kinds even when canonical
  // LIR has erased/incomplete numeric annotations. Unknown kinds still use
  // the helper; no ownership or lifetime check is elided here. Functions
  // with reference operations disable virtual float results to retain box
  // identity. Immediate integer results have no allocation/reference identity.
  if(a.small() && b.small()) {
    int64_t x=a.integer(), y=b.integer(), z=0; bool overflow=false;
    switch(op) {
    case HAdd: overflow=__builtin_add_overflow(x,y,&z); break;
    case HSub: overflow=__builtin_sub_overflow(x,y,&z); break;
    case HMul: overflow=__builtin_mul_overflow(x,y,&z); break;
    case HDiv: if(!y) return N(2ULL); z=x/y; break;
    case HMod: if(!y) return N(2ULL); z=x%y; break;
    default: overflow=true;
    }
    if(!overflow && z>=-(int64_t(1)<<60) && z<=(int64_t(1)<<60)-1)
      return N((static_cast<V>(z)<<3)|1ULL);
  }
  if(allow_fast && op!=HMod && a.numeric() && b.numeric() && (a.floating() || b.floating())) {
    double x=a.number(api),y=b.number(api);
    switch(op) {
    case HAdd:return real(api,ctx,x+y);
    case HSub:return real(api,ctx,x-y);
    case HMul:return real(api,ctx,x*y);
    case HDiv:return y==0?N(2ULL):real(api,ctx,x/y);
    }
  }
  return N(api->helper(ctx,op,a.boxed(api,ctx),b.boxed(api,ctx),2ULL,nullptr,nullptr,0));
}
static inline __attribute__((always_inline)) bool equal(const Api* api,void* ctx,const N& a,const N& b,bool typed) {
  if(a.value && a.value==b.value) return true;
  if(typed && a.small() && b.small()) return a.integer()==b.integer();
  if(typed && a.numeric() && b.numeric()) return a.number(api)==b.number(api);
  return api->equal(a.boxed(api,ctx),b.boxed(api,ctx));
}
static inline __attribute__((always_inline)) int compare(const Api* api,void* ctx,const N& a,const N& b,bool typed) {
  if(typed && a.small() && b.small()) return a.integer()<b.integer()?-1:a.integer()>b.integer()?1:0;
  if(typed && a.numeric() && b.numeric()) {
    double x=a.number(api),y=b.number(api);return x<y?-1:x>y?1:0;
  }
  return api->compare(a.boxed(api,ctx),b.boxed(api,ctx));
}
constexpr uint32_t HDirectOperations=53;
struct DirectOperations { uint32_t version; uint32_t size;uint64_t(*frame_get)(void*, uint64_t, uint32_t, bool);uint64_t(*frame_set)(void*, uint64_t, uint32_t, uint64_t, bool);uint64_t(*sequence_get)(uint64_t, int64_t);uint64_t(*sequence_set)(void*, uint64_t, uint64_t, uint64_t);uint64_t(*list_append)(void*, uint64_t, uint64_t);uint64_t(*list_length)(uint64_t);uint64_t(*dict_get)(uint64_t, uint64_t);uint64_t(*dict_has)(uint64_t, uint64_t);uint64_t(*dict_length)(uint64_t);uint64_t(*string_index)(uint64_t, int64_t);uint64_t(*string_contains)(uint64_t, uint64_t);uint64_t(*string_starts_with)(uint64_t, uint64_t);uint64_t(*string_ends_with)(uint64_t, uint64_t);uint64_t(*string_index_of)(uint64_t, uint64_t);uint64_t(*string_byte_length)(uint64_t);uint64_t(*string_byte_at)(uint64_t, int64_t);};

static const DirectOperations* direct_operations(const Api* api, void* ctx) {
    struct Cached { const Api* api=nullptr; const DirectOperations* ops=nullptr; };
    static thread_local Cached cached;
    if(cached.api!=api) {
        auto* ops=reinterpret_cast<const DirectOperations*>(
            api->helper(ctx,HDirectOperations,1ULL,0,0,nullptr,nullptr,0));
        if(!ops || ops->version!=1 || ops->size!=sizeof(DirectOperations))
            throw std::runtime_error("Unsupported native direct operations");
        cached={api,ops};
    }
    return cached.ops;
}
static V substring_equal(const Api* api,void* ctx,V source,V begin,V end,V needle) {
if(source && !(source&7ULL) && needle && !(needle&7ULL)) { uint32_t a,b; std::memcpy(&a,reinterpret_cast<const void*>(source),sizeof(a)); std::memcpy(&b,reinterpret_cast<const void*>(needle),sizeof(b));
if(a==11 && b==11) { uint64_t length,expected; const char* data; const char* wanted;
std::memcpy(&length,reinterpret_cast<const unsigned char*>(source)+8,sizeof(length));
std::memcpy(&expected,reinterpret_cast<const unsigned char*>(needle)+8,sizeof(expected));
data=reinterpret_cast<const char*>(source)+24;
wanted=reinterpret_cast<const char*>(needle)+24;
int64_t first=api->read_int(begin),last=api->read_int(end); uint64_t count=0,offset=0;
if(first>=0) { uint64_t finish=last<0?0:std::min(length,static_cast<uint64_t>(last)); offset=static_cast<uint64_t>(first); if(offset<finish) count=finish-offset; }
return expected==count && (!count || std::memcmp(data+offset,wanted,count)==0)?18ULL:10ULL; } }
V args[]={source,begin,end}; V part=api->helper(ctx,HBuiltin,2ULL,2ULL,2ULL,"_builtin_substring",args,3); return api->equal(part,needle)?18ULL:10ULL; }
static V native_length(const Api* api,void* ctx,V value) {
if(value==2ULL) return 1ULL; if(value && !(value&7ULL)) {
const auto* data=reinterpret_cast<const unsigned char*>(value); uint32_t type; std::memcpy(&type,data+0,sizeof(type)); size_t offset;
switch(type) {
case 11: offset=8; break;
case 1: offset=16; break;
case 2: offset=24; break;
default: goto generic; } uint64_t length; std::memcpy(&length,data+offset,sizeof(length));
if(length<=(uint64_t(1)<<60)-1) return (length<<3)|1ULL; }
generic: V args[]={value}; return api->helper(ctx,HBuiltin,2ULL,2ULL,2ULL,"len",args,1); }
struct NativeScope { const Api* api; void* ctx; V depth=0; V result=2ULL; bool managed; NativeScope(const Api* a,void* c,bool m=true):api(a),ctx(c),managed(m){if(managed)depth=api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_call_enter",nullptr,0);} V track(V value){ if(!managed || (value&7ULL)!=0 || !value) return value; V argv[]={value}; return api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_track",argv,1); } N track(N n){if(n.value)track(n.value);return n;} ~NativeScope(){ if(!managed)return; V argv[]={depth,result}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_call_leave",argv,2);} };
static N indirect(const Api*,void*,V,const N*,size_t);
static N f0(const Api*,void*,const N*,size_t);
static N f1(const Api*,void*,const N*,size_t);
static N f2(const Api*,void*,const N*,size_t);
static N f3(const Api*,void*,const N*,size_t);
static N f4(const Api*,void*,const N*,size_t);
static N f5(const Api*,void*,const N*,size_t);
static N f6(const Api*,void*,const N*,size_t);
static N f7(const Api*,void*,const N*,size_t);
static N f8(const Api*,void*,const N*,size_t);
static N f9(const Api*,void*,const N*,size_t);
static N f10(const Api*,void*,const N*,size_t);
static N f11(const Api*,void*,const N*,size_t);
static N f12(const Api*,void*,const N*,size_t);
static N f13(const Api*,void*,const N*,size_t);
static N f14(const Api*,void*,const N*,size_t);
static N f15(const Api*,void*,const N*,size_t);
static N f16(const Api*,void*,const N*,size_t);
static N f17(const Api*,void*,const N*,size_t);
static N f18(const Api*,void*,const N*,size_t);
static N f19(const Api*,void*,const N*,size_t);
static N f20(const Api*,void*,const N*,size_t);
static N f21(const Api*,void*,const N*,size_t);
static N f22(const Api*,void*,const N*,size_t);
static N f23(const Api*,void*,const N*,size_t);
static N f24(const Api*,void*,const N*,size_t);
static N f25(const Api*,void*,const N*,size_t);
static N f26(const Api*,void*,const N*,size_t);
static N f27(const Api*,void*,const N*,size_t);
static N f28(const Api*,void*,const N*,size_t);
static N f29(const Api*,void*,const N*,size_t);
static N f30(const Api*,void*,const N*,size_t);
static N f31(const Api*,void*,const N*,size_t);
static N f32(const Api*,void*,const N*,size_t);
static N f33(const Api*,void*,const N*,size_t);
static N f34(const Api*,void*,const N*,size_t);
static N f35(const Api*,void*,const N*,size_t);
static N f36(const Api*,void*,const N*,size_t);
static N f37(const Api*,void*,const N*,size_t);
static N f38(const Api*,void*,const N*,size_t);
static N f39(const Api*,void*,const N*,size_t);
static N f40(const Api*,void*,const N*,size_t);
static N f41(const Api*,void*,const N*,size_t);
static N f42(const Api*,void*,const N*,size_t);
static N f43(const Api*,void*,const N*,size_t);
static N f44(const Api*,void*,const N*,size_t);
static N f45(const Api*,void*,const N*,size_t);
static N f46(const Api*,void*,const N*,size_t);
static N f47(const Api*,void*,const N*,size_t);
static N f48(const Api*,void*,const N*,size_t);
static N f49(const Api*,void*,const N*,size_t);
static N f50(const Api*,void*,const N*,size_t);
static N f51(const Api*,void*,const N*,size_t);
static N f52(const Api*,void*,const N*,size_t);
static N f53(const Api*,void*,const N*,size_t);
static N f54(const Api*,void*,const N*,size_t);
static N f55(const Api*,void*,const N*,size_t);
static N f56(const Api*,void*,const N*,size_t);
static N f57(const Api*,void*,const N*,size_t);
static N f58(const Api*,void*,const N*,size_t);
static N f59(const Api*,void*,const N*,size_t);
static N f60(const Api*,void*,const N*,size_t);
static N f61(const Api*,void*,const N*,size_t);
static N f62(const Api*,void*,const N*,size_t);
static N f63(const Api*,void*,const N*,size_t);
static N f64(const Api*,void*,const N*,size_t);
static N f65(const Api*,void*,const N*,size_t);
static N f66(const Api*,void*,const N*,size_t);
static N f67(const Api*,void*,const N*,size_t);
static N f68(const Api*,void*,const N*,size_t);
static N f69(const Api*,void*,const N*,size_t);
static N f70(const Api*,void*,const N*,size_t);
static N f71(const Api*,void*,const N*,size_t);
static N f72(const Api*,void*,const N*,size_t);
static N f73(const Api*,void*,const N*,size_t);
static N f74(const Api*,void*,const N*,size_t);
static N f75(const Api*,void*,const N*,size_t);
static N f76(const Api*,void*,const N*,size_t);
static N f77(const Api*,void*,const N*,size_t);
static N f78(const Api*,void*,const N*,size_t);
static N f79(const Api*,void*,const N*,size_t);
// __top_level_wrapper__
static N f0(const Api* api,void* ctx,const N* args,size_t count) {
N r[4]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<4;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { N argv[] = {N(2ULL)}; r[0]=scope.track(f78(api,ctx,argv,0)); }
L2: { N argv[] = {N(2ULL)}; r[1]=scope.track(f51(api,ctx,argv,0)); }
L3: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L4: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L5: return 2ULL; }
// std.native.d3d11.gfx_device
static N f1(const Api* api,void* ctx,const N* args,size_t count) {
N r[2]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<2;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L3: { V argv[]={r[0].value?r[0].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L4: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L5: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L6: { scope.result=r[0].value?r[0].value:2ULL;return r[0]; }
L7: return 2ULL; }
// std.native.d3d11.gfx_context
static N f2(const Api* api,void* ctx,const N* args,size_t count) {
N r[2]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<2;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L3: { V argv[]={r[0].value?r[0].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L4: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L5: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L6: { scope.result=r[0].value?r[0].value:2ULL;return r[0]; }
L7: return 2ULL; }
// std.native.d3d11.gfx_update_texture_rgba
static N f3(const Api* api,void* ctx,const N* args,size_t count) {
N r[25]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<25;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[4]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[5]=scope.track(1ULL); }
L5: { r[6]=scope.track((equal(api,ctx,r[4],r[5],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[6].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[7]=scope.track(1ULL); }
L9: { V argv[]={r[7].value?r[7].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[7].value?r[7].value:2ULL;return r[7]; }
L15: { r[8]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L16: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_UPDATE_SUB",nullptr,0)); }
L17: { r[10]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L18: { ops->list_append(ctx,r[10].boxed(api,ctx),r[0].boxed(api,ctx)); }
L19: { r[12]=scope.track(1ULL); }
L20: { ops->list_append(ctx,r[10].boxed(api,ctx),r[12].boxed(api,ctx)); }
L21: { r[14]=scope.track(1ULL); }
L22: { ops->list_append(ctx,r[10].boxed(api,ctx),r[14].boxed(api,ctx)); }
L23: { ops->list_append(ctx,r[10].boxed(api,ctx),r[3].boxed(api,ctx)); }
L24: { r[17]=scope.track(33ULL); }
L25: { r[18]=scope.track(arithmetic(api,ctx,2,r[1],r[17],true)); }
L26: { ops->list_append(ctx,r[10].boxed(api,ctx),r[18].boxed(api,ctx)); }
L27: { r[20]=scope.track(1ULL); }
L28: { ops->list_append(ctx,r[10].boxed(api,ctx),r[20].boxed(api,ctx)); }
L29: { r[10]=N(r[10].boxed(api,ctx));N argv[] = {r[8],r[9],r[10],N(2ULL)}; r[22]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L30: { r[23]=scope.track(9ULL); }
L31: { V argv[]={r[23].value?r[23].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L32: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L33: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L34: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L35: { scope.result=r[23].value?r[23].value:2ULL;return r[23]; }
L36: return 2ULL; }
// std.native.d3d11.gfx_texture_create_rgba
static N f4(const Api* api,void* ctx,const N* args,size_t count) {
N r[83]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<83;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[3]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track((equal(api,ctx,r[3],r[4],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[5].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[6]=scope.track(1ULL); }
L9: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L15: { r[8]=scope.track(1ULL); }
L16: { r[9]=scope.track((compare(api,ctx,r[0],r[8],true)<=0?18ULL:10ULL)); }
L17: { r[7]=scope.track(r[9]); }
L18: { if(api->truthy(r[9].boxed(api,ctx))) goto L23; }
L19: { r[10]=scope.track(1ULL); }
L20: { r[11]=scope.track((compare(api,ctx,r[1],r[10],true)<=0?18ULL:10ULL)); }
L21: { r[7]=scope.track(r[11]); }
L22: { goto L23; }
L23: { if(!api->truthy(r[7].boxed(api,ctx))) goto L32; }
L24: {  }
L25: { r[12]=scope.track(1ULL); }
L26: { V argv[]={r[12].value?r[12].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L27: {  }
L28: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L29: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L30: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L31: { scope.result=r[12].value?r[12].value:2ULL;return r[12]; }
L32: { r[13]=scope.track(385ULL); }
L33: { V argv[] = {r[13].boxed(api,ctx),2ULL}; r[14]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L34: { r[15]=scope.track(r[14]); }
L35: {  }
L36: { r[16]=scope.track(1ULL); }
L37: { r[17]=scope.track(385ULL); }
L38: { V argv[] = {r[15].boxed(api,ctx),r[16].boxed(api,ctx),r[17].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L39: { V argv[] = {r[15].boxed(api,ctx),r[0].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L40: { r[20]=scope.track(33ULL); }
L41: { V argv[] = {r[15].boxed(api,ctx),r[20].boxed(api,ctx),2ULL}; r[21]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L42: { V argv[] = {r[21].boxed(api,ctx),r[1].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L43: { r[23]=scope.track(65ULL); }
L44: { V argv[] = {r[15].boxed(api,ctx),r[23].boxed(api,ctx),2ULL}; r[24]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L45: { r[25]=scope.track(9ULL); }
L46: { V argv[] = {r[24].boxed(api,ctx),r[25].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L47: { r[27]=scope.track(97ULL); }
L48: { V argv[] = {r[15].boxed(api,ctx),r[27].boxed(api,ctx),2ULL}; r[28]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L49: { r[29]=scope.track(9ULL); }
L50: { V argv[] = {r[28].boxed(api,ctx),r[29].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L51: { r[31]=scope.track(129ULL); }
L52: { V argv[] = {r[15].boxed(api,ctx),r[31].boxed(api,ctx),2ULL}; r[32]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L53: { r[33]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R8G8B8A8_UNORM",nullptr,0)); }
L54: { V argv[] = {r[32].boxed(api,ctx),r[33].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L55: { r[35]=scope.track(161ULL); }
L56: { V argv[] = {r[15].boxed(api,ctx),r[35].boxed(api,ctx),2ULL}; r[36]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L57: { r[37]=scope.track(9ULL); }
L58: { V argv[] = {r[36].boxed(api,ctx),r[37].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L59: { r[39]=scope.track(225ULL); }
L60: { V argv[] = {r[15].boxed(api,ctx),r[39].boxed(api,ctx),2ULL}; r[40]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L61: { r[41]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.USAGE_DEFAULT",nullptr,0)); }
L62: { V argv[] = {r[40].boxed(api,ctx),r[41].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L63: { r[43]=scope.track(257ULL); }
L64: { V argv[] = {r[15].boxed(api,ctx),r[43].boxed(api,ctx),2ULL}; r[44]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L65: { r[45]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.BIND_SHADER_RESOURCE",nullptr,0)); }
L66: { V argv[] = {r[44].boxed(api,ctx),r[45].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L67: { r[47]=scope.track(129ULL); }
L68: { V argv[] = {r[47].boxed(api,ctx),2ULL}; r[48]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L69: { r[49]=scope.track(r[48]); }
L70: {  }
L71: { V argv[] = {r[49].boxed(api,ctx),r[2].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L72: { r[51]=scope.track(65ULL); }
L73: { V argv[] = {r[49].boxed(api,ctx),r[51].boxed(api,ctx),2ULL}; r[52]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L74: { r[53]=scope.track(33ULL); }
L75: { r[54]=scope.track(arithmetic(api,ctx,2,r[0],r[53],true)); }
L76: { V argv[] = {r[52].boxed(api,ctx),r[54].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L77: { r[56]=scope.track(97ULL); }
L78: { V argv[] = {r[49].boxed(api,ctx),r[56].boxed(api,ctx),2ULL}; r[57]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L79: { r[58]=scope.track(1ULL); }
L80: { V argv[] = {r[57].boxed(api,ctx),r[58].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L81: { r[60]=scope.track(65ULL); }
L82: { V argv[] = {r[60].boxed(api,ctx),2ULL}; r[61]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L83: { r[62]=scope.track(r[61]); }
L84: {  }
L85: { r[63]=scope.track(1ULL); }
L86: { V argv[] = {r[62].boxed(api,ctx),r[63].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L87: { r[65]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L88: { r[66]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_TEX2D",nullptr,0)); }
L89: { r[67]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L90: { ops->list_append(ctx,r[67].boxed(api,ctx),r[15].boxed(api,ctx)); }
L91: { ops->list_append(ctx,r[67].boxed(api,ctx),r[49].boxed(api,ctx)); }
L92: { ops->list_append(ctx,r[67].boxed(api,ctx),r[62].boxed(api,ctx)); }
L93: { r[67]=N(r[67].boxed(api,ctx));N argv[] = {r[65],r[66],r[67],N(2ULL)}; r[71]=scope.track(f48(api,ctx,argv,3)); }
L94: { r[72]=scope.track(r[71]); }
L95: {  }
L96: { V argv[] = {r[15].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L97: { V argv[] = {r[49].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L98: { r[75]=scope.track(1ULL); }
L99: { r[76]=scope.track((!equal(api,ctx,r[72],r[75],true)?18ULL:10ULL)); }
L100: { if(!api->truthy(r[76].boxed(api,ctx))) goto L110; }
L101: {  }
L102: { V argv[] = {r[62].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L103: { r[78]=scope.track(1ULL); }
L104: { V argv[]={r[78].value?r[78].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L105: {  }
L106: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L107: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L108: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L109: { scope.result=r[78].value?r[78].value:2ULL;return r[78]; }
L110: { V argv[] = {r[62].boxed(api,ctx),49ULL,2ULL}; r[79]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L111: { r[80]=scope.track(r[79]); }
L112: {  }
L113: { V argv[] = {r[62].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L114: { V argv[]={r[80].value?r[80].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L115: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L116: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L117: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L118: { scope.result=r[80].value?r[80].value:2ULL;return r[80]; }
L119: return 2ULL; }
// std.native.d3d11.gfx_set_raster_state
static N f5(const Api* api,void* ctx,const N* args,size_t count) {
N r[7]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<7;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_RS_STATE",nullptr,0)); }
L5: { r[3]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[3].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { r[3]=N(r[3].boxed(api,ctx));N argv[] = {r[1],r[2],r[3],N(2ULL)}; r[5]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L8: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L9: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L12: return 2ULL; }
// std.native.d3d11.gfx_set_depth_state
static N f6(const Api* api,void* ctx,const N* args,size_t count) {
N r[9]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<9;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_OM_DEPTH",nullptr,0)); }
L5: { r[4]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[4].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { ops->list_append(ctx,r[4].boxed(api,ctx),r[1].boxed(api,ctx)); }
L8: { r[4]=N(r[4].boxed(api,ctx));N argv[] = {r[2],r[3],r[4],N(2ULL)}; r[7]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L9: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L13: return 2ULL; }
// std.native.d3d11.gfx_sampler_create
static N f7(const Api* api,void* ctx,const N* args,size_t count) {
N r[60]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<60;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[3]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track((equal(api,ctx,r[3],r[4],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[5].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[6]=scope.track(1ULL); }
L9: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L15: { r[7]=scope.track(417ULL); }
L16: { V argv[] = {r[7].boxed(api,ctx),2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[9]=scope.track(r[8]); }
L18: {  }
L19: { r[10]=scope.track(1ULL); }
L20: { r[11]=scope.track(417ULL); }
L21: { V argv[] = {r[9].boxed(api,ctx),r[10].boxed(api,ctx),r[11].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L22: { V argv[] = {r[9].boxed(api,ctx),r[0].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L23: { r[14]=scope.track(33ULL); }
L24: { V argv[] = {r[9].boxed(api,ctx),r[14].boxed(api,ctx),2ULL}; r[15]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L25: { V argv[] = {r[15].boxed(api,ctx),r[1].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L26: { r[17]=scope.track(65ULL); }
L27: { V argv[] = {r[9].boxed(api,ctx),r[17].boxed(api,ctx),2ULL}; r[18]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L28: { V argv[] = {r[18].boxed(api,ctx),r[2].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L29: { r[20]=scope.track(97ULL); }
L30: { V argv[] = {r[9].boxed(api,ctx),r[20].boxed(api,ctx),2ULL}; r[21]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L31: { V argv[] = {r[21].boxed(api,ctx),r[2].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L32: { r[23]=scope.track(161ULL); }
L33: { V argv[] = {r[9].boxed(api,ctx),r[23].boxed(api,ctx),2ULL}; r[24]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L34: { r[25]=scope.track(9ULL); }
L35: { V argv[] = {r[24].boxed(api,ctx),r[25].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L36: { r[27]=scope.track(193ULL); }
L37: { V argv[] = {r[9].boxed(api,ctx),r[27].boxed(api,ctx),2ULL}; r[28]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L38: { r[29]=scope.track(9ULL); }
L39: { V argv[] = {r[28].boxed(api,ctx),r[29].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L40: { r[31]=scope.track(353ULL); }
L41: { V argv[] = {r[9].boxed(api,ctx),r[31].boxed(api,ctx),2ULL}; r[32]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L42: { r[33]=scope.track(real(api,ctx,0x0p+0));r[33].cache_float(api); }
L43: { V argv[] = {r[32].boxed(api,ctx),r[33].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L44: { r[35]=scope.track(385ULL); }
L45: { V argv[] = {r[9].boxed(api,ctx),r[35].boxed(api,ctx),2ULL}; r[36]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L46: { r[37]=scope.track(real(api,ctx,0x1.fffffe54daff8p+127));r[37].cache_float(api); }
L47: { V argv[] = {r[36].boxed(api,ctx),r[37].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L48: { r[39]=scope.track(65ULL); }
L49: { V argv[] = {r[39].boxed(api,ctx),2ULL}; r[40]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L50: { r[41]=scope.track(r[40]); }
L51: {  }
L52: { r[42]=scope.track(1ULL); }
L53: { V argv[] = {r[41].boxed(api,ctx),r[42].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L54: { r[44]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L55: { r[45]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_SS",nullptr,0)); }
L56: { r[46]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L57: { ops->list_append(ctx,r[46].boxed(api,ctx),r[9].boxed(api,ctx)); }
L58: { ops->list_append(ctx,r[46].boxed(api,ctx),r[41].boxed(api,ctx)); }
L59: { r[46]=N(r[46].boxed(api,ctx));N argv[] = {r[44],r[45],r[46],N(2ULL)}; r[49]=scope.track(f48(api,ctx,argv,3)); }
L60: { r[50]=scope.track(r[49]); }
L61: {  }
L62: { V argv[] = {r[9].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L63: { r[52]=scope.track(1ULL); }
L64: { r[53]=scope.track((!equal(api,ctx,r[50],r[52],true)?18ULL:10ULL)); }
L65: { if(!api->truthy(r[53].boxed(api,ctx))) goto L75; }
L66: {  }
L67: { V argv[] = {r[41].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L68: { r[55]=scope.track(1ULL); }
L69: { V argv[]={r[55].value?r[55].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L70: {  }
L71: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L72: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L73: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L74: { scope.result=r[55].value?r[55].value:2ULL;return r[55]; }
L75: { V argv[] = {r[41].boxed(api,ctx),49ULL,2ULL}; r[56]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L76: { r[57]=scope.track(r[56]); }
L77: {  }
L78: { V argv[] = {r[41].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L79: { V argv[]={r[57].value?r[57].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L80: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L81: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L82: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L83: { scope.result=r[57].value?r[57].value:2ULL;return r[57]; }
L84: return 2ULL; }
// std.native.d3d11.gfx_depth_state_create
static N f8(const Api* api,void* ctx,const N* args,size_t count) {
N r[66]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<66;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[3]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track((equal(api,ctx,r[3],r[4],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[5].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[6]=scope.track(1ULL); }
L9: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L15: { r[7]=scope.track(417ULL); }
L16: { V argv[] = {r[7].boxed(api,ctx),2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[9]=scope.track(r[8]); }
L18: {  }
L19: { r[10]=scope.track(1ULL); }
L20: { r[11]=scope.track(417ULL); }
L21: { V argv[] = {r[9].boxed(api,ctx),r[10].boxed(api,ctx),r[11].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L22: { V argv[] = {r[9].boxed(api,ctx),r[0].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L23: { r[14]=scope.track(33ULL); }
L24: { V argv[] = {r[9].boxed(api,ctx),r[14].boxed(api,ctx),2ULL}; r[15]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L25: { V argv[] = {r[15].boxed(api,ctx),r[1].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L26: { r[17]=scope.track(65ULL); }
L27: { V argv[] = {r[9].boxed(api,ctx),r[17].boxed(api,ctx),2ULL}; r[18]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L28: { V argv[] = {r[18].boxed(api,ctx),r[2].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L29: { r[20]=scope.track(1ULL); }
L30: {  }
L31: {  }
L32: { goto L33; }
L33: { r[21]=scope.track(17ULL); }
L34: { r[22]=scope.track((compare(api,ctx,r[20],r[21],true)<0?18ULL:10ULL)); }
L35: { if(!api->truthy(r[22].boxed(api,ctx))) goto L65; }
L36: {  }
L37: { r[23]=scope.track(161ULL); }
L38: { r[24]=scope.track(129ULL); }
L39: { r[25]=scope.track(arithmetic(api,ctx,2,r[20],r[24],true)); }
L40: { r[26]=scope.track(api->integer(api->read_int(r[23].boxed(api,ctx)) + api->read_int(r[25].boxed(api,ctx)))); }
L41: { V argv[] = {r[9].boxed(api,ctx),r[26].boxed(api,ctx),2ULL}; r[27]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L42: { r[28]=scope.track(r[27]); }
L43: {  }
L44: { r[29]=scope.track(9ULL); }
L45: { V argv[] = {r[28].boxed(api,ctx),r[29].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L46: { r[31]=scope.track(33ULL); }
L47: { V argv[] = {r[28].boxed(api,ctx),r[31].boxed(api,ctx),2ULL}; r[32]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L48: { r[33]=scope.track(9ULL); }
L49: { V argv[] = {r[32].boxed(api,ctx),r[33].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L50: { r[35]=scope.track(65ULL); }
L51: { V argv[] = {r[28].boxed(api,ctx),r[35].boxed(api,ctx),2ULL}; r[36]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L52: { r[37]=scope.track(9ULL); }
L53: { V argv[] = {r[36].boxed(api,ctx),r[37].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L54: { r[39]=scope.track(97ULL); }
L55: { V argv[] = {r[28].boxed(api,ctx),r[39].boxed(api,ctx),2ULL}; r[40]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L56: { r[41]=scope.track(65ULL); }
L57: { V argv[] = {r[40].boxed(api,ctx),r[41].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L58: { r[43]=scope.track(9ULL); }
L59: { r[44]=scope.track(api->integer(api->read_int(r[20].boxed(api,ctx)) + api->read_int(r[43].boxed(api,ctx)))); }
L60: { r[20]=scope.track(r[44]); }
L61: {  }
L62: {  }
L63: {  }
L64: { goto L33; }
L65: { V argv[]={r[20].value?r[20].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L66: {  }
L67: { r[45]=scope.track(65ULL); }
L68: { V argv[] = {r[45].boxed(api,ctx),2ULL}; r[46]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L69: { r[47]=scope.track(r[46]); }
L70: {  }
L71: { r[48]=scope.track(1ULL); }
L72: { V argv[] = {r[47].boxed(api,ctx),r[48].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L73: { r[50]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L74: { r[51]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_DSS",nullptr,0)); }
L75: { r[52]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L76: { ops->list_append(ctx,r[52].boxed(api,ctx),r[9].boxed(api,ctx)); }
L77: { ops->list_append(ctx,r[52].boxed(api,ctx),r[47].boxed(api,ctx)); }
L78: { r[52]=N(r[52].boxed(api,ctx));N argv[] = {r[50],r[51],r[52],N(2ULL)}; r[55]=scope.track(f48(api,ctx,argv,3)); }
L79: { r[56]=scope.track(r[55]); }
L80: {  }
L81: { V argv[] = {r[9].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L82: { r[58]=scope.track(1ULL); }
L83: { r[59]=scope.track((!equal(api,ctx,r[56],r[58],true)?18ULL:10ULL)); }
L84: { if(!api->truthy(r[59].boxed(api,ctx))) goto L94; }
L85: {  }
L86: { V argv[] = {r[47].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L87: { r[61]=scope.track(1ULL); }
L88: { V argv[]={r[61].value?r[61].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L89: {  }
L90: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L91: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L92: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L93: { scope.result=r[61].value?r[61].value:2ULL;return r[61]; }
L94: { V argv[] = {r[47].boxed(api,ctx),49ULL,2ULL}; r[62]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L95: { r[63]=scope.track(r[62]); }
L96: {  }
L97: { V argv[] = {r[47].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L98: { V argv[]={r[63].value?r[63].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L99: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L100: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L101: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L102: { scope.result=r[63].value?r[63].value:2ULL;return r[63]; }
L103: return 2ULL; }
// std.native.d3d11.gfx_discard_all
static N f9(const Api* api,void* ctx,const N* args,size_t count) {
N r[34]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<34;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L4: { r[1]=scope.track(1ULL); }
L5: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[2].boxed(api,ctx))) goto L15; }
L7: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L8: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L9: { N argv[] = {r[3],N(2ULL)}; r[4]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L10: { r[5]=scope.track(1ULL); }
L11: { api->helper(ctx,43,r[5].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0); }
L12: {  }
L13: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { goto L15; }
L15: { r[6]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L16: { r[7]=scope.track(1ULL); }
L17: { r[8]=scope.track((!equal(api,ctx,r[6],r[7],true)?18ULL:10ULL)); }
L18: { if(!api->truthy(r[8].boxed(api,ctx))) goto L27; }
L19: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L20: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L21: { N argv[] = {r[9],N(2ULL)}; r[10]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L22: { r[11]=scope.track(1ULL); }
L23: { api->helper(ctx,43,r[11].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0); }
L24: {  }
L25: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L26: { goto L27; }
L27: { r[12]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0)); }
L28: { r[13]=scope.track(1ULL); }
L29: { r[14]=scope.track((!equal(api,ctx,r[12],r[13],true)?18ULL:10ULL)); }
L30: { if(!api->truthy(r[14].boxed(api,ctx))) goto L39; }
L31: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L32: { r[15]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0)); }
L33: { N argv[] = {r[15],N(2ULL)}; r[16]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L34: { r[17]=scope.track(1ULL); }
L35: { api->helper(ctx,43,r[17].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0); }
L36: {  }
L37: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L38: { goto L39; }
L39: { r[18]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L40: { r[19]=scope.track(1ULL); }
L41: { r[20]=scope.track((!equal(api,ctx,r[18],r[19],true)?18ULL:10ULL)); }
L42: { if(!api->truthy(r[20].boxed(api,ctx))) goto L51; }
L43: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L44: { r[21]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L45: { N argv[] = {r[21],N(2ULL)}; r[22]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L46: { r[23]=scope.track(1ULL); }
L47: { api->helper(ctx,43,r[23].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0); }
L48: {  }
L49: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L50: { goto L51; }
L51: { r[24]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._factory",nullptr,0)); }
L52: { r[25]=scope.track(1ULL); }
L53: { r[26]=scope.track((!equal(api,ctx,r[24],r[25],true)?18ULL:10ULL)); }
L54: { if(!api->truthy(r[26].boxed(api,ctx))) goto L63; }
L55: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L56: { r[27]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._factory",nullptr,0)); }
L57: { N argv[] = {r[27],N(2ULL)}; r[28]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L58: { r[29]=scope.track(1ULL); }
L59: { api->helper(ctx,43,r[29].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._factory",nullptr,0); }
L60: {  }
L61: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L62: { goto L63; }
L63: { r[30]=scope.track(1ULL); }
L64: { api->helper(ctx,43,r[30].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._hwnd",nullptr,0); }
L65: {  }
L66: { r[31]=scope.track(1ULL); }
L67: { api->helper(ctx,43,r[31].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._width",nullptr,0); }
L68: {  }
L69: { r[32]=scope.track(1ULL); }
L70: { api->helper(ctx,43,r[32].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._height",nullptr,0); }
L71: {  }
L72: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L73: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L74: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L75: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L76: return 2ULL; }
// std.native.d3d11.gfx_ps_set_cb
static N f10(const Api* api,void* ctx,const N* args,size_t count) {
N r[16]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<16;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(65ULL); }
L4: { V argv[] = {r[2].boxed(api,ctx),2ULL}; r[3]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L5: { r[4]=scope.track(r[3]); }
L6: {  }
L7: { V argv[] = {r[4].boxed(api,ctx),r[1].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L8: { r[6]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L9: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_PS_CB",nullptr,0)); }
L10: { r[8]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L11: { ops->list_append(ctx,r[8].boxed(api,ctx),r[0].boxed(api,ctx)); }
L12: { r[10]=scope.track(9ULL); }
L13: { ops->list_append(ctx,r[8].boxed(api,ctx),r[10].boxed(api,ctx)); }
L14: { ops->list_append(ctx,r[8].boxed(api,ctx),r[4].boxed(api,ctx)); }
L15: { r[8]=N(r[8].boxed(api,ctx));N argv[] = {r[6],r[7],r[8],N(2ULL)}; r[13]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L16: { V argv[] = {r[4].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L17: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L18: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L19: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L20: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L21: return 2ULL; }
// std.native.d3d11.gfx_vs_set_cb
static N f11(const Api* api,void* ctx,const N* args,size_t count) {
N r[16]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<16;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(65ULL); }
L4: { V argv[] = {r[2].boxed(api,ctx),2ULL}; r[3]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L5: { r[4]=scope.track(r[3]); }
L6: {  }
L7: { V argv[] = {r[4].boxed(api,ctx),r[1].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L8: { r[6]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L9: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_VS_CB",nullptr,0)); }
L10: { r[8]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L11: { ops->list_append(ctx,r[8].boxed(api,ctx),r[0].boxed(api,ctx)); }
L12: { r[10]=scope.track(9ULL); }
L13: { ops->list_append(ctx,r[8].boxed(api,ctx),r[10].boxed(api,ctx)); }
L14: { ops->list_append(ctx,r[8].boxed(api,ctx),r[4].boxed(api,ctx)); }
L15: { r[8]=N(r[8].boxed(api,ctx));N argv[] = {r[6],r[7],r[8],N(2ULL)}; r[13]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L16: { V argv[] = {r[4].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L17: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L18: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L19: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L20: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L21: return 2ULL; }
// std.native.d3d11.gfx_cb_create
static N f12(const Api* api,void* ctx,const N* args,size_t count) {
N r[9]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<9;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.USAGE_DEFAULT",nullptr,0)); }
L3: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.BIND_CONSTANT_BUFFER",nullptr,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track(1ULL); }
L6: { r[6]=scope.track(1ULL); }
L7: { N argv[] = {r[0],r[2],r[3],r[4],r[5],r[6],r[1],N(2ULL)}; r[7]=scope.track(f44(api,ctx,argv,7)); }
L8: { V argv[]={r[7].value?r[7].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L9: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { scope.result=r[7].value?r[7].value:2ULL;return r[7]; }
L12: return 2ULL; }
// std.native.d3d11.gfx_set_input_layout
static N f13(const Api* api,void* ctx,const N* args,size_t count) {
N r[7]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<7;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_IA_LAYOUT",nullptr,0)); }
L5: { r[3]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[3].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { r[3]=N(r[3].boxed(api,ctx));N argv[] = {r[1],r[2],r[3],N(2ULL)}; r[5]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L8: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L9: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L12: return 2ULL; }
// std.native.d3d11.gfx_set_shaders
static N f14(const Api* api,void* ctx,const N* args,size_t count) {
N r[21]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<21;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_VS_SHADER",nullptr,0)); }
L5: { r[4]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[4].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { r[6]=scope.track(1ULL); }
L8: { ops->list_append(ctx,r[4].boxed(api,ctx),r[6].boxed(api,ctx)); }
L9: { r[8]=scope.track(1ULL); }
L10: { ops->list_append(ctx,r[4].boxed(api,ctx),r[8].boxed(api,ctx)); }
L11: { r[4]=N(r[4].boxed(api,ctx));N argv[] = {r[2],r[3],r[4],N(2ULL)}; r[10]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L12: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L13: { r[12]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_PS_SHADER",nullptr,0)); }
L14: { r[13]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L15: { ops->list_append(ctx,r[13].boxed(api,ctx),r[1].boxed(api,ctx)); }
L16: { r[15]=scope.track(1ULL); }
L17: { ops->list_append(ctx,r[13].boxed(api,ctx),r[15].boxed(api,ctx)); }
L18: { r[17]=scope.track(1ULL); }
L19: { ops->list_append(ctx,r[13].boxed(api,ctx),r[17].boxed(api,ctx)); }
L20: { r[13]=N(r[13].boxed(api,ctx));N argv[] = {r[11],r[12],r[13],N(2ULL)}; r[19]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L21: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L22: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L23: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L24: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L25: return 2ULL; }
// std.native.d3d11.gfx_map_dynamic
static N f15(const Api* api,void* ctx,const N* args,size_t count) {
N r[29]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<29;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[1]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[2]=scope.track(1ULL); }
L5: { r[3]=scope.track((equal(api,ctx,r[1],r[2],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[3].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[4]=scope.track(1ULL); }
L9: { V argv[]={r[4].value?r[4].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[4].value?r[4].value:2ULL;return r[4]; }
L15: { r[5]=scope.track(129ULL); }
L16: { V argv[] = {r[5].boxed(api,ctx),2ULL}; r[6]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[7]=scope.track(r[6]); }
L18: {  }
L19: { r[8]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L20: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_MAP",nullptr,0)); }
L21: { r[10]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L22: { ops->list_append(ctx,r[10].boxed(api,ctx),r[0].boxed(api,ctx)); }
L23: { r[12]=scope.track(1ULL); }
L24: { ops->list_append(ctx,r[10].boxed(api,ctx),r[12].boxed(api,ctx)); }
L25: { r[14]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.MAP_WRITE_DISCARD",nullptr,0)); }
L26: { ops->list_append(ctx,r[10].boxed(api,ctx),r[14].boxed(api,ctx)); }
L27: { r[16]=scope.track(1ULL); }
L28: { ops->list_append(ctx,r[10].boxed(api,ctx),r[16].boxed(api,ctx)); }
L29: { ops->list_append(ctx,r[10].boxed(api,ctx),r[7].boxed(api,ctx)); }
L30: { r[10]=N(r[10].boxed(api,ctx));N argv[] = {r[8],r[9],r[10],N(2ULL)}; r[19]=scope.track(f48(api,ctx,argv,3)); }
L31: { r[20]=scope.track(r[19]); }
L32: {  }
L33: { r[21]=scope.track(1ULL); }
L34: { r[22]=scope.track((!equal(api,ctx,r[20],r[21],true)?18ULL:10ULL)); }
L35: { if(!api->truthy(r[22].boxed(api,ctx))) goto L45; }
L36: {  }
L37: { V argv[] = {r[7].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L38: { r[24]=scope.track(1ULL); }
L39: { V argv[]={r[24].value?r[24].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L40: {  }
L41: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L42: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L44: { scope.result=r[24].value?r[24].value:2ULL;return r[24]; }
L45: { V argv[] = {r[7].boxed(api,ctx),49ULL,2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L46: { r[26]=scope.track(r[25]); }
L47: {  }
L48: { V argv[] = {r[7].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L49: { V argv[]={r[26].value?r[26].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L50: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L51: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L52: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L53: { scope.result=r[26].value?r[26].value:2ULL;return r[26]; }
L54: return 2ULL; }
// std.native.d3d11.gfx_input_layout_create
static N f16(const Api* api,void* ctx,const N* args,size_t count) {
N r[134]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<134;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[4]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[5]=scope.track(1ULL); }
L5: { r[6]=scope.track((equal(api,ctx,r[4],r[5],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[6].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[7]=scope.track(1ULL); }
L9: { V argv[]={r[7].value?r[7].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[7].value?r[7].value:2ULL;return r[7]; }
L15: {  }
L16: { r[8]=scope.track(native_length(api,ctx,r[0].boxed(api,ctx))); }
L17: { r[9]=scope.track(r[8]); }
L18: {  }
L19: { r[11]=scope.track(1ULL); }
L20: { r[12]=scope.track((equal(api,ctx,r[9],r[11],true)?18ULL:10ULL)); }
L21: { r[10]=scope.track(r[12]); }
L22: { if(api->truthy(r[12].boxed(api,ctx))) goto L28; }
L23: {  }
L24: { r[13]=scope.track(native_length(api,ctx,r[1].boxed(api,ctx))); }
L25: { r[14]=scope.track((!equal(api,ctx,r[9],r[13],true)?18ULL:10ULL)); }
L26: { r[10]=scope.track(r[14]); }
L27: { goto L28; }
L28: { if(!api->truthy(r[10].boxed(api,ctx))) goto L37; }
L29: {  }
L30: { r[15]=scope.track(1ULL); }
L31: { V argv[]={r[15].value?r[15].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L32: {  }
L33: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L34: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L35: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L36: { scope.result=r[15].value?r[15].value:2ULL;return r[15]; }
L37: { r[16]=scope.track(257ULL); }
L38: { r[17]=scope.track(arithmetic(api,ctx,2,r[9],r[16],true)); }
L39: { V argv[] = {r[17].boxed(api,ctx),2ULL}; r[18]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L40: { r[19]=scope.track(r[18]); }
L41: {  }
L42: { r[20]=scope.track(1ULL); }
L43: { r[21]=scope.track(257ULL); }
L44: { r[22]=scope.track(arithmetic(api,ctx,2,r[9],r[21],true)); }
L45: { V argv[] = {r[19].boxed(api,ctx),r[20].boxed(api,ctx),r[22].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L46: { r[24]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L47: { r[25]=scope.track(r[24]); }
L48: { r[26]=scope.track(r[25]); }
L49: {  }
L50: { r[27]=scope.track(1ULL); }
L51: {  }
L52: { r[28]=scope.track(1ULL); }
L53: {  }
L54: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L55: { goto L56; }
L56: { r[29]=scope.track((compare(api,ctx,r[28],r[9],true)<0?18ULL:10ULL)); }
L57: { if(!api->truthy(r[29].boxed(api,ctx))) goto L152; }
L58: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L59: { r[30]=scope.track(257ULL); }
L60: { r[31]=scope.track(arithmetic(api,ctx,2,r[28],r[30],true)); }
L61: { V argv[] = {r[19].boxed(api,ctx),r[31].boxed(api,ctx),2ULL}; r[32]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L62: { r[33]=scope.track(r[32]); }
L63: {  }
L64: {  }
L65: { r[34]=scope.track(ops->sequence_get(r[0].boxed(api,ctx),(r[28].small()?r[28].integer():api->read_int(r[28].boxed(api,ctx))))); }
L66: { r[34]=N(r[34].boxed(api,ctx));N argv[] = {r[34],N(2ULL)}; r[35]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L67: { r[36]=scope.track(r[35]); }
L68: {  }
L69: {  }
L70: {  }
L71: { ops->list_append(ctx,r[26].boxed(api,ctx),r[36].boxed(api,ctx)); }
L72: {  }
L73: { r[38]=scope.track(ops->frame_get(ctx,r[36].boxed(api,ctx),0,false)); }
L74: { V argv[] = {r[33].boxed(api,ctx),r[38].boxed(api,ctx),81ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L75: { r[40]=scope.track(65ULL); }
L76: { V argv[] = {r[33].boxed(api,ctx),r[40].boxed(api,ctx),2ULL}; r[41]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L77: { r[42]=scope.track(1ULL); }
L78: { V argv[] = {r[41].boxed(api,ctx),r[42].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L79: { r[44]=scope.track(97ULL); }
L80: { V argv[] = {r[33].boxed(api,ctx),r[44].boxed(api,ctx),2ULL}; r[45]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L81: {  }
L82: { r[46]=scope.track(ops->sequence_get(r[1].boxed(api,ctx),(r[28].small()?r[28].integer():api->read_int(r[28].boxed(api,ctx))))); }
L83: { V argv[] = {r[45].boxed(api,ctx),r[46].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L84: { r[48]=scope.track(129ULL); }
L85: { V argv[] = {r[33].boxed(api,ctx),r[48].boxed(api,ctx),2ULL}; r[49]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L86: { r[50]=scope.track(1ULL); }
L87: { V argv[] = {r[49].boxed(api,ctx),r[50].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L88: {  }
L89: { r[52]=scope.track(ops->sequence_get(r[1].boxed(api,ctx),(r[28].small()?r[28].integer():api->read_int(r[28].boxed(api,ctx))))); }
L90: { N argv[] = {r[52],N(2ULL)}; r[53]=scope.track(f17(api,ctx,argv,1)); }
L91: { r[54]=scope.track(r[53]); }
L92: {  }
L93: { r[55]=scope.track(r[27]); }
L94: {  }
L95: {  }
L96: { goto L97; }
L97: { r[56]=scope.track(arithmetic(api,ctx,4,r[55],r[54],true)); }
L98: { r[57]=scope.track(1ULL); }
L99: { r[58]=scope.track((!equal(api,ctx,r[56],r[57],true)?18ULL:10ULL)); }
L100: { if(!api->truthy(r[58].boxed(api,ctx))) goto L109; }
L101: {  }
L102: { r[59]=scope.track(9ULL); }
L103: { r[60]=scope.track(api->integer(api->read_int(r[55].boxed(api,ctx)) + api->read_int(r[59].boxed(api,ctx)))); }
L104: { r[55]=scope.track(r[60]); }
L105: {  }
L106: {  }
L107: {  }
L108: { goto L97; }
L109: { V argv[]={r[55].value?r[55].boxed(api,ctx):2ULL,57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L110: {  }
L111: { r[61]=scope.track(161ULL); }
L112: { V argv[] = {r[33].boxed(api,ctx),r[61].boxed(api,ctx),2ULL}; r[62]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L113: { V argv[] = {r[62].boxed(api,ctx),r[55].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L114: { r[64]=scope.track(193ULL); }
L115: { V argv[] = {r[33].boxed(api,ctx),r[64].boxed(api,ctx),2ULL}; r[65]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L116: { r[66]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.INPUT_PER_VERTEX",nullptr,0)); }
L117: { V argv[] = {r[65].boxed(api,ctx),r[66].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L118: { r[68]=scope.track(225ULL); }
L119: { V argv[] = {r[33].boxed(api,ctx),r[68].boxed(api,ctx),2ULL}; r[69]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L120: { r[70]=scope.track(1ULL); }
L121: { V argv[] = {r[69].boxed(api,ctx),r[70].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L122: {  }
L123: { r[72]=scope.track(ops->sequence_get(r[1].boxed(api,ctx),(r[28].small()?r[28].integer():api->read_int(r[28].boxed(api,ctx))))); }
L124: { N argv[] = {r[72],N(2ULL)}; r[73]=scope.track(f18(api,ctx,argv,1)); }
L125: { r[74]=scope.track(r[73]); }
L126: {  }
L127: { r[75]=scope.track(1ULL); }
L128: { r[76]=scope.track((equal(api,ctx,r[74],r[75],true)?18ULL:10ULL)); }
L129: { if(!api->truthy(r[76].boxed(api,ctx))) goto L141; }
L130: {  }
L131: { V argv[] = {r[19].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L132: { r[78]=scope.track(1ULL); }
L133: { V argv[]={r[78].value?r[78].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L134: {  }
L135: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L136: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L137: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L138: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L139: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L140: { scope.result=r[78].value?r[78].value:2ULL;return r[78]; }
L141: { r[79]=scope.track(api->integer(api->read_int(r[27].boxed(api,ctx)) + api->read_int(r[74].boxed(api,ctx)))); }
L142: { r[27]=scope.track(r[79]); }
L143: {  }
L144: { r[80]=scope.track(9ULL); }
L145: { r[81]=scope.track(api->integer(api->read_int(r[28].boxed(api,ctx)) + api->read_int(r[80].boxed(api,ctx)))); }
L146: { r[28]=scope.track(r[81]); }
L147: {  }
L148: { V argv[]={r[28].value?r[28].boxed(api,ctx):2ULL,49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L149: { V argv[]={r[27].value?r[27].boxed(api,ctx):2ULL,49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L150: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L151: { goto L56; }
L152: { V argv[]={r[27].value?r[27].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L153: { V argv[]={r[28].value?r[28].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L154: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L155: { r[82]=scope.track(65ULL); }
L156: { V argv[] = {r[82].boxed(api,ctx),2ULL}; r[83]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L157: { r[84]=scope.track(r[83]); }
L158: {  }
L159: { r[85]=scope.track(1ULL); }
L160: { V argv[] = {r[84].boxed(api,ctx),r[85].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L161: { r[87]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L162: { V argv[] = {r[87].boxed(api,ctx),81ULL,2ULL}; r[88]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L163: { r[89]=scope.track(r[88]); }
L164: {  }
L165: { r[90]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_IL",nullptr,0)); }
L166: { r[91]=scope.track(65ULL); }
L167: { r[92]=scope.track(arithmetic(api,ctx,2,r[90],r[91],true)); }
L168: { V argv[] = {r[89].boxed(api,ctx),r[92].boxed(api,ctx),2ULL}; r[93]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L169: { V argv[] = {r[93].boxed(api,ctx),81ULL,2ULL}; r[94]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L170: { r[95]=scope.track(r[94]); }
L171: {  }
L172: { r[96]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L173: { r[97]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L174: { ops->list_append(ctx,r[96].boxed(api,ctx),r[97].boxed(api,ctx)); }
L175: { ops->list_append(ctx,r[96].boxed(api,ctx),r[19].boxed(api,ctx)); }
L176: { ops->list_append(ctx,r[96].boxed(api,ctx),r[9].boxed(api,ctx)); }
L177: { ops->list_append(ctx,r[96].boxed(api,ctx),r[2].boxed(api,ctx)); }
L178: { ops->list_append(ctx,r[96].boxed(api,ctx),r[3].boxed(api,ctx)); }
L179: { ops->list_append(ctx,r[96].boxed(api,ctx),r[84].boxed(api,ctx)); }
L180: { r[104]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L181: { r[105]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L182: { r[106]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L183: { ops->list_append(ctx,r[105].boxed(api,ctx),r[106].boxed(api,ctx)); }
L184: { r[108]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L185: { ops->list_append(ctx,r[105].boxed(api,ctx),r[108].boxed(api,ctx)); }
L186: { r[110]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U32",nullptr,0)); }
L187: { ops->list_append(ctx,r[105].boxed(api,ctx),r[110].boxed(api,ctx)); }
L188: { r[112]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L189: { ops->list_append(ctx,r[105].boxed(api,ctx),r[112].boxed(api,ctx)); }
L190: { r[114]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U64",nullptr,0)); }
L191: { ops->list_append(ctx,r[105].boxed(api,ctx),r[114].boxed(api,ctx)); }
L192: { r[116]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L193: { ops->list_append(ctx,r[105].boxed(api,ctx),r[116].boxed(api,ctx)); }
L194: { V argv[] = {r[95].boxed(api,ctx),r[96].boxed(api,ctx),r[104].boxed(api,ctx),r[105].boxed(api,ctx),2ULL}; r[118]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L195: { r[119]=scope.track((r[118].floating() && std::isfinite(r[118].number(api)) && r[118].number(api)>=-0x1p60 && r[118].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[118].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[118].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L196: { r[120]=scope.track(r[119]); }
L197: {  }
L198: { V argv[] = {r[19].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L199: { r[122]=scope.track(1ULL); }
L200: { r[123]=scope.track((!equal(api,ctx,r[120],r[122],true)?18ULL:10ULL)); }
L201: { if(!api->truthy(r[123].boxed(api,ctx))) goto L215; }
L202: { V argv[]={89ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L203: { V argv[] = {r[84].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L204: { r[125]=scope.track(api->helper(ctx,11,49ULL,2ULL,2ULL,"IL hr=",nullptr,0)); }
L205: { r[126]=scope.track(api->helper(ctx,6,r[120].boxed(api,ctx),89ULL,2ULL,nullptr,nullptr,0)); }
L206: { r[127]=scope.track(api->helper(ctx,8,r[125].boxed(api,ctx),r[126].boxed(api,ctx),2ULL,nullptr,nullptr,0)); }
L207: { V argv[] = {r[127].boxed(api,ctx),2ULL}; r[128]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L208: { r[129]=scope.track(1ULL); }
L209: { V argv[]={r[129].value?r[129].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L210: { V argv[]={89ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L211: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L212: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L213: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L214: { scope.result=r[129].value?r[129].value:2ULL;return r[129]; }
L215: { V argv[] = {r[84].boxed(api,ctx),49ULL,2ULL}; r[130]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L216: { r[131]=scope.track(r[130]); }
L217: {  }
L218: { V argv[] = {r[84].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L219: { V argv[]={r[131].value?r[131].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L220: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L221: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L222: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L223: { scope.result=r[131].value?r[131].value:2ULL;return r[131]; }
L224: return 2ULL; }
// std.native.d3d11.fmt_align
static N f17(const Api* api,void* ctx,const N* args,size_t count) {
N r[17]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<17;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { N argv[] = {r[0],N(2ULL)}; r[1]=scope.track(f18(api,ctx,argv,1)); }
L3: { r[2]=scope.track(r[1]); }
L4: {  }
L5: { r[3]=scope.track(129ULL); }
L6: { r[4]=scope.track((compare(api,ctx,r[2],r[3],true)>=0?18ULL:10ULL)); }
L7: { if(!api->truthy(r[4].boxed(api,ctx))) goto L15; }
L8: {  }
L9: { r[5]=scope.track(129ULL); }
L10: { V argv[]={r[5].value?r[5].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L11: {  }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[5].value?r[5].value:2ULL;return r[5]; }
L15: { r[6]=scope.track(65ULL); }
L16: { r[7]=scope.track((equal(api,ctx,r[2],r[6],true)?18ULL:10ULL)); }
L17: { if(!api->truthy(r[7].boxed(api,ctx))) goto L25; }
L18: {  }
L19: { r[8]=scope.track(65ULL); }
L20: { V argv[]={r[8].value?r[8].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L21: {  }
L22: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L23: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L24: { scope.result=r[8].value?r[8].value:2ULL;return r[8]; }
L25: { r[9]=scope.track(17ULL); }
L26: { r[10]=scope.track((equal(api,ctx,r[2],r[9],true)?18ULL:10ULL)); }
L27: { if(!api->truthy(r[10].boxed(api,ctx))) goto L35; }
L28: {  }
L29: { r[11]=scope.track(17ULL); }
L30: { V argv[]={r[11].value?r[11].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L31: {  }
L32: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L33: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L34: { scope.result=r[11].value?r[11].value:2ULL;return r[11]; }
L35: { r[12]=scope.track(9ULL); }
L36: { r[13]=scope.track((equal(api,ctx,r[2],r[12],true)?18ULL:10ULL)); }
L37: { if(!api->truthy(r[13].boxed(api,ctx))) goto L45; }
L38: {  }
L39: { r[14]=scope.track(9ULL); }
L40: { V argv[]={r[14].value?r[14].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L41: {  }
L42: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L44: { scope.result=r[14].value?r[14].value:2ULL;return r[14]; }
L45: { r[15]=scope.track(33ULL); }
L46: { V argv[]={r[15].value?r[15].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L47: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L48: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L49: { scope.result=r[15].value?r[15].value:2ULL;return r[15]; }
L50: return 2ULL; }
// std.native.d3d11.fmt_size
static N f18(const Api* api,void* ctx,const N* args,size_t count) {
N r[39]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<39;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32G32B32A32_FLOAT",nullptr,0)); }
L3: { r[2]=scope.track((equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L4: { if(!api->truthy(r[2].boxed(api,ctx))) goto L12; }
L5: {  }
L6: { r[3]=scope.track(129ULL); }
L7: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L8: {  }
L9: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { scope.result=r[3].value?r[3].value:2ULL;return r[3]; }
L12: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32G32B32_FLOAT",nullptr,0)); }
L13: { r[5]=scope.track((equal(api,ctx,r[0],r[4],true)?18ULL:10ULL)); }
L14: { if(!api->truthy(r[5].boxed(api,ctx))) goto L22; }
L15: {  }
L16: { r[6]=scope.track(97ULL); }
L17: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L18: {  }
L19: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L20: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L21: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L22: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R16G16B16A16_FLOAT",nullptr,0)); }
L23: { r[8]=scope.track((equal(api,ctx,r[0],r[7],true)?18ULL:10ULL)); }
L24: { if(!api->truthy(r[8].boxed(api,ctx))) goto L32; }
L25: {  }
L26: { r[9]=scope.track(65ULL); }
L27: { V argv[]={r[9].value?r[9].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L28: {  }
L29: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L30: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L31: { scope.result=r[9].value?r[9].value:2ULL;return r[9]; }
L32: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32G32_FLOAT",nullptr,0)); }
L33: { r[12]=scope.track((equal(api,ctx,r[0],r[11],true)?18ULL:10ULL)); }
L34: { r[10]=scope.track(r[12]); }
L35: { if(api->truthy(r[12].boxed(api,ctx))) goto L40; }
L36: { r[13]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32G32_UINT",nullptr,0)); }
L37: { r[14]=scope.track((equal(api,ctx,r[0],r[13],true)?18ULL:10ULL)); }
L38: { r[10]=scope.track(r[14]); }
L39: { goto L40; }
L40: { if(!api->truthy(r[10].boxed(api,ctx))) goto L48; }
L41: {  }
L42: { r[15]=scope.track(65ULL); }
L43: { V argv[]={r[15].value?r[15].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L44: {  }
L45: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L46: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L47: { scope.result=r[15].value?r[15].value:2ULL;return r[15]; }
L48: { r[20]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R8G8B8A8_UNORM",nullptr,0)); }
L49: { r[21]=scope.track((equal(api,ctx,r[0],r[20],true)?18ULL:10ULL)); }
L50: { r[19]=scope.track(r[21]); }
L51: { if(api->truthy(r[21].boxed(api,ctx))) goto L56; }
L52: { r[22]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R8G8B8A8_UINT",nullptr,0)); }
L53: { r[23]=scope.track((equal(api,ctx,r[0],r[22],true)?18ULL:10ULL)); }
L54: { r[19]=scope.track(r[23]); }
L55: { goto L56; }
L56: { r[18]=scope.track(r[19]); }
L57: { if(api->truthy(r[19].boxed(api,ctx))) goto L62; }
L58: { r[24]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_B8G8R8A8_UNORM",nullptr,0)); }
L59: { r[25]=scope.track((equal(api,ctx,r[0],r[24],true)?18ULL:10ULL)); }
L60: { r[18]=scope.track(r[25]); }
L61: { goto L62; }
L62: { r[17]=scope.track(r[18]); }
L63: { if(api->truthy(r[18].boxed(api,ctx))) goto L68; }
L64: { r[26]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32_FLOAT",nullptr,0)); }
L65: { r[27]=scope.track((equal(api,ctx,r[0],r[26],true)?18ULL:10ULL)); }
L66: { r[17]=scope.track(r[27]); }
L67: { goto L68; }
L68: { r[16]=scope.track(r[17]); }
L69: { if(api->truthy(r[17].boxed(api,ctx))) goto L74; }
L70: { r[28]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32_UINT",nullptr,0)); }
L71: { r[29]=scope.track((equal(api,ctx,r[0],r[28],true)?18ULL:10ULL)); }
L72: { r[16]=scope.track(r[29]); }
L73: { goto L74; }
L74: { if(!api->truthy(r[16].boxed(api,ctx))) goto L82; }
L75: {  }
L76: { r[30]=scope.track(33ULL); }
L77: { V argv[]={r[30].value?r[30].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L78: {  }
L79: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L80: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L81: { scope.result=r[30].value?r[30].value:2ULL;return r[30]; }
L82: { r[31]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R16_UINT",nullptr,0)); }
L83: { r[32]=scope.track((equal(api,ctx,r[0],r[31],true)?18ULL:10ULL)); }
L84: { if(!api->truthy(r[32].boxed(api,ctx))) goto L92; }
L85: {  }
L86: { r[33]=scope.track(17ULL); }
L87: { V argv[]={r[33].value?r[33].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L88: {  }
L89: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L90: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L91: { scope.result=r[33].value?r[33].value:2ULL;return r[33]; }
L92: { r[34]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R8_UINT",nullptr,0)); }
L93: { r[35]=scope.track((equal(api,ctx,r[0],r[34],true)?18ULL:10ULL)); }
L94: { if(!api->truthy(r[35].boxed(api,ctx))) goto L102; }
L95: {  }
L96: { r[36]=scope.track(9ULL); }
L97: { V argv[]={r[36].value?r[36].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L98: {  }
L99: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L100: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L101: { scope.result=r[36].value?r[36].value:2ULL;return r[36]; }
L102: { r[37]=scope.track(1ULL); }
L103: { V argv[]={r[37].value?r[37].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L104: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L105: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L106: { scope.result=r[37].value?r[37].value:2ULL;return r[37]; }
L107: return 2ULL; }
// std.native.d3d11.gfx_ps_create
static N f19(const Api* api,void* ctx,const N* args,size_t count) {
N r[29]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<29;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[2]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[3]=scope.track(1ULL); }
L5: { r[4]=scope.track((equal(api,ctx,r[2],r[3],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[4].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[5]=scope.track(1ULL); }
L9: { V argv[]={r[5].value?r[5].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[5].value?r[5].value:2ULL;return r[5]; }
L15: { r[6]=scope.track(65ULL); }
L16: { V argv[] = {r[6].boxed(api,ctx),2ULL}; r[7]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[8]=scope.track(r[7]); }
L18: {  }
L19: { r[9]=scope.track(1ULL); }
L20: { V argv[] = {r[8].boxed(api,ctx),r[9].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L21: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L22: { r[12]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_PS",nullptr,0)); }
L23: { r[13]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L24: { ops->list_append(ctx,r[13].boxed(api,ctx),r[0].boxed(api,ctx)); }
L25: { ops->list_append(ctx,r[13].boxed(api,ctx),r[1].boxed(api,ctx)); }
L26: { r[16]=scope.track(1ULL); }
L27: { ops->list_append(ctx,r[13].boxed(api,ctx),r[16].boxed(api,ctx)); }
L28: { ops->list_append(ctx,r[13].boxed(api,ctx),r[8].boxed(api,ctx)); }
L29: { r[13]=N(r[13].boxed(api,ctx));N argv[] = {r[11],r[12],r[13],N(2ULL)}; r[19]=scope.track(f48(api,ctx,argv,3)); }
L30: { r[20]=scope.track(r[19]); }
L31: {  }
L32: { r[21]=scope.track(1ULL); }
L33: { r[22]=scope.track((!equal(api,ctx,r[20],r[21],true)?18ULL:10ULL)); }
L34: { if(!api->truthy(r[22].boxed(api,ctx))) goto L44; }
L35: {  }
L36: { V argv[] = {r[8].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L37: { r[24]=scope.track(1ULL); }
L38: { V argv[]={r[24].value?r[24].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L39: {  }
L40: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L41: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L42: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { scope.result=r[24].value?r[24].value:2ULL;return r[24]; }
L44: { V argv[] = {r[8].boxed(api,ctx),49ULL,2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L45: { r[26]=scope.track(r[25]); }
L46: {  }
L47: { V argv[] = {r[8].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L48: { V argv[]={r[26].value?r[26].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L49: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L50: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L51: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L52: { scope.result=r[26].value?r[26].value:2ULL;return r[26]; }
L53: return 2ULL; }
// std.native.d3d11.gfx_blob_size
static N f20(const Api* api,void* ctx,const N* args,size_t count) {
N r[3]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<3;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { N argv[] = {r[0],N(2ULL)}; r[1]=scope.track(f71(api,ctx,argv,1)); }
L3: { V argv[]={r[1].value?r[1].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L4: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L5: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L6: { scope.result=r[1].value?r[1].value:2ULL;return r[1]; }
L7: return 2ULL; }
// std.native.d3d11.gfx_blob_ptr
static N f21(const Api* api,void* ctx,const N* args,size_t count) {
N r[3]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<3;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { N argv[] = {r[0],N(2ULL)}; r[1]=scope.track(f67(api,ctx,argv,1)); }
L3: { V argv[]={r[1].value?r[1].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L4: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L5: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L6: { scope.result=r[1].value?r[1].value:2ULL;return r[1]; }
L7: return 2ULL; }
// std.native.d3d11.gfx_set_render_targets
static N f22(const Api* api,void* ctx,const N* args,size_t count) {
N r[26]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<26;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: {  }
L4: { r[2]=scope.track(native_length(api,ctx,r[0].boxed(api,ctx))); }
L5: { r[3]=scope.track(r[2]); }
L6: {  }
L7: { r[4]=scope.track(65ULL); }
L8: { r[5]=scope.track(arithmetic(api,ctx,2,r[3],r[4],true)); }
L9: { V argv[] = {r[5].boxed(api,ctx),2ULL}; r[6]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L10: { r[7]=scope.track(r[6]); }
L11: {  }
L12: { r[8]=scope.track(1ULL); }
L13: {  }
L14: {  }
L15: { goto L16; }
L16: { r[9]=scope.track((compare(api,ctx,r[8],r[3],true)<0?18ULL:10ULL)); }
L17: { if(!api->truthy(r[9].boxed(api,ctx))) goto L32; }
L18: {  }
L19: { r[10]=scope.track(65ULL); }
L20: { r[11]=scope.track(arithmetic(api,ctx,2,r[8],r[10],true)); }
L21: { V argv[] = {r[7].boxed(api,ctx),r[11].boxed(api,ctx),2ULL}; r[12]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L22: {  }
L23: { r[13]=scope.track(ops->sequence_get(r[0].boxed(api,ctx),(r[8].small()?r[8].integer():api->read_int(r[8].boxed(api,ctx))))); }
L24: { V argv[] = {r[12].boxed(api,ctx),r[13].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L25: { r[15]=scope.track(9ULL); }
L26: { r[16]=scope.track(api->integer(api->read_int(r[8].boxed(api,ctx)) + api->read_int(r[15].boxed(api,ctx)))); }
L27: { r[8]=scope.track(r[16]); }
L28: {  }
L29: {  }
L30: {  }
L31: { goto L16; }
L32: { V argv[]={r[8].value?r[8].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L33: {  }
L34: { r[17]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L35: { r[18]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_OM_RTV",nullptr,0)); }
L36: { r[19]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L37: { ops->list_append(ctx,r[19].boxed(api,ctx),r[3].boxed(api,ctx)); }
L38: { ops->list_append(ctx,r[19].boxed(api,ctx),r[7].boxed(api,ctx)); }
L39: { ops->list_append(ctx,r[19].boxed(api,ctx),r[1].boxed(api,ctx)); }
L40: { r[19]=N(r[19].boxed(api,ctx));N argv[] = {r[17],r[18],r[19],N(2ULL)}; r[23]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L41: { V argv[] = {r[7].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L42: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L44: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L45: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L46: return 2ULL; }
// std.native.d3d11.gfx_compile
static N f23(const Api* api,void* ctx,const N* args,size_t count) {
N r[84]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<84;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[3]=scope.track(f68(api,ctx,argv,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track((equal(api,ctx,r[3],r[4],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[5].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[6]=scope.track(1ULL); }
L9: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L15: { r[0]=N(r[0].boxed(api,ctx));N argv[] = {r[0],N(2ULL)}; r[7]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L16: { r[8]=scope.track(r[7]); }
L17: {  }
L18: { r[9]=scope.track(api->helper(ctx,11,113ULL,2ULL,2ULL,"lymar_gfx.hlsl",nullptr,0)); }
L19: { r[9]=N(r[9].boxed(api,ctx));N argv[] = {r[9],N(2ULL)}; r[10]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L20: { r[11]=scope.track(r[10]); }
L21: {  }
L22: { r[1]=N(r[1].boxed(api,ctx));N argv[] = {r[1],N(2ULL)}; r[12]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L23: { r[13]=scope.track(r[12]); }
L24: {  }
L25: { r[2]=N(r[2].boxed(api,ctx));N argv[] = {r[2],N(2ULL)}; r[14]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L26: { r[15]=scope.track(r[14]); }
L27: {  }
L28: { r[16]=scope.track(65ULL); }
L29: { V argv[] = {r[16].boxed(api,ctx),2ULL}; r[17]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L30: { r[18]=scope.track(r[17]); }
L31: {  }
L32: { r[19]=scope.track(65ULL); }
L33: { V argv[] = {r[19].boxed(api,ctx),2ULL}; r[20]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L34: { r[21]=scope.track(r[20]); }
L35: {  }
L36: { r[22]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compile_fn",nullptr,0)); }
L37: { r[23]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L38: {  }
L39: { r[24]=scope.track(ops->frame_get(ctx,r[8].boxed(api,ctx),0,false)); }
L40: { ops->list_append(ctx,r[23].boxed(api,ctx),r[24].boxed(api,ctx)); }
L41: { r[26]=scope.track(native_length(api,ctx,r[0].boxed(api,ctx))); }
L42: { ops->list_append(ctx,r[23].boxed(api,ctx),r[26].boxed(api,ctx)); }
L43: {  }
L44: { r[28]=scope.track(ops->frame_get(ctx,r[11].boxed(api,ctx),0,false)); }
L45: { ops->list_append(ctx,r[23].boxed(api,ctx),r[28].boxed(api,ctx)); }
L46: { r[30]=scope.track(1ULL); }
L47: { ops->list_append(ctx,r[23].boxed(api,ctx),r[30].boxed(api,ctx)); }
L48: { r[32]=scope.track(1ULL); }
L49: { ops->list_append(ctx,r[23].boxed(api,ctx),r[32].boxed(api,ctx)); }
L50: {  }
L51: { r[34]=scope.track(ops->frame_get(ctx,r[13].boxed(api,ctx),0,false)); }
L52: { ops->list_append(ctx,r[23].boxed(api,ctx),r[34].boxed(api,ctx)); }
L53: {  }
L54: { r[36]=scope.track(ops->frame_get(ctx,r[15].boxed(api,ctx),0,false)); }
L55: { ops->list_append(ctx,r[23].boxed(api,ctx),r[36].boxed(api,ctx)); }
L56: { r[38]=scope.track(1ULL); }
L57: { ops->list_append(ctx,r[23].boxed(api,ctx),r[38].boxed(api,ctx)); }
L58: { r[40]=scope.track(1ULL); }
L59: { ops->list_append(ctx,r[23].boxed(api,ctx),r[40].boxed(api,ctx)); }
L60: { ops->list_append(ctx,r[23].boxed(api,ctx),r[18].boxed(api,ctx)); }
L61: { ops->list_append(ctx,r[23].boxed(api,ctx),r[21].boxed(api,ctx)); }
L62: { r[44]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L63: { r[45]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L64: { r[46]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L65: { ops->list_append(ctx,r[45].boxed(api,ctx),r[46].boxed(api,ctx)); }
L66: { r[48]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U64",nullptr,0)); }
L67: { ops->list_append(ctx,r[45].boxed(api,ctx),r[48].boxed(api,ctx)); }
L68: { r[50]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L69: { ops->list_append(ctx,r[45].boxed(api,ctx),r[50].boxed(api,ctx)); }
L70: { r[52]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L71: { ops->list_append(ctx,r[45].boxed(api,ctx),r[52].boxed(api,ctx)); }
L72: { r[54]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L73: { ops->list_append(ctx,r[45].boxed(api,ctx),r[54].boxed(api,ctx)); }
L74: { r[56]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L75: { ops->list_append(ctx,r[45].boxed(api,ctx),r[56].boxed(api,ctx)); }
L76: { r[58]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L77: { ops->list_append(ctx,r[45].boxed(api,ctx),r[58].boxed(api,ctx)); }
L78: { r[60]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U32",nullptr,0)); }
L79: { ops->list_append(ctx,r[45].boxed(api,ctx),r[60].boxed(api,ctx)); }
L80: { r[62]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U32",nullptr,0)); }
L81: { ops->list_append(ctx,r[45].boxed(api,ctx),r[62].boxed(api,ctx)); }
L82: { r[64]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L83: { ops->list_append(ctx,r[45].boxed(api,ctx),r[64].boxed(api,ctx)); }
L84: { r[66]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L85: { ops->list_append(ctx,r[45].boxed(api,ctx),r[66].boxed(api,ctx)); }
L86: { V argv[] = {r[22].boxed(api,ctx),r[23].boxed(api,ctx),r[44].boxed(api,ctx),r[45].boxed(api,ctx),2ULL}; r[68]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L87: { r[69]=scope.track((r[68].floating() && std::isfinite(r[68].number(api)) && r[68].number(api)>=-0x1p60 && r[68].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[68].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[68].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L88: { r[70]=scope.track(r[69]); }
L89: {  }
L90: { r[71]=scope.track(1ULL); }
L91: {  }
L92: { r[72]=scope.track(1ULL); }
L93: { r[73]=scope.track((equal(api,ctx,r[70],r[72],true)?18ULL:10ULL)); }
L94: { if(!api->truthy(r[73].boxed(api,ctx))) goto L102; }
L95: {  }
L96: { V argv[] = {r[18].boxed(api,ctx),49ULL,2ULL}; r[74]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L97: { r[71]=scope.track(r[74]); }
L98: {  }
L99: { V argv[]={r[71].value?r[71].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L100: {  }
L101: { goto L102; }
L102: { V argv[] = {r[18].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L103: { V argv[] = {r[21].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L104: { r[77]=scope.track(1ULL); }
L105: { r[78]=scope.track((equal(api,ctx,r[71],r[77],true)?18ULL:10ULL)); }
L106: { if(!api->truthy(r[78].boxed(api,ctx))) goto L114; }
L107: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L108: { r[79]=scope.track(api->helper(ctx,11,121ULL,2ULL,2ULL,"gfx_compile hr=",nullptr,0)); }
L109: { r[80]=scope.track(api->helper(ctx,6,r[70].boxed(api,ctx),89ULL,2ULL,nullptr,nullptr,0)); }
L110: { r[81]=scope.track(api->helper(ctx,8,r[79].boxed(api,ctx),r[80].boxed(api,ctx),2ULL,nullptr,nullptr,0)); }
L111: { V argv[] = {r[81].boxed(api,ctx),2ULL}; r[82]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L112: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L113: { goto L114; }
L114: { V argv[]={r[71].value?r[71].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L115: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L116: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L117: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L118: { scope.result=r[71].value?r[71].value:2ULL;return r[71]; }
L119: return 2ULL; }
// std.native.d3d11.gfx_draw_indexed
static N f24(const Api* api,void* ctx,const N* args,size_t count) {
N r[11]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<11;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_DRAW_INDEXED",nullptr,0)); }
L5: { r[5]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[5].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { ops->list_append(ctx,r[5].boxed(api,ctx),r[1].boxed(api,ctx)); }
L8: { ops->list_append(ctx,r[5].boxed(api,ctx),r[2].boxed(api,ctx)); }
L9: { r[5]=N(r[5].boxed(api,ctx));N argv[] = {r[3],r[4],r[5],N(2ULL)}; r[9]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L10: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L14: return 2ULL; }
// std.native.d3d11.gfx_set_vertex_buffer
static N f25(const Api* api,void* ctx,const N* args,size_t count) {
N r[30]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<30;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[4]=scope.track(65ULL); }
L4: { V argv[] = {r[4].boxed(api,ctx),2ULL}; r[5]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L5: { r[6]=scope.track(r[5]); }
L6: {  }
L7: { V argv[] = {r[6].boxed(api,ctx),r[1].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L8: { r[8]=scope.track(33ULL); }
L9: { V argv[] = {r[8].boxed(api,ctx),2ULL}; r[9]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L10: { r[10]=scope.track(r[9]); }
L11: {  }
L12: { V argv[] = {r[10].boxed(api,ctx),r[2].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L13: { r[12]=scope.track(33ULL); }
L14: { V argv[] = {r[12].boxed(api,ctx),2ULL}; r[13]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L15: { r[14]=scope.track(r[13]); }
L16: {  }
L17: { V argv[] = {r[14].boxed(api,ctx),r[3].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L18: { r[16]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L19: { r[17]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_IA_VB",nullptr,0)); }
L20: { r[18]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L21: { ops->list_append(ctx,r[18].boxed(api,ctx),r[0].boxed(api,ctx)); }
L22: { r[20]=scope.track(9ULL); }
L23: { ops->list_append(ctx,r[18].boxed(api,ctx),r[20].boxed(api,ctx)); }
L24: { ops->list_append(ctx,r[18].boxed(api,ctx),r[6].boxed(api,ctx)); }
L25: { ops->list_append(ctx,r[18].boxed(api,ctx),r[10].boxed(api,ctx)); }
L26: { ops->list_append(ctx,r[18].boxed(api,ctx),r[14].boxed(api,ctx)); }
L27: { r[18]=N(r[18].boxed(api,ctx));N argv[] = {r[16],r[17],r[18],N(2ULL)}; r[25]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L28: { V argv[] = {r[6].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L29: { V argv[] = {r[10].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L30: { V argv[] = {r[14].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L31: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L32: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L33: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L34: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L35: return 2ULL; }
// std.native.d3d11.gfx_release_all
static N f26(const Api* api,void* ctx,const N* args,size_t count) {
N r[14]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<14;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[0]=scope.track(N(f9(api,ctx,argv,0).boxed(api,ctx))); }
L4: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L5: { r[2]=scope.track(1ULL); }
L6: { r[3]=scope.track((!equal(api,ctx,r[1],r[2],true)?18ULL:10ULL)); }
L7: { if(!api->truthy(r[3].boxed(api,ctx))) goto L16; }
L8: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L9: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L10: { N argv[] = {r[4],N(2ULL)}; r[5]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L11: { r[6]=scope.track(1ULL); }
L12: { api->helper(ctx,43,r[6].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._context",nullptr,0); }
L13: {  }
L14: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L15: { goto L16; }
L16: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L17: { r[8]=scope.track(1ULL); }
L18: { r[9]=scope.track((!equal(api,ctx,r[7],r[8],true)?18ULL:10ULL)); }
L19: { if(!api->truthy(r[9].boxed(api,ctx))) goto L28; }
L20: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L21: { r[10]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L22: { N argv[] = {r[10],N(2ULL)}; r[11]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L23: { r[12]=scope.track(1ULL); }
L24: { api->helper(ctx,43,r[12].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._device",nullptr,0); }
L25: {  }
L26: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L27: { goto L28; }
L28: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L29: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L30: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L31: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L32: return 2ULL; }
// std.native.d3d11.gfx_buffer_create_dynamic
static N f27(const Api* api,void* ctx,const N* args,size_t count) {
N r[9]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<9;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.USAGE_DYNAMIC",nullptr,0)); }
L3: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.CPU_WRITE",nullptr,0)); }
L4: { r[5]=scope.track(1ULL); }
L5: { r[6]=scope.track(1ULL); }
L6: { N argv[] = {r[0],r[3],r[1],r[4],r[5],r[2],r[6],N(2ULL)}; r[7]=scope.track(f44(api,ctx,argv,7)); }
L7: { V argv[]={r[7].value?r[7].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L8: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L9: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { scope.result=r[7].value?r[7].value:2ULL;return r[7]; }
L11: return 2ULL; }
// std.native.d3d11.gfx_index_buffer_create
static N f28(const Api* api,void* ctx,const N* args,size_t count) {
N r[9]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<9;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.USAGE_DEFAULT",nullptr,0)); }
L3: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.BIND_INDEX_BUFFER",nullptr,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track(1ULL); }
L6: { r[6]=scope.track(1ULL); }
L7: { N argv[] = {r[0],r[2],r[3],r[4],r[5],r[6],r[1],N(2ULL)}; r[7]=scope.track(f44(api,ctx,argv,7)); }
L8: { V argv[]={r[7].value?r[7].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L9: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { scope.result=r[7].value?r[7].value:2ULL;return r[7]; }
L12: return 2ULL; }
// std.native.d3d11.gfx_vertex_buffer_create
static N f29(const Api* api,void* ctx,const N* args,size_t count) {
N r[9]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<9;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.USAGE_DEFAULT",nullptr,0)); }
L3: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.BIND_VERTEX_BUFFER",nullptr,0)); }
L4: { r[5]=scope.track(1ULL); }
L5: { r[6]=scope.track(1ULL); }
L6: { N argv[] = {r[0],r[3],r[4],r[5],r[6],r[1],r[2],N(2ULL)}; r[7]=scope.track(f44(api,ctx,argv,7)); }
L7: { V argv[]={r[7].value?r[7].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L8: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L9: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { scope.result=r[7].value?r[7].value:2ULL;return r[7]; }
L11: return 2ULL; }
// std.native.d3d11.gfx_end_frame
static N f30(const Api* api,void* ctx,const N* args,size_t count) {
N r[12]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<12;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L4: { r[1]=scope.track(1ULL); }
L5: { r[2]=scope.track((equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[2].boxed(api,ctx))) goto L13; }
L7: {  }
L8: {  }
L9: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L13: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L14: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_SWAP_PRESENT",nullptr,0)); }
L15: { r[5]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L16: { r[6]=scope.track(9ULL); }
L17: { ops->list_append(ctx,r[5].boxed(api,ctx),r[6].boxed(api,ctx)); }
L18: { r[8]=scope.track(1ULL); }
L19: { ops->list_append(ctx,r[5].boxed(api,ctx),r[8].boxed(api,ctx)); }
L20: { r[5]=N(r[5].boxed(api,ctx));N argv[] = {r[3],r[4],r[5],N(2ULL)}; r[10]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L21: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L22: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L23: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L24: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L25: return 2ULL; }
// std.native.d3d11.gfx_clear_depth
static N f31(const Api* api,void* ctx,const N* args,size_t count) {
N r[37]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<37;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
r[0].cache_float(api);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L4: { r[2]=scope.track(1ULL); }
L5: { r[3]=scope.track((equal(api,ctx,r[1],r[2],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[3].boxed(api,ctx))) goto L13; }
L7: {  }
L8: {  }
L9: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L13: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L14: { V argv[] = {r[4].boxed(api,ctx),81ULL,2ULL}; r[5]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L15: { r[6]=scope.track(r[5]); }
L16: {  }
L17: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_CLEAR_DSV",nullptr,0)); }
L18: { r[8]=scope.track(65ULL); }
L19: { r[9]=scope.track(arithmetic(api,ctx,2,r[7],r[8],true)); }
L20: { V argv[] = {r[6].boxed(api,ctx),r[9].boxed(api,ctx),2ULL}; r[10]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L21: { V argv[] = {r[10].boxed(api,ctx),81ULL,2ULL}; r[11]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L22: { r[12]=scope.track(r[11]); }
L23: {  }
L24: { r[13]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L25: { r[14]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L26: { ops->list_append(ctx,r[13].boxed(api,ctx),r[14].boxed(api,ctx)); }
L27: { r[16]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L28: { ops->list_append(ctx,r[13].boxed(api,ctx),r[16].boxed(api,ctx)); }
L29: { r[18]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.CLEAR_DEPTH",nullptr,0)); }
L30: { ops->list_append(ctx,r[13].boxed(api,ctx),r[18].boxed(api,ctx)); }
L31: { ops->list_append(ctx,r[13].boxed(api,ctx),r[0].boxed(api,ctx)); }
L32: { r[21]=scope.track(1ULL); }
L33: { ops->list_append(ctx,r[13].boxed(api,ctx),r[21].boxed(api,ctx)); }
L34: { r[23]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_VOID",nullptr,0)); }
L35: { r[24]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L36: { r[25]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L37: { ops->list_append(ctx,r[24].boxed(api,ctx),r[25].boxed(api,ctx)); }
L38: { r[27]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L39: { ops->list_append(ctx,r[24].boxed(api,ctx),r[27].boxed(api,ctx)); }
L40: { r[29]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U32",nullptr,0)); }
L41: { ops->list_append(ctx,r[24].boxed(api,ctx),r[29].boxed(api,ctx)); }
L42: { r[31]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_F32",nullptr,0)); }
L43: { ops->list_append(ctx,r[24].boxed(api,ctx),r[31].boxed(api,ctx)); }
L44: { r[33]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U32",nullptr,0)); }
L45: { ops->list_append(ctx,r[24].boxed(api,ctx),r[33].boxed(api,ctx)); }
L46: { V argv[] = {r[12].boxed(api,ctx),r[13].boxed(api,ctx),r[23].boxed(api,ctx),r[24].boxed(api,ctx),2ULL}; r[35]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L47: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L48: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L49: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L50: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L51: return 2ULL; }
// std.native.d3d11.gfx_unmap
static N f32(const Api* api,void* ctx,const N* args,size_t count) {
N r[9]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<9;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_UNMAP",nullptr,0)); }
L5: { r[3]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[3].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { r[5]=scope.track(1ULL); }
L8: { ops->list_append(ctx,r[3].boxed(api,ctx),r[5].boxed(api,ctx)); }
L9: { r[3]=N(r[3].boxed(api,ctx));N argv[] = {r[1],r[2],r[3],N(2ULL)}; r[7]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L10: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L14: return 2ULL; }
// std.native.d3d11.gfx_clear
static N f33(const Api* api,void* ctx,const N* args,size_t count) {
N r[30]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<30;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
r[0].cache_float(api);
r[1].cache_float(api);
r[2].cache_float(api);
r[3].cache_float(api);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L4: { r[5]=scope.track(1ULL); }
L5: { r[6]=scope.track((equal(api,ctx,r[4],r[5],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[6].boxed(api,ctx))) goto L13; }
L7: {  }
L8: {  }
L9: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L13: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._color",nullptr,0)); }
L14: { V argv[] = {r[7].boxed(api,ctx),r[0].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L15: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._color",nullptr,0)); }
L16: { r[10]=scope.track(33ULL); }
L17: { V argv[] = {r[9].boxed(api,ctx),r[10].boxed(api,ctx),2ULL}; r[11]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L18: { V argv[] = {r[11].boxed(api,ctx),r[1].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L19: { r[13]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._color",nullptr,0)); }
L20: { r[14]=scope.track(65ULL); }
L21: { V argv[] = {r[13].boxed(api,ctx),r[14].boxed(api,ctx),2ULL}; r[15]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L22: { V argv[] = {r[15].boxed(api,ctx),r[2].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L23: { r[17]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._color",nullptr,0)); }
L24: { r[18]=scope.track(97ULL); }
L25: { V argv[] = {r[17].boxed(api,ctx),r[18].boxed(api,ctx),2ULL}; r[19]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L26: { V argv[] = {r[19].boxed(api,ctx),r[3].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L27: { r[21]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L28: { r[22]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_CLEAR_RTV",nullptr,0)); }
L29: { r[23]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L30: { r[24]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L31: { ops->list_append(ctx,r[23].boxed(api,ctx),r[24].boxed(api,ctx)); }
L32: { r[26]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._color",nullptr,0)); }
L33: { ops->list_append(ctx,r[23].boxed(api,ctx),r[26].boxed(api,ctx)); }
L34: { r[23]=N(r[23].boxed(api,ctx));N argv[] = {r[21],r[22],r[23],N(2ULL)}; r[28]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L35: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L36: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L37: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L38: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L39: return 2ULL; }
// std.native.d3d11.gfx_begin_frame
static N f34(const Api* api,void* ctx,const N* args,size_t count) {
N r[61]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<61;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L4: { r[2]=scope.track(1ULL); }
L5: { r[3]=scope.track((equal(api,ctx,r[1],r[2],true)?18ULL:10ULL)); }
L6: { r[0]=scope.track(r[3]); }
L7: { if(api->truthy(r[3].boxed(api,ctx))) goto L13; }
L8: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L9: { r[5]=scope.track(1ULL); }
L10: { r[6]=scope.track((equal(api,ctx,r[4],r[5],true)?18ULL:10ULL)); }
L11: { r[0]=scope.track(r[6]); }
L12: { goto L13; }
L13: { if(!api->truthy(r[0].boxed(api,ctx))) goto L22; }
L14: {  }
L15: { r[7]=scope.track(1ULL); }
L16: { V argv[]={r[7].value?r[7].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L17: {  }
L18: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L19: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L20: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L21: { scope.result=r[7].value?r[7].value:2ULL;return r[7]; }
L22: { r[8]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv_arr",nullptr,0)); }
L23: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L24: { V argv[] = {r[8].boxed(api,ctx),r[9].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L25: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L26: { r[12]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_OM_RTV",nullptr,0)); }
L27: { r[13]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L28: { r[14]=scope.track(9ULL); }
L29: { ops->list_append(ctx,r[13].boxed(api,ctx),r[14].boxed(api,ctx)); }
L30: { r[16]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv_arr",nullptr,0)); }
L31: { ops->list_append(ctx,r[13].boxed(api,ctx),r[16].boxed(api,ctx)); }
L32: { r[18]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L33: { ops->list_append(ctx,r[13].boxed(api,ctx),r[18].boxed(api,ctx)); }
L34: { r[13]=N(r[13].boxed(api,ctx));N argv[] = {r[11],r[12],r[13],N(2ULL)}; r[20]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L35: { r[21]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L36: { r[22]=scope.track(real(api,ctx,0x0p+0));r[22].cache_float(api); }
L37: { V argv[] = {r[21].boxed(api,ctx),r[22].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L38: { r[24]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L39: { r[25]=scope.track(33ULL); }
L40: { V argv[] = {r[24].boxed(api,ctx),r[25].boxed(api,ctx),2ULL}; r[26]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L41: { r[27]=scope.track(real(api,ctx,0x0p+0));r[27].cache_float(api); }
L42: { V argv[] = {r[26].boxed(api,ctx),r[27].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L43: { r[29]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L44: { r[30]=scope.track(65ULL); }
L45: { V argv[] = {r[29].boxed(api,ctx),r[30].boxed(api,ctx),2ULL}; r[31]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L46: { r[32]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._width",nullptr,0)); }
L47: { r[33]=scope.track((r[32].numeric()?real(api,ctx,r[32].number(api)):N(api->helper(ctx,6,r[32].boxed(api,ctx),73ULL,2ULL,nullptr,nullptr,0))));r[33].cache_float(api); }
L48: { V argv[] = {r[31].boxed(api,ctx),r[33].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L49: { r[35]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L50: { r[36]=scope.track(97ULL); }
L51: { V argv[] = {r[35].boxed(api,ctx),r[36].boxed(api,ctx),2ULL}; r[37]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L52: { r[38]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._height",nullptr,0)); }
L53: { r[39]=scope.track((r[38].numeric()?real(api,ctx,r[38].number(api)):N(api->helper(ctx,6,r[38].boxed(api,ctx),73ULL,2ULL,nullptr,nullptr,0))));r[39].cache_float(api); }
L54: { V argv[] = {r[37].boxed(api,ctx),r[39].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L55: { r[41]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L56: { r[42]=scope.track(129ULL); }
L57: { V argv[] = {r[41].boxed(api,ctx),r[42].boxed(api,ctx),2ULL}; r[43]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L58: { r[44]=scope.track(real(api,ctx,0x0p+0));r[44].cache_float(api); }
L59: { V argv[] = {r[43].boxed(api,ctx),r[44].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L60: { r[46]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L61: { r[47]=scope.track(161ULL); }
L62: { V argv[] = {r[46].boxed(api,ctx),r[47].boxed(api,ctx),2ULL}; r[48]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L63: { r[49]=scope.track(real(api,ctx,0x1p+0));r[49].cache_float(api); }
L64: { V argv[] = {r[48].boxed(api,ctx),r[49].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L65: { r[51]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L66: { r[52]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_RS_VP",nullptr,0)); }
L67: { r[53]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L68: { r[54]=scope.track(9ULL); }
L69: { ops->list_append(ctx,r[53].boxed(api,ctx),r[54].boxed(api,ctx)); }
L70: { r[56]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L71: { ops->list_append(ctx,r[53].boxed(api,ctx),r[56].boxed(api,ctx)); }
L72: { r[53]=N(r[53].boxed(api,ctx));N argv[] = {r[51],r[52],r[53],N(2ULL)}; r[58]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L73: { r[59]=scope.track(9ULL); }
L74: { V argv[]={r[59].value?r[59].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L75: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L76: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L77: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L78: { scope.result=r[59].value?r[59].value:2ULL;return r[59]; }
L79: return 2ULL; }
// std.native.d3d11.gfx_raster_state_create
static N f35(const Api* api,void* ctx,const N* args,size_t count) {
N r[41]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<41;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[2]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[3]=scope.track(1ULL); }
L5: { r[4]=scope.track((equal(api,ctx,r[2],r[3],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[4].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[5]=scope.track(1ULL); }
L9: { V argv[]={r[5].value?r[5].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[5].value?r[5].value:2ULL;return r[5]; }
L15: { r[6]=scope.track(321ULL); }
L16: { V argv[] = {r[6].boxed(api,ctx),2ULL}; r[7]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[8]=scope.track(r[7]); }
L18: {  }
L19: { r[9]=scope.track(1ULL); }
L20: { r[10]=scope.track(321ULL); }
L21: { V argv[] = {r[8].boxed(api,ctx),r[9].boxed(api,ctx),r[10].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L22: { V argv[] = {r[8].boxed(api,ctx),r[0].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L23: { r[13]=scope.track(33ULL); }
L24: { V argv[] = {r[8].boxed(api,ctx),r[13].boxed(api,ctx),2ULL}; r[14]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L25: { V argv[] = {r[14].boxed(api,ctx),r[1].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L26: { r[16]=scope.track(193ULL); }
L27: { V argv[] = {r[8].boxed(api,ctx),r[16].boxed(api,ctx),2ULL}; r[17]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L28: { r[18]=scope.track(9ULL); }
L29: { V argv[] = {r[17].boxed(api,ctx),r[18].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L30: { r[20]=scope.track(65ULL); }
L31: { V argv[] = {r[20].boxed(api,ctx),2ULL}; r[21]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L32: { r[22]=scope.track(r[21]); }
L33: {  }
L34: { r[23]=scope.track(1ULL); }
L35: { V argv[] = {r[22].boxed(api,ctx),r[23].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L36: { r[25]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L37: { r[26]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_RS",nullptr,0)); }
L38: { r[27]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L39: { ops->list_append(ctx,r[27].boxed(api,ctx),r[8].boxed(api,ctx)); }
L40: { ops->list_append(ctx,r[27].boxed(api,ctx),r[22].boxed(api,ctx)); }
L41: { r[27]=N(r[27].boxed(api,ctx));N argv[] = {r[25],r[26],r[27],N(2ULL)}; r[30]=scope.track(f48(api,ctx,argv,3)); }
L42: { r[31]=scope.track(r[30]); }
L43: {  }
L44: { V argv[] = {r[8].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L45: { r[33]=scope.track(1ULL); }
L46: { r[34]=scope.track((!equal(api,ctx,r[31],r[33],true)?18ULL:10ULL)); }
L47: { if(!api->truthy(r[34].boxed(api,ctx))) goto L57; }
L48: {  }
L49: { V argv[] = {r[22].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L50: { r[36]=scope.track(1ULL); }
L51: { V argv[]={r[36].value?r[36].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L52: {  }
L53: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L54: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L55: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L56: { scope.result=r[36].value?r[36].value:2ULL;return r[36]; }
L57: { V argv[] = {r[22].boxed(api,ctx),49ULL,2ULL}; r[37]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L58: { r[38]=scope.track(r[37]); }
L59: {  }
L60: { V argv[] = {r[22].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L61: { V argv[]={r[38].value?r[38].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L62: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L63: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L64: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L65: { scope.result=r[38].value?r[38].value:2ULL;return r[38]; }
L66: return 2ULL; }
// std.native.d3d11.gfx_height
static N f36(const Api* api,void* ctx,const N* args,size_t count) {
N r[2]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<2;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._height",nullptr,0)); }
L3: { V argv[]={r[0].value?r[0].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L4: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L5: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L6: { scope.result=r[0].value?r[0].value:2ULL;return r[0]; }
L7: return 2ULL; }
// std.native.d3d11.gfx_attached
static N f37(const Api* api,void* ctx,const N* args,size_t count) {
N r[6]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<6;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L3: { r[1]=scope.track(1ULL); }
L4: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L5: { if(!api->truthy(r[2].boxed(api,ctx))) goto L13; }
L6: {  }
L7: { r[3]=scope.track(9ULL); }
L8: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L9: {  }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=r[3].value?r[3].value:2ULL;return r[3]; }
L13: { r[4]=scope.track(1ULL); }
L14: { V argv[]={r[4].value?r[4].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L15: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L16: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L17: { scope.result=r[4].value?r[4].value:2ULL;return r[4]; }
L18: return 2ULL; }
// std.native.d3d11.gfx_create_views
static N f38(const Api* api,void* ctx,const N* args,size_t count) {
N r[157]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<157;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[0]=scope.track(14909527953ULL); }
L4: { r[1]=scope.track(430145ULL); }
L5: { r[2]=scope.track(160841ULL); }
L6: { r[3]=scope.track(20036560081ULL); }
L7: { r[4]=scope.track(20979816873ULL); }
L8: { N argv[] = {r[0],r[1],r[2],r[3],r[4],N(2ULL)}; r[5]=scope.track(f76(api,ctx,argv,5)); }
L9: { r[6]=scope.track(65ULL); }
L10: { V argv[] = {r[6].boxed(api,ctx),2ULL}; r[7]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L11: { r[8]=scope.track(r[7]); }
L12: {  }
L13: { r[9]=scope.track(1ULL); }
L14: { V argv[] = {r[8].boxed(api,ctx),r[9].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L15: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L16: { r[12]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_SWAP_GET_BUFFER",nullptr,0)); }
L17: { r[13]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L18: { r[14]=scope.track(1ULL); }
L19: { ops->list_append(ctx,r[13].boxed(api,ctx),r[14].boxed(api,ctx)); }
L20: { r[16]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L21: { ops->list_append(ctx,r[13].boxed(api,ctx),r[16].boxed(api,ctx)); }
L22: { ops->list_append(ctx,r[13].boxed(api,ctx),r[8].boxed(api,ctx)); }
L23: { r[13]=N(r[13].boxed(api,ctx));N argv[] = {r[11],r[12],r[13],N(2ULL)}; r[19]=scope.track(f48(api,ctx,argv,3)); }
L24: { r[20]=scope.track(1ULL); }
L25: { r[21]=scope.track((!equal(api,ctx,r[19],r[20],true)?18ULL:10ULL)); }
L26: { if(!api->truthy(r[21].boxed(api,ctx))) goto L38; }
L27: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L28: { V argv[] = {r[8].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L29: { r[23]=scope.track(api->helper(ctx,11,137ULL,2ULL,2ULL,"V1 GetBuffer fail",nullptr,0)); }
L30: { V argv[] = {r[23].boxed(api,ctx),2ULL}; r[24]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L31: { r[25]=scope.track(1ULL); }
L32: { V argv[]={r[25].value?r[25].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L33: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L34: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L35: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L36: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L37: { scope.result=r[25].value?r[25].value:2ULL;return r[25]; }
L38: { V argv[] = {r[8].boxed(api,ctx),49ULL,2ULL}; r[26]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L39: { r[27]=scope.track(r[26]); }
L40: {  }
L41: { V argv[] = {r[8].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L42: { r[29]=scope.track(1ULL); }
L43: { r[30]=scope.track((equal(api,ctx,r[27],r[29],true)?18ULL:10ULL)); }
L44: { if(!api->truthy(r[30].boxed(api,ctx))) goto L55; }
L45: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L46: { r[31]=scope.track(api->helper(ctx,11,97ULL,2ULL,2ULL,"V2 back null",nullptr,0)); }
L47: { V argv[] = {r[31].boxed(api,ctx),2ULL}; r[32]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L48: { r[33]=scope.track(1ULL); }
L49: { V argv[]={r[33].value?r[33].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L50: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L51: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L52: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L53: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L54: { scope.result=r[33].value?r[33].value:2ULL;return r[33]; }
L55: { r[34]=scope.track(65ULL); }
L56: { V argv[] = {r[34].boxed(api,ctx),2ULL}; r[35]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L57: { r[36]=scope.track(r[35]); }
L58: {  }
L59: { r[37]=scope.track(1ULL); }
L60: { V argv[] = {r[36].boxed(api,ctx),r[37].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L61: { r[39]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L62: { r[40]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_RTV",nullptr,0)); }
L63: { r[41]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L64: { ops->list_append(ctx,r[41].boxed(api,ctx),r[27].boxed(api,ctx)); }
L65: { r[43]=scope.track(1ULL); }
L66: { ops->list_append(ctx,r[41].boxed(api,ctx),r[43].boxed(api,ctx)); }
L67: { ops->list_append(ctx,r[41].boxed(api,ctx),r[36].boxed(api,ctx)); }
L68: { r[41]=N(r[41].boxed(api,ctx));N argv[] = {r[39],r[40],r[41],N(2ULL)}; r[46]=scope.track(f48(api,ctx,argv,3)); }
L69: { r[47]=scope.track(r[46]); }
L70: {  }
L71: { N argv[] = {r[27],N(2ULL)}; r[48]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L72: { r[49]=scope.track(1ULL); }
L73: { r[50]=scope.track((!equal(api,ctx,r[47],r[49],true)?18ULL:10ULL)); }
L74: { if(!api->truthy(r[50].boxed(api,ctx))) goto L88; }
L75: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L76: { V argv[] = {r[36].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L77: { r[52]=scope.track(api->helper(ctx,11,129ULL,2ULL,2ULL,"V3 CreateRTV hr=",nullptr,0)); }
L78: { r[53]=scope.track(api->helper(ctx,6,r[47].boxed(api,ctx),89ULL,2ULL,nullptr,nullptr,0)); }
L79: { r[54]=scope.track(api->helper(ctx,8,r[52].boxed(api,ctx),r[53].boxed(api,ctx),2ULL,nullptr,nullptr,0)); }
L80: { V argv[] = {r[54].boxed(api,ctx),2ULL}; r[55]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L81: { r[56]=scope.track(1ULL); }
L82: { V argv[]={r[56].value?r[56].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L83: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L84: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L85: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L86: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L87: { scope.result=r[56].value?r[56].value:2ULL;return r[56]; }
L88: { V argv[] = {r[36].boxed(api,ctx),49ULL,2ULL}; r[57]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L89: { api->helper(ctx,43,r[57].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0); }
L90: {  }
L91: { V argv[] = {r[36].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L92: { r[59]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L93: { r[60]=scope.track(1ULL); }
L94: { r[61]=scope.track((equal(api,ctx,r[59],r[60],true)?18ULL:10ULL)); }
L95: { if(!api->truthy(r[61].boxed(api,ctx))) goto L106; }
L96: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L97: { r[62]=scope.track(api->helper(ctx,11,89ULL,2ULL,2ULL,"V4 rtv null",nullptr,0)); }
L98: { V argv[] = {r[62].boxed(api,ctx),2ULL}; r[63]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L99: { r[64]=scope.track(1ULL); }
L100: { V argv[]={r[64].value?r[64].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L101: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L102: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L103: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L104: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L105: { scope.result=r[64].value?r[64].value:2ULL;return r[64]; }
L106: { r[65]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L107: { r[66]=scope.track(1ULL); }
L108: { r[67]=scope.track(385ULL); }
L109: { V argv[] = {r[65].boxed(api,ctx),r[66].boxed(api,ctx),r[67].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L110: { r[69]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L111: { r[70]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._width",nullptr,0)); }
L112: { V argv[] = {r[69].boxed(api,ctx),r[70].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L113: { r[72]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L114: { r[73]=scope.track(33ULL); }
L115: { V argv[] = {r[72].boxed(api,ctx),r[73].boxed(api,ctx),2ULL}; r[74]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L116: { r[75]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._height",nullptr,0)); }
L117: { V argv[] = {r[74].boxed(api,ctx),r[75].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L118: { r[77]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L119: { r[78]=scope.track(65ULL); }
L120: { V argv[] = {r[77].boxed(api,ctx),r[78].boxed(api,ctx),2ULL}; r[79]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L121: { r[80]=scope.track(9ULL); }
L122: { V argv[] = {r[79].boxed(api,ctx),r[80].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L123: { r[82]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L124: { r[83]=scope.track(97ULL); }
L125: { V argv[] = {r[82].boxed(api,ctx),r[83].boxed(api,ctx),2ULL}; r[84]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L126: { r[85]=scope.track(9ULL); }
L127: { V argv[] = {r[84].boxed(api,ctx),r[85].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L128: { r[87]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L129: { r[88]=scope.track(129ULL); }
L130: { V argv[] = {r[87].boxed(api,ctx),r[88].boxed(api,ctx),2ULL}; r[89]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L131: { r[90]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_D32_FLOAT",nullptr,0)); }
L132: { V argv[] = {r[89].boxed(api,ctx),r[90].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L133: { r[92]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L134: { r[93]=scope.track(161ULL); }
L135: { V argv[] = {r[92].boxed(api,ctx),r[93].boxed(api,ctx),2ULL}; r[94]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L136: { r[95]=scope.track(9ULL); }
L137: { V argv[] = {r[94].boxed(api,ctx),r[95].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L138: { r[97]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L139: { r[98]=scope.track(225ULL); }
L140: { V argv[] = {r[97].boxed(api,ctx),r[98].boxed(api,ctx),2ULL}; r[99]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L141: { r[100]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.USAGE_DEFAULT",nullptr,0)); }
L142: { V argv[] = {r[99].boxed(api,ctx),r[100].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L143: { r[102]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L144: { r[103]=scope.track(257ULL); }
L145: { V argv[] = {r[102].boxed(api,ctx),r[103].boxed(api,ctx),2ULL}; r[104]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L146: { r[105]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.BIND_DEPTH_STENCIL",nullptr,0)); }
L147: { V argv[] = {r[104].boxed(api,ctx),r[105].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L148: { r[107]=scope.track(65ULL); }
L149: { V argv[] = {r[107].boxed(api,ctx),2ULL}; r[108]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L150: { r[109]=scope.track(r[108]); }
L151: {  }
L152: { r[110]=scope.track(1ULL); }
L153: { V argv[] = {r[109].boxed(api,ctx),r[110].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L154: { r[112]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L155: { r[113]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_TEX2D",nullptr,0)); }
L156: { r[114]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L157: { r[115]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0)); }
L158: { ops->list_append(ctx,r[114].boxed(api,ctx),r[115].boxed(api,ctx)); }
L159: { r[117]=scope.track(1ULL); }
L160: { ops->list_append(ctx,r[114].boxed(api,ctx),r[117].boxed(api,ctx)); }
L161: { ops->list_append(ctx,r[114].boxed(api,ctx),r[109].boxed(api,ctx)); }
L162: { r[114]=N(r[114].boxed(api,ctx));N argv[] = {r[112],r[113],r[114],N(2ULL)}; r[120]=scope.track(f48(api,ctx,argv,3)); }
L163: { r[47]=scope.track(r[120]); }
L164: {  }
L165: { r[121]=scope.track(1ULL); }
L166: { r[122]=scope.track((!equal(api,ctx,r[47],r[121],true)?18ULL:10ULL)); }
L167: { if(!api->truthy(r[122].boxed(api,ctx))) goto L177; }
L168: {  }
L169: { V argv[] = {r[109].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L170: { r[124]=scope.track(1ULL); }
L171: { V argv[]={r[124].value?r[124].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L172: {  }
L173: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L174: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L175: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L176: { scope.result=r[124].value?r[124].value:2ULL;return r[124]; }
L177: { V argv[] = {r[109].boxed(api,ctx),49ULL,2ULL}; r[125]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L178: { api->helper(ctx,43,r[125].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0); }
L179: {  }
L180: { V argv[] = {r[109].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L181: { r[127]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0)); }
L182: { r[128]=scope.track(1ULL); }
L183: { r[129]=scope.track((equal(api,ctx,r[127],r[128],true)?18ULL:10ULL)); }
L184: { if(!api->truthy(r[129].boxed(api,ctx))) goto L193; }
L185: {  }
L186: { r[130]=scope.track(1ULL); }
L187: { V argv[]={r[130].value?r[130].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L188: {  }
L189: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L190: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L191: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L192: { scope.result=r[130].value?r[130].value:2ULL;return r[130]; }
L193: { r[131]=scope.track(65ULL); }
L194: { V argv[] = {r[131].boxed(api,ctx),2ULL}; r[132]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L195: { r[133]=scope.track(r[132]); }
L196: {  }
L197: { r[134]=scope.track(1ULL); }
L198: { V argv[] = {r[133].boxed(api,ctx),r[134].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L199: { r[136]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L200: { r[137]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_DSV",nullptr,0)); }
L201: { r[138]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L202: { r[139]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0)); }
L203: { ops->list_append(ctx,r[138].boxed(api,ctx),r[139].boxed(api,ctx)); }
L204: { r[141]=scope.track(1ULL); }
L205: { ops->list_append(ctx,r[138].boxed(api,ctx),r[141].boxed(api,ctx)); }
L206: { ops->list_append(ctx,r[138].boxed(api,ctx),r[133].boxed(api,ctx)); }
L207: { r[138]=N(r[138].boxed(api,ctx));N argv[] = {r[136],r[137],r[138],N(2ULL)}; r[144]=scope.track(f48(api,ctx,argv,3)); }
L208: { r[47]=scope.track(r[144]); }
L209: {  }
L210: { r[145]=scope.track(1ULL); }
L211: { r[146]=scope.track((!equal(api,ctx,r[47],r[145],true)?18ULL:10ULL)); }
L212: { if(!api->truthy(r[146].boxed(api,ctx))) goto L222; }
L213: {  }
L214: { V argv[] = {r[133].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L215: { r[148]=scope.track(1ULL); }
L216: { V argv[]={r[148].value?r[148].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L217: {  }
L218: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L219: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L220: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L221: { scope.result=r[148].value?r[148].value:2ULL;return r[148]; }
L222: { V argv[] = {r[133].boxed(api,ctx),49ULL,2ULL}; r[149]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L223: { api->helper(ctx,43,r[149].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0); }
L224: {  }
L225: { V argv[] = {r[133].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L226: { r[151]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L227: { r[152]=scope.track(1ULL); }
L228: { r[153]=scope.track((equal(api,ctx,r[151],r[152],true)?18ULL:10ULL)); }
L229: { if(!api->truthy(r[153].boxed(api,ctx))) goto L238; }
L230: {  }
L231: { r[154]=scope.track(1ULL); }
L232: { V argv[]={r[154].value?r[154].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L233: {  }
L234: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L235: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L236: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L237: { scope.result=r[154].value?r[154].value:2ULL;return r[154]; }
L238: { r[155]=scope.track(9ULL); }
L239: { V argv[]={r[155].value?r[155].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L240: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L241: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L242: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L243: { scope.result=r[155].value?r[155].value:2ULL;return r[155]; }
L244: return 2ULL; }
// std.native.d3d11.gpu_buffer_read
static N f39(const Api* api,void* ctx,const N* args,size_t count) {
N r[59]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<59;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[3]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track((equal(api,ctx,r[3],r[4],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[5].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[6]=scope.track(1ULL); }
L9: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L15: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.USAGE_STAGING",nullptr,0)); }
L16: { r[8]=scope.track(1ULL); }
L17: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.CPU_READ",nullptr,0)); }
L18: { r[10]=scope.track(1ULL); }
L19: { r[11]=scope.track(1ULL); }
L20: { r[12]=scope.track(1ULL); }
L21: { N argv[] = {r[2],r[7],r[8],r[9],r[10],r[11],r[12],N(2ULL)}; r[13]=scope.track(f44(api,ctx,argv,7)); }
L22: { r[14]=scope.track(r[13]); }
L23: {  }
L24: { r[15]=scope.track(1ULL); }
L25: { r[16]=scope.track((equal(api,ctx,r[14],r[15],true)?18ULL:10ULL)); }
L26: { if(!api->truthy(r[16].boxed(api,ctx))) goto L35; }
L27: {  }
L28: { r[17]=scope.track(1ULL); }
L29: { V argv[]={r[17].value?r[17].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L30: {  }
L31: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L32: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L33: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L34: { scope.result=r[17].value?r[17].value:2ULL;return r[17]; }
L35: { r[18]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L36: { r[19]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_COPY_RESOURCE",nullptr,0)); }
L37: { r[20]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L38: { ops->list_append(ctx,r[20].boxed(api,ctx),r[14].boxed(api,ctx)); }
L39: { ops->list_append(ctx,r[20].boxed(api,ctx),r[0].boxed(api,ctx)); }
L40: { r[20]=N(r[20].boxed(api,ctx));N argv[] = {r[18],r[19],r[20],N(2ULL)}; r[23]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L41: { r[24]=scope.track(129ULL); }
L42: { V argv[] = {r[24].boxed(api,ctx),2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L43: { r[26]=scope.track(r[25]); }
L44: {  }
L45: { r[27]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L46: { r[28]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_MAP",nullptr,0)); }
L47: { r[29]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L48: { ops->list_append(ctx,r[29].boxed(api,ctx),r[14].boxed(api,ctx)); }
L49: { r[31]=scope.track(1ULL); }
L50: { ops->list_append(ctx,r[29].boxed(api,ctx),r[31].boxed(api,ctx)); }
L51: { r[33]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.MAP_READ",nullptr,0)); }
L52: { ops->list_append(ctx,r[29].boxed(api,ctx),r[33].boxed(api,ctx)); }
L53: { r[35]=scope.track(1ULL); }
L54: { ops->list_append(ctx,r[29].boxed(api,ctx),r[35].boxed(api,ctx)); }
L55: { ops->list_append(ctx,r[29].boxed(api,ctx),r[26].boxed(api,ctx)); }
L56: { r[29]=N(r[29].boxed(api,ctx));N argv[] = {r[27],r[28],r[29],N(2ULL)}; r[38]=scope.track(f48(api,ctx,argv,3)); }
L57: { r[39]=scope.track(r[38]); }
L58: {  }
L59: { r[40]=scope.track(1ULL); }
L60: { r[41]=scope.track((equal(api,ctx,r[39],r[40],true)?18ULL:10ULL)); }
L61: { if(!api->truthy(r[41].boxed(api,ctx))) goto L76; }
L62: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L63: { V argv[] = {r[26].boxed(api,ctx),49ULL,2ULL}; r[42]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L64: { r[43]=scope.track(r[42]); }
L65: {  }
L66: { V argv[] = {r[1].boxed(api,ctx),r[43].boxed(api,ctx),r[2].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_copy",argv,3); }
L67: { r[45]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L68: { r[46]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_UNMAP",nullptr,0)); }
L69: { r[47]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L70: { ops->list_append(ctx,r[47].boxed(api,ctx),r[14].boxed(api,ctx)); }
L71: { r[49]=scope.track(1ULL); }
L72: { ops->list_append(ctx,r[47].boxed(api,ctx),r[49].boxed(api,ctx)); }
L73: { r[47]=N(r[47].boxed(api,ctx));N argv[] = {r[45],r[46],r[47],N(2ULL)}; r[51]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L74: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L75: { goto L76; }
L76: { V argv[] = {r[26].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L77: { N argv[] = {r[14],N(2ULL)}; r[53]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L78: { r[54]=scope.track(1ULL); }
L79: { r[55]=scope.track((equal(api,ctx,r[39],r[54],true)?18ULL:10ULL)); }
L80: { if(!api->truthy(r[55].boxed(api,ctx))) goto L89; }
L81: {  }
L82: { r[56]=scope.track(9ULL); }
L83: { V argv[]={r[56].value?r[56].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L84: {  }
L85: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L86: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L87: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L88: { scope.result=r[56].value?r[56].value:2ULL;return r[56]; }
L89: { r[57]=scope.track(1ULL); }
L90: { V argv[]={r[57].value?r[57].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L91: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L92: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L93: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L94: { scope.result=r[57].value?r[57].value:2ULL;return r[57]; }
L95: return 2ULL; }
// std.native.d3d11.gpu_buffer_write
static N f40(const Api* api,void* ctx,const N* args,size_t count) {
N r[40]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<40;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[3]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track((equal(api,ctx,r[3],r[4],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[5].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[6]=scope.track(1ULL); }
L9: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L15: { r[7]=scope.track(129ULL); }
L16: { V argv[] = {r[7].boxed(api,ctx),2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[9]=scope.track(r[8]); }
L18: {  }
L19: { r[10]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L20: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_MAP",nullptr,0)); }
L21: { r[12]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L22: { ops->list_append(ctx,r[12].boxed(api,ctx),r[0].boxed(api,ctx)); }
L23: { r[14]=scope.track(1ULL); }
L24: { ops->list_append(ctx,r[12].boxed(api,ctx),r[14].boxed(api,ctx)); }
L25: { r[16]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.MAP_WRITE_DISCARD",nullptr,0)); }
L26: { ops->list_append(ctx,r[12].boxed(api,ctx),r[16].boxed(api,ctx)); }
L27: { r[18]=scope.track(1ULL); }
L28: { ops->list_append(ctx,r[12].boxed(api,ctx),r[18].boxed(api,ctx)); }
L29: { ops->list_append(ctx,r[12].boxed(api,ctx),r[9].boxed(api,ctx)); }
L30: { r[12]=N(r[12].boxed(api,ctx));N argv[] = {r[10],r[11],r[12],N(2ULL)}; r[21]=scope.track(f48(api,ctx,argv,3)); }
L31: { r[22]=scope.track(r[21]); }
L32: {  }
L33: { r[23]=scope.track(1ULL); }
L34: { r[24]=scope.track((!equal(api,ctx,r[22],r[23],true)?18ULL:10ULL)); }
L35: { if(!api->truthy(r[24].boxed(api,ctx))) goto L45; }
L36: {  }
L37: { V argv[] = {r[9].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L38: { r[26]=scope.track(1ULL); }
L39: { V argv[]={r[26].value?r[26].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L40: {  }
L41: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L42: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L44: { scope.result=r[26].value?r[26].value:2ULL;return r[26]; }
L45: { V argv[] = {r[9].boxed(api,ctx),49ULL,2ULL}; r[27]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L46: { r[28]=scope.track(r[27]); }
L47: {  }
L48: { V argv[] = {r[28].boxed(api,ctx),r[1].boxed(api,ctx),r[2].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_copy",argv,3); }
L49: { r[30]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L50: { r[31]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_UNMAP",nullptr,0)); }
L51: { r[32]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L52: { ops->list_append(ctx,r[32].boxed(api,ctx),r[0].boxed(api,ctx)); }
L53: { r[34]=scope.track(1ULL); }
L54: { ops->list_append(ctx,r[32].boxed(api,ctx),r[34].boxed(api,ctx)); }
L55: { r[32]=N(r[32].boxed(api,ctx));N argv[] = {r[30],r[31],r[32],N(2ULL)}; r[36]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L56: { V argv[] = {r[9].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L57: { r[38]=scope.track(9ULL); }
L58: { V argv[]={r[38].value?r[38].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L59: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L60: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L61: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L62: { scope.result=r[38].value?r[38].value:2ULL;return r[38]; }
L63: return 2ULL; }
// std.native.d3d11.gpu_srv_create
static N f41(const Api* api,void* ctx,const N* args,size_t count) {
N r[25]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<25;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[1]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[2]=scope.track(1ULL); }
L5: { r[3]=scope.track((equal(api,ctx,r[1],r[2],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[3].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[4]=scope.track(1ULL); }
L9: { V argv[]={r[4].value?r[4].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[4].value?r[4].value:2ULL;return r[4]; }
L15: { r[5]=scope.track(65ULL); }
L16: { V argv[] = {r[5].boxed(api,ctx),2ULL}; r[6]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[7]=scope.track(r[6]); }
L18: {  }
L19: { r[8]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L20: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_SRV",nullptr,0)); }
L21: { r[10]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L22: { ops->list_append(ctx,r[10].boxed(api,ctx),r[0].boxed(api,ctx)); }
L23: { r[12]=scope.track(1ULL); }
L24: { ops->list_append(ctx,r[10].boxed(api,ctx),r[12].boxed(api,ctx)); }
L25: { ops->list_append(ctx,r[10].boxed(api,ctx),r[7].boxed(api,ctx)); }
L26: { r[10]=N(r[10].boxed(api,ctx));N argv[] = {r[8],r[9],r[10],N(2ULL)}; r[15]=scope.track(f48(api,ctx,argv,3)); }
L27: { r[16]=scope.track(r[15]); }
L28: {  }
L29: { r[17]=scope.track(1ULL); }
L30: { r[18]=scope.track((!equal(api,ctx,r[16],r[17],true)?18ULL:10ULL)); }
L31: { if(!api->truthy(r[18].boxed(api,ctx))) goto L41; }
L32: {  }
L33: { V argv[] = {r[7].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L34: { r[20]=scope.track(1ULL); }
L35: { V argv[]={r[20].value?r[20].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L36: {  }
L37: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L38: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L39: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L40: { scope.result=r[20].value?r[20].value:2ULL;return r[20]; }
L41: { V argv[] = {r[7].boxed(api,ctx),49ULL,2ULL}; r[21]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L42: { r[22]=scope.track(r[21]); }
L43: {  }
L44: { V argv[] = {r[7].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L45: { V argv[]={r[22].value?r[22].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L46: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L47: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L48: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L49: { scope.result=r[22].value?r[22].value:2ULL;return r[22]; }
L50: return 2ULL; }
// std.native.d3d11.gpu_uav_create
static N f42(const Api* api,void* ctx,const N* args,size_t count) {
N r[25]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<25;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[1]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[2]=scope.track(1ULL); }
L5: { r[3]=scope.track((equal(api,ctx,r[1],r[2],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[3].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[4]=scope.track(1ULL); }
L9: { V argv[]={r[4].value?r[4].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[4].value?r[4].value:2ULL;return r[4]; }
L15: { r[5]=scope.track(65ULL); }
L16: { V argv[] = {r[5].boxed(api,ctx),2ULL}; r[6]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[7]=scope.track(r[6]); }
L18: {  }
L19: { r[8]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L20: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_UAV",nullptr,0)); }
L21: { r[10]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L22: { ops->list_append(ctx,r[10].boxed(api,ctx),r[0].boxed(api,ctx)); }
L23: { r[12]=scope.track(1ULL); }
L24: { ops->list_append(ctx,r[10].boxed(api,ctx),r[12].boxed(api,ctx)); }
L25: { ops->list_append(ctx,r[10].boxed(api,ctx),r[7].boxed(api,ctx)); }
L26: { r[10]=N(r[10].boxed(api,ctx));N argv[] = {r[8],r[9],r[10],N(2ULL)}; r[15]=scope.track(f48(api,ctx,argv,3)); }
L27: { r[16]=scope.track(r[15]); }
L28: {  }
L29: { r[17]=scope.track(1ULL); }
L30: { r[18]=scope.track((!equal(api,ctx,r[16],r[17],true)?18ULL:10ULL)); }
L31: { if(!api->truthy(r[18].boxed(api,ctx))) goto L41; }
L32: {  }
L33: { V argv[] = {r[7].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L34: { r[20]=scope.track(1ULL); }
L35: { V argv[]={r[20].value?r[20].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L36: {  }
L37: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L38: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L39: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L40: { scope.result=r[20].value?r[20].value:2ULL;return r[20]; }
L41: { V argv[] = {r[7].boxed(api,ctx),49ULL,2ULL}; r[21]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L42: { r[22]=scope.track(r[21]); }
L43: {  }
L44: { V argv[] = {r[7].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L45: { V argv[]={r[22].value?r[22].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L46: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L47: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L48: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L49: { scope.result=r[22].value?r[22].value:2ULL;return r[22]; }
L50: return 2ULL; }
// std.native.d3d11.gpu_uav_create_typed
static N f43(const Api* api,void* ctx,const N* args,size_t count) {
N r[49]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<49;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[3]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track((equal(api,ctx,r[3],r[4],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[5].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[6]=scope.track(1ULL); }
L9: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L15: { r[7]=scope.track(513ULL); }
L16: { V argv[] = {r[7].boxed(api,ctx),2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[9]=scope.track(r[8]); }
L18: {  }
L19: { r[10]=scope.track(1ULL); }
L20: { r[11]=scope.track(513ULL); }
L21: { V argv[] = {r[9].boxed(api,ctx),r[10].boxed(api,ctx),r[11].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L22: { V argv[] = {r[9].boxed(api,ctx),r[1].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L23: { r[14]=scope.track(33ULL); }
L24: { V argv[] = {r[9].boxed(api,ctx),r[14].boxed(api,ctx),2ULL}; r[15]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L25: { r[16]=scope.track(9ULL); }
L26: { V argv[] = {r[15].boxed(api,ctx),r[16].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L27: { r[18]=scope.track(65ULL); }
L28: { V argv[] = {r[9].boxed(api,ctx),r[18].boxed(api,ctx),2ULL}; r[19]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L29: { r[20]=scope.track(1ULL); }
L30: { V argv[] = {r[19].boxed(api,ctx),r[20].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L31: { r[22]=scope.track(97ULL); }
L32: { V argv[] = {r[9].boxed(api,ctx),r[22].boxed(api,ctx),2ULL}; r[23]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L33: { V argv[] = {r[23].boxed(api,ctx),r[2].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L34: { r[25]=scope.track(129ULL); }
L35: { V argv[] = {r[9].boxed(api,ctx),r[25].boxed(api,ctx),2ULL}; r[26]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L36: { r[27]=scope.track(1ULL); }
L37: { V argv[] = {r[26].boxed(api,ctx),r[27].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L38: { r[29]=scope.track(65ULL); }
L39: { V argv[] = {r[29].boxed(api,ctx),2ULL}; r[30]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L40: { r[31]=scope.track(r[30]); }
L41: {  }
L42: { r[32]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L43: { r[33]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_UAV",nullptr,0)); }
L44: { r[34]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L45: { ops->list_append(ctx,r[34].boxed(api,ctx),r[0].boxed(api,ctx)); }
L46: { ops->list_append(ctx,r[34].boxed(api,ctx),r[9].boxed(api,ctx)); }
L47: { ops->list_append(ctx,r[34].boxed(api,ctx),r[31].boxed(api,ctx)); }
L48: { r[34]=N(r[34].boxed(api,ctx));N argv[] = {r[32],r[33],r[34],N(2ULL)}; r[38]=scope.track(f48(api,ctx,argv,3)); }
L49: { r[39]=scope.track(r[38]); }
L50: {  }
L51: { V argv[] = {r[9].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L52: { r[41]=scope.track(1ULL); }
L53: { r[42]=scope.track((!equal(api,ctx,r[39],r[41],true)?18ULL:10ULL)); }
L54: { if(!api->truthy(r[42].boxed(api,ctx))) goto L64; }
L55: {  }
L56: { V argv[] = {r[31].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L57: { r[44]=scope.track(1ULL); }
L58: { V argv[]={r[44].value?r[44].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L59: {  }
L60: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L61: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L62: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L63: { scope.result=r[44].value?r[44].value:2ULL;return r[44]; }
L64: { V argv[] = {r[31].boxed(api,ctx),49ULL,2ULL}; r[45]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L65: { r[46]=scope.track(r[45]); }
L66: {  }
L67: { V argv[] = {r[31].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L68: { V argv[]={r[46].value?r[46].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L69: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L70: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L71: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L72: { scope.result=r[46].value?r[46].value:2ULL;return r[46]; }
L73: return 2ULL; }
// std.native.d3d11.gpu_buffer_create
static N f44(const Api* api,void* ctx,const N* args,size_t count) {
N r[67]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<67;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[7]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[8]=scope.track(1ULL); }
L5: { r[9]=scope.track((equal(api,ctx,r[7],r[8],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[9].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[10]=scope.track(1ULL); }
L9: { V argv[]={r[10].value?r[10].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[10].value?r[10].value:2ULL;return r[10]; }
L15: { r[11]=scope.track(193ULL); }
L16: { V argv[] = {r[11].boxed(api,ctx),2ULL}; r[12]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[13]=scope.track(r[12]); }
L18: {  }
L19: { V argv[] = {r[13].boxed(api,ctx),r[0].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L20: { r[15]=scope.track(33ULL); }
L21: { V argv[] = {r[13].boxed(api,ctx),r[15].boxed(api,ctx),2ULL}; r[16]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L22: { V argv[] = {r[16].boxed(api,ctx),r[1].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L23: { r[18]=scope.track(65ULL); }
L24: { V argv[] = {r[13].boxed(api,ctx),r[18].boxed(api,ctx),2ULL}; r[19]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L25: { V argv[] = {r[19].boxed(api,ctx),r[2].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L26: { r[21]=scope.track(97ULL); }
L27: { V argv[] = {r[13].boxed(api,ctx),r[21].boxed(api,ctx),2ULL}; r[22]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L28: { V argv[] = {r[22].boxed(api,ctx),r[3].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L29: { r[24]=scope.track(129ULL); }
L30: { V argv[] = {r[13].boxed(api,ctx),r[24].boxed(api,ctx),2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L31: { V argv[] = {r[25].boxed(api,ctx),r[4].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L32: { r[27]=scope.track(161ULL); }
L33: { V argv[] = {r[13].boxed(api,ctx),r[27].boxed(api,ctx),2ULL}; r[28]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L34: { V argv[] = {r[28].boxed(api,ctx),r[5].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L35: { r[30]=scope.track(1ULL); }
L36: {  }
L37: { r[31]=scope.track(1ULL); }
L38: { r[32]=scope.track((!equal(api,ctx,r[6],r[31],true)?18ULL:10ULL)); }
L39: { if(!api->truthy(r[32].boxed(api,ctx))) goto L57; }
L40: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L41: { r[33]=scope.track(129ULL); }
L42: { V argv[] = {r[33].boxed(api,ctx),2ULL}; r[34]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L43: { r[30]=scope.track(r[34]); }
L44: {  }
L45: { V argv[] = {r[30].boxed(api,ctx),r[6].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L46: { r[36]=scope.track(65ULL); }
L47: { V argv[] = {r[30].boxed(api,ctx),r[36].boxed(api,ctx),2ULL}; r[37]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L48: { r[38]=scope.track(1ULL); }
L49: { V argv[] = {r[37].boxed(api,ctx),r[38].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L50: { r[40]=scope.track(97ULL); }
L51: { V argv[] = {r[30].boxed(api,ctx),r[40].boxed(api,ctx),2ULL}; r[41]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L52: { r[42]=scope.track(1ULL); }
L53: { V argv[] = {r[41].boxed(api,ctx),r[42].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L54: { V argv[]={r[30].value?r[30].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L55: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L56: { goto L57; }
L57: { r[44]=scope.track(65ULL); }
L58: { V argv[] = {r[44].boxed(api,ctx),2ULL}; r[45]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L59: { r[46]=scope.track(r[45]); }
L60: {  }
L61: { r[47]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L62: { r[48]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_BUFFER",nullptr,0)); }
L63: { r[49]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L64: { ops->list_append(ctx,r[49].boxed(api,ctx),r[13].boxed(api,ctx)); }
L65: { ops->list_append(ctx,r[49].boxed(api,ctx),r[30].boxed(api,ctx)); }
L66: { ops->list_append(ctx,r[49].boxed(api,ctx),r[46].boxed(api,ctx)); }
L67: { r[49]=N(r[49].boxed(api,ctx));N argv[] = {r[47],r[48],r[49],N(2ULL)}; r[53]=scope.track(f48(api,ctx,argv,3)); }
L68: { r[54]=scope.track(r[53]); }
L69: {  }
L70: { V argv[] = {r[13].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L71: { r[56]=scope.track(1ULL); }
L72: { r[57]=scope.track((!equal(api,ctx,r[30],r[56],true)?18ULL:10ULL)); }
L73: { if(!api->truthy(r[57].boxed(api,ctx))) goto L78; }
L74: {  }
L75: { V argv[] = {r[30].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L76: {  }
L77: { goto L78; }
L78: { r[59]=scope.track(1ULL); }
L79: { r[60]=scope.track((!equal(api,ctx,r[54],r[59],true)?18ULL:10ULL)); }
L80: { if(!api->truthy(r[60].boxed(api,ctx))) goto L90; }
L81: {  }
L82: { V argv[] = {r[46].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L83: { r[62]=scope.track(1ULL); }
L84: { V argv[]={r[62].value?r[62].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L85: {  }
L86: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L87: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L88: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L89: { scope.result=r[62].value?r[62].value:2ULL;return r[62]; }
L90: { V argv[] = {r[46].boxed(api,ctx),49ULL,2ULL}; r[63]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L91: { r[64]=scope.track(r[63]); }
L92: {  }
L93: { V argv[] = {r[46].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L94: { V argv[]={r[64].value?r[64].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L95: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L96: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L97: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L98: { scope.result=r[64].value?r[64].value:2ULL;return r[64]; }
L99: return 2ULL; }
// std.native.d3d11.gpu_init
static N f45(const Api* api,void* ctx,const N* args,size_t count) {
N r[102]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<102;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L4: { r[1]=scope.track(1ULL); }
L5: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[2].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[3]=scope.track(9ULL); }
L9: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[3].value?r[3].value:2ULL;return r[3]; }
L15: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._d3d11",nullptr,0)); }
L16: { r[5]=scope.track(1ULL); }
L17: { r[6]=scope.track((equal(api,ctx,r[4],r[5],true)?18ULL:10ULL)); }
L18: { if(!api->truthy(r[6].boxed(api,ctx))) goto L26; }
L19: {  }
L20: { r[7]=scope.track(api->helper(ctx,11,73ULL,2ULL,2ULL,"d3d11.dll",nullptr,0)); }
L21: { V argv[] = {r[7].boxed(api,ctx),2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_lib_load",argv,1)); }
L22: { api->helper(ctx,43,r[8].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._d3d11",nullptr,0); }
L23: {  }
L24: {  }
L25: { goto L26; }
L26: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._d3d11",nullptr,0)); }
L27: { r[10]=scope.track(1ULL); }
L28: { r[11]=scope.track((equal(api,ctx,r[9],r[10],true)?18ULL:10ULL)); }
L29: { if(!api->truthy(r[11].boxed(api,ctx))) goto L38; }
L30: {  }
L31: { r[12]=scope.track(1ULL); }
L32: { V argv[]={r[12].value?r[12].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L33: {  }
L34: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L35: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L36: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L37: { scope.result=r[12].value?r[12].value:2ULL;return r[12]; }
L38: { N argv[] = {N(2ULL)}; r[13]=scope.track(f68(api,ctx,argv,0)); }
L39: { r[14]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._d3d11",nullptr,0)); }
L40: { r[15]=scope.track(api->helper(ctx,11,137ULL,2ULL,2ULL,"D3D11CreateDevice",nullptr,0)); }
L41: { V argv[] = {r[14].boxed(api,ctx),r[15].boxed(api,ctx),2ULL}; r[16]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_lib_symbol",argv,2)); }
L42: { r[17]=scope.track(r[16]); }
L43: {  }
L44: { r[18]=scope.track(1ULL); }
L45: { r[19]=scope.track((equal(api,ctx,r[17],r[18],true)?18ULL:10ULL)); }
L46: { if(!api->truthy(r[19].boxed(api,ctx))) goto L55; }
L47: {  }
L48: { r[20]=scope.track(1ULL); }
L49: { V argv[]={r[20].value?r[20].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L50: {  }
L51: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L52: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L53: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L54: { scope.result=r[20].value?r[20].value:2ULL;return r[20]; }
L55: { r[21]=scope.track(65ULL); }
L56: { V argv[] = {r[21].boxed(api,ctx),2ULL}; r[22]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L57: { r[23]=scope.track(r[22]); }
L58: {  }
L59: { r[24]=scope.track(33ULL); }
L60: { V argv[] = {r[24].boxed(api,ctx),2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L61: { r[26]=scope.track(r[25]); }
L62: {  }
L63: { r[27]=scope.track(65ULL); }
L64: { V argv[] = {r[27].boxed(api,ctx),2ULL}; r[28]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L65: { r[29]=scope.track(r[28]); }
L66: {  }
L67: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L68: { goto L69; }
L69: { r[30]=scope.track(1ULL); }
L70: {  }
L71: { goto L72; }
L72: { r[32]=scope.track(17ULL); }
L73: { r[33]=scope.track((compare(api,ctx,r[30],r[32],true)<0?18ULL:10ULL)); }
L74: { if(!api->truthy(r[33].boxed(api,ctx))) goto L167; }
L75: { V argv[]={73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L76: { r[34]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DRIVER_HARDWARE",nullptr,0)); }
L77: { r[35]=scope.track(r[34]); }
L78: {  }
L79: { r[36]=scope.track(9ULL); }
L80: { r[37]=scope.track((equal(api,ctx,r[30],r[36],true)?18ULL:10ULL)); }
L81: { if(!api->truthy(r[37].boxed(api,ctx))) goto L89; }
L82: {  }
L83: { r[38]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DRIVER_WARP",nullptr,0)); }
L84: { r[35]=scope.track(r[38]); }
L85: {  }
L86: { V argv[]={r[35].value?r[35].boxed(api,ctx):2ULL,73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L87: {  }
L88: { goto L89; }
L89: { r[39]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L90: { r[40]=scope.track(1ULL); }
L91: { ops->list_append(ctx,r[39].boxed(api,ctx),r[40].boxed(api,ctx)); }
L92: { ops->list_append(ctx,r[39].boxed(api,ctx),r[35].boxed(api,ctx)); }
L93: { r[43]=scope.track(1ULL); }
L94: { ops->list_append(ctx,r[39].boxed(api,ctx),r[43].boxed(api,ctx)); }
L95: { r[45]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.FLAG_BGRA_SUPPORT",nullptr,0)); }
L96: { ops->list_append(ctx,r[39].boxed(api,ctx),r[45].boxed(api,ctx)); }
L97: { r[47]=scope.track(1ULL); }
L98: { ops->list_append(ctx,r[39].boxed(api,ctx),r[47].boxed(api,ctx)); }
L99: { r[49]=scope.track(1ULL); }
L100: { ops->list_append(ctx,r[39].boxed(api,ctx),r[49].boxed(api,ctx)); }
L101: { r[51]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.SDK_VERSION",nullptr,0)); }
L102: { ops->list_append(ctx,r[39].boxed(api,ctx),r[51].boxed(api,ctx)); }
L103: { ops->list_append(ctx,r[39].boxed(api,ctx),r[23].boxed(api,ctx)); }
L104: { ops->list_append(ctx,r[39].boxed(api,ctx),r[26].boxed(api,ctx)); }
L105: { ops->list_append(ctx,r[39].boxed(api,ctx),r[29].boxed(api,ctx)); }
L106: { r[56]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L107: { r[57]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L108: { r[58]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L109: { ops->list_append(ctx,r[57].boxed(api,ctx),r[58].boxed(api,ctx)); }
L110: { r[60]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L111: { ops->list_append(ctx,r[57].boxed(api,ctx),r[60].boxed(api,ctx)); }
L112: { r[62]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L113: { ops->list_append(ctx,r[57].boxed(api,ctx),r[62].boxed(api,ctx)); }
L114: { r[64]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L115: { ops->list_append(ctx,r[57].boxed(api,ctx),r[64].boxed(api,ctx)); }
L116: { r[66]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L117: { ops->list_append(ctx,r[57].boxed(api,ctx),r[66].boxed(api,ctx)); }
L118: { r[68]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L119: { ops->list_append(ctx,r[57].boxed(api,ctx),r[68].boxed(api,ctx)); }
L120: { r[70]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L121: { ops->list_append(ctx,r[57].boxed(api,ctx),r[70].boxed(api,ctx)); }
L122: { r[72]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L123: { ops->list_append(ctx,r[57].boxed(api,ctx),r[72].boxed(api,ctx)); }
L124: { r[74]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L125: { ops->list_append(ctx,r[57].boxed(api,ctx),r[74].boxed(api,ctx)); }
L126: { r[76]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L127: { ops->list_append(ctx,r[57].boxed(api,ctx),r[76].boxed(api,ctx)); }
L128: { V argv[] = {r[17].boxed(api,ctx),r[39].boxed(api,ctx),r[56].boxed(api,ctx),r[57].boxed(api,ctx),2ULL}; r[78]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L129: { r[79]=scope.track((r[78].floating() && std::isfinite(r[78].number(api)) && r[78].number(api)>=-0x1p60 && r[78].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[78].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[78].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L130: { r[80]=scope.track(r[79]); }
L131: {  }
L132: { r[81]=scope.track(1ULL); }
L133: { r[82]=scope.track((equal(api,ctx,r[80],r[81],true)?18ULL:10ULL)); }
L134: { if(!api->truthy(r[82].boxed(api,ctx))) goto L144; }
L135: {  }
L136: { V argv[]={r[29].value?r[29].boxed(api,ctx):2ULL,65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L137: { V argv[]={r[26].value?r[26].boxed(api,ctx):2ULL,65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L138: { V argv[]={r[23].value?r[23].boxed(api,ctx):2ULL,65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L139: { V argv[]={r[17].value?r[17].boxed(api,ctx):2ULL,65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L140: { V argv[]={r[30].value?r[30].boxed(api,ctx):2ULL,65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L141: {  }
L142: { V argv[]={73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L143: { goto L167; }
L144: { r[83]=scope.track(9ULL); }
L145: { r[84]=scope.track((equal(api,ctx,r[30],r[83],true)?18ULL:10ULL)); }
L146: { if(!api->truthy(r[84].boxed(api,ctx))) goto L160; }
L147: {  }
L148: { V argv[] = {r[23].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L149: { V argv[] = {r[26].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L150: { V argv[] = {r[29].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L151: { r[88]=scope.track(1ULL); }
L152: { V argv[]={r[88].value?r[88].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L153: {  }
L154: { V argv[]={73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L155: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L156: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L157: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L158: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L159: { scope.result=r[88].value?r[88].value:2ULL;return r[88]; }
L160: { V argv[]={73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L161: { goto L162; }
L162: { r[89]=scope.track(9ULL); }
L163: { r[90]=scope.track(api->integer(api->read_int(r[30].boxed(api,ctx)) + api->read_int(r[89].boxed(api,ctx)))); }
L164: { r[30]=scope.track(r[90]); }
L165: {  }
L166: { goto L72; }
L167: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L168: { V argv[] = {r[23].boxed(api,ctx),49ULL,2ULL}; r[91]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L169: { api->helper(ctx,43,r[91].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._device",nullptr,0); }
L170: {  }
L171: { V argv[] = {r[29].boxed(api,ctx),49ULL,2ULL}; r[92]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L172: { api->helper(ctx,43,r[92].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._context",nullptr,0); }
L173: {  }
L174: { V argv[] = {r[23].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L175: { V argv[] = {r[26].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L176: { V argv[] = {r[29].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L177: { r[96]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L178: { r[97]=scope.track(1ULL); }
L179: { r[98]=scope.track((!equal(api,ctx,r[96],r[97],true)?18ULL:10ULL)); }
L180: { if(!api->truthy(r[98].boxed(api,ctx))) goto L189; }
L181: {  }
L182: { r[99]=scope.track(9ULL); }
L183: { V argv[]={r[99].value?r[99].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L184: {  }
L185: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L186: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L187: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L188: { scope.result=r[99].value?r[99].value:2ULL;return r[99]; }
L189: { r[100]=scope.track(1ULL); }
L190: { V argv[]={r[100].value?r[100].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L191: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L192: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L193: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L194: { scope.result=r[100].value?r[100].value:2ULL;return r[100]; }
L195: return 2ULL; }
// std.native.d3d11.release
static N f46(const Api* api,void* ctx,const N* args,size_t count) {
N r[7]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<7;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[1]=scope.track(1ULL); }
L3: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L4: { if(!api->truthy(r[2].boxed(api,ctx))) goto L11; }
L5: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L6: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_RELEASE",nullptr,0)); }
L7: { r[4]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L8: { r[4]=N(r[4].boxed(api,ctx));N argv[] = {r[0],r[3],r[4],N(2ULL)}; r[5]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L9: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { goto L11; }
L11: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L14: return 2ULL; }
// std.native.d3d11.com_void
static N f47(const Api* api,void* ctx,const N* args,size_t count) {
N r[24]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<24;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { V argv[] = {r[0].boxed(api,ctx),81ULL,2ULL}; r[3]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L4: { r[4]=scope.track(r[3]); }
L5: {  }
L6: { r[5]=scope.track(65ULL); }
L7: { r[6]=scope.track(arithmetic(api,ctx,2,r[1],r[5],true)); }
L8: { V argv[] = {r[4].boxed(api,ctx),r[6].boxed(api,ctx),2ULL}; r[7]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L9: { V argv[] = {r[7].boxed(api,ctx),81ULL,2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L10: { r[9]=scope.track(r[8]); }
L11: {  }
L12: { r[10]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L13: { ops->list_append(ctx,r[10].boxed(api,ctx),r[0].boxed(api,ctx)); }
L14: { r[12]=scope.track(r[10]); }
L15: {  }
L16: { r[13]=scope.track(1ULL); }
L17: {  }
L18: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L19: { goto L20; }
L20: {  }
L21: { r[14]=scope.track(native_length(api,ctx,r[2].boxed(api,ctx))); }
L22: { r[15]=scope.track((compare(api,ctx,r[13],r[14],true)<0?18ULL:10ULL)); }
L23: { if(!api->truthy(r[15].boxed(api,ctx))) goto L36; }
L24: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L25: {  }
L26: {  }
L27: { r[16]=scope.track(ops->sequence_get(r[2].boxed(api,ctx),(r[13].small()?r[13].integer():api->read_int(r[13].boxed(api,ctx))))); }
L28: { ops->list_append(ctx,r[12].boxed(api,ctx),r[16].boxed(api,ctx)); }
L29: { r[18]=scope.track(9ULL); }
L30: { r[19]=scope.track(api->integer(api->read_int(r[13].boxed(api,ctx)) + api->read_int(r[18].boxed(api,ctx)))); }
L31: { r[13]=scope.track(r[19]); }
L32: {  }
L33: { V argv[]={r[13].value?r[13].boxed(api,ctx):2ULL,33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L34: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L35: { goto L20; }
L36: { V argv[]={r[13].value?r[13].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L37: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L38: {  }
L39: { r[20]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_VOID",nullptr,0)); }
L40: { r[21]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L41: { V argv[] = {r[9].boxed(api,ctx),r[12].boxed(api,ctx),r[20].boxed(api,ctx),r[21].boxed(api,ctx),2ULL}; r[22]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L42: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L44: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L45: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L46: return 2ULL; }
// std.native.d3d11.com_i32
static N f48(const Api* api,void* ctx,const N* args,size_t count) {
N r[25]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<25;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { V argv[] = {r[0].boxed(api,ctx),81ULL,2ULL}; r[3]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L4: { r[4]=scope.track(r[3]); }
L5: {  }
L6: { r[5]=scope.track(65ULL); }
L7: { r[6]=scope.track(arithmetic(api,ctx,2,r[1],r[5],true)); }
L8: { V argv[] = {r[4].boxed(api,ctx),r[6].boxed(api,ctx),2ULL}; r[7]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L9: { V argv[] = {r[7].boxed(api,ctx),81ULL,2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L10: { r[9]=scope.track(r[8]); }
L11: {  }
L12: { r[10]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L13: { ops->list_append(ctx,r[10].boxed(api,ctx),r[0].boxed(api,ctx)); }
L14: { r[12]=scope.track(r[10]); }
L15: {  }
L16: { r[13]=scope.track(1ULL); }
L17: {  }
L18: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L19: { goto L20; }
L20: {  }
L21: { r[14]=scope.track(native_length(api,ctx,r[2].boxed(api,ctx))); }
L22: { r[15]=scope.track((compare(api,ctx,r[13],r[14],true)<0?18ULL:10ULL)); }
L23: { if(!api->truthy(r[15].boxed(api,ctx))) goto L36; }
L24: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L25: {  }
L26: {  }
L27: { r[16]=scope.track(ops->sequence_get(r[2].boxed(api,ctx),(r[13].small()?r[13].integer():api->read_int(r[13].boxed(api,ctx))))); }
L28: { ops->list_append(ctx,r[12].boxed(api,ctx),r[16].boxed(api,ctx)); }
L29: { r[18]=scope.track(9ULL); }
L30: { r[19]=scope.track(api->integer(api->read_int(r[13].boxed(api,ctx)) + api->read_int(r[18].boxed(api,ctx)))); }
L31: { r[13]=scope.track(r[19]); }
L32: {  }
L33: { V argv[]={r[13].value?r[13].boxed(api,ctx):2ULL,33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L34: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L35: { goto L20; }
L36: { V argv[]={r[13].value?r[13].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L37: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L38: {  }
L39: { r[20]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L40: { r[21]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L41: { V argv[] = {r[9].boxed(api,ctx),r[12].boxed(api,ctx),r[20].boxed(api,ctx),r[21].boxed(api,ctx),2ULL}; r[22]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L42: { r[23]=scope.track((r[22].floating() && std::isfinite(r[22].number(api)) && r[22].number(api)>=-0x1p60 && r[22].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[22].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[22].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L43: { V argv[]={r[23].value?r[23].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L44: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L45: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L46: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L47: { scope.result=r[23].value?r[23].value:2ULL;return r[23]; }
L48: return 2ULL; }
// std.native.d3d11.com
static N f49(const Api* api,void* ctx,const N* args,size_t count) {
N r[24]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<24;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { V argv[] = {r[0].boxed(api,ctx),81ULL,2ULL}; r[4]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L4: { r[5]=scope.track(r[4]); }
L5: {  }
L6: { r[6]=scope.track(65ULL); }
L7: { r[7]=scope.track(arithmetic(api,ctx,2,r[1],r[6],true)); }
L8: { V argv[] = {r[5].boxed(api,ctx),r[7].boxed(api,ctx),2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L9: { V argv[] = {r[8].boxed(api,ctx),81ULL,2ULL}; r[9]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L10: { r[10]=scope.track(r[9]); }
L11: {  }
L12: { r[11]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L13: { ops->list_append(ctx,r[11].boxed(api,ctx),r[0].boxed(api,ctx)); }
L14: { r[13]=scope.track(r[11]); }
L15: {  }
L16: { r[14]=scope.track(1ULL); }
L17: {  }
L18: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L19: { goto L20; }
L20: {  }
L21: { r[15]=scope.track(native_length(api,ctx,r[2].boxed(api,ctx))); }
L22: { r[16]=scope.track((compare(api,ctx,r[14],r[15],true)<0?18ULL:10ULL)); }
L23: { if(!api->truthy(r[16].boxed(api,ctx))) goto L36; }
L24: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L25: {  }
L26: {  }
L27: { r[17]=scope.track(ops->sequence_get(r[2].boxed(api,ctx),(r[14].small()?r[14].integer():api->read_int(r[14].boxed(api,ctx))))); }
L28: { ops->list_append(ctx,r[13].boxed(api,ctx),r[17].boxed(api,ctx)); }
L29: { r[19]=scope.track(9ULL); }
L30: { r[20]=scope.track(api->integer(api->read_int(r[14].boxed(api,ctx)) + api->read_int(r[19].boxed(api,ctx)))); }
L31: { r[14]=scope.track(r[20]); }
L32: {  }
L33: { V argv[]={r[14].value?r[14].boxed(api,ctx):2ULL,33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L34: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L35: { goto L20; }
L36: { V argv[]={r[14].value?r[14].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L37: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L38: {  }
L39: { r[21]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L40: { V argv[] = {r[10].boxed(api,ctx),r[13].boxed(api,ctx),r[3].boxed(api,ctx),r[21].boxed(api,ctx),2ULL}; r[22]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L41: { V argv[]={r[22].value?r[22].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L42: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L44: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L45: { scope.result=r[22].value?r[22].value:2ULL;return r[22]; }
L46: return 2ULL; }
// std.native.d3d11.gfx_set_blend_state
static N f50(const Api* api,void* ctx,const N* args,size_t count) {
N r[11]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<11;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_OM_BLEND",nullptr,0)); }
L5: { r[3]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[3].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { r[5]=scope.track(1ULL); }
L8: { ops->list_append(ctx,r[3].boxed(api,ctx),r[5].boxed(api,ctx)); }
L9: { r[7]=scope.track(34359738361ULL); }
L10: { ops->list_append(ctx,r[3].boxed(api,ctx),r[7].boxed(api,ctx)); }
L11: { r[3]=N(r[3].boxed(api,ctx));N argv[] = {r[1],r[2],r[3],N(2ULL)}; r[9]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L12: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L15: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L16: return 2ULL; }
// std.native.d3d11.__init__
static N f51(const Api* api,void* ctx,const N* args,size_t count) {
N r[144]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<144;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { N argv[] = {N(2ULL)}; r[0]=scope.track(f78(api,ctx,argv,0)); }
L2: { r[1]=scope.track(9ULL); }
L3: { api->helper(ctx,43,r[1].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DRIVER_HARDWARE",nullptr,0); }
L4: {  }
L5: { r[2]=scope.track(41ULL); }
L6: { api->helper(ctx,43,r[2].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DRIVER_WARP",nullptr,0); }
L7: {  }
L8: { r[3]=scope.track(57ULL); }
L9: { api->helper(ctx,43,r[3].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.SDK_VERSION",nullptr,0); }
L10: {  }
L11: { r[4]=scope.track(1ULL); }
L12: { api->helper(ctx,43,r[4].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.USAGE_DEFAULT",nullptr,0); }
L13: {  }
L14: { r[5]=scope.track(9ULL); }
L15: { api->helper(ctx,43,r[5].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.USAGE_IMMUTABLE",nullptr,0); }
L16: {  }
L17: { r[6]=scope.track(17ULL); }
L18: { api->helper(ctx,43,r[6].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.USAGE_DYNAMIC",nullptr,0); }
L19: {  }
L20: { r[7]=scope.track(25ULL); }
L21: { api->helper(ctx,43,r[7].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.USAGE_STAGING",nullptr,0); }
L22: {  }
L23: { r[8]=scope.track(9ULL); }
L24: { api->helper(ctx,43,r[8].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BIND_VERTEX_BUFFER",nullptr,0); }
L25: {  }
L26: { r[9]=scope.track(17ULL); }
L27: { api->helper(ctx,43,r[9].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BIND_INDEX_BUFFER",nullptr,0); }
L28: {  }
L29: { r[10]=scope.track(33ULL); }
L30: { api->helper(ctx,43,r[10].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BIND_CONSTANT_BUFFER",nullptr,0); }
L31: {  }
L32: { r[11]=scope.track(65ULL); }
L33: { api->helper(ctx,43,r[11].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BIND_SHADER_RESOURCE",nullptr,0); }
L34: {  }
L35: { r[12]=scope.track(257ULL); }
L36: { api->helper(ctx,43,r[12].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BIND_RENDER_TARGET",nullptr,0); }
L37: {  }
L38: { r[13]=scope.track(513ULL); }
L39: { api->helper(ctx,43,r[13].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BIND_DEPTH_STENCIL",nullptr,0); }
L40: {  }
L41: { r[14]=scope.track(1025ULL); }
L42: { api->helper(ctx,43,r[14].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BIND_UNORDERED_ACCESS",nullptr,0); }
L43: {  }
L44: { r[15]=scope.track(524289ULL); }
L45: { api->helper(ctx,43,r[15].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.CPU_WRITE",nullptr,0); }
L46: {  }
L47: { r[16]=scope.track(1048577ULL); }
L48: { api->helper(ctx,43,r[16].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.CPU_READ",nullptr,0); }
L49: {  }
L50: { r[17]=scope.track(513ULL); }
L51: { api->helper(ctx,43,r[17].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.MISC_STRUCTURED",nullptr,0); }
L52: {  }
L53: { r[18]=scope.track(9ULL); }
L54: { api->helper(ctx,43,r[18].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.MAP_READ",nullptr,0); }
L55: {  }
L56: { r[19]=scope.track(17ULL); }
L57: { api->helper(ctx,43,r[19].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.MAP_WRITE",nullptr,0); }
L58: {  }
L59: { r[20]=scope.track(33ULL); }
L60: { api->helper(ctx,43,r[20].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.MAP_WRITE_DISCARD",nullptr,0); }
L61: {  }
L62: { r[21]=scope.track(17ULL); }
L63: { api->helper(ctx,43,r[21].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_RELEASE",nullptr,0); }
L64: {  }
L65: { r[22]=scope.track(25ULL); }
L66: { api->helper(ctx,43,r[22].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_BUFFER",nullptr,0); }
L67: {  }
L68: { r[23]=scope.track(57ULL); }
L69: { api->helper(ctx,43,r[23].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_SRV",nullptr,0); }
L70: {  }
L71: { r[24]=scope.track(65ULL); }
L72: { api->helper(ctx,43,r[24].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_UAV",nullptr,0); }
L73: {  }
L74: { r[25]=scope.track(145ULL); }
L75: { api->helper(ctx,43,r[25].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_CS",nullptr,0); }
L76: {  }
L77: { r[26]=scope.track(113ULL); }
L78: { api->helper(ctx,43,r[26].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_MAP",nullptr,0); }
L79: {  }
L80: { r[27]=scope.track(121ULL); }
L81: { api->helper(ctx,43,r[27].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_UNMAP",nullptr,0); }
L82: {  }
L83: { r[28]=scope.track(329ULL); }
L84: { api->helper(ctx,43,r[28].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_DISPATCH",nullptr,0); }
L85: {  }
L86: { r[29]=scope.track(377ULL); }
L87: { api->helper(ctx,43,r[29].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_COPY_RESOURCE",nullptr,0); }
L88: {  }
L89: { r[30]=scope.track(537ULL); }
L90: { api->helper(ctx,43,r[30].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_CS_SRV",nullptr,0); }
L91: {  }
L92: { r[31]=scope.track(545ULL); }
L93: { api->helper(ctx,43,r[31].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_CS_UAV",nullptr,0); }
L94: {  }
L95: { r[32]=scope.track(553ULL); }
L96: { api->helper(ctx,43,r[32].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_CS_SHADER",nullptr,0); }
L97: {  }
L98: { r[33]=scope.track(9ULL); }
L99: { api->helper(ctx,43,r[33].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.TOPO_POINTLIST",nullptr,0); }
L100: {  }
L101: { r[34]=scope.track(17ULL); }
L102: { api->helper(ctx,43,r[34].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.TOPO_LINELIST",nullptr,0); }
L103: {  }
L104: { r[35]=scope.track(33ULL); }
L105: { api->helper(ctx,43,r[35].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.TOPO_TRIANGLELIST",nullptr,0); }
L106: {  }
L107: { r[36]=scope.track(41ULL); }
L108: { api->helper(ctx,43,r[36].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.TOPO_TRIANGLESTRIP",nullptr,0); }
L109: {  }
L110: { r[37]=scope.track(9ULL); }
L111: { api->helper(ctx,43,r[37].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.CLEAR_DEPTH",nullptr,0); }
L112: {  }
L113: { r[38]=scope.track(17ULL); }
L114: { api->helper(ctx,43,r[38].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.CLEAR_STENCIL",nullptr,0); }
L115: {  }
L116: { r[39]=scope.track(257ULL); }
L117: { api->helper(ctx,43,r[39].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.FLAG_BGRA_SUPPORT",nullptr,0); }
L118: {  }
L119: { r[40]=scope.track(1ULL); }
L120: { api->helper(ctx,43,r[40].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_UNKNOWN",nullptr,0); }
L121: {  }
L122: { r[41]=scope.track(17ULL); }
L123: { api->helper(ctx,43,r[41].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32G32B32A32_FLOAT",nullptr,0); }
L124: {  }
L125: { r[42]=scope.track(49ULL); }
L126: { api->helper(ctx,43,r[42].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32G32B32_FLOAT",nullptr,0); }
L127: {  }
L128: { r[43]=scope.track(81ULL); }
L129: { api->helper(ctx,43,r[43].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R16G16B16A16_FLOAT",nullptr,0); }
L130: {  }
L131: { r[44]=scope.track(129ULL); }
L132: { api->helper(ctx,43,r[44].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32G32_FLOAT",nullptr,0); }
L133: {  }
L134: { r[45]=scope.track(137ULL); }
L135: { api->helper(ctx,43,r[45].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32G32_UINT",nullptr,0); }
L136: {  }
L137: { r[46]=scope.track(225ULL); }
L138: { api->helper(ctx,43,r[46].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R8G8B8A8_UNORM",nullptr,0); }
L139: {  }
L140: { r[47]=scope.track(241ULL); }
L141: { api->helper(ctx,43,r[47].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R8G8B8A8_UINT",nullptr,0); }
L142: {  }
L143: { r[48]=scope.track(329ULL); }
L144: { api->helper(ctx,43,r[48].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32_FLOAT",nullptr,0); }
L145: {  }
L146: { r[49]=scope.track(337ULL); }
L147: { api->helper(ctx,43,r[49].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R32_UINT",nullptr,0); }
L148: {  }
L149: { r[50]=scope.track(321ULL); }
L150: { api->helper(ctx,43,r[50].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_D32_FLOAT",nullptr,0); }
L151: {  }
L152: { r[51]=scope.track(457ULL); }
L153: { api->helper(ctx,43,r[51].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R16_UINT",nullptr,0); }
L154: {  }
L155: { r[52]=scope.track(497ULL); }
L156: { api->helper(ctx,43,r[52].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_R8_UINT",nullptr,0); }
L157: {  }
L158: { r[53]=scope.track(697ULL); }
L159: { api->helper(ctx,43,r[53].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_FMT_B8G8R8A8_UNORM",nullptr,0); }
L160: {  }
L161: { r[54]=scope.track(257ULL); }
L162: { api->helper(ctx,43,r[54].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_USAGE_RENDER_TARGET",nullptr,0); }
L163: {  }
L164: { r[55]=scope.track(33ULL); }
L165: { api->helper(ctx,43,r[55].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_SWAP_FLIP_DISCARD",nullptr,0); }
L166: {  }
L167: { r[56]=scope.track(25ULL); }
L168: { api->helper(ctx,43,r[56].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_ALPHA_IGNORE",nullptr,0); }
L169: {  }
L170: { r[57]=scope.track(1ULL); }
L171: { api->helper(ctx,43,r[57].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_SCALING_STRETCH",nullptr,0); }
L172: {  }
L173: { r[58]=scope.track(9ULL); }
L174: { api->helper(ctx,43,r[58].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_MWA_NO_WINDOW_CHANGES",nullptr,0); }
L175: {  }
L176: { r[59]=scope.track(17ULL); }
L177: { api->helper(ctx,43,r[59].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DXGI_MWA_NO_ALT_ENTER",nullptr,0); }
L178: {  }
L179: { r[60]=scope.track(17ULL); }
L180: { api->helper(ctx,43,r[60].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.FILL_WIREFRAME",nullptr,0); }
L181: {  }
L182: { r[61]=scope.track(25ULL); }
L183: { api->helper(ctx,43,r[61].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.FILL_SOLID",nullptr,0); }
L184: {  }
L185: { r[62]=scope.track(9ULL); }
L186: { api->helper(ctx,43,r[62].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.CULL_NONE",nullptr,0); }
L187: {  }
L188: { r[63]=scope.track(17ULL); }
L189: { api->helper(ctx,43,r[63].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.CULL_FRONT",nullptr,0); }
L190: {  }
L191: { r[64]=scope.track(25ULL); }
L192: { api->helper(ctx,43,r[64].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.CULL_BACK",nullptr,0); }
L193: {  }
L194: { r[65]=scope.track(9ULL); }
L195: { api->helper(ctx,43,r[65].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.COMPARE_NEVER",nullptr,0); }
L196: {  }
L197: { r[66]=scope.track(17ULL); }
L198: { api->helper(ctx,43,r[66].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.COMPARE_LESS",nullptr,0); }
L199: {  }
L200: { r[67]=scope.track(25ULL); }
L201: { api->helper(ctx,43,r[67].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.COMPARE_EQUAL",nullptr,0); }
L202: {  }
L203: { r[68]=scope.track(33ULL); }
L204: { api->helper(ctx,43,r[68].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.COMPARE_LESS_EQUAL",nullptr,0); }
L205: {  }
L206: { r[69]=scope.track(41ULL); }
L207: { api->helper(ctx,43,r[69].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.COMPARE_GREATER",nullptr,0); }
L208: {  }
L209: { r[70]=scope.track(49ULL); }
L210: { api->helper(ctx,43,r[70].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.COMPARE_NOT_EQUAL",nullptr,0); }
L211: {  }
L212: { r[71]=scope.track(57ULL); }
L213: { api->helper(ctx,43,r[71].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.COMPARE_GREATER_EQUAL",nullptr,0); }
L214: {  }
L215: { r[72]=scope.track(65ULL); }
L216: { api->helper(ctx,43,r[72].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.COMPARE_ALWAYS",nullptr,0); }
L217: {  }
L218: { r[73]=scope.track(1ULL); }
L219: { api->helper(ctx,43,r[73].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DEPTH_WRITE_ZERO",nullptr,0); }
L220: {  }
L221: { r[74]=scope.track(9ULL); }
L222: { api->helper(ctx,43,r[74].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.DEPTH_WRITE_ALL",nullptr,0); }
L223: {  }
L224: { r[75]=scope.track(9ULL); }
L225: { api->helper(ctx,43,r[75].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BLEND_OP_ADD",nullptr,0); }
L226: {  }
L227: { r[76]=scope.track(17ULL); }
L228: { api->helper(ctx,43,r[76].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BLEND_ONE",nullptr,0); }
L229: {  }
L230: { r[77]=scope.track(41ULL); }
L231: { api->helper(ctx,43,r[77].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BLEND_SRC_ALPHA",nullptr,0); }
L232: {  }
L233: { r[78]=scope.track(49ULL); }
L234: { api->helper(ctx,43,r[78].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.BLEND_INV_SRC_ALPHA",nullptr,0); }
L235: {  }
L236: { r[79]=scope.track(169ULL); }
L237: { api->helper(ctx,43,r[79].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.FILTER_MIN_MAG_MIP_LINEAR",nullptr,0); }
L238: {  }
L239: { r[80]=scope.track(681ULL); }
L240: { api->helper(ctx,43,r[80].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.FILTER_ANISOTROPIC",nullptr,0); }
L241: {  }
L242: { r[81]=scope.track(9ULL); }
L243: { api->helper(ctx,43,r[81].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.ADDR_WRAP",nullptr,0); }
L244: {  }
L245: { r[82]=scope.track(25ULL); }
L246: { api->helper(ctx,43,r[82].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.ADDR_CLAMP",nullptr,0); }
L247: {  }
L248: { r[83]=scope.track(1ULL); }
L249: { api->helper(ctx,43,r[83].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.INPUT_PER_VERTEX",nullptr,0); }
L250: {  }
L251: { r[84]=scope.track(1ULL); }
L252: { api->helper(ctx,43,r[84].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_QI",nullptr,0); }
L253: {  }
L254: { r[85]=scope.track(41ULL); }
L255: { api->helper(ctx,43,r[85].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_TEX2D",nullptr,0); }
L256: {  }
L257: { r[86]=scope.track(73ULL); }
L258: { api->helper(ctx,43,r[86].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_RTV",nullptr,0); }
L259: {  }
L260: { r[87]=scope.track(81ULL); }
L261: { api->helper(ctx,43,r[87].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_DSV",nullptr,0); }
L262: {  }
L263: { r[88]=scope.track(89ULL); }
L264: { api->helper(ctx,43,r[88].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_IL",nullptr,0); }
L265: {  }
L266: { r[89]=scope.track(97ULL); }
L267: { api->helper(ctx,43,r[89].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_VS",nullptr,0); }
L268: {  }
L269: { r[90]=scope.track(121ULL); }
L270: { api->helper(ctx,43,r[90].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_PS",nullptr,0); }
L271: {  }
L272: { r[91]=scope.track(161ULL); }
L273: { api->helper(ctx,43,r[91].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_BLEND",nullptr,0); }
L274: {  }
L275: { r[92]=scope.track(169ULL); }
L276: { api->helper(ctx,43,r[92].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_DSS",nullptr,0); }
L277: {  }
L278: { r[93]=scope.track(177ULL); }
L279: { api->helper(ctx,43,r[93].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_RS",nullptr,0); }
L280: {  }
L281: { r[94]=scope.track(185ULL); }
L282: { api->helper(ctx,43,r[94].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_SS",nullptr,0); }
L283: {  }
L284: { r[95]=scope.track(57ULL); }
L285: { api->helper(ctx,43,r[95].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_VS_CB",nullptr,0); }
L286: {  }
L287: { r[96]=scope.track(65ULL); }
L288: { api->helper(ctx,43,r[96].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_PS_SRV",nullptr,0); }
L289: {  }
L290: { r[97]=scope.track(73ULL); }
L291: { api->helper(ctx,43,r[97].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_PS_SHADER",nullptr,0); }
L292: {  }
L293: { r[98]=scope.track(81ULL); }
L294: { api->helper(ctx,43,r[98].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_PS_SAMPLERS",nullptr,0); }
L295: {  }
L296: { r[99]=scope.track(89ULL); }
L297: { api->helper(ctx,43,r[99].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_VS_SHADER",nullptr,0); }
L298: {  }
L299: { r[100]=scope.track(97ULL); }
L300: { api->helper(ctx,43,r[100].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_DRAW_INDEXED",nullptr,0); }
L301: {  }
L302: { r[101]=scope.track(105ULL); }
L303: { api->helper(ctx,43,r[101].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_DRAW",nullptr,0); }
L304: {  }
L305: { r[102]=scope.track(129ULL); }
L306: { api->helper(ctx,43,r[102].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_PS_CB",nullptr,0); }
L307: {  }
L308: { r[103]=scope.track(137ULL); }
L309: { api->helper(ctx,43,r[103].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_IA_LAYOUT",nullptr,0); }
L310: {  }
L311: { r[104]=scope.track(145ULL); }
L312: { api->helper(ctx,43,r[104].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_IA_VB",nullptr,0); }
L313: {  }
L314: { r[105]=scope.track(153ULL); }
L315: { api->helper(ctx,43,r[105].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_IA_IB",nullptr,0); }
L316: {  }
L317: { r[106]=scope.track(193ULL); }
L318: { api->helper(ctx,43,r[106].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_IA_TOPO",nullptr,0); }
L319: {  }
L320: { r[107]=scope.track(265ULL); }
L321: { api->helper(ctx,43,r[107].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_OM_RTV",nullptr,0); }
L322: {  }
L323: { r[108]=scope.track(281ULL); }
L324: { api->helper(ctx,43,r[108].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_OM_BLEND",nullptr,0); }
L325: {  }
L326: { r[109]=scope.track(289ULL); }
L327: { api->helper(ctx,43,r[109].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_OM_DEPTH",nullptr,0); }
L328: {  }
L329: { r[110]=scope.track(345ULL); }
L330: { api->helper(ctx,43,r[110].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_RS_STATE",nullptr,0); }
L331: {  }
L332: { r[111]=scope.track(353ULL); }
L333: { api->helper(ctx,43,r[111].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_RS_VP",nullptr,0); }
L334: {  }
L335: { r[112]=scope.track(385ULL); }
L336: { api->helper(ctx,43,r[112].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_UPDATE_SUB",nullptr,0); }
L337: {  }
L338: { r[113]=scope.track(401ULL); }
L339: { api->helper(ctx,43,r[113].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_CLEAR_RTV",nullptr,0); }
L340: {  }
L341: { r[114]=scope.track(425ULL); }
L342: { api->helper(ctx,43,r[114].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_CTX_CLEAR_DSV",nullptr,0); }
L343: {  }
L344: { r[115]=scope.track(57ULL); }
L345: { api->helper(ctx,43,r[115].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DXGI_GET_ADAPTER",nullptr,0); }
L346: {  }
L347: { r[116]=scope.track(49ULL); }
L348: { api->helper(ctx,43,r[116].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_DXGI_GET_PARENT",nullptr,0); }
L349: {  }
L350: { r[117]=scope.track(65ULL); }
L351: { api->helper(ctx,43,r[117].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_FACTORY_MWA",nullptr,0); }
L352: {  }
L353: { r[118]=scope.track(121ULL); }
L354: { api->helper(ctx,43,r[118].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_FACTORY_SWAP_HWND",nullptr,0); }
L355: {  }
L356: { r[119]=scope.track(65ULL); }
L357: { api->helper(ctx,43,r[119].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_SWAP_PRESENT",nullptr,0); }
L358: {  }
L359: { r[120]=scope.track(73ULL); }
L360: { api->helper(ctx,43,r[120].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_SWAP_GET_BUFFER",nullptr,0); }
L361: {  }
L362: { r[121]=scope.track(105ULL); }
L363: { api->helper(ctx,43,r[121].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11.VT_SWAP_RESIZE",nullptr,0); }
L364: {  }
L365: { r[122]=scope.track(1ULL); }
L366: { api->helper(ctx,43,r[122].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._device",nullptr,0); }
L367: {  }
L368: { r[123]=scope.track(1ULL); }
L369: { api->helper(ctx,43,r[123].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._context",nullptr,0); }
L370: {  }
L371: { r[124]=scope.track(1ULL); }
L372: { api->helper(ctx,43,r[124].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._d3d11",nullptr,0); }
L373: {  }
L374: { r[125]=scope.track(1ULL); }
L375: { api->helper(ctx,43,r[125].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0); }
L376: {  }
L377: { r[126]=scope.track(1ULL); }
L378: { api->helper(ctx,43,r[126].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._compile_fn",nullptr,0); }
L379: {  }
L380: { r[127]=scope.track(1ULL); }
L381: { api->helper(ctx,43,r[127].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0); }
L382: {  }
L383: { r[128]=scope.track(1ULL); }
L384: { api->helper(ctx,43,r[128].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._factory",nullptr,0); }
L385: {  }
L386: { r[129]=scope.track(1ULL); }
L387: { api->helper(ctx,43,r[129].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0); }
L388: {  }
L389: { r[130]=scope.track(1ULL); }
L390: { api->helper(ctx,43,r[130].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0); }
L391: {  }
L392: { r[131]=scope.track(1ULL); }
L393: { api->helper(ctx,43,r[131].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0); }
L394: {  }
L395: { r[132]=scope.track(1ULL); }
L396: { api->helper(ctx,43,r[132].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._hwnd",nullptr,0); }
L397: {  }
L398: { r[133]=scope.track(1ULL); }
L399: { api->helper(ctx,43,r[133].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._width",nullptr,0); }
L400: {  }
L401: { r[134]=scope.track(1ULL); }
L402: { api->helper(ctx,43,r[134].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._height",nullptr,0); }
L403: {  }
L404: { r[135]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L405: { r[136]=scope.track(r[135]); }
L406: { api->helper(ctx,43,r[136].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._keep",nullptr,0); }
L407: {  }
L408: { r[137]=scope.track(1ULL); }
L409: { api->helper(ctx,43,r[137].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0); }
L410: {  }
L411: { r[138]=scope.track(1ULL); }
L412: { api->helper(ctx,43,r[138].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0); }
L413: {  }
L414: { r[139]=scope.track(1ULL); }
L415: { api->helper(ctx,43,r[139].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0); }
L416: {  }
L417: { r[140]=scope.track(1ULL); }
L418: { api->helper(ctx,43,r[140].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0); }
L419: {  }
L420: { r[141]=scope.track(1ULL); }
L421: { api->helper(ctx,43,r[141].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._color",nullptr,0); }
L422: {  }
L423: { r[142]=scope.track(1ULL); }
L424: { api->helper(ctx,43,r[142].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._rtv_arr",nullptr,0); }
L425: {  }
L426: { V argv[]={r[0].value?r[0].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L427: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L428: { scope.result=r[0].value?r[0].value:2ULL;return r[0]; }
L429: return 2ULL; }
// std.native.d3d11.gpu_release
static N f52(const Api* api,void* ctx,const N* args,size_t count) {
N r[6]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<6;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(1ULL); }
L4: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L5: { if(!api->truthy(r[2].boxed(api,ctx))) goto L10; }
L6: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L7: { N argv[] = {r[0],N(2ULL)}; r[3]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L8: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L9: { goto L10; }
L10: { r[4]=scope.track(9ULL); }
L11: { V argv[]={r[4].value?r[4].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L12: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L15: { scope.result=r[4].value?r[4].value:2ULL;return r[4]; }
L16: return 2ULL; }
// std.native.d3d11.gfx_ps_set_shader_resource
static N f53(const Api* api,void* ctx,const N* args,size_t count) {
N r[16]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<16;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(65ULL); }
L4: { V argv[] = {r[2].boxed(api,ctx),2ULL}; r[3]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L5: { r[4]=scope.track(r[3]); }
L6: {  }
L7: { V argv[] = {r[4].boxed(api,ctx),r[1].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L8: { r[6]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L9: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_PS_SRV",nullptr,0)); }
L10: { r[8]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L11: { ops->list_append(ctx,r[8].boxed(api,ctx),r[0].boxed(api,ctx)); }
L12: { r[10]=scope.track(9ULL); }
L13: { ops->list_append(ctx,r[8].boxed(api,ctx),r[10].boxed(api,ctx)); }
L14: { ops->list_append(ctx,r[8].boxed(api,ctx),r[4].boxed(api,ctx)); }
L15: { r[8]=N(r[8].boxed(api,ctx));N argv[] = {r[6],r[7],r[8],N(2ULL)}; r[13]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L16: { V argv[] = {r[4].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L17: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L18: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L19: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L20: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L21: return 2ULL; }
// std.native.d3d11.keep
static N f54(const Api* api,void* ctx,const N* args,size_t count) {
N r[4]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<4;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._keep",nullptr,0)); }
L3: {  }
L4: { ops->list_append(ctx,r[1].boxed(api,ctx),r[0].boxed(api,ctx)); }
L5: { V argv[]={r[0].value?r[0].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L6: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L7: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L8: { scope.result=r[0].value?r[0].value:2ULL;return r[0]; }
L9: return 2ULL; }
// std.native.d3d11.ensure_device
static N f55(const Api* api,void* ctx,const N* args,size_t count) {
N r[6]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<6;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L3: { r[1]=scope.track(1ULL); }
L4: { r[2]=scope.track((equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L5: { if(!api->truthy(r[2].boxed(api,ctx))) goto L13; }
L6: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L7: { N argv[] = {N(2ULL)}; r[3]=scope.track(f45(api,ctx,argv,0)); }
L8: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L9: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=r[3].value?r[3].value:2ULL;return r[3]; }
L13: { r[4]=scope.track(9ULL); }
L14: { V argv[]={r[4].value?r[4].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L15: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L16: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L17: { scope.result=r[4].value?r[4].value:2ULL;return r[4]; }
L18: return 2ULL; }
// std.native.d3d11.gfx_set_topology
static N f56(const Api* api,void* ctx,const N* args,size_t count) {
N r[7]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<7;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_IA_TOPO",nullptr,0)); }
L5: { r[3]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[3].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { r[3]=N(r[3].boxed(api,ctx));N argv[] = {r[1],r[2],r[3],N(2ULL)}; r[5]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L8: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L9: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L12: return 2ULL; }
// std.native.d3d11.gfx_set_viewport
static N f57(const Api* api,void* ctx,const N* args,size_t count) {
N r[40]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<40;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
r[0].cache_float(api);
r[1].cache_float(api);
r[2].cache_float(api);
r[3].cache_float(api);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L4: { r[5]=scope.track(1ULL); }
L5: { r[6]=scope.track((equal(api,ctx,r[4],r[5],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[6].boxed(api,ctx))) goto L13; }
L7: {  }
L8: {  }
L9: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L13: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L14: { V argv[] = {r[7].boxed(api,ctx),r[0].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L15: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L16: { r[10]=scope.track(33ULL); }
L17: { V argv[] = {r[9].boxed(api,ctx),r[10].boxed(api,ctx),2ULL}; r[11]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L18: { V argv[] = {r[11].boxed(api,ctx),r[1].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L19: { r[13]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L20: { r[14]=scope.track(65ULL); }
L21: { V argv[] = {r[13].boxed(api,ctx),r[14].boxed(api,ctx),2ULL}; r[15]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L22: { V argv[] = {r[15].boxed(api,ctx),r[2].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L23: { r[17]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L24: { r[18]=scope.track(97ULL); }
L25: { V argv[] = {r[17].boxed(api,ctx),r[18].boxed(api,ctx),2ULL}; r[19]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L26: { V argv[] = {r[19].boxed(api,ctx),r[3].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L27: { r[21]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L28: { r[22]=scope.track(129ULL); }
L29: { V argv[] = {r[21].boxed(api,ctx),r[22].boxed(api,ctx),2ULL}; r[23]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L30: { r[24]=scope.track(real(api,ctx,0x0p+0));r[24].cache_float(api); }
L31: { V argv[] = {r[23].boxed(api,ctx),r[24].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L32: { r[26]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L33: { r[27]=scope.track(161ULL); }
L34: { V argv[] = {r[26].boxed(api,ctx),r[27].boxed(api,ctx),2ULL}; r[28]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L35: { r[29]=scope.track(real(api,ctx,0x1p+0));r[29].cache_float(api); }
L36: { V argv[] = {r[28].boxed(api,ctx),r[29].boxed(api,ctx),65ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L37: { r[31]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L38: { r[32]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_RS_VP",nullptr,0)); }
L39: { r[33]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L40: { r[34]=scope.track(9ULL); }
L41: { ops->list_append(ctx,r[33].boxed(api,ctx),r[34].boxed(api,ctx)); }
L42: { r[36]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0)); }
L43: { ops->list_append(ctx,r[33].boxed(api,ctx),r[36].boxed(api,ctx)); }
L44: { r[33]=N(r[33].boxed(api,ctx));N argv[] = {r[31],r[32],r[33],N(2ULL)}; r[38]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L45: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L46: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L47: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L48: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L49: return 2ULL; }
// std.native.d3d11.gfx_device_ok
static N f58(const Api* api,void* ctx,const N* args,size_t count) {
N r[6]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<6;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L3: { r[1]=scope.track(1ULL); }
L4: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L5: { if(!api->truthy(r[2].boxed(api,ctx))) goto L13; }
L6: {  }
L7: { r[3]=scope.track(9ULL); }
L8: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L9: {  }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=r[3].value?r[3].value:2ULL;return r[3]; }
L13: { r[4]=scope.track(1ULL); }
L14: { V argv[]={r[4].value?r[4].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L15: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L16: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L17: { scope.result=r[4].value?r[4].value:2ULL;return r[4]; }
L18: return 2ULL; }
// std.native.d3d11.p2i
static N f59(const Api* api,void* ctx,const N* args,size_t count) {
N r[9]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<9;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[1]=scope.track(65ULL); }
L4: { V argv[] = {r[1].boxed(api,ctx),2ULL}; r[2]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L5: { r[3]=scope.track(r[2]); }
L6: {  }
L7: { V argv[] = {r[3].boxed(api,ctx),r[0].boxed(api,ctx),81ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L8: { V argv[] = {r[3].boxed(api,ctx),49ULL,2ULL}; r[5]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L9: { r[6]=scope.track(r[5]); }
L10: {  }
L11: { V argv[] = {r[3].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L12: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L13: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L15: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L16: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L17: return 2ULL; }
// std.native.d3d11.gfx_resize
static N f60(const Api* api,void* ctx,const N* args,size_t count) {
N r[48]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<48;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L4: { r[3]=scope.track(1ULL); }
L5: { r[4]=scope.track((equal(api,ctx,r[2],r[3],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[4].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[5]=scope.track(1ULL); }
L9: { V argv[]={r[5].value?r[5].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[5].value?r[5].value:2ULL;return r[5]; }
L15: { r[7]=scope.track(1ULL); }
L16: { r[8]=scope.track((compare(api,ctx,r[0],r[7],true)<=0?18ULL:10ULL)); }
L17: { r[6]=scope.track(r[8]); }
L18: { if(api->truthy(r[8].boxed(api,ctx))) goto L23; }
L19: { r[9]=scope.track(1ULL); }
L20: { r[10]=scope.track((compare(api,ctx,r[1],r[9],true)<=0?18ULL:10ULL)); }
L21: { r[6]=scope.track(r[10]); }
L22: { goto L23; }
L23: { if(!api->truthy(r[6].boxed(api,ctx))) goto L32; }
L24: {  }
L25: { r[11]=scope.track(1ULL); }
L26: { V argv[]={r[11].value?r[11].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L27: {  }
L28: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L29: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L30: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L31: { scope.result=r[11].value?r[11].value:2ULL;return r[11]; }
L32: { r[12]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L33: { r[13]=scope.track(1ULL); }
L34: { r[14]=scope.track((!equal(api,ctx,r[12],r[13],true)?18ULL:10ULL)); }
L35: { if(!api->truthy(r[14].boxed(api,ctx))) goto L44; }
L36: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L37: { r[15]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L38: { N argv[] = {r[15],N(2ULL)}; r[16]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L39: { r[17]=scope.track(1ULL); }
L40: { api->helper(ctx,43,r[17].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0); }
L41: {  }
L42: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { goto L44; }
L44: { r[18]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L45: { r[19]=scope.track(1ULL); }
L46: { r[20]=scope.track((!equal(api,ctx,r[18],r[19],true)?18ULL:10ULL)); }
L47: { if(!api->truthy(r[20].boxed(api,ctx))) goto L56; }
L48: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L49: { r[21]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L50: { N argv[] = {r[21],N(2ULL)}; r[22]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L51: { r[23]=scope.track(1ULL); }
L52: { api->helper(ctx,43,r[23].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0); }
L53: {  }
L54: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L55: { goto L56; }
L56: { r[24]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0)); }
L57: { r[25]=scope.track(1ULL); }
L58: { r[26]=scope.track((!equal(api,ctx,r[24],r[25],true)?18ULL:10ULL)); }
L59: { if(!api->truthy(r[26].boxed(api,ctx))) goto L68; }
L60: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L61: { r[27]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0)); }
L62: { N argv[] = {r[27],N(2ULL)}; r[28]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L63: { r[29]=scope.track(1ULL); }
L64: { api->helper(ctx,43,r[29].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0); }
L65: {  }
L66: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L67: { goto L68; }
L68: { r[30]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L69: { r[31]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_SWAP_RESIZE",nullptr,0)); }
L70: { r[32]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L71: { r[33]=scope.track(1ULL); }
L72: { ops->list_append(ctx,r[32].boxed(api,ctx),r[33].boxed(api,ctx)); }
L73: { ops->list_append(ctx,r[32].boxed(api,ctx),r[0].boxed(api,ctx)); }
L74: { ops->list_append(ctx,r[32].boxed(api,ctx),r[1].boxed(api,ctx)); }
L75: { r[37]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_UNKNOWN",nullptr,0)); }
L76: { ops->list_append(ctx,r[32].boxed(api,ctx),r[37].boxed(api,ctx)); }
L77: { r[39]=scope.track(1ULL); }
L78: { ops->list_append(ctx,r[32].boxed(api,ctx),r[39].boxed(api,ctx)); }
L79: { r[32]=N(r[32].boxed(api,ctx));N argv[] = {r[30],r[31],r[32],N(2ULL)}; r[41]=scope.track(f48(api,ctx,argv,3)); }
L80: { r[42]=scope.track(r[41]); }
L81: {  }
L82: { r[43]=scope.track(1ULL); }
L83: { r[44]=scope.track((!equal(api,ctx,r[42],r[43],true)?18ULL:10ULL)); }
L84: { if(!api->truthy(r[44].boxed(api,ctx))) goto L93; }
L85: {  }
L86: { r[45]=scope.track(1ULL); }
L87: { V argv[]={r[45].value?r[45].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L88: {  }
L89: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L90: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L91: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L92: { scope.result=r[45].value?r[45].value:2ULL;return r[45]; }
L93: { api->helper(ctx,43,r[0].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._width",nullptr,0); }
L94: {  }
L95: { api->helper(ctx,43,r[1].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._height",nullptr,0); }
L96: {  }
L97: { N argv[] = {N(2ULL)}; r[46]=scope.track(f38(api,ctx,argv,0)); }
L98: { V argv[]={r[46].value?r[46].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L99: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L100: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L101: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L102: { scope.result=r[46].value?r[46].value:2ULL;return r[46]; }
L103: return 2ULL; }
// std.native.d3d11.gfx_width
static N f61(const Api* api,void* ctx,const N* args,size_t count) {
N r[2]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<2;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._width",nullptr,0)); }
L3: { V argv[]={r[0].value?r[0].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L4: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L5: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L6: { scope.result=r[0].value?r[0].value:2ULL;return r[0]; }
L7: return 2ULL; }
// std.native.d3d11.gfx_draw
static N f62(const Api* api,void* ctx,const N* args,size_t count) {
N r[9]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<9;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_DRAW",nullptr,0)); }
L5: { r[4]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[4].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { ops->list_append(ctx,r[4].boxed(api,ctx),r[1].boxed(api,ctx)); }
L8: { r[4]=N(r[4].boxed(api,ctx));N argv[] = {r[2],r[3],r[4],N(2ULL)}; r[7]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L9: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L10: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L13: return 2ULL; }
// std.native.d3d11.gfx_blend_state_create
static N f63(const Api* api,void* ctx,const N* args,size_t count) {
N r[31]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<31;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[0]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[1]=scope.track(1ULL); }
L5: { r[2]=scope.track((equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[2].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[3]=scope.track(1ULL); }
L9: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[3].value?r[3].value:2ULL;return r[3]; }
L15: { r[4]=scope.track(2113ULL); }
L16: { V argv[] = {r[4].boxed(api,ctx),2ULL}; r[5]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[6]=scope.track(r[5]); }
L18: {  }
L19: { r[7]=scope.track(1ULL); }
L20: { r[8]=scope.track(2113ULL); }
L21: { V argv[] = {r[6].boxed(api,ctx),r[7].boxed(api,ctx),r[8].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L22: { r[10]=scope.track(65ULL); }
L23: { V argv[] = {r[10].boxed(api,ctx),2ULL}; r[11]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L24: { r[12]=scope.track(r[11]); }
L25: {  }
L26: { r[13]=scope.track(1ULL); }
L27: { V argv[] = {r[12].boxed(api,ctx),r[13].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L28: { r[15]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L29: { r[16]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_BLEND",nullptr,0)); }
L30: { r[17]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L31: { ops->list_append(ctx,r[17].boxed(api,ctx),r[6].boxed(api,ctx)); }
L32: { ops->list_append(ctx,r[17].boxed(api,ctx),r[12].boxed(api,ctx)); }
L33: { r[17]=N(r[17].boxed(api,ctx));N argv[] = {r[15],r[16],r[17],N(2ULL)}; r[20]=scope.track(f48(api,ctx,argv,3)); }
L34: { r[21]=scope.track(r[20]); }
L35: {  }
L36: { V argv[] = {r[6].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L37: { r[23]=scope.track(1ULL); }
L38: { r[24]=scope.track((!equal(api,ctx,r[21],r[23],true)?18ULL:10ULL)); }
L39: { if(!api->truthy(r[24].boxed(api,ctx))) goto L49; }
L40: {  }
L41: { V argv[] = {r[12].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L42: { r[26]=scope.track(1ULL); }
L43: { V argv[]={r[26].value?r[26].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L44: {  }
L45: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L46: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L47: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L48: { scope.result=r[26].value?r[26].value:2ULL;return r[26]; }
L49: { V argv[] = {r[12].boxed(api,ctx),49ULL,2ULL}; r[27]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L50: { r[28]=scope.track(r[27]); }
L51: {  }
L52: { V argv[] = {r[12].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L53: { V argv[]={r[28].value?r[28].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L54: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L55: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L56: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L57: { scope.result=r[28].value?r[28].value:2ULL;return r[28]; }
L58: return 2ULL; }
// std.native.d3d11.gfx_vs_create
static N f64(const Api* api,void* ctx,const N* args,size_t count) {
N r[29]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<29;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[2]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[3]=scope.track(1ULL); }
L5: { r[4]=scope.track((equal(api,ctx,r[2],r[3],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[4].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[5]=scope.track(1ULL); }
L9: { V argv[]={r[5].value?r[5].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[5].value?r[5].value:2ULL;return r[5]; }
L15: { r[6]=scope.track(65ULL); }
L16: { V argv[] = {r[6].boxed(api,ctx),2ULL}; r[7]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { r[8]=scope.track(r[7]); }
L18: {  }
L19: { r[9]=scope.track(1ULL); }
L20: { V argv[] = {r[8].boxed(api,ctx),r[9].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L21: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L22: { r[12]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_VS",nullptr,0)); }
L23: { r[13]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L24: { ops->list_append(ctx,r[13].boxed(api,ctx),r[0].boxed(api,ctx)); }
L25: { ops->list_append(ctx,r[13].boxed(api,ctx),r[1].boxed(api,ctx)); }
L26: { r[16]=scope.track(1ULL); }
L27: { ops->list_append(ctx,r[13].boxed(api,ctx),r[16].boxed(api,ctx)); }
L28: { ops->list_append(ctx,r[13].boxed(api,ctx),r[8].boxed(api,ctx)); }
L29: { r[13]=N(r[13].boxed(api,ctx));N argv[] = {r[11],r[12],r[13],N(2ULL)}; r[19]=scope.track(f48(api,ctx,argv,3)); }
L30: { r[20]=scope.track(r[19]); }
L31: {  }
L32: { r[21]=scope.track(1ULL); }
L33: { r[22]=scope.track((!equal(api,ctx,r[20],r[21],true)?18ULL:10ULL)); }
L34: { if(!api->truthy(r[22].boxed(api,ctx))) goto L44; }
L35: {  }
L36: { V argv[] = {r[8].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L37: { r[24]=scope.track(1ULL); }
L38: { V argv[]={r[24].value?r[24].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L39: {  }
L40: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L41: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L42: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { scope.result=r[24].value?r[24].value:2ULL;return r[24]; }
L44: { V argv[] = {r[8].boxed(api,ctx),49ULL,2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L45: { r[26]=scope.track(r[25]); }
L46: {  }
L47: { V argv[] = {r[8].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L48: { V argv[]={r[26].value?r[26].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L49: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L50: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L51: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L52: { scope.result=r[26].value?r[26].value:2ULL;return r[26]; }
L53: return 2ULL; }
// std.native.d3d11.gfx_detach
static N f65(const Api* api,void* ctx,const N* args,size_t count) {
N r[34]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<34;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L4: { r[1]=scope.track(1ULL); }
L5: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[2].boxed(api,ctx))) goto L15; }
L7: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L8: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0)); }
L9: { N argv[] = {r[3],N(2ULL)}; r[4]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L10: { r[5]=scope.track(1ULL); }
L11: { api->helper(ctx,43,r[5].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._rtv",nullptr,0); }
L12: {  }
L13: { V argv[]={33ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { goto L15; }
L15: { r[6]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L16: { r[7]=scope.track(1ULL); }
L17: { r[8]=scope.track((!equal(api,ctx,r[6],r[7],true)?18ULL:10ULL)); }
L18: { if(!api->truthy(r[8].boxed(api,ctx))) goto L27; }
L19: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L20: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0)); }
L21: { N argv[] = {r[9],N(2ULL)}; r[10]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L22: { r[11]=scope.track(1ULL); }
L23: { api->helper(ctx,43,r[11].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._dsv",nullptr,0); }
L24: {  }
L25: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L26: { goto L27; }
L27: { r[12]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0)); }
L28: { r[13]=scope.track(1ULL); }
L29: { r[14]=scope.track((!equal(api,ctx,r[12],r[13],true)?18ULL:10ULL)); }
L30: { if(!api->truthy(r[14].boxed(api,ctx))) goto L39; }
L31: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L32: { r[15]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0)); }
L33: { N argv[] = {r[15],N(2ULL)}; r[16]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L34: { r[17]=scope.track(1ULL); }
L35: { api->helper(ctx,43,r[17].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._depth_tex",nullptr,0); }
L36: {  }
L37: { V argv[]={49ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L38: { goto L39; }
L39: { r[18]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L40: { r[19]=scope.track(1ULL); }
L41: { r[20]=scope.track((!equal(api,ctx,r[18],r[19],true)?18ULL:10ULL)); }
L42: { if(!api->truthy(r[20].boxed(api,ctx))) goto L51; }
L43: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L44: { r[21]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L45: { N argv[] = {r[21],N(2ULL)}; r[22]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L46: { r[23]=scope.track(1ULL); }
L47: { api->helper(ctx,43,r[23].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0); }
L48: {  }
L49: { V argv[]={57ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L50: { goto L51; }
L51: { r[24]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._factory",nullptr,0)); }
L52: { r[25]=scope.track(1ULL); }
L53: { r[26]=scope.track((!equal(api,ctx,r[24],r[25],true)?18ULL:10ULL)); }
L54: { if(!api->truthy(r[26].boxed(api,ctx))) goto L63; }
L55: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L56: { r[27]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._factory",nullptr,0)); }
L57: { N argv[] = {r[27],N(2ULL)}; r[28]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L58: { r[29]=scope.track(1ULL); }
L59: { api->helper(ctx,43,r[29].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._factory",nullptr,0); }
L60: {  }
L61: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L62: { goto L63; }
L63: { r[30]=scope.track(1ULL); }
L64: { api->helper(ctx,43,r[30].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._hwnd",nullptr,0); }
L65: {  }
L66: { r[31]=scope.track(1ULL); }
L67: { api->helper(ctx,43,r[31].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._width",nullptr,0); }
L68: {  }
L69: { r[32]=scope.track(1ULL); }
L70: { api->helper(ctx,43,r[32].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._height",nullptr,0); }
L71: {  }
L72: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L73: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L74: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L75: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L76: return 2ULL; }
// std.native.d3d11.gpu_shader_create
static N f66(const Api* api,void* ctx,const N* args,size_t count) {
N r[138]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<138;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[1]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[2]=scope.track(1ULL); }
L5: { r[3]=scope.track((equal(api,ctx,r[1],r[2],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[3].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[4]=scope.track(1ULL); }
L9: { V argv[]={r[4].value?r[4].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[4].value?r[4].value:2ULL;return r[4]; }
L15: { r[5]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compile_fn",nullptr,0)); }
L16: { r[6]=scope.track(1ULL); }
L17: { r[7]=scope.track((equal(api,ctx,r[5],r[6],true)?18ULL:10ULL)); }
L18: { if(!api->truthy(r[7].boxed(api,ctx))) goto L27; }
L19: {  }
L20: { r[8]=scope.track(1ULL); }
L21: { V argv[]={r[8].value?r[8].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L22: {  }
L23: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L24: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L25: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L26: { scope.result=r[8].value?r[8].value:2ULL;return r[8]; }
L27: { r[0]=N(r[0].boxed(api,ctx));N argv[] = {r[0],N(2ULL)}; r[9]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L28: { r[10]=scope.track(r[9]); }
L29: {  }
L30: { r[11]=scope.track(api->helper(ctx,11,113ULL,2ULL,2ULL,"lymar_gpu.hlsl",nullptr,0)); }
L31: { r[11]=N(r[11].boxed(api,ctx));N argv[] = {r[11],N(2ULL)}; r[12]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L32: { r[13]=scope.track(r[12]); }
L33: {  }
L34: { r[14]=scope.track(api->helper(ctx,11,33ULL,2ULL,2ULL,"main",nullptr,0)); }
L35: { r[14]=N(r[14].boxed(api,ctx));N argv[] = {r[14],N(2ULL)}; r[15]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L36: { r[16]=scope.track(r[15]); }
L37: {  }
L38: { r[17]=scope.track(api->helper(ctx,11,49ULL,2ULL,2ULL,"cs_5_0",nullptr,0)); }
L39: { r[17]=N(r[17].boxed(api,ctx));N argv[] = {r[17],N(2ULL)}; r[18]=scope.track(N(f79(api,ctx,argv,1).boxed(api,ctx))); }
L40: { r[19]=scope.track(r[18]); }
L41: {  }
L42: { r[20]=scope.track(65ULL); }
L43: { V argv[] = {r[20].boxed(api,ctx),2ULL}; r[21]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L44: { r[22]=scope.track(r[21]); }
L45: {  }
L46: { r[23]=scope.track(65ULL); }
L47: { V argv[] = {r[23].boxed(api,ctx),2ULL}; r[24]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L48: { r[25]=scope.track(r[24]); }
L49: {  }
L50: { r[26]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compile_fn",nullptr,0)); }
L51: { r[27]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L52: {  }
L53: { r[28]=scope.track(ops->frame_get(ctx,r[10].boxed(api,ctx),0,false)); }
L54: { ops->list_append(ctx,r[27].boxed(api,ctx),r[28].boxed(api,ctx)); }
L55: { r[30]=scope.track(native_length(api,ctx,r[0].boxed(api,ctx))); }
L56: { ops->list_append(ctx,r[27].boxed(api,ctx),r[30].boxed(api,ctx)); }
L57: {  }
L58: { r[32]=scope.track(ops->frame_get(ctx,r[13].boxed(api,ctx),0,false)); }
L59: { ops->list_append(ctx,r[27].boxed(api,ctx),r[32].boxed(api,ctx)); }
L60: { r[34]=scope.track(1ULL); }
L61: { ops->list_append(ctx,r[27].boxed(api,ctx),r[34].boxed(api,ctx)); }
L62: { r[36]=scope.track(1ULL); }
L63: { ops->list_append(ctx,r[27].boxed(api,ctx),r[36].boxed(api,ctx)); }
L64: {  }
L65: { r[38]=scope.track(ops->frame_get(ctx,r[16].boxed(api,ctx),0,false)); }
L66: { ops->list_append(ctx,r[27].boxed(api,ctx),r[38].boxed(api,ctx)); }
L67: {  }
L68: { r[40]=scope.track(ops->frame_get(ctx,r[19].boxed(api,ctx),0,false)); }
L69: { ops->list_append(ctx,r[27].boxed(api,ctx),r[40].boxed(api,ctx)); }
L70: { r[42]=scope.track(1ULL); }
L71: { ops->list_append(ctx,r[27].boxed(api,ctx),r[42].boxed(api,ctx)); }
L72: { r[44]=scope.track(1ULL); }
L73: { ops->list_append(ctx,r[27].boxed(api,ctx),r[44].boxed(api,ctx)); }
L74: { ops->list_append(ctx,r[27].boxed(api,ctx),r[22].boxed(api,ctx)); }
L75: { ops->list_append(ctx,r[27].boxed(api,ctx),r[25].boxed(api,ctx)); }
L76: { r[48]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0)); }
L77: { r[49]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L78: { r[50]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L79: { ops->list_append(ctx,r[49].boxed(api,ctx),r[50].boxed(api,ctx)); }
L80: { r[52]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U64",nullptr,0)); }
L81: { ops->list_append(ctx,r[49].boxed(api,ctx),r[52].boxed(api,ctx)); }
L82: { r[54]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L83: { ops->list_append(ctx,r[49].boxed(api,ctx),r[54].boxed(api,ctx)); }
L84: { r[56]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L85: { ops->list_append(ctx,r[49].boxed(api,ctx),r[56].boxed(api,ctx)); }
L86: { r[58]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L87: { ops->list_append(ctx,r[49].boxed(api,ctx),r[58].boxed(api,ctx)); }
L88: { r[60]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L89: { ops->list_append(ctx,r[49].boxed(api,ctx),r[60].boxed(api,ctx)); }
L90: { r[62]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L91: { ops->list_append(ctx,r[49].boxed(api,ctx),r[62].boxed(api,ctx)); }
L92: { r[64]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U32",nullptr,0)); }
L93: { ops->list_append(ctx,r[49].boxed(api,ctx),r[64].boxed(api,ctx)); }
L94: { r[66]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_U32",nullptr,0)); }
L95: { ops->list_append(ctx,r[49].boxed(api,ctx),r[66].boxed(api,ctx)); }
L96: { r[68]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L97: { ops->list_append(ctx,r[49].boxed(api,ctx),r[68].boxed(api,ctx)); }
L98: { r[70]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L99: { ops->list_append(ctx,r[49].boxed(api,ctx),r[70].boxed(api,ctx)); }
L100: { V argv[] = {r[26].boxed(api,ctx),r[27].boxed(api,ctx),r[48].boxed(api,ctx),r[49].boxed(api,ctx),2ULL}; r[72]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L101: { r[73]=scope.track((r[72].floating() && std::isfinite(r[72].number(api)) && r[72].number(api)>=-0x1p60 && r[72].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[72].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[72].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L102: { r[74]=scope.track(r[73]); }
L103: {  }
L104: { r[75]=scope.track(1ULL); }
L105: {  }
L106: { r[76]=scope.track(1ULL); }
L107: { r[77]=scope.track((equal(api,ctx,r[74],r[76],true)?18ULL:10ULL)); }
L108: { if(!api->truthy(r[77].boxed(api,ctx))) goto L116; }
L109: {  }
L110: { V argv[] = {r[22].boxed(api,ctx),49ULL,2ULL}; r[78]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L111: { r[75]=scope.track(r[78]); }
L112: {  }
L113: { V argv[]={r[75].value?r[75].boxed(api,ctx):2ULL,25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L114: {  }
L115: { goto L116; }
L116: { V argv[] = {r[22].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L117: { V argv[] = {r[25].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L118: { r[81]=scope.track(1ULL); }
L119: { r[82]=scope.track((equal(api,ctx,r[75],r[81],true)?18ULL:10ULL)); }
L120: { if(!api->truthy(r[82].boxed(api,ctx))) goto L129; }
L121: {  }
L122: { r[83]=scope.track(1ULL); }
L123: { V argv[]={r[83].value?r[83].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L124: {  }
L125: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L126: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L127: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L128: { scope.result=r[83].value?r[83].value:2ULL;return r[83]; }
L129: { V argv[] = {r[75].boxed(api,ctx),81ULL,2ULL}; r[84]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L130: { r[85]=scope.track(r[84]); }
L131: {  }
L132: { r[86]=scope.track(25ULL); }
L133: { r[87]=scope.track(65ULL); }
L134: { r[88]=scope.track(arithmetic(api,ctx,2,r[86],r[87],true)); }
L135: { V argv[] = {r[85].boxed(api,ctx),r[88].boxed(api,ctx),2ULL}; r[89]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L136: { V argv[] = {r[89].boxed(api,ctx),81ULL,2ULL}; r[90]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L137: { r[91]=scope.track(r[90]); }
L138: {  }
L139: { r[92]=scope.track(33ULL); }
L140: { r[93]=scope.track(65ULL); }
L141: { r[94]=scope.track(arithmetic(api,ctx,2,r[92],r[93],true)); }
L142: { V argv[] = {r[85].boxed(api,ctx),r[94].boxed(api,ctx),2ULL}; r[95]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L143: { V argv[] = {r[95].boxed(api,ctx),81ULL,2ULL}; r[96]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L144: { r[97]=scope.track(r[96]); }
L145: {  }
L146: { r[98]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L147: { ops->list_append(ctx,r[98].boxed(api,ctx),r[75].boxed(api,ctx)); }
L148: { r[100]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I64",nullptr,0)); }
L149: { r[101]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L150: { r[102]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L151: { ops->list_append(ctx,r[101].boxed(api,ctx),r[102].boxed(api,ctx)); }
L152: { V argv[] = {r[91].boxed(api,ctx),r[98].boxed(api,ctx),r[100].boxed(api,ctx),r[101].boxed(api,ctx),2ULL}; r[104]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L153: { r[105]=scope.track((r[104].floating() && std::isfinite(r[104].number(api)) && r[104].number(api)>=-0x1p60 && r[104].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[104].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[104].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L154: { r[106]=scope.track(r[105]); }
L155: {  }
L156: { r[107]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L157: { ops->list_append(ctx,r[107].boxed(api,ctx),r[75].boxed(api,ctx)); }
L158: { r[109]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I64",nullptr,0)); }
L159: { r[110]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L160: { r[111]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L161: { ops->list_append(ctx,r[110].boxed(api,ctx),r[111].boxed(api,ctx)); }
L162: { V argv[] = {r[97].boxed(api,ctx),r[107].boxed(api,ctx),r[109].boxed(api,ctx),r[110].boxed(api,ctx),2ULL}; r[113]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L163: { r[114]=scope.track((r[113].floating() && std::isfinite(r[113].number(api)) && r[113].number(api)>=-0x1p60 && r[113].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[113].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[113].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L164: { r[115]=scope.track(r[114]); }
L165: {  }
L166: { r[116]=scope.track(65ULL); }
L167: { V argv[] = {r[116].boxed(api,ctx),2ULL}; r[117]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L168: { r[118]=scope.track(r[117]); }
L169: {  }
L170: { r[119]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L171: { r[120]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DEVICE_CREATE_CS",nullptr,0)); }
L172: { r[121]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L173: { ops->list_append(ctx,r[121].boxed(api,ctx),r[106].boxed(api,ctx)); }
L174: { ops->list_append(ctx,r[121].boxed(api,ctx),r[115].boxed(api,ctx)); }
L175: { r[124]=scope.track(1ULL); }
L176: { ops->list_append(ctx,r[121].boxed(api,ctx),r[124].boxed(api,ctx)); }
L177: { ops->list_append(ctx,r[121].boxed(api,ctx),r[118].boxed(api,ctx)); }
L178: { r[121]=N(r[121].boxed(api,ctx));N argv[] = {r[119],r[120],r[121],N(2ULL)}; r[127]=scope.track(f48(api,ctx,argv,3)); }
L179: { r[128]=scope.track(r[127]); }
L180: {  }
L181: { N argv[] = {r[75],N(2ULL)}; r[129]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L182: { r[130]=scope.track(1ULL); }
L183: { r[131]=scope.track((!equal(api,ctx,r[128],r[130],true)?18ULL:10ULL)); }
L184: { if(!api->truthy(r[131].boxed(api,ctx))) goto L194; }
L185: {  }
L186: { V argv[] = {r[118].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L187: { r[133]=scope.track(1ULL); }
L188: { V argv[]={r[133].value?r[133].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L189: {  }
L190: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L191: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L192: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L193: { scope.result=r[133].value?r[133].value:2ULL;return r[133]; }
L194: { V argv[] = {r[118].boxed(api,ctx),49ULL,2ULL}; r[134]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L195: { r[135]=scope.track(r[134]); }
L196: {  }
L197: { V argv[] = {r[118].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L198: { V argv[]={r[135].value?r[135].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L199: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L200: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L201: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L202: { scope.result=r[135].value?r[135].value:2ULL;return r[135]; }
L203: return 2ULL; }
// std.native.d3d11.blob_code
static N f67(const Api* api,void* ctx,const N* args,size_t count) {
N r[18]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<18;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { V argv[] = {r[0].boxed(api,ctx),81ULL,2ULL}; r[1]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L4: { r[2]=scope.track(r[1]); }
L5: {  }
L6: { r[3]=scope.track(25ULL); }
L7: { r[4]=scope.track(65ULL); }
L8: { r[5]=scope.track(arithmetic(api,ctx,2,r[3],r[4],true)); }
L9: { V argv[] = {r[2].boxed(api,ctx),r[5].boxed(api,ctx),2ULL}; r[6]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L10: { V argv[] = {r[6].boxed(api,ctx),81ULL,2ULL}; r[7]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L11: { r[8]=scope.track(r[7]); }
L12: {  }
L13: { r[9]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L14: { ops->list_append(ctx,r[9].boxed(api,ctx),r[0].boxed(api,ctx)); }
L15: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I64",nullptr,0)); }
L16: { r[12]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L17: { r[13]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L18: { ops->list_append(ctx,r[12].boxed(api,ctx),r[13].boxed(api,ctx)); }
L19: { V argv[] = {r[8].boxed(api,ctx),r[9].boxed(api,ctx),r[11].boxed(api,ctx),r[12].boxed(api,ctx),2ULL}; r[15]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L20: { r[16]=scope.track((r[15].floating() && std::isfinite(r[15].number(api)) && r[15].number(api)>=-0x1p60 && r[15].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[15].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[15].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L21: { V argv[]={r[16].value?r[16].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L22: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L23: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L24: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L25: { scope.result=r[16].value?r[16].value:2ULL;return r[16]; }
L26: return 2ULL; }
// std.native.d3d11.ensure_compiler
static N f68(const Api* api,void* ctx,const N* args,size_t count) {
N r[32]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<32;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: {  }
L3: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compile_fn",nullptr,0)); }
L4: { r[1]=scope.track(1ULL); }
L5: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[2].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[3]=scope.track(9ULL); }
L9: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: {  }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[3].value?r[3].value:2ULL;return r[3]; }
L15: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0)); }
L16: { r[5]=scope.track(1ULL); }
L17: { r[6]=scope.track((equal(api,ctx,r[4],r[5],true)?18ULL:10ULL)); }
L18: { if(!api->truthy(r[6].boxed(api,ctx))) goto L48; }
L19: {  }
L20: { r[7]=scope.track(api->helper(ctx,11,145ULL,2ULL,2ULL,"d3dcompiler_47.dll",nullptr,0)); }
L21: { V argv[] = {r[7].boxed(api,ctx),2ULL}; r[8]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_lib_load",argv,1)); }
L22: { api->helper(ctx,43,r[8].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0); }
L23: {  }
L24: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0)); }
L25: { r[10]=scope.track(1ULL); }
L26: { r[11]=scope.track((equal(api,ctx,r[9],r[10],true)?18ULL:10ULL)); }
L27: { if(!api->truthy(r[11].boxed(api,ctx))) goto L35; }
L28: {  }
L29: { r[12]=scope.track(api->helper(ctx,11,145ULL,2ULL,2ULL,"d3dcompiler_43.dll",nullptr,0)); }
L30: { V argv[] = {r[12].boxed(api,ctx),2ULL}; r[13]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_lib_load",argv,1)); }
L31: { api->helper(ctx,43,r[13].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0); }
L32: {  }
L33: {  }
L34: { goto L35; }
L35: { r[14]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0)); }
L36: { r[15]=scope.track(1ULL); }
L37: { r[16]=scope.track((equal(api,ctx,r[14],r[15],true)?18ULL:10ULL)); }
L38: { if(!api->truthy(r[16].boxed(api,ctx))) goto L46; }
L39: {  }
L40: { r[17]=scope.track(api->helper(ctx,11,121ULL,2ULL,2ULL,"d3dcompiler.dll",nullptr,0)); }
L41: { V argv[] = {r[17].boxed(api,ctx),2ULL}; r[18]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_lib_load",argv,1)); }
L42: { api->helper(ctx,43,r[18].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0); }
L43: {  }
L44: {  }
L45: { goto L46; }
L46: {  }
L47: { goto L48; }
L48: { r[19]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0)); }
L49: { r[20]=scope.track(1ULL); }
L50: { r[21]=scope.track((equal(api,ctx,r[19],r[20],true)?18ULL:10ULL)); }
L51: { if(!api->truthy(r[21].boxed(api,ctx))) goto L60; }
L52: {  }
L53: { r[22]=scope.track(1ULL); }
L54: { V argv[]={r[22].value?r[22].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L55: {  }
L56: {  }
L57: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L58: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L59: { scope.result=r[22].value?r[22].value:2ULL;return r[22]; }
L60: { r[23]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compiler",nullptr,0)); }
L61: { r[24]=scope.track(api->helper(ctx,11,81ULL,2ULL,2ULL,"D3DCompile",nullptr,0)); }
L62: { V argv[] = {r[23].boxed(api,ctx),r[24].boxed(api,ctx),2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_lib_symbol",argv,2)); }
L63: { api->helper(ctx,43,r[25].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._compile_fn",nullptr,0); }
L64: {  }
L65: { r[26]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._compile_fn",nullptr,0)); }
L66: { r[27]=scope.track(1ULL); }
L67: { r[28]=scope.track((equal(api,ctx,r[26],r[27],true)?18ULL:10ULL)); }
L68: { if(!api->truthy(r[28].boxed(api,ctx))) goto L77; }
L69: {  }
L70: { r[29]=scope.track(1ULL); }
L71: { V argv[]={r[29].value?r[29].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L72: {  }
L73: {  }
L74: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L75: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L76: { scope.result=r[29].value?r[29].value:2ULL;return r[29]; }
L77: { r[30]=scope.track(9ULL); }
L78: { V argv[]={r[30].value?r[30].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L79: {  }
L80: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L81: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L82: { scope.result=r[30].value?r[30].value:2ULL;return r[30]; }
L83: return 2ULL; }
// std.native.d3d11.gfx_ps_set_sampler
static N f69(const Api* api,void* ctx,const N* args,size_t count) {
N r[16]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<16;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(65ULL); }
L4: { V argv[] = {r[2].boxed(api,ctx),2ULL}; r[3]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L5: { r[4]=scope.track(r[3]); }
L6: {  }
L7: { V argv[] = {r[4].boxed(api,ctx),r[1].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L8: { r[6]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L9: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_PS_SAMPLERS",nullptr,0)); }
L10: { r[8]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L11: { ops->list_append(ctx,r[8].boxed(api,ctx),r[0].boxed(api,ctx)); }
L12: { r[10]=scope.track(9ULL); }
L13: { ops->list_append(ctx,r[8].boxed(api,ctx),r[10].boxed(api,ctx)); }
L14: { ops->list_append(ctx,r[8].boxed(api,ctx),r[4].boxed(api,ctx)); }
L15: { r[8]=N(r[8].boxed(api,ctx));N argv[] = {r[6],r[7],r[8],N(2ULL)}; r[13]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L16: { V argv[] = {r[4].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L17: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L18: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L19: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L20: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L21: return 2ULL; }
// std.native.d3d11.gfx_attach
static N f70(const Api* api,void* ctx,const N* args,size_t count) {
N r[199]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<199;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L4: { r[4]=scope.track(1ULL); }
L5: { r[5]=scope.track((!equal(api,ctx,r[3],r[4],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[5].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[6]=scope.track(9ULL); }
L9: { V argv[]={r[6].value?r[6].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[6].value?r[6].value:2ULL;return r[6]; }
L15: { r[8]=scope.track(1ULL); }
L16: { r[9]=scope.track((compare(api,ctx,r[1],r[8],true)<=0?18ULL:10ULL)); }
L17: { r[7]=scope.track(r[9]); }
L18: { if(api->truthy(r[9].boxed(api,ctx))) goto L23; }
L19: { r[10]=scope.track(1ULL); }
L20: { r[11]=scope.track((compare(api,ctx,r[2],r[10],true)<=0?18ULL:10ULL)); }
L21: { r[7]=scope.track(r[11]); }
L22: { goto L23; }
L23: { if(!api->truthy(r[7].boxed(api,ctx))) goto L32; }
L24: {  }
L25: { r[12]=scope.track(1ULL); }
L26: { V argv[]={r[12].value?r[12].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L27: {  }
L28: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L29: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L30: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L31: { scope.result=r[12].value?r[12].value:2ULL;return r[12]; }
L32: { N argv[] = {N(2ULL)}; r[13]=scope.track(f55(api,ctx,argv,0)); }
L33: { r[14]=scope.track(1ULL); }
L34: { r[15]=scope.track((equal(api,ctx,r[13],r[14],true)?18ULL:10ULL)); }
L35: { if(!api->truthy(r[15].boxed(api,ctx))) goto L44; }
L36: {  }
L37: { r[16]=scope.track(1ULL); }
L38: { V argv[]={r[16].value?r[16].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L39: {  }
L40: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L41: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L42: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L43: { scope.result=r[16].value?r[16].value:2ULL;return r[16]; }
L44: { N argv[] = {N(2ULL)}; r[17]=scope.track(f75(api,ctx,argv,0)); }
L45: {  }
L46: { r[18]=scope.track(1ULL); }
L47: { r[19]=scope.track((equal(api,ctx,r[17],r[18],true)?18ULL:10ULL)); }
L48: { if(!api->truthy(r[19].boxed(api,ctx))) goto L57; }
L49: {  }
L50: { r[20]=scope.track(1ULL); }
L51: { V argv[]={r[20].value?r[20].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L52: {  }
L53: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L54: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L55: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L56: { scope.result=r[20].value?r[20].value:2ULL;return r[20]; }
L57: { r[21]=scope.track(11398266833ULL); }
L58: { r[22]=scope.track(39865ULL); }
L59: { r[23]=scope.track(141105ULL); }
L60: { r[24]=scope.track(34028491873ULL); }
L61: { r[25]=scope.track(10305544953ULL); }
L62: { N argv[] = {r[21],r[22],r[23],r[24],r[25],N(2ULL)}; r[26]=scope.track(f76(api,ctx,argv,5)); }
L63: { r[27]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L64: { r[28]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L65: { N argv[] = {r[27],r[28],N(2ULL)}; r[29]=scope.track(f77(api,ctx,argv,2)); }
L66: { r[30]=scope.track(r[29]); }
L67: {  }
L68: { r[31]=scope.track(1ULL); }
L69: { r[32]=scope.track((equal(api,ctx,r[30],r[31],true)?18ULL:10ULL)); }
L70: { if(!api->truthy(r[32].boxed(api,ctx))) goto L81; }
L71: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L72: { r[33]=scope.track(api->helper(ctx,11,177ULL,2ULL,2ULL,"A1 qi IDXGIDevice fail",nullptr,0)); }
L73: { V argv[] = {r[33].boxed(api,ctx),2ULL}; r[34]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L74: { r[35]=scope.track(1ULL); }
L75: { V argv[]={r[35].value?r[35].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L76: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L77: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L78: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L79: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L80: { scope.result=r[35].value?r[35].value:2ULL;return r[35]; }
L81: { r[36]=scope.track(65ULL); }
L82: { V argv[] = {r[36].boxed(api,ctx),2ULL}; r[37]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L83: { r[38]=scope.track(r[37]); }
L84: {  }
L85: { r[39]=scope.track(1ULL); }
L86: { V argv[] = {r[38].boxed(api,ctx),r[39].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L87: { r[41]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DXGI_GET_ADAPTER",nullptr,0)); }
L88: { r[42]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L89: { ops->list_append(ctx,r[42].boxed(api,ctx),r[38].boxed(api,ctx)); }
L90: { r[42]=N(r[42].boxed(api,ctx));N argv[] = {r[30],r[41],r[42],N(2ULL)}; r[44]=scope.track(f48(api,ctx,argv,3)); }
L91: { r[45]=scope.track(1ULL); }
L92: { r[46]=scope.track((!equal(api,ctx,r[44],r[45],true)?18ULL:10ULL)); }
L93: { if(!api->truthy(r[46].boxed(api,ctx))) goto L106; }
L94: { V argv[]={73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L95: { V argv[] = {r[38].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L96: { N argv[] = {r[30],N(2ULL)}; r[48]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L97: { r[49]=scope.track(api->helper(ctx,11,169ULL,2ULL,2ULL,"A2 GetAdapter hr fail",nullptr,0)); }
L98: { V argv[] = {r[49].boxed(api,ctx),2ULL}; r[50]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L99: { r[51]=scope.track(1ULL); }
L100: { V argv[]={r[51].value?r[51].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L101: { V argv[]={73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L102: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L103: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L104: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L105: { scope.result=r[51].value?r[51].value:2ULL;return r[51]; }
L106: { V argv[] = {r[38].boxed(api,ctx),49ULL,2ULL}; r[52]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L107: { r[53]=scope.track(r[52]); }
L108: {  }
L109: { V argv[] = {r[38].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L110: { r[55]=scope.track(1ULL); }
L111: { r[56]=scope.track((equal(api,ctx,r[53],r[55],true)?18ULL:10ULL)); }
L112: { if(!api->truthy(r[56].boxed(api,ctx))) goto L124; }
L113: { V argv[]={81ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L114: { N argv[] = {r[30],N(2ULL)}; r[57]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L115: { r[58]=scope.track(api->helper(ctx,11,121ULL,2ULL,2ULL,"A3 adapter null",nullptr,0)); }
L116: { V argv[] = {r[58].boxed(api,ctx),2ULL}; r[59]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L117: { r[60]=scope.track(1ULL); }
L118: { V argv[]={r[60].value?r[60].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L119: { V argv[]={81ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L120: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L121: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L122: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L123: { scope.result=r[60].value?r[60].value:2ULL;return r[60]; }
L124: { r[61]=scope.track(10842394849ULL); }
L125: { r[62]=scope.track(459665ULL); }
L126: { r[63]=scope.track(156225ULL); }
L127: { r[64]=scope.track(6471124025ULL); }
L128: { r[65]=scope.track(28004431825ULL); }
L129: { N argv[] = {r[61],r[62],r[63],r[64],r[65],N(2ULL)}; r[66]=scope.track(f76(api,ctx,argv,5)); }
L130: { r[67]=scope.track(65ULL); }
L131: { V argv[] = {r[67].boxed(api,ctx),2ULL}; r[68]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L132: { r[69]=scope.track(r[68]); }
L133: {  }
L134: { r[70]=scope.track(1ULL); }
L135: { V argv[] = {r[69].boxed(api,ctx),r[70].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L136: { r[72]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_DXGI_GET_PARENT",nullptr,0)); }
L137: { r[73]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L138: { r[74]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L139: { ops->list_append(ctx,r[73].boxed(api,ctx),r[74].boxed(api,ctx)); }
L140: { ops->list_append(ctx,r[73].boxed(api,ctx),r[69].boxed(api,ctx)); }
L141: { r[73]=N(r[73].boxed(api,ctx));N argv[] = {r[53],r[72],r[73],N(2ULL)}; r[77]=scope.track(f48(api,ctx,argv,3)); }
L142: { r[78]=scope.track(r[77]); }
L143: {  }
L144: { r[79]=scope.track(1ULL); }
L145: { r[80]=scope.track((!equal(api,ctx,r[78],r[79],true)?18ULL:10ULL)); }
L146: { if(!api->truthy(r[80].boxed(api,ctx))) goto L162; }
L147: { V argv[]={89ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L148: { V argv[] = {r[69].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L149: { N argv[] = {r[53],N(2ULL)}; r[82]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L150: { N argv[] = {r[30],N(2ULL)}; r[83]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L151: { r[84]=scope.track(api->helper(ctx,11,129ULL,2ULL,2ULL,"A4 GetParent hr=",nullptr,0)); }
L152: { r[85]=scope.track(api->helper(ctx,6,r[78].boxed(api,ctx),89ULL,2ULL,nullptr,nullptr,0)); }
L153: { r[86]=scope.track(api->helper(ctx,8,r[84].boxed(api,ctx),r[85].boxed(api,ctx),2ULL,nullptr,nullptr,0)); }
L154: { V argv[] = {r[86].boxed(api,ctx),2ULL}; r[87]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L155: { r[88]=scope.track(1ULL); }
L156: { V argv[]={r[88].value?r[88].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L157: { V argv[]={89ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L158: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L159: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L160: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L161: { scope.result=r[88].value?r[88].value:2ULL;return r[88]; }
L162: { V argv[] = {r[69].boxed(api,ctx),49ULL,2ULL}; r[89]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L163: { r[90]=scope.track(r[89]); }
L164: {  }
L165: { V argv[] = {r[69].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L166: { N argv[] = {r[53],N(2ULL)}; r[92]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L167: { N argv[] = {r[30],N(2ULL)}; r[93]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L168: { r[94]=scope.track(1ULL); }
L169: { r[95]=scope.track((equal(api,ctx,r[90],r[94],true)?18ULL:10ULL)); }
L170: { if(!api->truthy(r[95].boxed(api,ctx))) goto L181; }
L171: { V argv[]={97ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L172: { r[96]=scope.track(api->helper(ctx,11,121ULL,2ULL,2ULL,"A5 factory null",nullptr,0)); }
L173: { V argv[] = {r[96].boxed(api,ctx),2ULL}; r[97]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L174: { r[98]=scope.track(1ULL); }
L175: { V argv[]={r[98].value?r[98].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L176: { V argv[]={97ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L177: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L178: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L179: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L180: { scope.result=r[98].value?r[98].value:2ULL;return r[98]; }
L181: { r[99]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L182: { r[100]=scope.track(1ULL); }
L183: { r[101]=scope.track(385ULL); }
L184: { V argv[] = {r[99].boxed(api,ctx),r[100].boxed(api,ctx),r[101].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_fill",argv,3); }
L185: { r[103]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L186: { V argv[] = {r[103].boxed(api,ctx),r[1].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L187: { r[105]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L188: { r[106]=scope.track(33ULL); }
L189: { V argv[] = {r[105].boxed(api,ctx),r[106].boxed(api,ctx),2ULL}; r[107]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L190: { V argv[] = {r[107].boxed(api,ctx),r[2].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L191: { r[109]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L192: { r[110]=scope.track(65ULL); }
L193: { V argv[] = {r[109].boxed(api,ctx),r[110].boxed(api,ctx),2ULL}; r[111]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L194: { r[112]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_FMT_B8G8R8A8_UNORM",nullptr,0)); }
L195: { V argv[] = {r[111].boxed(api,ctx),r[112].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L196: { r[114]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L197: { r[115]=scope.track(129ULL); }
L198: { V argv[] = {r[114].boxed(api,ctx),r[115].boxed(api,ctx),2ULL}; r[116]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L199: { r[117]=scope.track(9ULL); }
L200: { V argv[] = {r[116].boxed(api,ctx),r[117].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L201: { r[119]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L202: { r[120]=scope.track(193ULL); }
L203: { V argv[] = {r[119].boxed(api,ctx),r[120].boxed(api,ctx),2ULL}; r[121]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L204: { r[122]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_USAGE_RENDER_TARGET",nullptr,0)); }
L205: { V argv[] = {r[121].boxed(api,ctx),r[122].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L206: { r[124]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L207: { r[125]=scope.track(225ULL); }
L208: { V argv[] = {r[124].boxed(api,ctx),r[125].boxed(api,ctx),2ULL}; r[126]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L209: { r[127]=scope.track(17ULL); }
L210: { V argv[] = {r[126].boxed(api,ctx),r[127].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L211: { r[129]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L212: { r[130]=scope.track(257ULL); }
L213: { V argv[] = {r[129].boxed(api,ctx),r[130].boxed(api,ctx),2ULL}; r[131]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L214: { r[132]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_SCALING_STRETCH",nullptr,0)); }
L215: { V argv[] = {r[131].boxed(api,ctx),r[132].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L216: { r[134]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L217: { r[135]=scope.track(289ULL); }
L218: { V argv[] = {r[134].boxed(api,ctx),r[135].boxed(api,ctx),2ULL}; r[136]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L219: { r[137]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_SWAP_FLIP_DISCARD",nullptr,0)); }
L220: { V argv[] = {r[136].boxed(api,ctx),r[137].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L221: { r[139]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L222: { r[140]=scope.track(321ULL); }
L223: { V argv[] = {r[139].boxed(api,ctx),r[140].boxed(api,ctx),2ULL}; r[141]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L224: { r[142]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_ALPHA_IGNORE",nullptr,0)); }
L225: { V argv[] = {r[141].boxed(api,ctx),r[142].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L226: { r[144]=scope.track(65ULL); }
L227: { V argv[] = {r[144].boxed(api,ctx),2ULL}; r[145]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L228: { r[146]=scope.track(r[145]); }
L229: {  }
L230: { r[147]=scope.track(1ULL); }
L231: { V argv[] = {r[146].boxed(api,ctx),r[147].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L232: { r[149]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_FACTORY_SWAP_HWND",nullptr,0)); }
L233: { r[150]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L234: { r[151]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._device",nullptr,0)); }
L235: { ops->list_append(ctx,r[150].boxed(api,ctx),r[151].boxed(api,ctx)); }
L236: { ops->list_append(ctx,r[150].boxed(api,ctx),r[0].boxed(api,ctx)); }
L237: { r[154]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0)); }
L238: { ops->list_append(ctx,r[150].boxed(api,ctx),r[154].boxed(api,ctx)); }
L239: { r[156]=scope.track(1ULL); }
L240: { ops->list_append(ctx,r[150].boxed(api,ctx),r[156].boxed(api,ctx)); }
L241: { r[158]=scope.track(1ULL); }
L242: { ops->list_append(ctx,r[150].boxed(api,ctx),r[158].boxed(api,ctx)); }
L243: { ops->list_append(ctx,r[150].boxed(api,ctx),r[146].boxed(api,ctx)); }
L244: { r[150]=N(r[150].boxed(api,ctx));N argv[] = {r[90],r[149],r[150],N(2ULL)}; r[161]=scope.track(f48(api,ctx,argv,3)); }
L245: { r[162]=scope.track(r[161]); }
L246: {  }
L247: { r[163]=scope.track(1ULL); }
L248: { r[164]=scope.track((!equal(api,ctx,r[162],r[163],true)?18ULL:10ULL)); }
L249: { if(!api->truthy(r[164].boxed(api,ctx))) goto L264; }
L250: { V argv[]={105ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L251: { V argv[] = {r[146].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L252: { N argv[] = {r[90],N(2ULL)}; r[166]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L253: { r[167]=scope.track(api->helper(ctx,11,233ULL,2ULL,2ULL,"A6 CreateSwapChainForHwnd hr=",nullptr,0)); }
L254: { r[168]=scope.track(api->helper(ctx,6,r[162].boxed(api,ctx),89ULL,2ULL,nullptr,nullptr,0)); }
L255: { r[169]=scope.track(api->helper(ctx,8,r[167].boxed(api,ctx),r[168].boxed(api,ctx),2ULL,nullptr,nullptr,0)); }
L256: { V argv[] = {r[169].boxed(api,ctx),2ULL}; r[170]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L257: { r[171]=scope.track(1ULL); }
L258: { V argv[]={r[171].value?r[171].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L259: { V argv[]={105ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L260: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L261: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L262: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L263: { scope.result=r[171].value?r[171].value:2ULL;return r[171]; }
L264: { V argv[] = {r[146].boxed(api,ctx),49ULL,2ULL}; r[172]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L265: { api->helper(ctx,43,r[172].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0); }
L266: {  }
L267: { V argv[] = {r[146].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L268: { r[174]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._swapchain",nullptr,0)); }
L269: { r[175]=scope.track(1ULL); }
L270: { r[176]=scope.track((equal(api,ctx,r[174],r[175],true)?18ULL:10ULL)); }
L271: { if(!api->truthy(r[176].boxed(api,ctx))) goto L283; }
L272: { V argv[]={113ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L273: { N argv[] = {r[90],N(2ULL)}; r[177]=scope.track(N(f46(api,ctx,argv,1).boxed(api,ctx))); }
L274: { r[178]=scope.track(api->helper(ctx,11,137ULL,2ULL,2ULL,"A7 swapchain null",nullptr,0)); }
L275: { V argv[] = {r[178].boxed(api,ctx),2ULL}; r[179]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L276: { r[180]=scope.track(1ULL); }
L277: { V argv[]={r[180].value?r[180].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L278: { V argv[]={113ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L279: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L280: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L281: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L282: { scope.result=r[180].value?r[180].value:2ULL;return r[180]; }
L283: { api->helper(ctx,43,r[90].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._factory",nullptr,0); }
L284: {  }
L285: { api->helper(ctx,43,r[0].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._hwnd",nullptr,0); }
L286: {  }
L287: { api->helper(ctx,43,r[1].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._width",nullptr,0); }
L288: {  }
L289: { api->helper(ctx,43,r[2].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._height",nullptr,0); }
L290: {  }
L291: { r[181]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._factory",nullptr,0)); }
L292: { r[182]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_FACTORY_MWA",nullptr,0)); }
L293: { r[183]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L294: { ops->list_append(ctx,r[183].boxed(api,ctx),r[0].boxed(api,ctx)); }
L295: { r[185]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_MWA_NO_WINDOW_CHANGES",nullptr,0)); }
L296: { r[186]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.DXGI_MWA_NO_ALT_ENTER",nullptr,0)); }
L297: { r[187]=scope.track(api->integer(api->read_int(r[185].boxed(api,ctx))|api->read_int(r[186].boxed(api,ctx)))); }
L298: { ops->list_append(ctx,r[183].boxed(api,ctx),r[187].boxed(api,ctx)); }
L299: { r[183]=N(r[183].boxed(api,ctx));N argv[] = {r[181],r[182],r[183],N(2ULL)}; r[189]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L300: { N argv[] = {N(2ULL)}; r[190]=scope.track(f38(api,ctx,argv,0)); }
L301: { r[191]=scope.track(1ULL); }
L302: { r[192]=scope.track((equal(api,ctx,r[190],r[191],true)?18ULL:10ULL)); }
L303: { if(!api->truthy(r[192].boxed(api,ctx))) goto L315; }
L304: { V argv[]={121ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L305: { r[193]=scope.track(api->helper(ctx,11,105ULL,2ULL,2ULL,"A8 views fail",nullptr,0)); }
L306: { V argv[] = {r[193].boxed(api,ctx),2ULL}; r[194]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"print",argv,1)); }
L307: { N argv[] = {N(2ULL)}; r[195]=scope.track(N(f65(api,ctx,argv,0).boxed(api,ctx))); }
L308: { r[196]=scope.track(1ULL); }
L309: { V argv[]={r[196].value?r[196].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L310: { V argv[]={121ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L311: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L312: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L313: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L314: { scope.result=r[196].value?r[196].value:2ULL;return r[196]; }
L315: { r[197]=scope.track(9ULL); }
L316: { V argv[]={r[197].value?r[197].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L317: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L318: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L319: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L320: { scope.result=r[197].value?r[197].value:2ULL;return r[197]; }
L321: return 2ULL; }
// std.native.d3d11.blob_size
static N f71(const Api* api,void* ctx,const N* args,size_t count) {
N r[18]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<18;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { V argv[] = {r[0].boxed(api,ctx),81ULL,2ULL}; r[1]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L4: { r[2]=scope.track(r[1]); }
L5: {  }
L6: { r[3]=scope.track(33ULL); }
L7: { r[4]=scope.track(65ULL); }
L8: { r[5]=scope.track(arithmetic(api,ctx,2,r[3],r[4],true)); }
L9: { V argv[] = {r[2].boxed(api,ctx),r[5].boxed(api,ctx),2ULL}; r[6]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L10: { V argv[] = {r[6].boxed(api,ctx),81ULL,2ULL}; r[7]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L11: { r[8]=scope.track(r[7]); }
L12: {  }
L13: { r[9]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L14: { ops->list_append(ctx,r[9].boxed(api,ctx),r[0].boxed(api,ctx)); }
L15: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_I64",nullptr,0)); }
L16: { r[12]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L17: { r[13]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0)); }
L18: { ops->list_append(ctx,r[12].boxed(api,ctx),r[13].boxed(api,ctx)); }
L19: { V argv[] = {r[8].boxed(api,ctx),r[9].boxed(api,ctx),r[11].boxed(api,ctx),r[12].boxed(api,ctx),2ULL}; r[15]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_foreign_call",argv,4)); }
L20: { r[16]=scope.track((r[15].floating() && std::isfinite(r[15].number(api)) && r[15].number(api)>=-0x1p60 && r[15].number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(r[15].number(api)))<<3)|1ULL):N(api->helper(ctx,6,r[15].boxed(api,ctx),49ULL,2ULL,nullptr,nullptr,0)))); }
L21: { V argv[]={r[16].value?r[16].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L22: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L23: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L24: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L25: { scope.result=r[16].value?r[16].value:2ULL;return r[16]; }
L26: return 2ULL; }
// std.native.d3d11.gfx_buffer_update
static N f72(const Api* api,void* ctx,const N* args,size_t count) {
N r[23]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<23;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[4]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[5]=scope.track(1ULL); }
L5: { r[6]=scope.track((equal(api,ctx,r[4],r[5],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[6].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[7]=scope.track(1ULL); }
L9: { V argv[]={r[7].value?r[7].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[7].value?r[7].value:2ULL;return r[7]; }
L15: { r[8]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L16: { r[9]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_UPDATE_SUB",nullptr,0)); }
L17: { r[10]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L18: { ops->list_append(ctx,r[10].boxed(api,ctx),r[0].boxed(api,ctx)); }
L19: { r[12]=scope.track(1ULL); }
L20: { ops->list_append(ctx,r[10].boxed(api,ctx),r[12].boxed(api,ctx)); }
L21: { r[14]=scope.track(1ULL); }
L22: { ops->list_append(ctx,r[10].boxed(api,ctx),r[14].boxed(api,ctx)); }
L23: { ops->list_append(ctx,r[10].boxed(api,ctx),r[1].boxed(api,ctx)); }
L24: { ops->list_append(ctx,r[10].boxed(api,ctx),r[3].boxed(api,ctx)); }
L25: { r[18]=scope.track(1ULL); }
L26: { ops->list_append(ctx,r[10].boxed(api,ctx),r[18].boxed(api,ctx)); }
L27: { r[10]=N(r[10].boxed(api,ctx));N argv[] = {r[8],r[9],r[10],N(2ULL)}; r[20]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L28: { r[21]=scope.track(9ULL); }
L29: { V argv[]={r[21].value?r[21].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L30: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L31: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L32: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L33: { scope.result=r[21].value?r[21].value:2ULL;return r[21]; }
L34: return 2ULL; }
// std.native.d3d11.gfx_set_index_buffer
static N f73(const Api* api,void* ctx,const N* args,size_t count) {
N r[11]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<11;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[3]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L4: { r[4]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_IA_IB",nullptr,0)); }
L5: { r[5]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L6: { ops->list_append(ctx,r[5].boxed(api,ctx),r[0].boxed(api,ctx)); }
L7: { ops->list_append(ctx,r[5].boxed(api,ctx),r[1].boxed(api,ctx)); }
L8: { ops->list_append(ctx,r[5].boxed(api,ctx),r[2].boxed(api,ctx)); }
L9: { r[5]=N(r[5].boxed(api,ctx));N argv[] = {r[3],r[4],r[5],N(2ULL)}; r[9]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L10: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L11: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { scope.result=N(2ULL).value?N(2ULL).value:2ULL;return N(2ULL); }
L14: return 2ULL; }
// std.native.d3d11.gpu_dispatch
static N f74(const Api* api,void* ctx,const N* args,size_t count) {
N r[106]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<106;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { N argv[] = {N(2ULL)}; r[6]=scope.track(f55(api,ctx,argv,0)); }
L4: { r[7]=scope.track(1ULL); }
L5: { r[8]=scope.track((equal(api,ctx,r[6],r[7],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[8].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[9]=scope.track(1ULL); }
L9: { V argv[]={r[9].value?r[9].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[9].value?r[9].value:2ULL;return r[9]; }
L15: { r[10]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L16: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_CS_SHADER",nullptr,0)); }
L17: { r[12]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L18: { ops->list_append(ctx,r[12].boxed(api,ctx),r[0].boxed(api,ctx)); }
L19: { r[14]=scope.track(1ULL); }
L20: { ops->list_append(ctx,r[12].boxed(api,ctx),r[14].boxed(api,ctx)); }
L21: { r[16]=scope.track(1ULL); }
L22: { ops->list_append(ctx,r[12].boxed(api,ctx),r[16].boxed(api,ctx)); }
L23: { r[12]=N(r[12].boxed(api,ctx));N argv[] = {r[10],r[11],r[12],N(2ULL)}; r[18]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L24: {  }
L25: { r[19]=scope.track(native_length(api,ctx,r[1].boxed(api,ctx))); }
L26: { r[20]=scope.track(r[19]); }
L27: {  }
L28: { r[21]=scope.track(1ULL); }
L29: { r[22]=scope.track((compare(api,ctx,r[20],r[21],true)>0?18ULL:10ULL)); }
L30: { if(!api->truthy(r[22].boxed(api,ctx))) goto L72; }
L31: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L32: { r[23]=scope.track(65ULL); }
L33: { r[24]=scope.track(arithmetic(api,ctx,2,r[20],r[23],true)); }
L34: { V argv[] = {r[24].boxed(api,ctx),2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L35: { r[26]=scope.track(r[25]); }
L36: {  }
L37: {  }
L38: { goto L39; }
L39: { r[27]=scope.track(1ULL); }
L40: {  }
L41: { goto L42; }
L42: { r[29]=scope.track((compare(api,ctx,r[27],r[20],true)<0?18ULL:10ULL)); }
L43: { if(!api->truthy(r[29].boxed(api,ctx))) goto L58; }
L44: {  }
L45: { r[30]=scope.track(65ULL); }
L46: { r[31]=scope.track(arithmetic(api,ctx,2,r[27],r[30],true)); }
L47: { V argv[] = {r[26].boxed(api,ctx),r[31].boxed(api,ctx),2ULL}; r[32]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L48: {  }
L49: { r[33]=scope.track(ops->sequence_get(r[1].boxed(api,ctx),(r[27].small()?r[27].integer():api->read_int(r[27].boxed(api,ctx))))); }
L50: { V argv[] = {r[32].boxed(api,ctx),r[33].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L51: {  }
L52: { goto L53; }
L53: { r[35]=scope.track(9ULL); }
L54: { r[36]=scope.track(api->integer(api->read_int(r[27].boxed(api,ctx)) + api->read_int(r[35].boxed(api,ctx)))); }
L55: { r[27]=scope.track(r[36]); }
L56: {  }
L57: { goto L42; }
L58: {  }
L59: { r[37]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L60: { r[38]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_CS_UAV",nullptr,0)); }
L61: { r[39]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L62: { r[40]=scope.track(1ULL); }
L63: { ops->list_append(ctx,r[39].boxed(api,ctx),r[40].boxed(api,ctx)); }
L64: { ops->list_append(ctx,r[39].boxed(api,ctx),r[20].boxed(api,ctx)); }
L65: { ops->list_append(ctx,r[39].boxed(api,ctx),r[26].boxed(api,ctx)); }
L66: { r[44]=scope.track(1ULL); }
L67: { ops->list_append(ctx,r[39].boxed(api,ctx),r[44].boxed(api,ctx)); }
L68: { r[39]=N(r[39].boxed(api,ctx));N argv[] = {r[37],r[38],r[39],N(2ULL)}; r[46]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L69: { V argv[] = {r[26].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L70: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L71: { goto L87; }
L72: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L73: { r[48]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L74: { r[49]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_CS_UAV",nullptr,0)); }
L75: { r[50]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L76: { r[51]=scope.track(1ULL); }
L77: { ops->list_append(ctx,r[50].boxed(api,ctx),r[51].boxed(api,ctx)); }
L78: { r[53]=scope.track(1ULL); }
L79: { ops->list_append(ctx,r[50].boxed(api,ctx),r[53].boxed(api,ctx)); }
L80: { r[55]=scope.track(1ULL); }
L81: { ops->list_append(ctx,r[50].boxed(api,ctx),r[55].boxed(api,ctx)); }
L82: { r[57]=scope.track(1ULL); }
L83: { ops->list_append(ctx,r[50].boxed(api,ctx),r[57].boxed(api,ctx)); }
L84: { r[50]=N(r[50].boxed(api,ctx));N argv[] = {r[48],r[49],r[50],N(2ULL)}; r[59]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L85: { V argv[]={65ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L86: { goto L87; }
L87: {  }
L88: { r[60]=scope.track(native_length(api,ctx,r[2].boxed(api,ctx))); }
L89: { r[61]=scope.track(r[60]); }
L90: {  }
L91: { r[62]=scope.track(1ULL); }
L92: { r[63]=scope.track((compare(api,ctx,r[61],r[62],true)>0?18ULL:10ULL)); }
L93: { if(!api->truthy(r[63].boxed(api,ctx))) goto L133; }
L94: { V argv[]={73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L95: { r[64]=scope.track(65ULL); }
L96: { r[65]=scope.track(arithmetic(api,ctx,2,r[61],r[64],true)); }
L97: { V argv[] = {r[65].boxed(api,ctx),2ULL}; r[66]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L98: { r[67]=scope.track(r[66]); }
L99: {  }
L100: {  }
L101: { goto L102; }
L102: { r[68]=scope.track(1ULL); }
L103: {  }
L104: { goto L105; }
L105: { r[70]=scope.track((compare(api,ctx,r[68],r[61],true)<0?18ULL:10ULL)); }
L106: { if(!api->truthy(r[70].boxed(api,ctx))) goto L121; }
L107: {  }
L108: { r[71]=scope.track(65ULL); }
L109: { r[72]=scope.track(arithmetic(api,ctx,2,r[68],r[71],true)); }
L110: { V argv[] = {r[67].boxed(api,ctx),r[72].boxed(api,ctx),2ULL}; r[73]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L111: {  }
L112: { r[74]=scope.track(ops->sequence_get(r[2].boxed(api,ctx),(r[68].small()?r[68].integer():api->read_int(r[68].boxed(api,ctx))))); }
L113: { V argv[] = {r[73].boxed(api,ctx),r[74].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L114: {  }
L115: { goto L116; }
L116: { r[76]=scope.track(9ULL); }
L117: { r[77]=scope.track(api->integer(api->read_int(r[68].boxed(api,ctx)) + api->read_int(r[76].boxed(api,ctx)))); }
L118: { r[68]=scope.track(r[77]); }
L119: {  }
L120: { goto L105; }
L121: {  }
L122: { r[78]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L123: { r[79]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_CS_SRV",nullptr,0)); }
L124: { r[80]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L125: { r[81]=scope.track(1ULL); }
L126: { ops->list_append(ctx,r[80].boxed(api,ctx),r[81].boxed(api,ctx)); }
L127: { ops->list_append(ctx,r[80].boxed(api,ctx),r[61].boxed(api,ctx)); }
L128: { ops->list_append(ctx,r[80].boxed(api,ctx),r[67].boxed(api,ctx)); }
L129: { r[80]=N(r[80].boxed(api,ctx));N argv[] = {r[78],r[79],r[80],N(2ULL)}; r[85]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L130: { V argv[] = {r[67].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L131: { V argv[]={73ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L132: { goto L146; }
L133: { V argv[]={97ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L134: { r[87]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L135: { r[88]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_CS_SRV",nullptr,0)); }
L136: { r[89]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L137: { r[90]=scope.track(1ULL); }
L138: { ops->list_append(ctx,r[89].boxed(api,ctx),r[90].boxed(api,ctx)); }
L139: { r[92]=scope.track(1ULL); }
L140: { ops->list_append(ctx,r[89].boxed(api,ctx),r[92].boxed(api,ctx)); }
L141: { r[94]=scope.track(1ULL); }
L142: { ops->list_append(ctx,r[89].boxed(api,ctx),r[94].boxed(api,ctx)); }
L143: { r[89]=N(r[89].boxed(api,ctx));N argv[] = {r[87],r[88],r[89],N(2ULL)}; r[96]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L144: { V argv[]={97ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L145: { goto L146; }
L146: { r[97]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._context",nullptr,0)); }
L147: { r[98]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_CTX_DISPATCH",nullptr,0)); }
L148: { r[99]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L149: { ops->list_append(ctx,r[99].boxed(api,ctx),r[3].boxed(api,ctx)); }
L150: { ops->list_append(ctx,r[99].boxed(api,ctx),r[4].boxed(api,ctx)); }
L151: { ops->list_append(ctx,r[99].boxed(api,ctx),r[5].boxed(api,ctx)); }
L152: { r[99]=N(r[99].boxed(api,ctx));N argv[] = {r[97],r[98],r[99],N(2ULL)}; r[103]=scope.track(N(f47(api,ctx,argv,3).boxed(api,ctx))); }
L153: { r[104]=scope.track(9ULL); }
L154: { V argv[]={r[104].value?r[104].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L155: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L156: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L157: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L158: { scope.result=r[104].value?r[104].value:2ULL;return r[104]; }
L159: return 2ULL; }
// std.native.d3d11.ensure_scratch
static N f75(const Api* api,void* ctx,const N* args,size_t count) {
N r[30]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<30;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[0]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L4: { r[1]=scope.track(1ULL); }
L5: { r[2]=scope.track((!equal(api,ctx,r[0],r[1],true)?18ULL:10ULL)); }
L6: { if(!api->truthy(r[2].boxed(api,ctx))) goto L15; }
L7: {  }
L8: { r[3]=scope.track(9ULL); }
L9: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L10: {  }
L11: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L12: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L14: { scope.result=r[3].value?r[3].value:2ULL;return r[3]; }
L15: { r[4]=scope.track(129ULL); }
L16: { V argv[] = {r[4].boxed(api,ctx),2ULL}; r[5]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L17: { N argv[] = {r[5],N(2ULL)}; r[6]=scope.track(f54(api,ctx,argv,1)); }
L18: {  }
L19: { N argv[] = {r[6],N(2ULL)}; r[7]=scope.track(f59(api,ctx,argv,1)); }
L20: { api->helper(ctx,43,r[7].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0); }
L21: {  }
L22: { r[8]=scope.track(385ULL); }
L23: { V argv[] = {r[8].boxed(api,ctx),2ULL}; r[9]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L24: { N argv[] = {r[9],N(2ULL)}; r[10]=scope.track(f54(api,ctx,argv,1)); }
L25: {  }
L26: { N argv[] = {r[10],N(2ULL)}; r[11]=scope.track(f59(api,ctx,argv,1)); }
L27: { api->helper(ctx,43,r[11].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._swap_desc",nullptr,0); }
L28: {  }
L29: { r[12]=scope.track(385ULL); }
L30: { V argv[] = {r[12].boxed(api,ctx),2ULL}; r[13]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L31: { N argv[] = {r[13],N(2ULL)}; r[14]=scope.track(f54(api,ctx,argv,1)); }
L32: {  }
L33: { N argv[] = {r[14],N(2ULL)}; r[15]=scope.track(f59(api,ctx,argv,1)); }
L34: { api->helper(ctx,43,r[15].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._depth_desc",nullptr,0); }
L35: {  }
L36: { r[16]=scope.track(193ULL); }
L37: { V argv[] = {r[16].boxed(api,ctx),2ULL}; r[17]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L38: { N argv[] = {r[17],N(2ULL)}; r[18]=scope.track(f54(api,ctx,argv,1)); }
L39: {  }
L40: { N argv[] = {r[18],N(2ULL)}; r[19]=scope.track(f59(api,ctx,argv,1)); }
L41: { api->helper(ctx,43,r[19].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._viewport",nullptr,0); }
L42: {  }
L43: { r[20]=scope.track(129ULL); }
L44: { V argv[] = {r[20].boxed(api,ctx),2ULL}; r[21]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L45: { N argv[] = {r[21],N(2ULL)}; r[22]=scope.track(f54(api,ctx,argv,1)); }
L46: {  }
L47: { N argv[] = {r[22],N(2ULL)}; r[23]=scope.track(f59(api,ctx,argv,1)); }
L48: { api->helper(ctx,43,r[23].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._color",nullptr,0); }
L49: {  }
L50: { r[24]=scope.track(65ULL); }
L51: { V argv[] = {r[24].boxed(api,ctx),2ULL}; r[25]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L52: { N argv[] = {r[25],N(2ULL)}; r[26]=scope.track(f54(api,ctx,argv,1)); }
L53: {  }
L54: { N argv[] = {r[26],N(2ULL)}; r[27]=scope.track(f59(api,ctx,argv,1)); }
L55: { api->helper(ctx,43,r[27].boxed(api,ctx),2ULL,2ULL,"std.native.d3d11._rtv_arr",nullptr,0); }
L56: {  }
L57: { r[28]=scope.track(9ULL); }
L58: { V argv[]={r[28].value?r[28].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L59: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L60: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L61: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L62: { scope.result=r[28].value?r[28].value:2ULL;return r[28]; }
L63: return 2ULL; }
// std.native.d3d11.w_guid
static N f76(const Api* api,void* ctx,const N* args,size_t count) {
N r[25]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<25;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: {  }
L3: { r[5]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L4: { V argv[] = {r[5].boxed(api,ctx),r[0].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L5: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L6: { r[8]=scope.track(33ULL); }
L7: { V argv[] = {r[7].boxed(api,ctx),r[8].boxed(api,ctx),2ULL}; r[9]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L8: { V argv[] = {r[9].boxed(api,ctx),r[1].boxed(api,ctx),25ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L9: { r[11]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L10: { r[12]=scope.track(49ULL); }
L11: { V argv[] = {r[11].boxed(api,ctx),r[12].boxed(api,ctx),2ULL}; r[13]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L12: { V argv[] = {r[13].boxed(api,ctx),r[2].boxed(api,ctx),25ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L13: { r[15]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L14: { r[16]=scope.track(65ULL); }
L15: { V argv[] = {r[15].boxed(api,ctx),r[16].boxed(api,ctx),2ULL}; r[17]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L16: { V argv[] = {r[17].boxed(api,ctx),r[3].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L17: { r[19]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L18: { r[20]=scope.track(97ULL); }
L19: { V argv[] = {r[19].boxed(api,ctx),r[20].boxed(api,ctx),2ULL}; r[21]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_ptr_add",argv,2)); }
L20: { V argv[] = {r[21].boxed(api,ctx),r[4].boxed(api,ctx),41ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L21: { r[23]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11._guid_buf",nullptr,0)); }
L22: { V argv[]={r[23].value?r[23].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L23: {  }
L24: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L25: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L26: { scope.result=r[23].value?r[23].value:2ULL;return r[23]; }
L27: return 2ULL; }
// std.native.d3d11.qi
static N f77(const Api* api,void* ctx,const N* args,size_t count) {
N r[20]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<20;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L3: { r[2]=scope.track(65ULL); }
L4: { V argv[] = {r[2].boxed(api,ctx),2ULL}; r[3]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_alloc",argv,1)); }
L5: { r[4]=scope.track(r[3]); }
L6: {  }
L7: { r[5]=scope.track(1ULL); }
L8: { V argv[] = {r[4].boxed(api,ctx),r[5].boxed(api,ctx),49ULL,2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_store",argv,3); }
L9: { r[7]=scope.track(api->helper(ctx,42,2ULL,2ULL,2ULL,"std.native.d3d11.VT_QI",nullptr,0)); }
L10: { r[8]=scope.track(api->helper(ctx,15,2ULL,2ULL,2ULL,nullptr,nullptr,0)); }
L11: { ops->list_append(ctx,r[8].boxed(api,ctx),r[1].boxed(api,ctx)); }
L12: { ops->list_append(ctx,r[8].boxed(api,ctx),r[4].boxed(api,ctx)); }
L13: { r[8]=N(r[8].boxed(api,ctx));N argv[] = {r[0],r[7],r[8],N(2ULL)}; r[11]=scope.track(f48(api,ctx,argv,3)); }
L14: { r[12]=scope.track(r[11]); }
L15: {  }
L16: { V argv[] = {r[4].boxed(api,ctx),49ULL,2ULL}; r[13]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_load",argv,2)); }
L17: { r[14]=scope.track(r[13]); }
L18: {  }
L19: { V argv[] = {r[4].boxed(api,ctx),2ULL}; api->helper(ctx,38,2ULL,2ULL,2ULL,"_ffi_free",argv,1); }
L20: { r[16]=scope.track(1ULL); }
L21: { r[17]=scope.track((!equal(api,ctx,r[12],r[16],true)?18ULL:10ULL)); }
L22: { if(!api->truthy(r[17].boxed(api,ctx))) goto L31; }
L23: {  }
L24: { r[18]=scope.track(1ULL); }
L25: { V argv[]={r[18].value?r[18].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L26: {  }
L27: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L28: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L29: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L30: { scope.result=r[18].value?r[18].value:2ULL;return r[18]; }
L31: { V argv[]={r[14].value?r[14].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L32: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L33: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L34: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L35: { scope.result=r[14].value?r[14].value:2ULL;return r[14]; }
L36: return 2ULL; }
// std.ffi.__init__
static N f78(const Api* api,void* ctx,const N* args,size_t count) {
N r[24]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<24;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
L0: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { r[0]=scope.track(9ULL); }
L2: { api->helper(ctx,43,r[0].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_CHAR",nullptr,0); }
L3: {  }
L4: { r[1]=scope.track(17ULL); }
L5: { api->helper(ctx,43,r[1].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_SHORT",nullptr,0); }
L6: {  }
L7: { r[2]=scope.track(33ULL); }
L8: { api->helper(ctx,43,r[2].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_INT",nullptr,0); }
L9: {  }
L10: { r[3]=scope.track(65ULL); }
L11: { api->helper(ctx,43,r[3].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_LONG",nullptr,0); }
L12: {  }
L13: { r[4]=scope.track(65ULL); }
L14: { api->helper(ctx,43,r[4].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_LONGLONG",nullptr,0); }
L15: {  }
L16: { r[5]=scope.track(65ULL); }
L17: { api->helper(ctx,43,r[5].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_PTR",nullptr,0); }
L18: {  }
L19: { r[6]=scope.track(33ULL); }
L20: { api->helper(ctx,43,r[6].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_FLOAT",nullptr,0); }
L21: {  }
L22: { r[7]=scope.track(65ULL); }
L23: { api->helper(ctx,43,r[7].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_DOUBLE",nullptr,0); }
L24: {  }
L25: { r[8]=scope.track(65ULL); }
L26: { api->helper(ctx,43,r[8].boxed(api,ctx),2ULL,2ULL,"std.ffi.ALIGNMENT_MAX",nullptr,0); }
L27: {  }
L28: { r[9]=scope.track(1ULL); }
L29: { api->helper(ctx,43,r[9].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_I8",nullptr,0); }
L30: {  }
L31: { r[10]=scope.track(9ULL); }
L32: { api->helper(ctx,43,r[10].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_U8",nullptr,0); }
L33: {  }
L34: { r[11]=scope.track(17ULL); }
L35: { api->helper(ctx,43,r[11].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_I16",nullptr,0); }
L36: {  }
L37: { r[12]=scope.track(25ULL); }
L38: { api->helper(ctx,43,r[12].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_U16",nullptr,0); }
L39: {  }
L40: { r[13]=scope.track(33ULL); }
L41: { api->helper(ctx,43,r[13].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_I32",nullptr,0); }
L42: {  }
L43: { r[14]=scope.track(41ULL); }
L44: { api->helper(ctx,43,r[14].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_U32",nullptr,0); }
L45: {  }
L46: { r[15]=scope.track(49ULL); }
L47: { api->helper(ctx,43,r[15].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_I64",nullptr,0); }
L48: {  }
L49: { r[16]=scope.track(57ULL); }
L50: { api->helper(ctx,43,r[16].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_U64",nullptr,0); }
L51: {  }
L52: { r[17]=scope.track(65ULL); }
L53: { api->helper(ctx,43,r[17].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_F32",nullptr,0); }
L54: {  }
L55: { r[18]=scope.track(73ULL); }
L56: { api->helper(ctx,43,r[18].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_F64",nullptr,0); }
L57: {  }
L58: { r[19]=scope.track(81ULL); }
L59: { api->helper(ctx,43,r[19].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_PTR",nullptr,0); }
L60: {  }
L61: { r[20]=scope.track(89ULL); }
L62: { api->helper(ctx,43,r[20].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_CSTRING",nullptr,0); }
L63: {  }
L64: { r[21]=scope.track(97ULL); }
L65: { api->helper(ctx,43,r[21].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_VOID",nullptr,0); }
L66: {  }
L67: { r[22]=scope.track(105ULL); }
L68: { api->helper(ctx,43,r[22].boxed(api,ctx),2ULL,2ULL,"std.ffi.TYPE_STRUCT",nullptr,0); }
L69: {  }
L70: { V argv[]={r[0].value?r[0].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L71: { V argv[]={41ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L72: { scope.result=r[0].value?r[0].value:2ULL;return r[0]; }
L73: return 2ULL; }
// std.ffi.string_to_cstring
static N f79(const Api* api,void* ctx,const N* args,size_t count) {
N r[8]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t i=0;i<count && i<8;++i) r[i]=args[i];
NativeScope scope(api,ctx,true);
const auto* ops=direct_operations(api,ctx);
L0: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L1: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L2: { r[1]=scope.track(native_length(api,ctx,r[0].boxed(api,ctx))); }
L3: { r[2]=scope.track(r[1]); }
L4: {  }
L5: { r[3]=scope.track(1ULL); }
L6: {  }
L7: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_enter",argv,1); }
L8: { V argv[] = {r[0].boxed(api,ctx),2ULL}; r[4]=scope.track(api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_string_to_cstr",argv,1)); }
L9: { r[3]=scope.track(r[4]); }
L10: {  }
L11: { V argv[]={r[3].value?r[3].boxed(api,ctx):2ULL,17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L12: { V argv[]={25ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L13: { r[5]=scope.track(api->helper(ctx,12,25ULL,2ULL,2ULL,"std.ffi.CString",nullptr,0)); }
L14: { ops->frame_set(ctx,r[5].boxed(api,ctx),0,r[3].boxed(api,ctx),false); }
L15: { ops->frame_set(ctx,r[5].boxed(api,ctx),1,r[2].boxed(api,ctx),false); }
L16: { r[6]=scope.track(9ULL); }
L17: { ops->frame_set(ctx,r[5].boxed(api,ctx),2,r[6].boxed(api,ctx),false); }
L18: { V argv[]={r[5].value?r[5].boxed(api,ctx):2ULL,1ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_move",argv,2); }
L19: { V argv[]={17ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L20: { V argv[]={9ULL};api->helper(ctx,38,2ULL,2ULL,2ULL,"_builtin_region_exit",argv,1); }
L21: { scope.result=r[5].value?r[5].value:2ULL;return r[5]; }
L22: return 2ULL; }
static N indirect(const Api* api,void* ctx,V target,const N* args,size_t count) { std::string_view name=api->string_data(api->helper(ctx,45,target,2ULL,2ULL,nullptr,nullptr,0)); std::vector<N> bound(args,args+count); if(api->truthy(api->helper(ctx,46,target,2ULL,2ULL,nullptr,nullptr,0))) bound.push_back(target);
if(name=="__top_level_wrapper__") return f0(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_device") return f1(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_context") return f2(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_update_texture_rgba") return f3(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_texture_create_rgba") return f4(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_raster_state") return f5(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_depth_state") return f6(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_sampler_create") return f7(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_depth_state_create") return f8(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_discard_all") return f9(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_ps_set_cb") return f10(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_vs_set_cb") return f11(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_cb_create") return f12(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_input_layout") return f13(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_shaders") return f14(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_map_dynamic") return f15(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_input_layout_create") return f16(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.fmt_align") return f17(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.fmt_size") return f18(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_ps_create") return f19(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_blob_size") return f20(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_blob_ptr") return f21(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_render_targets") return f22(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_compile") return f23(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_draw_indexed") return f24(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_vertex_buffer") return f25(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_release_all") return f26(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_buffer_create_dynamic") return f27(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_index_buffer_create") return f28(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_vertex_buffer_create") return f29(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_end_frame") return f30(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_clear_depth") return f31(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_unmap") return f32(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_clear") return f33(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_begin_frame") return f34(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_raster_state_create") return f35(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_height") return f36(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_attached") return f37(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_create_views") return f38(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_buffer_read") return f39(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_buffer_write") return f40(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_srv_create") return f41(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_uav_create") return f42(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_uav_create_typed") return f43(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_buffer_create") return f44(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_init") return f45(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.release") return f46(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.com_void") return f47(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.com_i32") return f48(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.com") return f49(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_blend_state") return f50(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.__init__") return f51(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_release") return f52(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_ps_set_shader_resource") return f53(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.keep") return f54(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.ensure_device") return f55(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_topology") return f56(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_viewport") return f57(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_device_ok") return f58(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.p2i") return f59(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_resize") return f60(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_width") return f61(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_draw") return f62(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_blend_state_create") return f63(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_vs_create") return f64(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_detach") return f65(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_shader_create") return f66(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.blob_code") return f67(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.ensure_compiler") return f68(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_ps_set_sampler") return f69(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_attach") return f70(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.blob_size") return f71(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_buffer_update") return f72(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gfx_set_index_buffer") return f73(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.gpu_dispatch") return f74(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.ensure_scratch") return f75(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.w_guid") return f76(api,ctx,bound.data(),bound.size());
if(name=="std.native.d3d11.qi") return f77(api,ctx,bound.data(),bound.size());
if(name=="std.ffi.__init__") return f78(api,ctx,bound.data(),bound.size());
if(name=="std.ffi.string_to_cstring") return f79(api,ctx,bound.data(),bound.size());
std::vector<V> boxed; for(const auto& arg:bound)boxed.push_back(arg.boxed(api,ctx)); return api->helper(ctx,47,target,2ULL,2ULL,name.data(),boxed.data(),boxed.size()); }
extern "C" LM_EXPORT V export1(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_device");
extern "C" LM_EXPORT V export1(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f1(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export2(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_context");
extern "C" LM_EXPORT V export2(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f2(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export3(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_update_texture_rgba");
extern "C" LM_EXPORT V export3(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=4) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,4> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f3(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export4(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_texture_create_rgba");
extern "C" LM_EXPORT V export4(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f4(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export5(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_raster_state");
extern "C" LM_EXPORT V export5(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f5(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export6(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_depth_state");
extern "C" LM_EXPORT V export6(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f6(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export7(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_sampler_create");
extern "C" LM_EXPORT V export7(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f7(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export8(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_depth_state_create");
extern "C" LM_EXPORT V export8(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f8(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export9(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_discard_all");
extern "C" LM_EXPORT V export9(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f9(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export10(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_ps_set_cb");
extern "C" LM_EXPORT V export10(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f10(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export11(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_vs_set_cb");
extern "C" LM_EXPORT V export11(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f11(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export12(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_cb_create");
extern "C" LM_EXPORT V export12(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f12(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export13(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_input_layout");
extern "C" LM_EXPORT V export13(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f13(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export14(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_shaders");
extern "C" LM_EXPORT V export14(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f14(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export15(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_map_dynamic");
extern "C" LM_EXPORT V export15(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f15(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export16(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_input_layout_create");
extern "C" LM_EXPORT V export16(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=4) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,4> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f16(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export17(const Api*,void*,const V*,size_t) asm("std.native.d3d11.fmt_align");
extern "C" LM_EXPORT V export17(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f17(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export18(const Api*,void*,const V*,size_t) asm("std.native.d3d11.fmt_size");
extern "C" LM_EXPORT V export18(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f18(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export19(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_ps_create");
extern "C" LM_EXPORT V export19(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f19(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export20(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_blob_size");
extern "C" LM_EXPORT V export20(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f20(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export21(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_blob_ptr");
extern "C" LM_EXPORT V export21(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f21(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export22(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_render_targets");
extern "C" LM_EXPORT V export22(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f22(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export23(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_compile");
extern "C" LM_EXPORT V export23(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f23(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export24(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_draw_indexed");
extern "C" LM_EXPORT V export24(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f24(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export25(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_vertex_buffer");
extern "C" LM_EXPORT V export25(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=4) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,4> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f25(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export26(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_release_all");
extern "C" LM_EXPORT V export26(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f26(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export27(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_buffer_create_dynamic");
extern "C" LM_EXPORT V export27(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f27(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export28(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_index_buffer_create");
extern "C" LM_EXPORT V export28(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f28(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export29(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_vertex_buffer_create");
extern "C" LM_EXPORT V export29(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f29(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export30(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_end_frame");
extern "C" LM_EXPORT V export30(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f30(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export31(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_clear_depth");
extern "C" LM_EXPORT V export31(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f31(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export32(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_unmap");
extern "C" LM_EXPORT V export32(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f32(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export33(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_clear");
extern "C" LM_EXPORT V export33(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=4) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,4> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f33(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export34(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_begin_frame");
extern "C" LM_EXPORT V export34(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f34(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export35(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_raster_state_create");
extern "C" LM_EXPORT V export35(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f35(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export36(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_height");
extern "C" LM_EXPORT V export36(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f36(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export37(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_attached");
extern "C" LM_EXPORT V export37(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f37(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export38(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_create_views");
extern "C" LM_EXPORT V export38(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f38(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export39(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_buffer_read");
extern "C" LM_EXPORT V export39(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f39(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export40(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_buffer_write");
extern "C" LM_EXPORT V export40(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f40(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export41(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_srv_create");
extern "C" LM_EXPORT V export41(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f41(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export42(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_uav_create");
extern "C" LM_EXPORT V export42(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f42(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export43(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_uav_create_typed");
extern "C" LM_EXPORT V export43(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f43(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export44(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_buffer_create");
extern "C" LM_EXPORT V export44(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=7) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,7> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f44(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export45(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_init");
extern "C" LM_EXPORT V export45(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f45(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export46(const Api*,void*,const V*,size_t) asm("std.native.d3d11.release");
extern "C" LM_EXPORT V export46(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f46(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export47(const Api*,void*,const V*,size_t) asm("std.native.d3d11.com_void");
extern "C" LM_EXPORT V export47(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f47(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export48(const Api*,void*,const V*,size_t) asm("std.native.d3d11.com_i32");
extern "C" LM_EXPORT V export48(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f48(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export49(const Api*,void*,const V*,size_t) asm("std.native.d3d11.com");
extern "C" LM_EXPORT V export49(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=4) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,4> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f49(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export50(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_blend_state");
extern "C" LM_EXPORT V export50(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f50(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export51(const Api*,void*,const V*,size_t) asm("std.native.d3d11.__init__");
extern "C" LM_EXPORT V export51(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f51(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export52(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_release");
extern "C" LM_EXPORT V export52(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f52(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export53(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_ps_set_shader_resource");
extern "C" LM_EXPORT V export53(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f53(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export54(const Api*,void*,const V*,size_t) asm("std.native.d3d11.keep");
extern "C" LM_EXPORT V export54(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f54(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export55(const Api*,void*,const V*,size_t) asm("std.native.d3d11.ensure_device");
extern "C" LM_EXPORT V export55(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f55(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export56(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_topology");
extern "C" LM_EXPORT V export56(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f56(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export57(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_viewport");
extern "C" LM_EXPORT V export57(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=4) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,4> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f57(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export58(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_device_ok");
extern "C" LM_EXPORT V export58(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f58(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export59(const Api*,void*,const V*,size_t) asm("std.native.d3d11.p2i");
extern "C" LM_EXPORT V export59(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f59(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export60(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_resize");
extern "C" LM_EXPORT V export60(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f60(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export61(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_width");
extern "C" LM_EXPORT V export61(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f61(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export62(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_draw");
extern "C" LM_EXPORT V export62(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f62(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export63(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_blend_state_create");
extern "C" LM_EXPORT V export63(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f63(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export64(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_vs_create");
extern "C" LM_EXPORT V export64(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f64(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export65(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_detach");
extern "C" LM_EXPORT V export65(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f65(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export66(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_shader_create");
extern "C" LM_EXPORT V export66(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f66(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export67(const Api*,void*,const V*,size_t) asm("std.native.d3d11.blob_code");
extern "C" LM_EXPORT V export67(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f67(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export68(const Api*,void*,const V*,size_t) asm("std.native.d3d11.ensure_compiler");
extern "C" LM_EXPORT V export68(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f68(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export69(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_ps_set_sampler");
extern "C" LM_EXPORT V export69(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f69(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export70(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_attach");
extern "C" LM_EXPORT V export70(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f70(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export71(const Api*,void*,const V*,size_t) asm("std.native.d3d11.blob_size");
extern "C" LM_EXPORT V export71(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=1) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,1> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f71(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export72(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_buffer_update");
extern "C" LM_EXPORT V export72(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=4) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,4> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f72(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export73(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gfx_set_index_buffer");
extern "C" LM_EXPORT V export73(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=3) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,3> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f73(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export74(const Api*,void*,const V*,size_t) asm("std.native.d3d11.gpu_dispatch");
extern "C" LM_EXPORT V export74(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=6) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,6> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f74(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export75(const Api*,void*,const V*,size_t) asm("std.native.d3d11.ensure_scratch");
extern "C" LM_EXPORT V export75(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=0) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,0> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f75(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export76(const Api*,void*,const V*,size_t) asm("std.native.d3d11.w_guid");
extern "C" LM_EXPORT V export76(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=5) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,5> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f76(api,ctx,native.data(),count).boxed(api,ctx); }
extern "C" LM_EXPORT V export77(const Api*,void*,const V*,size_t) asm("std.native.d3d11.qi");
extern "C" LM_EXPORT V export77(const Api* api,void* ctx,const V* args,size_t count) { if(!api || api->version!=1 || api->size!=sizeof(Api)) throw std::runtime_error("Lymar native module ABI mismatch"); if(count!=2) throw std::runtime_error("Lymar native argument count mismatch"); std::array<N,2> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f77(api,ctx,native.data(),count).boxed(api,ctx); }
