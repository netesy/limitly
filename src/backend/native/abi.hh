#pragma once
#include "backend/vm/vm_value_base.hh"
#include <cstddef>
#include <cstdint>

namespace LM::Backend::Native {
// Bump this version whenever the function table or tagged object layout
// changes.
constexpr uint32_t ABI_VERSION = 1;
enum class Helper : uint32_t {
  Add,
  Sub,
  Mul,
  Div,
  Mod,
  Neg,
  Cast,
  ToString,
  Concat,
  Format,
  StringIndex,
  StringNew,
  FrameNew,
  FrameGet,
  FrameSet,
  ListNew,
  ListAppend,
  ListGet,
  ListSet,
  ListLen,
  DictNew,
  DictGet,
  DictSet,
  DictHas,
  DictLen,
  DictItems,
  TupleNew,
  TupleGet,
  TupleSet,
  TupleLen,
  Ok,
  Error,
  IsError,
  Unwrap,
  UnwrapOr,
  Enum,
  Tag,
  Payload,
  Builtin,
  ResourceCreate,
  ResourceCall,
  ResourceDestroy,
  GlobalGet,
  GlobalSet,
  Transfer,
  CallableName,
  ClosureBound,
  Callback,
  RefCreate, RefResolve, RefRelease, OwnershipConsume, RefMove
};
struct Api {
  uint32_t version;
  uint32_t size;
  LmValue (*helper)(void *, uint32_t, LmValue, LmValue, LmValue, const char *,
                    const LmValue *, size_t);
  LmValue (*integer)(int64_t);
  LmValue (*floating)(double);
  int64_t (*read_int)(LmValue);
  double (*read_float)(LmValue);
  int (*equal)(LmValue, LmValue);
  int (*compare)(LmValue, LmValue);
  bool (*truthy)(LmValue);
  const char *(*string_data)(LmValue);
};
using Entry = LmValue (*)(const Api *, void *, const LmValue *, size_t);
const Api &host_api();
} // namespace LM::Backend::Native
