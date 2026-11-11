#include "../register.hh"
#include "../vm_value.hh"
#include "../vm_string.hh"
#include "../vm_list.hh"
#include "../vm_tuple.hh"
#include "../../../lir/function_registry.hh"

#include <string>
#include <vector>

namespace LM {
namespace Backend {
namespace VM {
namespace Register {

namespace {

// Extract a callable name from a first-class function value. Mirrors the
// CallIndirect resolution: plain string, string box, or closure tuple whose
// first element is the name.
std::string gpu_extract_callable_name(RegisterValue func_obj) {
    if (!IS_PTR(func_obj)) return "";
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(func_obj);
    if (!h) return "";
    if (h->type_id == TYPE_BOX && ((LmBox*)h)->type == LM_BOX_STRING) {
        return (char*)((LmBox*)h)->value.as_ptr;
    }
    if (h->type_id == TYPE_STRING) {
        return ((LmStringHeader*)h)->data;
    }
    if (h->type_id == TYPE_TUPLE) {
        LmTuple* closure_tuple = (LmTuple*)h;
        RegisterValue name_value = lm_tuple_get(closure_tuple, 0);
        if (IS_PTR(name_value)) {
            ObjHeader* name_header = (ObjHeader*)UNBOX_PTR(name_value);
            if (name_header->type_id == TYPE_BOX && ((LmBox*)name_header)->type == LM_BOX_STRING) {
                return (char*)((LmBox*)name_header)->value.as_ptr;
            }
            if (name_header->type_id == TYPE_STRING) {
                return ((LmStringHeader*)name_header)->data;
            }
        }
    }
    return "";
}

LmList* gpu_as_list(RegisterValue v) {
    if (!IS_PTR(v)) return nullptr;
    ObjHeader* h = (ObjHeader*)UNBOX_PTR(v);
    if (h && h->type_id == TYPE_LIST) return (LmList*)h;
    return nullptr;
}

} // namespace

void RegisterVM::execute_gpu(const LIR::LIR_Inst* pc) {
    const std::string& fname = pc->func_name;

    // gpu_thread_id / gpu_local_id / gpu_group_id / gpu_num_groups -> [x, y, z]
    if (fname == "gpu_thread_id" || fname == "gpu_local_id" ||
        fname == "gpu_group_id" || fname == "gpu_num_groups") {
        const int64_t* coords =
            fname == "gpu_thread_id" ? nullptr :
            fname == "gpu_local_id" ? gpu_local_id_ :
            fname == "gpu_group_id" ? gpu_group_id_ : gpu_num_groups_;
        int64_t x, y, z;
        if (fname == "gpu_thread_id") {
            // Global invocation id = group_id * local_size + local_id.
            // local_size is recovered as group*size+local - group*size; we store
            // the per-axis thread dims implicitly via num_groups and local ids,
            // so compute global coords directly from saved dispatch dims.
            x = gpu_group_id_[0] * gpu_thread_dims_[0] + gpu_local_id_[0];
            y = gpu_group_id_[1] * gpu_thread_dims_[1] + gpu_local_id_[1];
            z = gpu_group_id_[2] * gpu_thread_dims_[2] + gpu_local_id_[2];
        } else {
            x = coords[0]; y = coords[1]; z = coords[2];
        }
        LmList* list = lm_list_new();
        lm_list_append(list, make_i64(x));
        lm_list_append(list, make_i64(y));
        lm_list_append(list, make_i64(z));
        if (pc->dst != UINT32_MAX && pc->dst < registers.size()) {
            registers[pc->dst] = BOX_PTR(list);
            register_native_allocation(registers[pc->dst]);
        }
        return;
    }

    if (fname == "gpu_sync") {
        // Single-threaded emulation: workgroup barriers are implicit.
        if (pc->dst != UINT32_MAX && pc->dst < registers.size()) {
            registers[pc->dst] = VAL_NIL;
        }
        return;
    }

    if (fname == "gpu_set_mesh_counts" && pc->call_args.size() >= 2) {
        gpu_mesh_vertices_ = as_i64(registers[pc->call_args[0]]);
        gpu_mesh_primitives_ = as_i64(registers[pc->call_args[1]]);
        if (pc->dst != UINT32_MAX && pc->dst < registers.size()) {
            registers[pc->dst] = VAL_NIL;
        }
        return;
    }

    if (fname == "gpu_dispatch" && pc->call_args.size() >= 5) {
        RegisterValue task_val = registers[pc->call_args[0]];
        std::string task_name = gpu_extract_callable_name(task_val);
        if (task_name.empty()) {
            throw std::runtime_error("gpu_dispatch: first argument must be a gpu task function");
        }
        int64_t gx = as_i64(registers[pc->call_args[1]]);
        int64_t gy = as_i64(registers[pc->call_args[2]]);
        int64_t gz = as_i64(registers[pc->call_args[3]]);
        if (gx <= 0 || gy <= 0 || gz <= 0) {
            throw std::runtime_error("gpu_dispatch: grid dimensions must be positive");
        }

        auto* task = LIR::FunctionRegistry::getInstance().getFunction(task_name);
        if (!task) {
            throw std::runtime_error("gpu_dispatch: unknown gpu task '" + task_name + "'");
        }
        if (task->gpu_stage != 1) {
            throw std::runtime_error("gpu_dispatch: '" + task_name + "' is not a gpu task");
        }

        // Collect call arguments from the trailing list argument.
        std::vector<RegisterValue> arg_vals;
        RegisterValue args_list = registers[pc->call_args[4]];
        if (LmList* list = gpu_as_list(args_list)) {
            arg_vals.reserve(list->size);
            for (uint64_t i = 0; i < list->size; ++i) {
                arg_vals.push_back(list->data[i]);
            }
        } else if (args_list != VAL_NIL) {
            arg_vals.push_back(args_list);
        }

        const int64_t tx = task->gpu_threads[0];
        const int64_t ty = task->gpu_threads[1];
        const int64_t tz = task->gpu_threads[2];

        // Save outer thread context (nested dispatch support).
        int64_t saved_local[3] = {gpu_local_id_[0], gpu_local_id_[1], gpu_local_id_[2]};
        int64_t saved_group[3] = {gpu_group_id_[0], gpu_group_id_[1], gpu_group_id_[2]};
        int64_t saved_dims[3] = {gpu_thread_dims_[0], gpu_thread_dims_[1], gpu_thread_dims_[2]};
        int64_t saved_ngroups[3] = {gpu_num_groups_[0], gpu_num_groups_[1], gpu_num_groups_[2]};

        gpu_thread_dims_[0] = tx; gpu_thread_dims_[1] = ty; gpu_thread_dims_[2] = tz;
        gpu_num_groups_[0] = gx; gpu_num_groups_[1] = gy; gpu_num_groups_[2] = gz;

        try {
            for (int64_t gz_i = 0; gz_i < gz * tz; ++gz_i) {
                for (int64_t gy_i = 0; gy_i < gy * ty; ++gy_i) {
                    for (int64_t gx_i = 0; gx_i < gx * tx; ++gx_i) {
                        gpu_local_id_[0] = gx_i % tx;
                        gpu_local_id_[1] = gy_i % ty;
                        gpu_local_id_[2] = gz_i % tz;
                        gpu_group_id_[0] = gx_i / tx;
                        gpu_group_id_[1] = gy_i / ty;
                        gpu_group_id_[2] = gz_i / tz;
                        call_interpreted(task, arg_vals.data(), arg_vals.size());
                    }
                }
            }
        } catch (...) {
            gpu_local_id_[0] = saved_local[0]; gpu_local_id_[1] = saved_local[1]; gpu_local_id_[2] = saved_local[2];
            gpu_group_id_[0] = saved_group[0]; gpu_group_id_[1] = saved_group[1]; gpu_group_id_[2] = saved_group[2];
            gpu_thread_dims_[0] = saved_dims[0]; gpu_thread_dims_[1] = saved_dims[1]; gpu_thread_dims_[2] = saved_dims[2];
            gpu_num_groups_[0] = saved_ngroups[0]; gpu_num_groups_[1] = saved_ngroups[1]; gpu_num_groups_[2] = saved_ngroups[2];
            throw;
        }

        gpu_local_id_[0] = saved_local[0]; gpu_local_id_[1] = saved_local[1]; gpu_local_id_[2] = saved_local[2];
        gpu_group_id_[0] = saved_group[0]; gpu_group_id_[1] = saved_group[1]; gpu_group_id_[2] = saved_group[2];
        gpu_thread_dims_[0] = saved_dims[0]; gpu_thread_dims_[1] = saved_dims[1]; gpu_thread_dims_[2] = saved_dims[2];
        gpu_num_groups_[0] = saved_ngroups[0]; gpu_num_groups_[1] = saved_ngroups[1]; gpu_num_groups_[2] = saved_ngroups[2];

        if (pc->dst != UINT32_MAX && pc->dst < registers.size()) {
            registers[pc->dst] = VAL_NIL;
        }
        return;
    }

    throw std::runtime_error("Unknown gpu builtin: " + fname);
}

} // namespace Register
} // namespace VM
} // namespace Backend
} // namespace LM
