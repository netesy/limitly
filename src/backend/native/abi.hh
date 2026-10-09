#pragma once
#include "backend/vm/vm_value_base.hh"
#include <cstddef>
#include <cstdint>

namespace LM::Backend::Native {
// Bump this version whenever the function table or tagged object layout
// changes.
constexpr uint32_t ABI_VERSION = 2;
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

  // Direct typed runtime calls for hot container, string, and frame operations
  LmValue (*list_new)(void *ctx);
  LmValue (*list_append)(void *ctx, LmValue list, LmValue val);
  LmValue (*list_get)(void *ctx, LmValue list, LmValue idx);
  LmValue (*list_set)(void *ctx, LmValue list, LmValue idx, LmValue val);
  LmValue (*list_len)(void *ctx, LmValue list);

  LmValue (*string_new)(void *ctx, const char *text, int64_t len);
  LmValue (*string_index)(void *ctx, LmValue str, LmValue idx);
  LmValue (*string_concat)(void *ctx, LmValue a, LmValue b);
  LmValue (*string_format)(void *ctx, LmValue a, LmValue b);

  LmValue (*dict_new)(void *ctx);
  LmValue (*dict_get)(void *ctx, LmValue dict, LmValue key);
  LmValue (*dict_set)(void *ctx, LmValue dict, LmValue key, LmValue val);
  LmValue (*dict_has)(void *ctx, LmValue dict, LmValue key);
  LmValue (*dict_len)(void *ctx, LmValue dict);

  LmValue (*tuple_new)(void *ctx, int64_t len);
  LmValue (*tuple_get)(void *ctx, LmValue tuple, LmValue idx);
  LmValue (*tuple_set)(void *ctx, LmValue tuple, LmValue idx, LmValue val);
  LmValue (*tuple_len)(void *ctx, LmValue tuple);

  LmValue (*frame_new)(void *ctx, const char *name, int64_t fields);
  LmValue (*frame_get)(void *ctx, LmValue frame, int64_t idx);
  LmValue (*frame_set)(void *ctx, LmValue frame, int64_t idx, LmValue val);
};
using Entry = LmValue (*)(const Api *, void *, const LmValue *, size_t);
const Api &host_api();
} // namespace LM::Backend::Native
