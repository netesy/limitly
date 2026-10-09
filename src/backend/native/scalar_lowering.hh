#pragma once

namespace LM::Backend::Native {
// Private generated-code support, not an addition to the exported helper ABI.
inline constexpr const char *scalar_lowering_source = R"CPP(
struct N {
  V value=2ULL;
  double scalar=0;
  bool unboxed=false;
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
static inline __attribute__((always_inline)) N arithmetic(const Api* api,void* ctx,uint32_t op,const N& a,const N& b,bool typed) {
  if(typed && a.small() && b.small()) {
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
  if(typed && op!=HMod && a.numeric() && b.numeric() && (a.floating() || b.floating())) {
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
)CPP";
}
