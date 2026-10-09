#include "emitter.hh"
#include "abi.hh"
#include "scalar_lowering.hh"
#include "backend/vm/vm_list.hh"
#include "backend/vm/vm_runtime.hh"
#include "backend/vm/vm_string.hh"
#include "backend/vm/vm_value.hh"
#include "lir/builtin_functions.hh"
#include "lir/function_registry.hh"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

namespace LM::Backend::Native {
namespace {
std::string quote(const std::string &text) {
  std::ostringstream out;
  out << '"';
  for (unsigned char c : text) {
    if (c >= 32 && c <= 126 && c != '"' && c != '\\')
      out << c;
    else
      out << '\\' << std::oct << std::setw(3) << std::setfill('0')
          << static_cast<unsigned>(c) << std::dec;
  }
  return out.str() + '"';
}
std::string shell_quote(const std::string &text) {
  std::string result = "'";
  for (char c : text)
    result += c == '\'' ? "'\\''" : std::string(1, c);
  return result + "'";
}
struct Emitter {
  std::ostringstream out;
  std::unordered_map<std::string, size_t> names;
  std::vector<const LIR::LIR_Function *> functions;
  std::unordered_set<size_t> reference_functions;
  std::string raw(uint32_t r) {
    return r == UINT32_MAX ? "N(2ULL)" : "r[" + std::to_string(r) + "]";
  }
  std::string reg(uint32_t r) {
    return r == UINT32_MAX ? "2ULL" : raw(r) + ".boxed(api,ctx)";
  }
  std::string integer(int64_t i) {
    if (fits_smi_i64(i)) return std::to_string(BOX_INT(i)) + "ULL";
    return "api->integer(" + std::to_string(i) + "LL)";
  }
  std::string helper(Helper h, const std::string &a = "2ULL",
                     const std::string &b = "2ULL",
                     const std::string &c = "2ULL",
                     const std::string &text = "nullptr",
                     const std::string &args = "nullptr", size_t count = 0) {
    return "api->helper(ctx," + std::to_string(static_cast<unsigned>(h)) + "," +
           a + "," + b + "," + c + "," + text + "," + args + "," +
           std::to_string(count) + ")";
  }
  std::string constant(LmValue value) {
    if (IS_INT(value))
      return integer(UNBOX_INT(value));
    if (IS_BOOL(value) || IS_NIL(value) || !value)
      return std::to_string(value) + "ULL";
    if (auto *header = IS_PTR(value)
                           ? static_cast<ObjHeader *>(UNBOX_PTR(value))
                           : nullptr) {
      if (header->type_id == TYPE_STRING) {
        auto *s = reinterpret_cast<LmStringHeader *>(header);
        return helper(Helper::StringNew, integer(s->len), "2ULL", "2ULL",
                      quote(std::string(s->data, s->len)));
      }
      if (is_integer(value))
        return integer(as_i64(value));
      if (is_float(value)) {
        std::ostringstream x;
        x << std::hexfloat << as_float(value);
        return "api->floating(" + x.str() + ")";
      }
      if (header->type_id == TYPE_LIST &&
          reinterpret_cast<LmList *>(header)->size == 0)
        return helper(Helper::ListNew);
    }
    throw std::runtime_error("Unsupported native constant object");
  }
  void discover(const LIR::LIR_Function &root, const std::string &module) {
    auto &registry = LIR::FunctionRegistry::getInstance();
    std::vector<const LIR::LIR_Function *> pending{&root};
    for (const auto &name : registry.getFunctionNames())
      if (name.starts_with(module + "."))
        pending.push_back(registry.getFunction(name));
    for (size_t i = 0; i < pending.size(); ++i) {
      auto *function = pending[i];
      if (!function || names.count(function->name) ||
          LIR::BuiltinUtils::isBuiltinFunction(function->name))
        continue;
      names[function->name] = functions.size();
      functions.push_back(function);
      for (const auto& inst : function->instructions)
        if (inst.op == LIR::LIR_Op::RefCreate || inst.op == LIR::LIR_Op::RefResolve || inst.op == LIR::LIR_Op::RefMove ||
            inst.op == LIR::LIR_Op::RefRelease || inst.op == LIR::LIR_Op::OwnershipConsume)
          reference_functions.insert(functions.size() - 1);
      for (const auto &inst : function->instructions) {
        if (inst.op == LIR::LIR_Op::LoadConst && IS_PTR(inst.const_val)) {
          auto *header = static_cast<ObjHeader *>(UNBOX_PTR(inst.const_val));
          if (header->type_id == TYPE_STRING) {
            auto *text = reinterpret_cast<LmStringHeader *>(header);
            if (auto *target =
                    registry.getFunction(std::string(text->data, text->len)))
              pending.push_back(target);
          }
        }
        if (inst.op == LIR::LIR_Op::Call || inst.op == LIR::LIR_Op::CallVoid ||
            inst.op == LIR::LIR_Op::CallVariadic) {
          if (auto *target = registry.getFunction(inst.func_name))
            pending.push_back(target);
        }
      }
    }
  }
  void emit_function(const LIR::LIR_Function &function, size_t id) {
    out << "// " << function.name << "\n";
    out << "static N f" << id
        << "(const Api* api,void* ctx,const N* args,size_t count) {\n";
    size_t registers = function.register_count + 1;
    for (const auto &inst : function.instructions) {
      for (auto r : {inst.a, inst.b, inst.dst})
        if (r != UINT32_MAX)
          registers = std::max(registers, static_cast<size_t>(r) + 1);
      for (auto r : inst.call_args)
        registers = std::max(registers, static_cast<size_t>(r) + 1);
    }
    out << "N r[" << registers
        << "]; std::vector<V> staged_params; for(auto& v:r) v=N(2ULL); for(size_t "
           "i=0;i<count && i<"
        << registers << ";++i) r[i]=args[i];\n";
    out << "NativeScope scope(api,ctx);\n";
    using Op = LIR::LIR_Op;
    const bool references = std::any_of(function.instructions.begin(), function.instructions.end(), [](const auto& in) {
      return in.op == Op::RefCreate || in.op == Op::RefResolve || in.op == Op::RefMove ||
             in.op == Op::RefRelease || in.op == Op::OwnershipConsume;
    });
    auto numeric_type = [](LIR::Type t) { return t == LIR::Type::F64 || t == LIR::Type::F32 || t == LIR::Type::I64; };
    auto known_numeric = [&](uint32_t r, LIR::Type hint) {
      if (numeric_type(hint)) return true;
      auto it = function.register_types.find(r);
      return it != function.register_types.end() && numeric_type(it->second);
    };
    if (!references) {
      for (uint32_t param = 0; param < function.param_count; ++param) {
        auto type = function.register_types.find(param);
        if (type != function.register_types.end() &&
            (type->second == LIR::Type::F64 || type->second == LIR::Type::F32))
          out << raw(param) << ".cache_float(api);\n";
      }
    }
    for (size_t i = 0; i < function.instructions.size(); ++i) {
      const auto &inst = function.instructions[i];
      out << "L" << i << ": { ";
      std::string a = reg(inst.a), b = reg(inst.b), d = reg(inst.dst), expr;
      auto h = [&](Helper type) { return helper(type, a, b); };
      const bool typed = !references && known_numeric(inst.a, inst.type_a) && known_numeric(inst.b, inst.type_b);
      auto arith = [&](Helper type) {
        return "arithmetic(api,ctx," + std::to_string(static_cast<unsigned>(type)) + "," + raw(inst.a) + "," + raw(inst.b) + "," + (typed ? "true" : "false") + ")";
      };
      switch (inst.op) {
      case Op::LoadConst:
        if (!references && is_float(inst.const_val)) {
          std::ostringstream number; number << std::hexfloat << as_float(inst.const_val);
          expr = "real(api,ctx," + number.str() + ")";
        } else expr = constant(inst.const_val);
        break;
      case Op::Mov:
      case Op::Copy:
        expr = raw(inst.a);
        break;
      case Op::MakeTraitObject:
        expr = a;
        break;
      case Op::Add:
        expr = arith(Helper::Add);
        break;
      case Op::Sub:
        expr = arith(Helper::Sub);
        break;
      case Op::Mul:
        expr = arith(Helper::Mul);
        break;
      case Op::Div:
        expr = arith(Helper::Div);
        break;
      case Op::Mod:
        expr = arith(Helper::Mod);
        break;
      case Op::Neg:
        expr = "arithmetic(api,ctx," + std::to_string(static_cast<unsigned>(Helper::Sub)) + ",N(1ULL)," + raw(inst.a) + "," + (!references && known_numeric(inst.a, inst.type_a) ? "true" : "false") + ")";
        break;
      case Op::And:
      case Op::Or:
      case Op::Xor: {
        const char *op = inst.op == Op::And  ? "&"
                         : inst.op == Op::Or ? "|"
                                             : "^";
        expr = "api->integer(api->read_int(" + a + ")" + op + "api->read_int(" +
               b + "))";
        break;
      }
      case Op::Shl:
        expr = "api->integer(static_cast<int64_t>(static_cast<uint64_t>(api->"
               "read_int(" +
               a + ")) << (api->read_int(" + b + ")&63)))";
        break;
      case Op::Shr:
        expr = "api->integer(api->read_int(" + a + ") >> (api->read_int(" + b +
               ")&63))";
        break;
      case Op::CmpEQ:
        expr = "(equal(api,ctx," + raw(inst.a) + "," + raw(inst.b) + "," + (typed ? "true" : "false") + ")?18ULL:10ULL)";
        break;
      case Op::CmpNEQ:
        expr = "(!equal(api,ctx," + raw(inst.a) + "," + raw(inst.b) + "," + (typed ? "true" : "false") + ")?18ULL:10ULL)";
        break;
      case Op::CmpLT:
      case Op::CmpLE:
      case Op::CmpGT:
      case Op::CmpGE: {
        const char *op = inst.op == Op::CmpLT   ? "<"
                         : inst.op == Op::CmpLE ? "<="
                         : inst.op == Op::CmpGT ? ">"
                                                : ">=";
        expr = "(compare(api,ctx," + raw(inst.a) + "," + raw(inst.b) + "," + (typed ? "true" : "false") + ")" + op + "0?18ULL:10ULL)";
        break;
      }
      case Op::Jump:
        out << "goto L" << inst.imm << ";";
        break;
      case Op::JumpIf:
      case Op::JumpIfFalse:
        out << "if(" << (inst.op == Op::JumpIfFalse ? "!" : "")
            << "api->truthy(" << a << ")) goto L" << inst.imm << ";";
        break;
      case Op::Return:
      case Op::Ret:
        out << "scope.result=" << raw(inst.a) << ".value?" << raw(inst.a) << ".value:2ULL;return " << raw(inst.a) << ";";
        break;
      case Op::Cast:
        expr = helper(Helper::Cast, a, integer(static_cast<unsigned>(inst.result_type)));
        if (!references && inst.result_type == LIR::Type::I64)
          expr = "(" + raw(inst.a) + ".floating() && std::isfinite(" + raw(inst.a) + ".number(api)) && " + raw(inst.a) + ".number(api)>=-0x1p60 && " + raw(inst.a) + ".number(api)<0x1p60 ? N((static_cast<V>(static_cast<int64_t>(" + raw(inst.a) + ".number(api)))<<3)|1ULL):N(" + expr + "))";
        if (!references && (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32))
          expr = "(" + raw(inst.a) + ".numeric()?real(api,ctx," + raw(inst.a) + ".number(api)):N(" + expr + "))";
        break;
      case Op::ToString:
        expr = h(Helper::ToString);
        break;
      case Op::STR_CONCAT:
        expr = "api->string_concat(ctx," + a + "," + b + ")";
        break;
      case Op::STR_FORMAT:
        expr = "api->string_format(ctx," + a + "," + b + ")";
        break;
      case Op::StringIndex:
        expr = "api->string_index(ctx," + a + "," + b + ")";
        break;
      case Op::NewFrame:
        expr = "api->frame_new(ctx," + quote(inst.type_name) + "," + std::to_string(inst.imm) + "LL)";
        break;
      case Op::FrameGetField:
        expr = "api->frame_get(ctx," + a + "," + std::to_string(inst.b) + "LL)";
        break;
      case Op::FrameGetFieldAtomic:
        expr = helper(Helper::FrameGet, a, integer(inst.b), "1ULL");
        break;
      case Op::FrameSetField:
        expr = "api->frame_set(ctx," + d + "," + std::to_string(inst.a) + "LL," + b + ")";
        break;
      case Op::FrameSetFieldAtomic:
        expr = helper(Helper::FrameSet, d, integer(inst.a), b, "\"atomic\"");
        break;
      case Op::ListCreate:
        expr = "api->list_new(ctx)";
        break;
      case Op::ListAppend:
        expr = "api->list_append(ctx," + a + "," + b + ")";
        break;
      case Op::ListIndex:
        expr = "api->list_get(ctx," + a + "," + b + ")";
        break;
      case Op::ListSet:
        expr = "api->list_set(ctx," + d + "," + a + "," + b + ")";
        break;
      case Op::ListLen:
        expr = "api->list_len(ctx," + a + ")";
        break;
      case Op::DictCreate:
        expr = "api->dict_new(ctx)";
        break;
      case Op::DictGet:
        expr = "api->dict_get(ctx," + a + "," + b + ")";
        break;
      case Op::DictSet:
        expr = "api->dict_set(ctx," + d + "," + a + "," + b + ")";
        break;
      case Op::DictHas:
        expr = "api->dict_has(ctx," + a + "," + b + ")";
        break;
      case Op::DictLen:
        expr = "api->dict_len(ctx," + a + ")";
        break;
      case Op::DictItems:
        expr = h(Helper::DictItems);
        break;
      case Op::TupleCreate:
        expr = "api->tuple_new(ctx," + std::to_string(inst.imm) + "LL)";
        break;
      case Op::TupleGet:
        expr = "api->tuple_get(ctx," + a + "," + b + ")";
        break;
      case Op::TupleSet:
        expr = "api->tuple_set(ctx," + d + "," + a + "," + b + ")";
        break;
      case Op::TupleLen:
        expr = "api->tuple_len(ctx," + a + ")";
        break;
      case Op::ConstructOk:
        expr = h(Helper::Ok);
        break;
      case Op::ConstructError:
        out << "V error_payload=" << a
            << "; if(!staged_params.empty()) { "
               "error_payload=staged_params.back(); staged_params.pop_back(); "
               "} ";
        expr = helper(Helper::Error, "error_payload");
        break;
      case Op::IsError:
        expr = h(Helper::IsError);
        break;
      case Op::Unwrap:
        expr = h(Helper::Unwrap);
        break;
      case Op::UnwrapOr:
        expr = h(Helper::UnwrapOr);
        break;
      case Op::MakeEnum:
        expr = helper(Helper::Enum, a, integer(inst.imm), "2ULL",
                      quote(inst.func_name));
        break;
      case Op::GetTag:
        expr = h(Helper::Tag);
        break;
      case Op::GetPayload:
        expr = h(Helper::Payload);
        break;
      case Op::LoadGlobal:
        expr = helper(Helper::GlobalGet, "2ULL", "2ULL", "2ULL",
                      quote(inst.func_name));
        break;
      case Op::StoreGlobal:
        expr =
            helper(Helper::GlobalSet, a, "2ULL", "2ULL", quote(inst.func_name));
        break;
      case Op::Call:
      case Op::CallVoid:
      case Op::CallBuiltin:
      case Op::CallVariadic: {
        auto target = names.find(inst.func_name);
        const bool internal = target != names.end() && inst.op != Op::CallBuiltin;
        if (internal) {
          std::unordered_set<uint32_t> materialized;
          const auto& callee = *functions[target->second];
          for (size_t index = 0; index < inst.call_args.size(); ++index) {
            auto param_type = callee.register_types.find(index);
            const bool numeric_parameter = param_type != callee.register_types.end() && numeric_type(param_type->second);
            auto arg = inst.call_args[index];
            if ((!numeric_parameter || reference_functions.count(target->second)) && materialized.insert(arg).second)
              out << raw(arg) << "=N(" << reg(arg) << ");";
          }
        }
        out << (internal ? "N" : "V") << " argv[] = {";
        for (auto arg : inst.call_args) out << (internal ? raw(arg) : reg(arg)) << ",";
        out << (internal ? "N(2ULL)" : "2ULL") << "}; ";
        if (internal) {
          expr = "f" + std::to_string(target->second) + "(api,ctx,argv," + std::to_string(inst.call_args.size()) + ")";
          if (inst.op != Op::CallVoid && inst.dst != UINT32_MAX && !known_numeric(inst.dst, inst.result_type))
            expr = "N(" + expr + ".boxed(api,ctx))";
        } else expr = helper(Helper::Builtin, "2ULL", "2ULL", "2ULL", quote(inst.func_name), "argv", inst.call_args.size());
        break;
      }
      case Op::CallIndirect: {
        std::unordered_set<uint32_t> materialized;
        for (auto arg : inst.call_args) if (materialized.insert(arg).second)
          out << raw(arg) << "=N(" << reg(arg) << ");";
        out << "N argv[] = {";
        // Unknown callable effects form an erased boundary.
        for (auto arg : inst.call_args) out << "N(" << reg(arg) << "),";
        out << "N(2ULL)}; ";
        expr = "indirect(api,ctx," + a + ",argv," +
               std::to_string(inst.call_args.size()) + ")";
        break;
      }
      case Op::ResourceCreate:
        expr = h(Helper::ResourceCreate);
        break;
      case Op::ResourceDestroy:
        expr = h(Helper::ResourceDestroy);
        break;
      case Op::ResourceCall: {
        out << "V argv[] = {";
        for (size_t n = 2; n < inst.call_args.size(); ++n)
          out << reg(inst.call_args[n]) << ",";
        out << "2ULL}; ";
        expr = helper(
            Helper::ResourceCall, a,
            inst.b == UINT32_MAX ? integer(inst.imm) : b, "2ULL", "nullptr",
            "argv", inst.call_args.size() > 2 ? inst.call_args.size() - 2 : 0);
        break;
      }
      // Allocations remain in the caller's region, retaining all aliases
      // until control returns to the VM's scope-exit ownership machinery.
      case Op::RefCreate:
        expr = helper(Helper::RefCreate, a, integer(inst.imm)); break;
      case Op::RefResolve:
        expr = helper(Helper::RefResolve, a, integer(inst.imm)); break;
      case Op::RefMove:
        expr = helper(Helper::RefMove, a, integer(inst.imm)); break;
      case Op::RefRelease:
        out << helper(Helper::RefRelease, a, integer(inst.imm)) << ";"; break;
      case Op::OwnershipConsume:
        out << helper(Helper::OwnershipConsume, a) << ";"; break;
      case Op::RegionEnter:
      case Op::RegionExit: {
        out << "V argv[]={" << integer(inst.imm) << "};";
        out << helper(Helper::Builtin, "2ULL", "2ULL", "2ULL",
            inst.op == Op::RegionEnter ? "\"_builtin_region_enter\"" : "\"_builtin_region_exit\"", "argv", 1) << ";";
        break;
      }
      case Op::RegionMove:
        // A virtual scalar has no allocation graph to promote. Boxing it
        // solely for promotion would allocate an unused object in the parent
        // region. Keep target validation, passing nil for the absent graph.
        out << "V argv[]={" << raw(inst.a) << ".value?" << a << ":2ULL," << integer(inst.imm) << "};";
        out << helper(Helper::Builtin, "2ULL", "2ULL", "2ULL", "\"_builtin_region_move\"", "argv", 2) << ";";
        break;
      case Op::FrameCallDeinit:
        out << "V argv[]={" << a << "};";
        out << helper(Helper::Builtin, "2ULL", "2ULL", "2ULL", "\"_builtin_frame_deinit\"", "argv", 1) << ";";
        break;
      case Op::Nop:
      case Op::Label:
        break;
      case Op::Param:
        out << "staged_params.push_back(" << d << ");";
        break;
      case Op::FuncDef:
      case Op::BeginModule:
      case Op::EndModule:
      case Op::ImportModule:
      case Op::ExportSymbol:
      case Op::FrameCallInit:
      case Op::FrameCallMethod:
        break;
      default:
        throw std::runtime_error(
            "Native shared-module lowering missing opcode " +
            LIR::lir_op_to_string(inst.op) + " in " + function.name);
      }
      if (!expr.empty()) {
        const bool mutation =
            inst.op == Op::FrameSetField ||
            inst.op == Op::FrameSetFieldAtomic || inst.op == Op::ListSet ||
            inst.op == Op::DictSet || inst.op == Op::TupleSet ||
            inst.op == Op::ListAppend || inst.op == Op::StoreGlobal ||
            inst.op == Op::ResourceDestroy || inst.op == Op::CallVoid ||
            inst.op == Op::RegionMove;
        if (inst.dst != UINT32_MAX && !mutation)
          {
            out << raw(inst.dst) << "=scope.track(" << expr << ");";
            auto type = function.register_types.find(inst.dst);
            if (!references && (inst.result_type == LIR::Type::F64 || inst.result_type == LIR::Type::F32 ||
                (type != function.register_types.end() && (type->second == LIR::Type::F64 || type->second == LIR::Type::F32))))
              out << raw(inst.dst) << ".cache_float(api);";
          }
        else out << expr << ";";
      }
      out << " }\n";
    }
    out << "L" << function.instructions.size() << ": return 2ULL; }\n";
  }
};
} // namespace
bool emit_shared_module(const LIR::LIR_Function &root,
                        const std::string &module, const std::string &output,
                        int optimization, std::string &error) {
  std::string temporary;
  try {
    Emitter emitter;
    emitter.discover(root, module);
    emitter.out << R"CPP(#include <cstdint>
#include <cstddef>
#include <array>
#include <stdexcept>
#include <vector>
#include <string_view>
#include <cstring>
#include <cmath>
using V=uint64_t;
struct Api { uint32_t version; uint32_t size;
V(*helper)(void*,uint32_t,V,V,V,const char*,const V*,size_t);
V(*integer)(int64_t); V(*floating)(double); int64_t(*read_int)(V); double(*read_float)(V);
int(*equal)(V,V); int(*compare)(V,V); bool(*truthy)(V); const char*(*string_data)(V);
V(*list_new)(void*); V(*list_append)(void*,V,V); V(*list_get)(void*,V,V); V(*list_set)(void*,V,V,V); V(*list_len)(void*,V);
V(*string_new)(void*,const char*,int64_t); V(*string_index)(void*,V,V); V(*string_concat)(void*,V,V); V(*string_format)(void*,V,V);
V(*dict_new)(void*); V(*dict_get)(void*,V,V); V(*dict_set)(void*,V,V,V); V(*dict_has)(void*,V,V); V(*dict_len)(void*,V);
V(*tuple_new)(void*,int64_t); V(*tuple_get)(void*,V,V); V(*tuple_set)(void*,V,V,V); V(*tuple_len)(void*,V);
V(*frame_new)(void*,const char*,int64_t); V(*frame_get)(void*,V,int64_t); V(*frame_set)(void*,V,int64_t,V); };
)CPP";
    emitter.out << "extern \"C\" __attribute__((visibility(\"default\"))) uint32_t lymar_module_abi_version() { return " << ABI_VERSION << "; }\n";
    emitter.out << "constexpr uint32_t HBuiltin=" << static_cast<unsigned>(Helper::Builtin)
        << ", HAdd=" << static_cast<unsigned>(Helper::Add) << ", HSub=" << static_cast<unsigned>(Helper::Sub)
        << ", HMul=" << static_cast<unsigned>(Helper::Mul) << ", HDiv=" << static_cast<unsigned>(Helper::Div)
        << ", HMod=" << static_cast<unsigned>(Helper::Mod)
        << ", HFloat=" << TYPE_FLOAT << ";\n" << scalar_lowering_source;
    emitter.out << "struct NativeScope { const Api* api; void* ctx; V depth; V result=2ULL; "
        "NativeScope(const Api* a,void* c):api(a),ctx(c),depth("
        << emitter.helper(Helper::Builtin, "2ULL", "2ULL", "2ULL", "\"_builtin_region_call_enter\"")
        << "){} V track(V value){ if((value&7ULL)!=0 || !value) return value; V argv[]={value}; return "
        << emitter.helper(Helper::Builtin, "2ULL", "2ULL", "2ULL", "\"_builtin_track\"", "argv", 1)
        << "; } N track(N n){if(n.value)track(n.value);return n;} ~NativeScope(){ V argv[]={depth,result}; "
        << emitter.helper(Helper::Builtin, "2ULL", "2ULL", "2ULL", "\"_builtin_region_call_leave\"", "argv", 2)
        << ";} };\n";
    emitter.out << "static N indirect(const Api*,void*,V,const N*,size_t);\n";
    for (size_t i = 0; i < emitter.functions.size(); ++i)
      emitter.out << "static N f" << i
                  << "(const Api*,void*,const N*,size_t);\n";
    for (size_t i = 0; i < emitter.functions.size(); ++i)
      emitter.emit_function(*emitter.functions[i], i);
    emitter.out
        << "static N indirect(const Api* api,void* ctx,V target,const N* "
           "args,size_t count) { std::string_view name=api->string_data("
        << emitter.helper(Helper::CallableName, "target")
        << "); std::vector<N> bound(args,args+count); if(api->truthy("
        << emitter.helper(Helper::ClosureBound, "target")
        << ")) bound.push_back(target);\n";
    for (size_t i = 0; i < emitter.functions.size(); ++i)
      emitter.out << "if(name==" << quote(emitter.functions[i]->name)
                  << ") return f" << i
                  << "(api,ctx,bound.data(),bound.size());\n";
    emitter.out
        << "std::vector<V> boxed; for(const auto& arg:bound)boxed.push_back(arg.boxed(api,ctx)); return api->helper(ctx," << static_cast<unsigned>(Helper::Callback)
        << ",target,2ULL,2ULL,name.data(),boxed.data(),boxed.size()); }\n";
    for (size_t i = 0; i < emitter.functions.size(); ++i) {
      const auto &function = *emitter.functions[i];
      if (!function.name.starts_with(module + "."))
        continue;
      emitter.out
          << "extern \"C\" __attribute__((visibility(\"default\"))) V export"
          << i << "(const Api*,void*,const V*,size_t) asm("
          << quote(function.name) << ");\n";
      emitter.out
          << "extern \"C\" __attribute__((visibility(\"default\"))) V export"
          << i
          << "(const Api* api,void* ctx,const V* args,size_t count) { if(!api "
             "|| api->version!=" << ABI_VERSION << " || api->size!=sizeof(Api)) throw "
             "std::runtime_error(\"Lymar native module ABI mismatch\"); "
             "if(count!="
          << function.param_count
          << ") throw std::runtime_error(\"Lymar native argument count "
             "mismatch\"); std::array<N,"
          << function.param_count
          << "> native;for(size_t i=0;i<count;i++)native[i]=N(args[i]);return f"
          << i << "(api,ctx,native.data(),count).boxed(api,ctx); }\n";
    }
    temporary =
        output + ".lymar-" +
        std::to_string(
            std::chrono::steady_clock::now().time_since_epoch().count()) +
        ".cpp";
    {
      std::ofstream file(temporary);
      if (!file)
        throw std::runtime_error("Cannot write native module source");
      file << emitter.out.str();
    }
    const char *configured = std::getenv("LYMAR_NATIVE_CXX");
    const std::string compiler = configured ? configured : "c++";
    const std::string command =
        shell_quote(compiler) + " -std=c++20 -shared -fPIC -O" +
        std::to_string(std::clamp(optimization, 0, 3)) +
        " -fvisibility=hidden " + shell_quote(temporary) + " -o " +
        shell_quote(output);
    // Explicit exported visibility is required despite hidden internal helpers.
    if (std::system(command.c_str()) != 0)
      throw std::runtime_error(
          "Host native C++ compilation failed; generated source retained at " +
          temporary);
    if (!std::getenv("LYMAR_KEEP_NATIVE_SOURCE"))
      std::filesystem::remove(temporary);
    return true;
  } catch (const std::exception &exception) {
    error = exception.what();
    return false;
  }
}
} // namespace LM::Backend::Native
