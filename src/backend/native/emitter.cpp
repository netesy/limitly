#include "emitter.hh"
#include "abi.hh"
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
  std::string reg(uint32_t r) {
    return r == UINT32_MAX ? "2ULL" : "r[" + std::to_string(r) + "]";
  }
  std::string integer(int64_t i) {
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
    out << "static V f" << id
        << "(const Api* api,void* ctx,const V* args,size_t count) {\n";
    size_t registers = function.register_count + 1;
    for (const auto &inst : function.instructions) {
      for (auto r : {inst.a, inst.b, inst.dst})
        if (r != UINT32_MAX)
          registers = std::max(registers, static_cast<size_t>(r) + 1);
      for (auto r : inst.call_args)
        registers = std::max(registers, static_cast<size_t>(r) + 1);
    }
    out << "V r[" << registers
        << "]; std::vector<V> staged_params; for(auto& v:r) v=2ULL; for(size_t "
           "i=0;i<count && i<"
        << registers << ";++i) r[i]=args[i];\n";
    using Op = LIR::LIR_Op;
    for (size_t i = 0; i < function.instructions.size(); ++i) {
      const auto &inst = function.instructions[i];
      out << "L" << i << ": { ";
      std::string a = reg(inst.a), b = reg(inst.b), d = reg(inst.dst), expr;
      auto h = [&](Helper type) { return helper(type, a, b); };
      switch (inst.op) {
      case Op::LoadConst:
        expr = constant(inst.const_val);
        break;
      case Op::Mov:
      case Op::Copy:
      case Op::MakeTraitObject:
        expr = a;
        break;
      case Op::Add:
        expr = h(Helper::Add);
        break;
      case Op::Sub:
        expr = h(Helper::Sub);
        break;
      case Op::Mul:
        expr = h(Helper::Mul);
        break;
      case Op::Div:
        expr = h(Helper::Div);
        break;
      case Op::Mod:
        expr = h(Helper::Mod);
        break;
      case Op::Neg:
        expr = h(Helper::Neg);
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
        expr = "(api->equal(" + a + "," + b + ")?18ULL:10ULL)";
        break;
      case Op::CmpNEQ:
        expr = "(!api->equal(" + a + "," + b + ")?18ULL:10ULL)";
        break;
      case Op::CmpLT:
      case Op::CmpLE:
      case Op::CmpGT:
      case Op::CmpGE: {
        const char *op = inst.op == Op::CmpLT   ? "<"
                         : inst.op == Op::CmpLE ? "<="
                         : inst.op == Op::CmpGT ? ">"
                                                : ">=";
        expr = "(api->compare(" + a + "," + b + ")" + op + "0?18ULL:10ULL)";
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
        out << "return " << a << ";";
        break;
      case Op::Cast:
        expr = helper(Helper::Cast, a,
                      integer(static_cast<unsigned>(inst.result_type)));
        break;
      case Op::ToString:
        expr = h(Helper::ToString);
        break;
      case Op::STR_CONCAT:
        expr = h(Helper::Concat);
        break;
      case Op::STR_FORMAT:
        expr = h(Helper::Format);
        break;
      case Op::StringIndex:
        expr = h(Helper::StringIndex);
        break;
      case Op::NewFrame:
        expr = helper(Helper::FrameNew, integer(inst.imm), "2ULL", "2ULL",
                      quote(inst.type_name));
        break;
      case Op::FrameGetField:
      case Op::FrameGetFieldAtomic:
        expr = helper(Helper::FrameGet, a, integer(inst.b));
        break;
      case Op::FrameSetField:
      case Op::FrameSetFieldAtomic:
        expr = helper(Helper::FrameSet, d, integer(inst.a), b);
        break;
      case Op::ListCreate:
        expr = helper(Helper::ListNew);
        break;
      case Op::ListAppend:
        expr = h(Helper::ListAppend);
        break;
      case Op::ListIndex:
        expr = h(Helper::ListGet);
        break;
      case Op::ListSet:
        expr = helper(Helper::ListSet, d, a, b);
        break;
      case Op::ListLen:
        expr = h(Helper::ListLen);
        break;
      case Op::DictCreate:
        expr = helper(Helper::DictNew);
        break;
      case Op::DictGet:
        expr = h(Helper::DictGet);
        break;
      case Op::DictSet:
        expr = helper(Helper::DictSet, d, a, b);
        break;
      case Op::DictHas:
        expr = h(Helper::DictHas);
        break;
      case Op::DictLen:
        expr = h(Helper::DictLen);
        break;
      case Op::DictItems:
        expr = h(Helper::DictItems);
        break;
      case Op::TupleCreate:
        expr = helper(Helper::TupleNew, integer(inst.imm));
        break;
      case Op::TupleGet:
        expr = h(Helper::TupleGet);
        break;
      case Op::TupleSet:
        expr = helper(Helper::TupleSet, d, a, b);
        break;
      case Op::TupleLen:
        expr = h(Helper::TupleLen);
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
        out << "V argv[] = {";
        for (auto arg : inst.call_args)
          out << reg(arg) << ",";
        out << "2ULL}; ";
        auto target = names.find(inst.func_name);
        if (target != names.end() && inst.op != Op::CallBuiltin)
          expr = "f" + std::to_string(target->second) + "(api,ctx,argv," +
                 std::to_string(inst.call_args.size()) + ")";
        else
          expr = helper(Helper::Builtin, "2ULL", "2ULL", "2ULL",
                        quote(inst.func_name), "argv", inst.call_args.size());
        break;
      }
      case Op::CallIndirect: {
        out << "V argv[] = {";
        for (auto arg : inst.call_args)
          out << reg(arg) << ",";
        out << "2ULL}; ";
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
      case Op::RegionEnter:
      case Op::RegionExit:
      case Op::RegionMove:
      case Op::Nop:
      case Op::Label:
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
          out << d << "=";
        out << expr << ";";
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
#include <stdexcept>
#include <vector>
#include <string_view>
using V=uint64_t;
struct Api { uint32_t version; uint32_t size;
V(*helper)(void*,uint32_t,V,V,V,const char*,const V*,size_t);
V(*integer)(int64_t); V(*floating)(double); int64_t(*read_int)(V); double(*read_float)(V);
int(*equal)(V,V); int(*compare)(V,V); bool(*truthy)(V); const char*(*string_data)(V); };
extern "C" __attribute__((visibility("default"))) uint32_t lymar_module_abi_version() { return 2; }
)CPP";
    emitter.out << "static V indirect(const Api*,void*,V,const V*,size_t);\n";
    for (size_t i = 0; i < emitter.functions.size(); ++i)
      emitter.out << "static V f" << i
                  << "(const Api*,void*,const V*,size_t);\n";
    for (size_t i = 0; i < emitter.functions.size(); ++i)
      emitter.emit_function(*emitter.functions[i], i);
    emitter.out
        << "static V indirect(const Api* api,void* ctx,V target,const V* "
           "args,size_t count) { std::string_view name=api->string_data("
        << emitter.helper(Helper::CallableName, "target")
        << "); std::vector<V> bound(args,args+count); if(api->truthy("
        << emitter.helper(Helper::ClosureBound, "target")
        << ")) bound.push_back(target);\n";
    for (size_t i = 0; i < emitter.functions.size(); ++i)
      emitter.out << "if(name==" << quote(emitter.functions[i]->name)
                  << ") return f" << i
                  << "(api,ctx,bound.data(),bound.size());\n";
    emitter.out
        << "return api->helper(ctx," << static_cast<unsigned>(Helper::Callback)
        << ",target,2ULL,2ULL,name.data(),bound.data(),bound.size()); }\n";
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
             "|| api->version!=2 || api->size!=sizeof(Api)) throw "
             "std::runtime_error(\"Lymar native module ABI mismatch\"); "
             "if(count!="
          << function.param_count
          << ") throw std::runtime_error(\"Lymar native argument count "
             "mismatch\"); return f"
          << i << "(api,ctx,args,count); }\n";
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
