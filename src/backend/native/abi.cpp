#include "abi.hh"
#include "backend/vm/reference_ops.hh"
#include "backend/vm/constant_utils.hh"
#include "backend/vm/register.hh"
#include "backend/vm/resource_manager.hh"
#include "backend/vm/vm_dict.hh"
#include "backend/vm/vm_list.hh"
#include "backend/vm/vm_tuple.hh"
#include "lir/builtin_functions.hh"
#include "lir/function_registry.hh"
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <string_view>
#include <limits>

namespace LM::Backend::Native {
using Machine = VM::Register::RegisterVM;
namespace {
template <class T> T *object(LmValue v, uint32_t type) {
  auto *h = IS_PTR(v) ? static_cast<ObjHeader *>(UNBOX_PTR(v)) : nullptr;
  return h && h->type_id == type ? reinterpret_cast<T *>(h) : nullptr;
}
bool truthy(LmValue v) {
  if (v == VAL_NIL || v == VAL_FALSE || v == 0)
    return false;
  if (IS_INT(v))
    return UNBOX_INT(v) != 0;
  if (is_numeric(v))
    return as_float(v) != 0.0;
  return true;
}
const char *string_data(LmValue value) {
  if (auto *str = object<LmStringHeader>(value, TYPE_STRING))
    return str->data;
  if (auto *box = object<LmBox>(value, TYPE_BOX);
      box && box->type == LM_BOX_STRING)
    return static_cast<const char *>(box->value.as_ptr);
  throw std::runtime_error("Native callable name is not a string");
}
LmValue helper(void *context, uint32_t operation, LmValue a, LmValue b,
               LmValue c, const char *text, const LmValue *args, size_t count) {
  auto &vm = *static_cast<Machine *>(context);
  auto own = [&](LmValue value) {
    vm.register_native_allocation(value);
    return value;
  };
  auto transfer = [&](LmValue child, LmValue container) {
    vm.transfer_native_ownership(child, container);
  };
  auto field = [&](LmValue frame, int i) {
    return object<LmFrame>(frame, TYPE_FRAME)
               ? lm_frame_get_field(UNBOX_PTR(frame), i)
               : VAL_NIL;
  };
  auto frame = [&](const char *name, int fields) {
    return own(BOX_PTR(lm_frame_alloc(name, fields)));
  };
  auto unwrap = [&](LmValue value) {
    return object<LmFrame>(value, TYPE_FRAME) ? field(value, 1) : value;
  };
  auto sequence = [&](LmValue value) {
    std::vector<LmValue> result;
    if (auto *list = object<LmList>(value, TYPE_LIST))
      result.assign(list->data, list->data + list->size);
    else if (value != VAL_NIL)
      result.push_back(value);
    return result;
  };
  switch (static_cast<Helper>(operation)) {
  case Helper::RefCreate: return make_u64(Backend::VM::Register::ReferenceOperations::create(vm, a, as_u64(b)));
  case Helper::RefResolve: return Backend::VM::Register::ReferenceOperations::resolve(vm, as_u64(a), as_u64(b));
  case Helper::RefMove: return make_u64(Backend::VM::Register::ReferenceOperations::move(vm, as_u64(a), as_u64(b)));
  case Helper::RefRelease: Backend::VM::Register::ReferenceOperations::release(vm, as_u64(a), as_u64(b)); return VAL_NIL;
  case Helper::OwnershipConsume: vm.consume_memory(a); return VAL_NIL;
  case Helper::Add:
    return own(lm_add(a, b));
  case Helper::Sub:
    return own(lm_sub(a, b));
  case Helper::Mul:
    return own(lm_mul(a, b));
  case Helper::Div:
    return own(lm_div(a, b));
  case Helper::Neg:
    return lm_sub(make_i64(0), a);
  case Helper::Mod:
    if (is_integer(a) && is_integer(b))
      return as_i128(b) ? make_i128(as_i128(a) % as_i128(b)) : VAL_NIL;
    return as_float(b) ? make_float(std::fmod(as_float(a), as_float(b)))
                       : VAL_NIL;
  case Helper::StringNew:
    return own(BOX_PTR(lm_str_from_bytes(text, as_i64(a))));
  case Helper::Cast: {
    auto type = static_cast<LIR::Type>(as_i64(b));
    auto *str = object<LmStringHeader>(a, TYPE_STRING);
    if (type == LIR::Type::F64 || type == LIR::Type::F32) {
      if (str) {
        try {
          return own(make_float(std::stod(std::string(str->data, str->len))));
        } catch (...) {
        }
      }
      return own(make_float(as_float(a)));
    }
    if (type == LIR::Type::I64) {
      if (str) {
        try {
          return make_i64(std::stoll(std::string(str->data, str->len)));
        } catch (...) {
          if (str->len)
            return make_i64(static_cast<unsigned char>(str->data[0]));
        }
      }
      return make_i64(as_i64(a));
    }
    if (type == LIR::Type::Bool)
      return truthy(a) ? VAL_TRUE : VAL_FALSE;
    return a;
  }
  case Helper::ToString:
    return own(BOX_PTR(lm_value_to_string(a)));
  case Helper::StringIndex: {
    auto *str = object<LmStringHeader>(a, TYPE_STRING);
    int64_t index = as_i64(b);
    if (!str || index < 0 || static_cast<uint64_t>(index) >= str->len)
      return VAL_NIL;
    return make_i64(static_cast<unsigned char>(str->data[index]));
  }
  case Helper::Concat:
  case Helper::Format: {
    auto *x = object<LmStringHeader>(a, TYPE_STRING);
    auto *y = object<LmStringHeader>(b, TYPE_STRING);
    bool free_x = !x, free_y = !y;
    if (!x) {
      if (static_cast<Helper>(operation) == Helper::Concat && y &&
          is_integer(a) && as_i64(a) >= 0 && as_i64(a) <= 255) {
        char byte = static_cast<char>(as_i64(a));
        x = lm_str_from_bytes(&byte, 1);
      } else
        x = lm_value_to_string(a);
    }
    if (!y)
      y = lm_value_to_string(b);
    auto result = own(BOX_PTR(static_cast<Helper>(operation) == Helper::Concat
                                  ? lm_str_concat(x, y)
                                  : lm_str_format(x, y)));
    if (free_x)
      lm_str_free(x);
    if (free_y)
      lm_str_free(y);
    return result;
  }
  case Helper::FrameNew:
    return frame(text, as_i64(a));
  case Helper::FrameGet: {
    auto index = as_i64(b);
    if (index < 0 || static_cast<uint64_t>(index) > UINT32_MAX) throw std::runtime_error("Invalid frame field index");
    return c == 1 ? lm_frame_get_field_atomic(vm.checked_frame(a, static_cast<uint32_t>(index)), static_cast<int>(index))
                  : vm.checked_frame(a, static_cast<uint32_t>(index))->fields[index];
  }
  case Helper::FrameSet: {
    auto index = as_i64(b);
    if (index < 0 || static_cast<uint64_t>(index) > UINT32_MAX) throw std::runtime_error("Invalid frame field index");
    if (text && std::strcmp(text, "atomic") == 0)
      lm_frame_set_field_atomic(vm.checked_frame(a, static_cast<uint32_t>(index)), static_cast<int>(index), c);
    else
      vm.checked_frame(a, static_cast<uint32_t>(index))->fields[index] = c;
    transfer(c, a);
    return VAL_NIL;
  }
  case Helper::ListNew:
    return own(BOX_PTR(lm_list_new()));
  case Helper::ListAppend:
    if (auto *list = object<LmList>(a, TYPE_LIST)) {
      lm_list_append(list, b);
      transfer(b, a);
    }
    return VAL_NIL;
  case Helper::ListGet:
  case Helper::TupleGet:
    if (auto *list = object<LmList>(a, TYPE_LIST))
      return lm_list_get(list, as_i64(b));
    if (auto *tuple = object<LmTuple>(a, TYPE_TUPLE))
      return lm_tuple_get(tuple, as_i64(b));
    return VAL_NIL;
  case Helper::ListSet:
  case Helper::TupleSet:
  case Helper::DictSet:
    if (auto *list = object<LmList>(a, TYPE_LIST))
      lm_list_set(list, as_i64(b), c);
    else if (auto *tuple = object<LmTuple>(a, TYPE_TUPLE))
      lm_tuple_set(tuple, as_i64(b), c);
    else if (auto *dict = object<LmDict>(a, TYPE_DICT)) {
      lm_dict_set(dict, b, c);
      transfer(b, a);
    }
    transfer(c, a);
    return VAL_NIL;
  case Helper::ListLen:
    if (auto *list = object<LmList>(a, TYPE_LIST))
      return make_i64(list->size);
    return make_i64(0);
  case Helper::TupleNew:
    return own(BOX_PTR(lm_tuple_new(as_i64(a))));
  case Helper::TupleLen:
    if (auto *tuple = object<LmTuple>(a, TYPE_TUPLE))
      return make_i64(tuple->size);
    return make_i64(0);
  case Helper::DictNew:
    return own(BOX_PTR(lm_dict_new(hash_boxed_value, cmp_boxed_value)));
  case Helper::DictGet:
    if (auto *dict = object<LmDict>(a, TYPE_DICT))
      return lm_dict_get(dict, b);
    return VAL_NIL;
  case Helper::DictHas:
    if (auto *dict = object<LmDict>(a, TYPE_DICT))
      return lm_dict_contains(dict, b) ? VAL_TRUE : VAL_FALSE;
    return VAL_FALSE;
  case Helper::DictLen:
    if (auto *dict = object<LmDict>(a, TYPE_DICT))
      return make_i64(dict->size);
    return make_i64(0);
  case Helper::DictItems: {
    auto result = own(BOX_PTR(lm_list_new()));
    if (auto *dict = object<LmDict>(a, TYPE_DICT)) {
      uint64_t size = 0;
      auto *items = lm_dict_items(dict, &size);
      for (uint64_t i = 0; i < size; ++i) {
        auto pair = own(BOX_PTR(lm_tuple_new(2)));
        lm_tuple_set(static_cast<LmTuple *>(UNBOX_PTR(pair)), 0, items[2 * i]);
        lm_tuple_set(static_cast<LmTuple *>(UNBOX_PTR(pair)), 1,
                     items[2 * i + 1]);
        transfer(items[2 * i], pair);
        transfer(items[2 * i + 1], pair);
        lm_list_append(static_cast<LmList *>(UNBOX_PTR(result)), pair);
        transfer(pair, result);
      }
      free(items);
    }
    return result;
  }
  case Helper::Ok:
  case Helper::Error:
  case Helper::Enum: {
    bool enumeration = static_cast<Helper>(operation) == Helper::Enum;
    auto result =
        frame(enumeration ? "__lir_internal_enum__"
                          : (static_cast<Helper>(operation) == Helper::Ok
                                 ? "__lir_internal_ok__"
                                 : "__lir_internal_error__"),
              enumeration ? 3 : 2);
    lm_frame_set_field(UNBOX_PTR(result), 0,
                       enumeration ? b
                                   : make_i64(static_cast<Helper>(operation) ==
                                              Helper::Error));
    lm_frame_set_field(UNBOX_PTR(result), 1, a);
    transfer(a, result);
    if (enumeration) {
      auto name = own(BOX_PTR(lm_str_from_cstr(text)));
      lm_frame_set_field(UNBOX_PTR(result), 2, name);
      transfer(name, result);
    }
    return result;
  }
  case Helper::IsError:
    return object<LmFrame>(a, TYPE_FRAME) && as_i64(field(a, 0)) != 0
               ? VAL_TRUE
               : VAL_FALSE;
  case Helper::Unwrap:
    return unwrap(a);
  case Helper::UnwrapOr:
    return object<LmFrame>(a, TYPE_FRAME) && as_i64(field(a, 0)) != 0
               ? b
               : unwrap(a);
  case Helper::Tag:
    return field(a, 0);
  case Helper::Payload:
    return field(a, 1);
  case Helper::GlobalGet:
    return vm.get_global(text);
  case Helper::GlobalSet:
    vm.set_global(text, a);
    return VAL_NIL;
  case Helper::Transfer:
    transfer(a, b);
    return VAL_NIL;
  case Helper::CallableName:
    if (auto *tuple = object<LmTuple>(a, TYPE_TUPLE))
      return lm_tuple_get(tuple, 0);
    return a;
  case Helper::ClosureBound:
    return object<LmTuple>(a, TYPE_TUPLE) ? VAL_TRUE : VAL_FALSE;
  case Helper::Callback: {
    std::vector<LmValue> arguments(args, args + count);
    if (LIR::BuiltinUtils::isBuiltinFunction(text)) {
      return helper(context, static_cast<uint32_t>(Helper::Builtin), a, b, c,
                    text, args, count);
    }
    return vm.invoke_for_callback(text, arguments, true);
  }
  case Helper::ResourceCreate: {
    auto arguments = sequence(b);
    auto id = VM::ResourceManager::getInstance().create(
        static_cast<VM::ResourceType>(as_i64(a)), arguments);
    vm.track_resource(id);
    return id == -1 ? VAL_NIL : make_i64(id);
  }
  case Helper::ResourceDestroy:
    VM::ResourceManager::getInstance().destroy(as_i64(a));
    vm.untrack_resource(as_i64(a));
    return VAL_NIL;
  case Helper::ResourceCall: {
    std::vector<LmValue> arguments;
    for (size_t i = 0; i < count; ++i) {
      auto values = sequence(args[i]);
      arguments.insert(arguments.end(), values.begin(), values.end());
    }
    if (static_cast<VM::ResourceOperation>(as_i64(b)) == VM::ResourceOperation::SEND ||
        static_cast<VM::ResourceOperation>(as_i64(b)) == VM::ResourceOperation::PUSH)
      for (auto value : arguments) vm.publish_value(value);
    auto result = VM::ResourceManager::getInstance().call(
        as_i64(a), static_cast<VM::ResourceOperation>(as_i64(b)), arguments,
        vm.get_current_fiber());
    // Resources can return graphs (e.g. read buffers); register their elements.
    if (auto *list = object<LmList>(result, TYPE_LIST))
      for (uint64_t i = 0; i < list->size; ++i)
        own(list->data[i]);
    return own(result);
  }
  case Helper::Builtin: {
    const std::string_view name = text ? text : "";
    auto arg = [&](size_t i) {
      if (i >= count)
        throw std::runtime_error("Missing native builtin argument: " + std::string(name));
      return args[i];
    };
    auto string = [&](size_t i) {
      return object<LmStringHeader>(arg(i), TYPE_STRING);
    };
    if (name == "_builtin_track") return own(arg(0));
    if (name == "_builtin_frame_deinit") { vm.finalize_frame(arg(0)); return VAL_NIL; }
    if (name == "_builtin_region_call_enter") return make_i64(vm.begin_native_call());
    if (name == "_builtin_region_call_leave") {
      vm.end_native_call(as_i64(arg(0)), arg(1)); return VAL_NIL;
    }
    if (name == "_builtin_region_enter" || name == "_builtin_region_exit") {
      vm.native_region(name == "_builtin_region_enter" ? LIR::LIR_Op::RegionEnter : LIR::LIR_Op::RegionExit,
                       static_cast<uint32_t>(as_i64(arg(0)))); return VAL_NIL;
    }
    if (name == "_builtin_region_move") {
      vm.native_region(LIR::LIR_Op::RegionMove, static_cast<uint32_t>(as_i64(arg(1))), arg(0)); return VAL_NIL;
    }
    // Avoid converting entire object graphs to frontend values just to
    // inspect a collection's length inside native loops.
    if (name == "len") {
      auto value = arg(0);
      if (auto *list = object<LmList>(value, TYPE_LIST))
        return make_i64(list->size);
      if (auto *tuple = object<LmTuple>(value, TYPE_TUPLE))
        return make_i64(tuple->size);
      if (auto *dict = object<LmDict>(value, TYPE_DICT))
        return make_i64(dict->size);
      if (auto *str = object<LmStringHeader>(value, TYPE_STRING)) {
        // The language's len(str) counts decoded UTF-8 codepoints.
        std::vector<ValuePtr> values{
            VM::Register::register_to_value_ptr(value)};
        return VM::compiler_value_to_backend_value(
            LIR::BuiltinUtils::callBuiltinFunction(std::string(name), values));
      }
    }
    if (name == "_builtin_string_hash_bytes") {
      auto* value = string(0);
      if (!value) throw std::runtime_error("Byte hash expects a string");
      uint64_t hash = 5381;
      for (uint64_t i = 0; i < value->len; ++i)
        hash = (hash * 33 + static_cast<unsigned char>(value->data[i])) % 2147483647;
      return make_i64(hash);
    }
    if (name == "_builtin_list_slice") {
      auto *list = object<LmList>(arg(0), TYPE_LIST);
      if (!list && arg(0) != VAL_NIL) throw std::runtime_error("List slice expects a list");
      auto *result = lm_list_new();
      auto value = own(BOX_PTR(result));
      uint64_t size = list ? list->size : 0;
      auto start = std::min(size, static_cast<uint64_t>(std::max(int64_t(0), as_i64(arg(1)))));
      auto end = std::min(size, static_cast<uint64_t>(std::max(int64_t(0), as_i64(arg(2)))));
      for (auto i = start; i < end; ++i) {
        lm_list_append(result, list->data[i]);
        transfer(list->data[i], value);
      }
      return value;
    }
    if (name == "_builtin_string_join") {
      auto view = [&](LmValue value) -> std::string_view {
        if (value == VAL_NIL) return {};
        if (auto *str = object<LmStringHeader>(value, TYPE_STRING)) return {str->data, str->len};
        if (auto *box = object<LmBox>(value, TYPE_BOX); box && box->type == LM_BOX_STRING) {
          auto *text = static_cast<const char*>(box->value.as_ptr);
          return text ? std::string_view(text) : std::string_view();
        }
        throw std::runtime_error("String join expects string elements");
      };
      auto *list = object<LmList>(arg(0), TYPE_LIST);
      if (!list && arg(0) != VAL_NIL) throw std::runtime_error("String join expects a list");
      auto delimiter = view(arg(1));
      uint64_t length = 0;
      auto add_length = [&](uint64_t extra) {
        if (extra > std::numeric_limits<size_t>::max() - sizeof(LmStringHeader) - 1 - length)
          throw std::length_error("Joined string is too large");
        length += extra;
      };
      for (uint64_t i = 0; list && i < list->size; ++i) {
        if (i) add_length(delimiter.size());
        add_length(view(list->data[i]).size());
      }
      auto *result = lm_str_alloc(length);
      if (!result) throw std::bad_alloc();
      uint64_t offset = 0;
      auto copy = [&](std::string_view part) {
        if (!part.empty()) std::memcpy(result->data + offset, part.data(), part.size());
        offset += part.size();
      };
      for (uint64_t i = 0; list && i < list->size; ++i) {
        if (i) copy(delimiter);
        copy(view(list->data[i]));
      }
      result->len = length;
      result->data[length] = 0;
      return own(BOX_PTR(result));
    }
    if (name == "_builtin_string_byte_len")
      return make_i64(string(0) ? string(0)->len : 0);
    if (name == "_builtin_string_decode_next")
      return make_i64(lm_str_decode_next(string(0), as_i64(arg(1))));
    if (name == "_builtin_string_byte_at")
      return make_i64(lm_str_byte_at(string(0), as_i64(arg(1))));
    if (name == "_builtin_substring")
      return own(
          BOX_PTR(lm_str_substring(string(0), as_i64(arg(1)), as_i64(arg(2)))));
    if (name == "_builtin_string_index_of")
      return make_i64(lm_str_index_of(string(0), string(1)));
    if (name == "_builtin_string_contains")
      return lm_str_contains(string(0), string(1)) ? VAL_TRUE : VAL_FALSE;
    if (name == "_builtin_string_starts_with")
      return lm_str_starts_with(string(0), string(1)) ? VAL_TRUE : VAL_FALSE;
    if (name == "_builtin_string_ends_with")
      return lm_str_ends_with(string(0), string(1)) ? VAL_TRUE : VAL_FALSE;
    if (name == "_builtin_string_trim")
      return own(BOX_PTR(lm_str_trim(string(0))));
    if (name == "_builtin_string_to_lower")
      return own(BOX_PTR(lm_str_to_lower(string(0))));
    if (name == "_builtin_string_to_upper")
      return own(BOX_PTR(lm_str_to_upper(string(0))));
    if (name == "_builtin_string_replace")
      return own(BOX_PTR(lm_str_replace(string(0), string(1), string(2))));
    std::vector<ValuePtr> values;
    for (size_t i = 0; i < count; ++i)
      values.push_back(VM::Register::register_to_value_ptr(args[i]));
    return own(VM::compiler_value_to_backend_value(
        LIR::BuiltinUtils::callBuiltinFunction(std::string(name), values)));
  }
  }
  throw std::runtime_error("Unknown native runtime helper");
}
} // namespace
// Direct typed helper implementations for Api struct
static LmValue rt_list_new(void *ctx) {
  auto &vm = *static_cast<Machine *>(ctx);
  auto *list = lm_list_new();
  LmValue val = BOX_PTR(list);
  vm.register_native_allocation(val);
  return val;
}
static LmValue rt_list_append(void *ctx, LmValue list, LmValue val) {
  if (auto *l = object<LmList>(list, TYPE_LIST)) {
    lm_list_append(l, val);
    auto &vm = *static_cast<Machine *>(ctx);
    vm.transfer_native_ownership(val, list);
    return VAL_NIL;
  }
  return helper(ctx, static_cast<uint32_t>(Helper::ListAppend), list, val, 0, nullptr, nullptr, 0);
}
static LmValue rt_list_get(void *ctx, LmValue list, LmValue idx) {
  if (auto *l = object<LmList>(list, TYPE_LIST)) {
    if (is_integer(idx)) {
      int64_t i = as_i64(idx);
      if (i >= 0 && static_cast<uint64_t>(i) < l->size)
        return l->data[i];
    }
  }
  return helper(ctx, static_cast<uint32_t>(Helper::ListGet), list, idx, 0, nullptr, nullptr, 0);
}
static LmValue rt_list_set(void *ctx, LmValue list, LmValue idx, LmValue val) {
  if (auto *l = object<LmList>(list, TYPE_LIST)) {
    if (is_integer(idx)) {
      int64_t i = as_i64(idx);
      if (i >= 0 && static_cast<uint64_t>(i) < l->size) {
        l->data[i] = val;
        auto &vm = *static_cast<Machine *>(ctx);
        vm.transfer_native_ownership(val, list);
        return VAL_NIL;
      }
    }
  }
  return helper(ctx, static_cast<uint32_t>(Helper::ListSet), list, idx, val, nullptr, nullptr, 0);
}
static LmValue rt_list_len(void *ctx, LmValue list) {
  if (auto *l = object<LmList>(list, TYPE_LIST))
    return make_i64(l->size);
  return helper(ctx, static_cast<uint32_t>(Helper::ListLen), list, 0, 0, nullptr, nullptr, 0);
}

static LmValue rt_string_new(void *ctx, const char *text, int64_t len) {
  auto &vm = *static_cast<Machine *>(ctx);
  auto *str = lm_str_from_bytes(text, len);
  LmValue val = BOX_PTR(str);
  vm.register_native_allocation(val);
  return val;
}
static LmValue rt_string_index(void *ctx, LmValue str, LmValue idx) {
  if (auto *s = object<LmStringHeader>(str, TYPE_STRING)) {
    if (is_integer(idx)) {
      int64_t i = as_i64(idx);
      if (i >= 0 && static_cast<uint64_t>(i) < s->len)
        return make_i64(static_cast<unsigned char>(s->data[i]));
    }
  }
  return helper(ctx, static_cast<uint32_t>(Helper::StringIndex), str, idx, 0, nullptr, nullptr, 0);
}
static LmValue rt_string_concat(void *ctx, LmValue a, LmValue b) {
  auto *sa = object<LmStringHeader>(a, TYPE_STRING);
  auto *sb = object<LmStringHeader>(b, TYPE_STRING);
  if (sa && sb) {
    uint64_t len = sa->len + sb->len;
    auto *res = lm_str_alloc(len);
    if (res) {
      if (sa->len) std::memcpy(res->data, sa->data, sa->len);
      if (sb->len) std::memcpy(res->data + sa->len, sb->data, sb->len);
      res->len = len;
      res->data[len] = '\0';
      auto &vm = *static_cast<Machine *>(ctx);
      LmValue val = BOX_PTR(res);
      vm.register_native_allocation(val);
      return val;
    }
  }
  return helper(ctx, static_cast<uint32_t>(Helper::Concat), a, b, 0, nullptr, nullptr, 0);
}
static LmValue rt_string_format(void *ctx, LmValue a, LmValue b) {
  return helper(ctx, static_cast<uint32_t>(Helper::Format), a, b, 0, nullptr, nullptr, 0);
}

static LmValue rt_dict_new(void *ctx) {
  auto &vm = *static_cast<Machine *>(ctx);
  auto *dict = lm_dict_new(hash_boxed_value, cmp_boxed_value);
  LmValue val = BOX_PTR(dict);
  vm.register_native_allocation(val);
  return val;
}
static LmValue rt_dict_get(void *ctx, LmValue dict, LmValue key) {
  if (auto *d = object<LmDict>(dict, TYPE_DICT))
    return lm_dict_get(d, key);
  return helper(ctx, static_cast<uint32_t>(Helper::DictGet), dict, key, 0, nullptr, nullptr, 0);
}
static LmValue rt_dict_set(void *ctx, LmValue dict, LmValue key, LmValue val) {
  if (auto *d = object<LmDict>(dict, TYPE_DICT)) {
    lm_dict_set(d, key, val);
    auto &vm = *static_cast<Machine *>(ctx);
    vm.transfer_native_ownership(key, dict);
    vm.transfer_native_ownership(val, dict);
    return VAL_NIL;
  }
  return helper(ctx, static_cast<uint32_t>(Helper::DictSet), dict, key, val, nullptr, nullptr, 0);
}
static LmValue rt_dict_has(void *ctx, LmValue dict, LmValue key) {
  if (auto *d = object<LmDict>(dict, TYPE_DICT))
    return lm_dict_contains(d, key) ? VAL_TRUE : VAL_FALSE;
  return helper(ctx, static_cast<uint32_t>(Helper::DictHas), dict, key, 0, nullptr, nullptr, 0);
}
static LmValue rt_dict_len(void *ctx, LmValue dict) {
  if (auto *d = object<LmDict>(dict, TYPE_DICT))
    return make_i64(d->size);
  return helper(ctx, static_cast<uint32_t>(Helper::DictLen), dict, 0, 0, nullptr, nullptr, 0);
}

static LmValue rt_tuple_new(void *ctx, int64_t len) {
  auto &vm = *static_cast<Machine *>(ctx);
  auto *tuple = lm_tuple_new(len);
  LmValue val = BOX_PTR(tuple);
  vm.register_native_allocation(val);
  return val;
}
static LmValue rt_tuple_get(void *ctx, LmValue tuple, LmValue idx) {
  if (auto *t = object<LmTuple>(tuple, TYPE_TUPLE)) {
    if (is_integer(idx)) {
      int64_t i = as_i64(idx);
      if (i >= 0 && static_cast<uint64_t>(i) < t->size)
        return lm_tuple_get(t, i);
    }
  }
  return helper(ctx, static_cast<uint32_t>(Helper::TupleGet), tuple, idx, 0, nullptr, nullptr, 0);
}
static LmValue rt_tuple_set(void *ctx, LmValue tuple, LmValue idx, LmValue val) {
  if (auto *t = object<LmTuple>(tuple, TYPE_TUPLE)) {
    if (is_integer(idx)) {
      int64_t i = as_i64(idx);
      if (i >= 0 && static_cast<uint64_t>(i) < t->size) {
        lm_tuple_set(t, i, val);
        auto &vm = *static_cast<Machine *>(ctx);
        vm.transfer_native_ownership(val, tuple);
        return VAL_NIL;
      }
    }
  }
  return helper(ctx, static_cast<uint32_t>(Helper::TupleSet), tuple, idx, val, nullptr, nullptr, 0);
}
static LmValue rt_tuple_len(void *ctx, LmValue tuple) {
  if (auto *t = object<LmTuple>(tuple, TYPE_TUPLE))
    return make_i64(t->size);
  return helper(ctx, static_cast<uint32_t>(Helper::TupleLen), tuple, 0, 0, nullptr, nullptr, 0);
}

static LmValue rt_frame_new(void *ctx, const char *name, int64_t fields) {
  auto &vm = *static_cast<Machine *>(ctx);
  auto *f = lm_frame_alloc(name, static_cast<int>(fields));
  LmValue val = BOX_PTR(f);
  vm.register_native_allocation(val);
  return val;
}
static LmValue rt_frame_get(void *ctx, LmValue frame, int64_t idx) {
  auto &vm = *static_cast<Machine *>(ctx);
  if (idx >= 0 && static_cast<uint64_t>(idx) <= UINT32_MAX) {
    return vm.checked_frame(frame, static_cast<uint32_t>(idx))->fields[idx];
  }
  return helper(ctx, static_cast<uint32_t>(Helper::FrameGet), frame, make_i64(idx), 0, nullptr, nullptr, 0);
}
static LmValue rt_frame_set(void *ctx, LmValue frame, int64_t idx, LmValue val) {
  auto &vm = *static_cast<Machine *>(ctx);
  if (idx >= 0 && static_cast<uint64_t>(idx) <= UINT32_MAX) {
    vm.checked_frame(frame, static_cast<uint32_t>(idx))->fields[idx] = val;
    vm.transfer_native_ownership(val, frame);
    return VAL_NIL;
  }
  return helper(ctx, static_cast<uint32_t>(Helper::FrameSet), frame, make_i64(idx), val, nullptr, nullptr, 0);
}

const Api &host_api() {
  static const Api api{
      ABI_VERSION, sizeof(Api), helper, make_i64, make_float, as_i64, as_float,
      lm_value_eq, numeric_compare, truthy, string_data,
      rt_list_new, rt_list_append, rt_list_get, rt_list_set, rt_list_len,
      rt_string_new, rt_string_index, rt_string_concat, rt_string_format,
      rt_dict_new, rt_dict_get, rt_dict_set, rt_dict_has, rt_dict_len,
      rt_tuple_new, rt_tuple_get, rt_tuple_set, rt_tuple_len,
      rt_frame_new, rt_frame_get, rt_frame_set};
  return api;
}
} // namespace LM::Backend::Native
