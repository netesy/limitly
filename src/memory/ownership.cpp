#include "ownership.hh"
#include "../frontend/ast.hh"
#include "../frontend/module_manager.hh"
#include <atomic>
#include <algorithm>
#include <functional>
#include <sstream>

namespace LM::Memory {
namespace A = Frontend::AST;
namespace {
std::atomic<Identity> next_identity{1};
Identity identity(A::Node& node) {
    if (!node.memory_info.semantic_id) node.memory_info.semantic_id = next_identity.fetch_add(1);
    return node.memory_info.semantic_id;
}
bool managed(TypePtr type) {
    if (!type) return false;
    switch (type->tag) {
        case TypeTag::List: case TypeTag::Dict: case TypeTag::Tuple:
        case TypeTag::Frame: case TypeTag::UserDefined: case TypeTag::Structural: return true;
        default: return false;
    }
}
bool managed_annotation(const std::shared_ptr<A::TypeAnnotation>& t) {
    if (!t) return false;
    if (t->isList || t->isDict || t->isTuple || t->isStructural) return true;
    if (t->isFunction) return false;
    const auto& n = t->typeName;
    return !n.empty() && !t->isPrimitive && n != "any" && n != "nil" && n != "str" && n != "int" && n != "bool" && n != "float";
}
struct Value {
    bool managed = false, unknown = false, projected = false, invalidated = false;
    Identity source = 0, constructor = 0;
    std::set<Identity> allocations, callables;
    std::set<uint32_t> parameters;
    std::map<Identity, unsigned> references, captures;
    std::map<Identity, std::set<Identity>> capture_origins;
    std::set<Identity> symbolic_captures;
    bool operator==(const Value&) const = default;
};
struct State {
    Value value;
    bool unavailable = false, consumed = false;
    unsigned generation = 0;
    bool operator==(const State&) const = default;
};
struct Flow {
    std::vector<std::map<std::string, Identity>> scopes{{}};
    std::map<Identity, State> states;
    bool reachable = true;
    std::shared_ptr<const std::map<std::string, Identity>> module_bindings;
};
struct Callable {
    Identity id;
    std::string name;
    std::vector<std::pair<std::string, std::shared_ptr<A::TypeAnnotation>>> parameters;
    std::shared_ptr<A::BlockStatement> body;
    std::vector<std::string> captures;
    A::Program* owner = nullptr;
};
class Analyzer {
    std::shared_ptr<A::Program> program;
    std::shared_ptr<SemanticFacts> facts;
    std::map<Identity, Callable> functions;
    std::map<Identity, Identity> constructors;
    std::map<std::string, Identity> constructor_names;
    std::map<std::string, Identity> function_names;
    std::set<std::string> frame_names, intrinsic_names;
    Flow globals;
    std::map<Identity, State> initialized_globals;
    std::map<Identity, A::Program*> global_owners;
    std::map<A::Program*, Flow> environments;
    std::map<A::Program*, std::string> namespaces;
    A::Program* active_program = nullptr;
    std::map<Identity, Flow> closure_environments;
    std::map<Identity, A::Program*> body_owners;
    SemanticEffects* effect = nullptr;
    Identity current_function = 0;
    bool recording = false, validating_specialization = false;
    std::set<Identity> specializing, locals;
    std::map<Identity, SemanticEffects>* inference_inputs = nullptr;
    std::vector<Flow> breaks, continues;

    NodeOwnership& node(A::Node& n) { return facts->nodes[identity(n)]; }
    void error(A::Node& n, const std::string& text) {
        if (!recording && !validating_specialization) return;
        auto message = "Ownership error at line " + std::to_string(n.line) + ": " + text;
        if (std::find(facts->errors.begin(), facts->errors.end(), message) == facts->errors.end()) facts->errors.push_back(message);
    }
    Identity resolve(const Flow& flow, const std::string& name) {
        for (auto i = flow.scopes.rbegin(); i != flow.scopes.rend(); ++i) {
            auto found = i->find(name); if (found != i->end()) return found->second;
        }
        if (flow.module_bindings) {auto found = flow.module_bindings->find(name); if (found != flow.module_bindings->end()) return found->second;}
        return 0;
    }
    void read(Flow& flow, Identity id, A::Node& where) {
        if (!id) return;
        if (!flow.states.count(id) && initialized_globals.count(id)) flow.states[id] = initialized_globals.at(id);
        auto found = flow.states.find(id); if (found == flow.states.end()) return;
        auto& state = found->second;
        if (state.value.invalidated) error(where, "use of invalidated alias or closure capture");
        if (state.unavailable) error(where, "use of moved binding '" + facts->names[id] + "'");
        for (const auto& [origin, generation] : state.value.references) {
            auto owner = flow.states.find(origin);
            if (owner != flow.states.end() && (owner->second.unavailable || owner->second.generation != generation))
                error(where, "use of stale alias of '" + facts->names[origin] + "'");
        }
        if (effect) {
            for (auto p : state.value.parameters) effect->parameters[p] |= Read;
            if ((state.value.managed || !state.value.references.empty() || !state.value.captures.empty()) && state.value.parameters.empty() && !locals.count(id)) effect->captures_read.insert(id);
        }
        if (recording && (state.value.managed || !state.value.references.empty() || !state.value.captures.empty())) node(where).event.reads.push_back(id);
    }
    void invalidate_aliases(Flow& flow, Identity id) {
        for (auto& [binding, state] : flow.states)
            if (state.value.references.count(id) || state.value.captures.count(id)) state.value.invalidated = true;
    }
    void consume(Flow& flow, Identity id, A::Node& where) {
        if (!id) return;
        if (!flow.states.count(id) && initialized_globals.count(id)) flow.states[id] = initialized_globals.at(id);
        auto found = flow.states.find(id); if (found == flow.states.end() || (!found->second.value.managed && !found->second.value.unknown)) return;
        read(flow, id, where);
        auto& state = found->second;
        invalidate_aliases(flow, id);
        state.unavailable = true; state.consumed = true;
        state.generation = std::min(2u, state.generation + 1);
        if (effect) {
            for (auto p : state.value.parameters) effect->parameters[p] |= state.value.references.empty() ? Consume : Retain;
            if (state.value.parameters.empty() && !locals.count(id)) effect->captures_consumed.insert(id);
        }
        if (recording) node(where).event.consumes.push_back(id);
    }
    void define(Flow& flow, const std::string& name, Identity id, Value value, A::Node& where) {
        flow.scopes.back()[name] = id;
        facts->names[id] = name;
        if (current_function) locals.insert(id);
        auto& state = flow.states[id];
        state.value = std::move(value); state.value.source = id;
        state.unavailable = false; state.consumed = false;
        if (recording) {
            auto& info = node(where); info.binding = id; info.managed = state.value.managed;
            info.unknown_origin = state.value.unknown; info.origins = state.value.allocations;
            if (!info.origins.empty()) info.allocation = *info.origins.begin();
            info.event.defines.push_back(id);
            for (const auto& [origin, gen] : state.value.references) info.event.aliases.emplace_back(id, origin);
            for (const auto& [origin, gen] : state.value.captures) info.event.aliases.emplace_back(id, origin);
        }
    }
    static Value join_value(Value left, const Value& right) {
        left.managed |= right.managed; left.unknown |= right.unknown; left.projected |= right.projected; left.invalidated |= right.invalidated;
        left.allocations.insert(right.allocations.begin(), right.allocations.end());
        left.callables.insert(right.callables.begin(), right.callables.end());
        left.parameters.insert(right.parameters.begin(), right.parameters.end());
        left.symbolic_captures.insert(right.symbolic_captures.begin(), right.symbolic_captures.end());
        for (auto [id, gen] : right.references) {
            auto i = left.references.find(id);
            if (i == left.references.end()) left.references[id] = gen;
            else if (i->second != gen) left.unknown = true;
        }
        left.captures.insert(right.captures.begin(), right.captures.end());
        for (auto& [capture, origins] : right.capture_origins) left.capture_origins[capture].insert(origins.begin(), origins.end());
        return left;
    }
    static Flow join(Flow left, const Flow& right) {
        if (!left.reachable) return right;
        if (!right.reachable) return left;
        for (const auto& [id, state] : right.states) {
            auto i = left.states.find(id);
            if (i == left.states.end()) { left.states[id] = state; continue; }
            i->second.unavailable |= state.unavailable; i->second.consumed |= state.consumed;
            i->second.generation = std::max(i->second.generation, state.generation);
            i->second.value = join_value(i->second.value, state.value);
        }
        return left;
    }
    void register_callable(A::Node& declaration, std::string name,
        const std::vector<std::pair<std::string, std::shared_ptr<A::TypeAnnotation>>>& params,
        const std::shared_ptr<A::BlockStatement>& body, std::vector<std::string> captures = {}) {
        const auto id = identity(declaration);
        if (!body) return;
        auto body_id = identity(*body);
        auto owner = body_owners.try_emplace(body_id, active_program).first->second;
        if (!functions.count(id)) functions[id] = Callable{id, name, params, body, std::move(captures), owner};
        function_names[name] = id;
        auto& ids = facts->parameters[body_id];
        if (ids.empty() && facts->parameters.count(id)) ids = facts->parameters[id];
        while (ids.size() < params.size()) ids.push_back(next_identity.fetch_add(1));
        facts->parameters[id] = ids;
        facts->functions.try_emplace(id, SemanticEffects{std::vector<uint8_t>(params.size(), Read), {}, {}, {}, {}, false});
    }
    void collect(const std::shared_ptr<A::Statement>& s, const std::string& prefix = "") {
        if (!s) return;
        if (auto f = std::dynamic_pointer_cast<A::FunctionDeclaration>(s)) {
            auto p = f->params; for (const auto& optional : f->optionalParams) p.emplace_back(optional.first, optional.second.first);
            register_callable(*f, prefix + f->name, p, f->body);
            if (f->body) for (const auto& child : f->body->statements) collect(child);
        } else if (auto f = std::dynamic_pointer_cast<A::FrameDeclaration>(s)) {
            frame_names.insert(prefix + f->name);
            constructors[identity(*f)] = f->init ? identity(*f->init) : 0;
            constructor_names[prefix + f->name] = identity(*f);
            auto method = [&](const std::shared_ptr<A::FrameMethod>& m) {
                if (!m || !m->body) return;
                auto p = m->parameters;
                if (!m->isStatic) p.insert(p.begin(), {"self", nullptr});
                for (const auto& optional : m->optionalParams) p.emplace_back(optional.first, optional.second.first);
                register_callable(*m, prefix + f->name + "." + m->name, p, m->body);
            };
            method(f->init); method(f->deinit); for (const auto& m : f->methods) method(m);
        } else if (auto b = std::dynamic_pointer_cast<A::BlockStatement>(s)) {
            for (const auto& child : b->statements) collect(child, prefix);
        } else if (auto i = std::dynamic_pointer_cast<A::IfStatement>(s)) { collect(i->thenBranch, prefix); collect(i->elseBranch, prefix); }
    }
    SemanticEffects infer(Identity id, const std::vector<Value>* arguments = nullptr, const Flow* caller = nullptr) {
        auto f = functions.find(id); if (f == functions.end()) return {};
        auto old_effect = effect; auto old_function = current_function;
        auto old_locals = std::move(locals); locals.clear();
        auto old_breaks = std::move(breaks), old_continues = std::move(continues);
        breaks.clear(); continues.clear();
        SemanticEffects result; result.parameters.assign(f->second.parameters.size(), Read);
        Flow flow = closure_environments.count(id) ? closure_environments.at(id) : environments.at(f->second.owner);
        if (caller && !f->second.captures.empty()) for (const auto& name : f->second.captures) {
            auto captured = resolve(*caller, name);
            if (captured && caller->states.count(captured)) { flow.scopes.back()[name] = captured; flow.states[captured] = caller->states.at(captured); }
        }
        auto saved_program = active_program; active_program = f->second.owner;
        flow.reachable = true;
        // Parameter indices belong to an invocation summary, not to captured
        // bindings inherited from the caller. Rebase them before declaring formals.
        for (auto& [binding, state] : flow.states) {
            if (!state.value.parameters.empty()) state.value.symbolic_captures.insert(binding);
            state.value.parameters.clear();
        }
        flow.scopes.push_back({});
        effect = &result; current_function = id;
        for (size_t p = 0; p < f->second.parameters.size(); ++p) {
            Value value;
            value.managed = f->second.parameters[p].first == "self" || managed_annotation(f->second.parameters[p].second);
            value.unknown = f->second.parameters[p].second && f->second.parameters[p].second->typeName == "any";
            if (arguments && p < arguments->size()) {
                // `any` binding copies are borrowed even when a concrete
                // invocation carries a managed object. Specializing a captured
                // closure must not turn that copy into an ownership transfer.
                if (!value.unknown) value.managed |= (*arguments)[p].managed;
                value.callables = (*arguments)[p].callables;
            }
            value.parameters.insert(static_cast<uint32_t>(p));
            define(flow, f->second.parameters[p].first, facts->parameters[id][p], value, *f->second.body);
        }
        statement(f->second.body, flow);
        effect = old_effect; current_function = old_function; locals = std::move(old_locals);
        breaks = std::move(old_breaks); continues = std::move(old_continues);
        active_program = saved_program;
        return result;
    }
    SemanticEffects target_effect(Identity id, const std::vector<Value>& args, const Flow& caller) {
        // Record the first observed summary, including nested specialization
        // reads. A callee changed during inference invalidates the next reuse.
        if (inference_inputs) inference_inputs->try_emplace(id, facts->functions[id]);
        bool specialization = !functions[id].captures.empty() || std::any_of(args.begin(), args.end(), [](const Value& v) {return !v.callables.empty();});
        if (specialization && !specializing.count(id)) {
            specializing.insert(id);
            const bool saved_recording = recording, saved_validation = validating_specialization;
            validating_specialization |= recording; recording = false;
            auto result = infer(id, &args, &caller);
            recording = saved_recording; validating_specialization = saved_validation;
            specializing.erase(id); return result;
        }
        return facts->functions[id];
    }
    std::string qualified(const std::shared_ptr<A::Expression>& e) {
        if (auto v = std::dynamic_pointer_cast<A::VariableExpr>(e)) return v->name;
        if (auto m = std::dynamic_pointer_cast<A::MemberExpr>(e)) {
            auto prefix = qualified(m->object); return prefix.empty() ? m->name : prefix + "." + m->name;
        }
        return "";
    }
    Value call(A::CallExpr& c, Flow& flow) {
        Value callee = expression(c.callee, flow);
        std::vector<Value> args; for (auto& a : c.arguments) args.push_back(expression(a, flow));
        std::map<std::string,Value> named; for (auto& [name, arg] : c.namedArgs) named[name] = expression(arg, flow);
        auto name = qualified(c.callee);
        if (auto id = resolve(flow, name)) {
            if (constructors.count(id)) callee.constructor = id;
            else if (!flow.states.count(id) && functions.count(id)) callee.callables.insert(id);
            else callee.callables = flow.states[id].value.callables;
        }
        if (auto found = function_names.find(name); found != function_names.end() && callee.callables.empty()) callee.callables.insert(found->second);
        if (auto member = std::dynamic_pointer_cast<A::MemberExpr>(c.callee)) {
            // Resolve methods from the receiver's inferred nominal type, never
            // from a consuming-looking spelling.
            if (member->object && member->object->inferred_type) {
                std::string receiver_type;
                if (auto ft = std::get_if<FrameType>(&member->object->inferred_type->extra)) receiver_type = ft->name;
                auto method = function_names.find(namespaces[active_program] + receiver_type + "." + member->name);
                if (method == function_names.end()) method = function_names.find(receiver_type + "." + member->name);
                if (method != function_names.end()) {
                    callee.callables.insert(method->second);
                    args.insert(args.begin(), expression(member->object, flow));
                }
            }
        }
        if (callee.constructor) {
            Value self; self.managed = true; self.allocations.insert(identity(c)); args.insert(args.begin(), self);
            if (auto init = constructors.at(callee.constructor)) callee.callables.insert(init);
        }
        if (!callee.callables.empty() && !named.empty()) {
            const auto& parameters = functions.at(*callee.callables.begin()).parameters;
            args.resize(parameters.size());
            for (size_t p = 0; p < parameters.size(); ++p) if (named.count(parameters[p].first)) args[p] = named.at(parameters[p].first);
        } else if (callee.callables.empty()) for (auto& [name, value] : named) args.push_back(value);
        SemanticEffects combined; combined.parameters.assign(args.size(), 0);
        bool known = !callee.callables.empty() || callee.constructor;
        if (callee.constructor && callee.callables.empty()) for (auto& flags : combined.parameters) flags = Read | Retain;
        for (auto id : callee.callables) {
            auto summary = target_effect(id, args, flow);
            for (size_t p = 0; p < args.size() && p < summary.parameters.size(); ++p) combined.parameters[p] |= summary.parameters[p];
            combined.return_aliases.insert(summary.return_aliases.begin(), summary.return_aliases.end());
            combined.return_projections.insert(summary.return_projections.begin(), summary.return_projections.end());
            combined.captures_read.insert(summary.captures_read.begin(), summary.captures_read.end());
            combined.captures_consumed.insert(summary.captures_consumed.begin(), summary.captures_consumed.end());
            combined.captures_opaque.insert(summary.captures_opaque.begin(), summary.captures_opaque.end());
            combined.unknown_result |= summary.unknown_result;
            combined.returned_callables.insert(summary.returned_callables.begin(), summary.returned_callables.end());
            combined.returned_globals.insert(summary.returned_globals.begin(), summary.returned_globals.end());
            combined.returned_capture_parameters.insert(summary.returned_capture_parameters.begin(), summary.returned_capture_parameters.end());
        }
        // Compiler-owned intrinsics have explicit shared/borrow contracts.
        // Unknown function values stay opaque; their arguments may be retained,
        // mutated or consumed. No spelling heuristic grants a proof.
        if (!known) {
            bool intrinsic = callee.source == 0 && intrinsic_names.count(name);
            if (auto member = std::dynamic_pointer_cast<A::MemberExpr>(c.callee)) {
                auto type = member->object ? member->object->inferred_type : nullptr;
                intrinsic |= type && (type->tag == TypeTag::List || type->tag == TypeTag::Dict || type->tag == TypeTag::Tuple || type->tag == TypeTag::String);
            }
            for (size_t p = 0; p < args.size(); ++p) combined.parameters[p] = intrinsic ? Read | Retain : Read | Mutate | Retain | Opaque;
            combined.unknown_result = true;
        }
        Value result; result.managed = managed(c.inferred_type); result.unknown = combined.unknown_result;
        if (callee.constructor) {result.managed = true; result.unknown = false; result.allocations.insert(identity(c));}
        for (auto p : combined.return_aliases) if (p < args.size()) {
            result = join_value(result, args[p]);
            if (args[p].source) result.references[args[p].source] = flow.states[args[p].source].generation;
            result.source = 0;
        }
        for (auto p : combined.return_projections) if (p < args.size()) {
            result.parameters.insert(args[p].parameters.begin(), args[p].parameters.end());
            result.symbolic_captures.insert(args[p].symbolic_captures.begin(), args[p].symbolic_captures.end());
            result.projected = true; result.unknown |= result.managed;
            if (args[p].source) result.references[args[p].source] = flow.states[args[p].source].generation;
        }
        result.callables = combined.returned_callables;
        for (auto global : combined.returned_globals) {
            read(flow, global, c); result.references[global] = flow.states[global].generation;
        }
        for (auto [capture, p] : combined.returned_capture_parameters) if (p < args.size() && args[p].source) {
            result.captures[args[p].source] = flow.states[args[p].source].generation;
            result.capture_origins[capture].insert(args[p].source);
        }
        for (auto captured : combined.captures_read) {
            if (callee.capture_origins.count(captured)) for (auto origin : callee.capture_origins.at(captured)) read(flow, origin, c);
            else read(flow, captured, c);
        }
        // Captured parameter indices are not the nested function's formal
        // indices. Keep their binding identity until a caller can discharge
        // the obligation against the capture's actual ownership origin.
        for (auto capture : combined.captures_opaque) {
            std::set<Identity> origins{capture};
            if (callee.capture_origins.count(capture)) origins = callee.capture_origins.at(capture);
            for (auto origin : origins) {
                read(flow, origin, c);
                auto found = flow.states.find(origin);
                if (found == flow.states.end()) {
                    if (effect) effect->captures_opaque.insert(origin);
                    else if (recording || validating_specialization) error(c, "opaque captured callable contract has no proven ownership origin");
                    continue;
                }
                const auto& captured = found->second.value;
                if (effect && !captured.parameters.empty())
                    for (auto p : captured.parameters) effect->parameters[p] |= Opaque;
                else if (effect && !captured.symbolic_captures.empty())
                    effect->captures_opaque.insert(captured.symbolic_captures.begin(), captured.symbolic_captures.end());
                else if ((captured.managed || captured.unknown || !captured.references.empty()) && (recording || validating_specialization))
                    error(c, "opaque captured callable contract has no proven ownership contract for managed capture");
            }
        }
        for (const auto& [capture, generation] : callee.captures) {
            auto state = flow.states.find(capture);
            if (state != flow.states.end() && (state->second.unavailable || state->second.generation != generation))
                error(c, "closure uses an invalidated capture '" + facts->names[capture] + "'");
        }
        if (recording) node(c).arguments.clear();
        for (size_t p = 0; p < args.size(); ++p) {
            auto flags = combined.parameters[p];
            if (effect) {
                for (auto formal : args[p].parameters)
                    effect->parameters[formal] |= !args[p].projected ? flags : static_cast<uint8_t>(flags & (Read | Mutate | Retain | (args[p].managed ? Opaque : 0)));
                if ((flags & Opaque) && args[p].managed) effect->captures_opaque.insert(args[p].symbolic_captures.begin(), args[p].symbolic_captures.end());
            }
            if (flags & Consume) {
                consume(flow, args[p].source, c);
                // An exact alias/cast can have no direct binding, but consuming
                // it still transfers its originating owner. A projection does
                // not transfer the whole container that supplied the child.
                if (!args[p].source && !args[p].projected)
                    for (auto [origin, generation] : args[p].references) consume(flow, origin, c);
            }
            // A call depending on a formal (including a receiver projection)
            // contributes an unresolved contract to that formal. Reject only
            // when that obligation reaches a concrete owner; rejecting the
            // declaration itself would make unused generic library bodies
            // illegal. Opaque must survive projection and every caller edge.
            else if ((flags & Opaque) && args[p].managed && (args[p].source || !args[p].references.empty()) &&
                     (recording || validating_specialization) && (!current_function || (args[p].parameters.empty() && args[p].symbolic_captures.empty())))
                error(c, "opaque callable has no proven ownership contract for managed argument");
            if (recording) node(c).arguments.push_back(flags & Consume ? Ownership::Owned : flags & Opaque ? Ownership::Unspecified : flags & Mutate ? Ownership::WriteBorrow : args[p].managed ? Ownership::ReadBorrow : Ownership::Value);
        }
        for (auto captured : combined.captures_consumed) {
            if (callee.capture_origins.count(captured)) for (auto origin : callee.capture_origins.at(captured)) consume(flow, origin, c);
            else consume(flow, captured, c);
        }
        return result;
    }
    Value expression(const std::shared_ptr<A::Expression>& e, Flow& flow) {
        if (!e || !flow.reachable) return {};
        if (recording) node(*e).event = {};
        Value value; value.managed = managed(e->inferred_type);
        if (auto v = std::dynamic_pointer_cast<A::VariableExpr>(e)) {
            auto id = resolve(flow, v->name);
            if (id) {
                if (!flow.states.count(id) && functions.count(id)) flow.states[id].value.callables.insert(id);
                if (!flow.states.count(id) && constructors.count(id)) flow.states[id].value.constructor = id;
                if (!flow.states[id].value.constructor && flow.states[id].value.callables.empty() && v->inferred_type && v->inferred_type->tag != TypeTag::Any)
                    flow.states[id].value.managed = managed(v->inferred_type);
                read(flow, id, *v); value = flow.states[id].value; value.source = id;
                if (global_owners.count(id) && global_owners[id] != active_program && value.managed) {
                    value.references[id] = flow.states[id].generation; value.source = 0;
                }
            }
            else if (auto f = function_names.find(v->name); f != function_names.end()) value.callables.insert(f->second);
            if (recording) node(*v).binding = id;
        } else if (std::dynamic_pointer_cast<A::ThisExpr>(e)) {
            auto id = resolve(flow, "self"); read(flow, id, *e); value = flow.states[id].value; value.source = id;
            if (recording) node(*e).binding = id;
        } else if (auto c = std::dynamic_pointer_cast<A::CallExpr>(e)) return call(*c, flow);
        else if (auto a = std::dynamic_pointer_cast<A::AssignExpr>(e)) {
            expression(a->object, flow); expression(a->index, flow); value = expression(a->value, flow);
            if (!a->object && !a->index && !a->member) {
                auto id = resolve(flow, a->name); const bool existing = id != 0; if (!id) id = identity(*a);
                if (flow.states.count(id) && flow.states[id].consumed) error(*a, "cannot reassign a moved binding");
                if (value.managed && value.source && value.source != id) consume(flow, value.source, *a);
                const bool same_owner = (value.source == id || value.references.count(id)) && !value.projected && value.allocations == flow.states[id].value.allocations;
                if (same_owner) value.references.erase(id);
                if (!same_owner && flow.states.count(id)) {
                    invalidate_aliases(flow, id); flow.states[id].generation = std::min(2u, flow.states[id].generation + 1);
                }
                auto saved_scope = flow.scopes.back();
                define(flow, a->name, id, value, *a);
                if (existing) flow.scopes.back() = saved_scope;
                if (same_owner && recording) node(*a).event.defines.clear();
            } else if (effect) {
                auto receiver = std::dynamic_pointer_cast<A::VariableExpr>(a->object);
                if (receiver) for (auto p : flow.states[resolve(flow, receiver->name)].value.parameters) effect->parameters[p] |= Mutate;
                for (auto p : value.parameters) effect->parameters[p] |= Retain;
            }
        } else if (auto cast = std::dynamic_pointer_cast<A::CastExpr>(e)) {
            value = expression(cast->expression, flow);
            if (cast->targetType && cast->targetType->typeName == "any" && value.managed) {
                consume(flow, value.source, *cast); value.source = 0;
            } else if (managed(cast->inferred_type)) {
                if (value.source) value.references[value.source] = flow.states[value.source].generation;
                value.unknown |= !value.managed; value.managed = true; value.source = 0;
            }
        } else if (auto group = std::dynamic_pointer_cast<A::GroupingExpr>(e)) value = expression(group->expression, flow);
        else if (auto b = std::dynamic_pointer_cast<A::BinaryExpr>(e)) { expression(b->left, flow); expression(b->right, flow); }
        else if (auto u = std::dynamic_pointer_cast<A::UnaryExpr>(e)) expression(u->right, flow);
        else if (auto i = std::dynamic_pointer_cast<A::IndexExpr>(e)) {
            auto object = expression(i->object, flow); expression(i->index, flow);
            value.parameters = object.parameters; value.symbolic_captures = object.symbolic_captures; value.projected = true; value.unknown = value.managed;
            if (object.source && value.managed) value.references[object.source] = flow.states[object.source].generation;
        } else if (auto m = std::dynamic_pointer_cast<A::MemberExpr>(e)) {
            const auto imported_binding = resolve(flow, qualified(e));
            if (imported_binding && constructors.count(imported_binding)) {
                value = {}; value.constructor = imported_binding;
            } else if (imported_binding && functions.count(imported_binding)) {
                value = {}; value.callables.insert(imported_binding);
            } else if (imported_binding) {
                read(flow, imported_binding, *m); value = flow.states[imported_binding].value; value.source = 0;
                if (value.managed) value.references[imported_binding] = flow.states[imported_binding].generation;
                if (recording) node(*m).binding = imported_binding;
            } else {
            auto object = expression(m->object, flow); value.parameters = object.parameters; value.symbolic_captures = object.symbolic_captures; value.projected = true; value.unknown = value.managed;
            if (object.source && value.managed) value.references[object.source] = flow.states[object.source].generation;
            }
        } else if (auto list = std::dynamic_pointer_cast<A::ListExpr>(e)) {
            for (auto& child : list->elements) { auto v = expression(child, flow); if (effect) for (auto p : v.parameters) effect->parameters[p] |= Retain; }
            value.managed = true; value.allocations.insert(identity(*list));
        } else if (auto tuple = std::dynamic_pointer_cast<A::TupleExpr>(e)) {
            for (auto& child : tuple->elements) expression(child, flow);
            value.managed = true; value.allocations.insert(identity(*tuple));
        } else if (auto dict = std::dynamic_pointer_cast<A::DictExpr>(e)) {
            for (auto& [key, child] : dict->entries) { expression(key, flow); expression(child, flow); }
            value.managed = true; value.allocations.insert(identity(*dict));
        } else if (auto literal = std::dynamic_pointer_cast<A::ObjectLiteralExpr>(e)) {
            for (auto& [key, child] : literal->properties) expression(child, flow);
            value.managed = true; value.allocations.insert(identity(*literal));
        } else if (auto lambda = std::dynamic_pointer_cast<A::LambdaExpr>(e)) {
            auto id = identity(*lambda);
            register_callable(*lambda, "$lambda" + std::to_string(id), lambda->params, lambda->body, lambda->capturedVars);
            value.callables.insert(id);
            closure_environments[id] = flow;
            auto summary = infer(id, nullptr, &flow);
            facts->functions[id] = summary;
            for (auto capture : summary.captures_read) {
                if (flow.states.count(capture)) {
                    value.captures[capture] = flow.states[capture].generation;
                    auto name = facts->names[capture];
                    if (std::find(lambda->capturedVars.begin(), lambda->capturedVars.end(), name) == lambda->capturedVars.end())
                        lambda->capturedVars.push_back(name);
                }
            }
            functions[id].captures = lambda->capturedVars;
            for (const auto& capture : lambda->capturedVars) {
                auto origin = resolve(flow, capture); read(flow, origin, *lambda);
                if (origin && flow.states[origin].value.managed) value.captures[origin] = flow.states[origin].generation;
            }
        } else if (auto ok = std::dynamic_pointer_cast<A::OkConstructExpr>(e)) value = expression(ok->value, flow);
        else if (auto some = std::dynamic_pointer_cast<A::SomeConstructExpr>(e)) value = expression(some->value, flow);
        else if (auto fallible = std::dynamic_pointer_cast<A::FallibleExpr>(e)) {
            value = expression(fallible->expression, flow);
            if (fallible->elseHandler) {auto handled = flow; statement(fallible->elseHandler, handled); flow = join(flow, handled);}
        } else if (auto text = std::dynamic_pointer_cast<A::InterpolatedStringExpr>(e)) {
            for (auto& part : text->parts) if (auto child = std::get_if<std::shared_ptr<A::Expression>>(&part)) expression(*child, flow);
        } else if (auto range = std::dynamic_pointer_cast<A::RangeExpr>(e)) {
            expression(range->start, flow); expression(range->end, flow); expression(range->step, flow);
        } else if (auto error_value = std::dynamic_pointer_cast<A::ErrorConstructExpr>(e)) {
            for (auto& argument : error_value->arguments) expression(argument, flow);
        } else if (auto closure = std::dynamic_pointer_cast<A::CallClosureExpr>(e)) {
            A::CallExpr call_expr; call_expr.memory_info = closure->memory_info; call_expr.line = closure->line;
            call_expr.inferred_type = closure->inferred_type; call_expr.callee = closure->closure;
            call_expr.arguments = closure->arguments; call_expr.namedArgs = closure->namedArgs;
            value = call(call_expr, flow); closure->memory_info.semantic_id = call_expr.memory_info.semantic_id;
        } else if (auto moved = std::dynamic_pointer_cast<A::MoveExpr>(e)) {
            value = expression(moved->value, flow); consume(flow, value.source, *moved); value.source = 0;
        } else if (auto dropped = std::dynamic_pointer_cast<A::DropExpr>(e)) {
            value = expression(dropped->value, flow); consume(flow, value.source, *dropped); value = {};
        } else if (auto linear = std::dynamic_pointer_cast<A::MakeLinearExpr>(e)) value = expression(linear->value, flow);
        else if (auto reference = std::dynamic_pointer_cast<A::MakeRefExpr>(e)) {
            auto id = resolve(flow, reference->target_var); read(flow, id, *reference);
            value = flow.states[id].value; value.source = 0; value.references[id] = flow.states[id].generation;
        } else if (auto staged = std::dynamic_pointer_cast<A::StagedExpr>(e)) {
            value = expression(staged->expression, flow); statement(staged->block, flow);
        } else if (auto send = std::dynamic_pointer_cast<A::ChannelSendExpr>(e)) {
            expression(send->channel, flow); auto sent = expression(send->value, flow);
            consume(flow, sent.source, *send);
        } else if (auto send = std::dynamic_pointer_cast<A::ChannelOfferExpr>(e)) {
            expression(send->channel, flow); auto sent = expression(send->value, flow);
            auto delivered = flow; consume(delivered, sent.source, *send); flow = join(flow, delivered);
        } else if (auto recv = std::dynamic_pointer_cast<A::ChannelRecvExpr>(e)) expression(recv->channel, flow);
        else if (auto recv = std::dynamic_pointer_cast<A::ChannelPollExpr>(e)) expression(recv->channel, flow);
        if (recording) {
            auto& info = node(*e); info.managed = value.managed; info.unknown_origin = value.unknown; info.origins = value.allocations;
        }
        return value;
    }
    void loop(const std::shared_ptr<A::Statement>& body, const std::shared_ptr<A::Expression>& condition,
              const std::shared_ptr<A::Expression>& increment, Flow& flow, A::Node& where) {
        auto outer_breaks = std::move(breaks), outer_continues = std::move(continues);
        breaks.clear(); continues.clear();
        const auto initial = flow;
        auto header = initial;
        // The lattice is finite: availability is a bit, generations saturate,
        // and provenance/callable sets only grow. Iterate to the actual fixed point.
        for (;;) {
            auto iteration = header; expression(condition, iteration);
            statement(body, iteration);
            for (const auto& continued : continues) iteration = join(iteration, continued);
            continues.clear();
            expression(increment, iteration);
            auto next = join(initial, iteration);
            if (next.states == header.states) { header = next; break; }
            header = std::move(next);
        }
        flow = header; expression(condition, flow);
        for (const auto& stopped : breaks) flow = join(flow, stopped);
        breaks = std::move(outer_breaks); continues = std::move(outer_continues);
    }
    void statement(const std::shared_ptr<A::Statement>& s, Flow& flow) {
        if (!s || !flow.reachable) return;
        if (recording) node(*s).event = {};
        if (auto b = std::dynamic_pointer_cast<A::BlockStatement>(s)) {
            flow.scopes.push_back({});
            for (const auto& child : b->statements) if (auto f = std::dynamic_pointer_cast<A::FunctionDeclaration>(child)) {
                Value value; value.callables.insert(identity(*f)); define(flow, f->name, identity(*f), value, *f);
                closure_environments[identity(*f)] = flow;
            }
            for (const auto& child : b->statements) statement(child, flow);
            flow.scopes.pop_back();
        } else if (auto v = std::dynamic_pointer_cast<A::VarDeclaration>(s)) {
            auto value = expression(v->initializer, flow);
            if (value.managed && value.source) consume(flow, value.source, *v);
            define(flow, v->name, identity(*v), value, *v);
            if (!v->initializer) flow.states[identity(*v)].unavailable = true;
        } else if (auto e = std::dynamic_pointer_cast<A::ExprStatement>(s)) expression(e->expression, flow);
        else if (auto a = std::dynamic_pointer_cast<A::AssignExpr>(s)) expression(a, flow);
        else if (auto i = std::dynamic_pointer_cast<A::IfStatement>(s)) {
            expression(i->condition, flow); auto left = flow, right = flow;
            statement(i->thenBranch, left); statement(i->elseBranch, right); flow = join(left, right);
        } else if (auto w = std::dynamic_pointer_cast<A::WhileStatement>(s)) loop(w->body, w->condition, nullptr, flow, *w);
        else if (auto f = std::dynamic_pointer_cast<A::ForStatement>(s)) {
            flow.scopes.push_back({}); statement(f->initializer, flow); loop(f->body, f->condition, f->increment, flow, *f); flow.scopes.pop_back();
        } else if (auto i = std::dynamic_pointer_cast<A::IterStatement>(s)) {
            expression(i->iterable, flow); flow.scopes.push_back({});
            auto& ids = facts->parameters[identity(*i)];
            while (ids.size() < i->loopVars.size()) ids.push_back(next_identity.fetch_add(1));
            for (size_t p = 0; p < i->loopVars.size(); ++p) define(flow, i->loopVars[p], ids[p], {}, *i);
            loop(i->body, nullptr, nullptr, flow, *i); flow.scopes.pop_back();
        } else if (auto r = std::dynamic_pointer_cast<A::ReturnStatement>(s)) {
            auto value = expression(r->value, flow);
            if (effect) {
                if (value.managed || (r->value && r->value->inferred_type && r->value->inferred_type->tag == TypeTag::Any))
                    (value.projected ? effect->return_projections : effect->return_aliases).insert(value.parameters.begin(), value.parameters.end());
                effect->unknown_result |= value.unknown;
                effect->returned_callables.insert(value.callables.begin(), value.callables.end());
                if (value.managed && value.source && global_owners.count(value.source)) effect->returned_globals.insert(value.source);
                for (auto [origin, generation] : value.references) if (global_owners.count(origin)) effect->returned_globals.insert(origin);
                for (auto [capture, generation] : value.captures) if (flow.states.count(capture)) {
                    for (auto p : flow.states[capture].value.parameters) {
                        effect->returned_capture_parameters[capture] = p; effect->parameters[p] |= Retain;
                    }
                }
            }
            flow.reachable = false;
        } else if (std::dynamic_pointer_cast<A::BreakStatement>(s)) { breaks.push_back(flow); flow.reachable = false; }
        else if (std::dynamic_pointer_cast<A::ContinueStatement>(s)) { continues.push_back(flow); flow.reachable = false; }
        else if (auto u = std::dynamic_pointer_cast<A::UnsafeStatement>(s)) statement(u->body, flow);
        else if (auto m = std::dynamic_pointer_cast<A::MatchStatement>(s)) {
            auto value = expression(m->value, flow); auto initial = flow; Flow result = flow; result.reachable = false;
            for (auto& arm : m->cases) {
                auto branch = initial; branch.scopes.push_back({});
                if (auto v = std::dynamic_pointer_cast<A::VariableExpr>(arm.pattern)) {
                    if (v->name != "_") define(branch, v->name, identity(*v), value, *v);
                }
                if (auto pattern = std::dynamic_pointer_cast<A::ValPatternExpr>(arm.pattern)) define(branch, pattern->variableName, identity(*pattern), value, *pattern);
                if (auto pattern = std::dynamic_pointer_cast<A::ErrPatternExpr>(arm.pattern)) define(branch, pattern->variableName, identity(*pattern), {}, *pattern);
                expression(arm.guard, branch); statement(arm.body, branch); branch.scopes.pop_back(); result = join(result, branch);
            }
            flow = join(initial, result); // Unless exhaustiveness is proven, retain the unmatched path.
        } else if (auto c = std::dynamic_pointer_cast<A::ContractStatement>(s)) { expression(c->condition, flow); expression(c->message, flow); }
        else if (auto parallel = std::dynamic_pointer_cast<A::ParallelStatement>(s)) statement(parallel->body, flow);
        else if (auto concurrent = std::dynamic_pointer_cast<A::ConcurrentStatement>(s)) statement(concurrent->body, flow);
        else if (auto task = std::dynamic_pointer_cast<A::TaskStatement>(s)) {
            expression(task->iterable, flow); flow.scopes.push_back({});
            define(flow, task->loopVar, identity(*task), {}, *task);
            loop(task->body, nullptr, nullptr, flow, *task); flow.scopes.pop_back();
        } else if (auto worker = std::dynamic_pointer_cast<A::WorkerStatement>(s)) {
            expression(worker->iterable, flow); flow.scopes.push_back({});
            define(flow, worker->paramName, identity(*worker), {}, *worker);
            loop(worker->body, nullptr, nullptr, flow, *worker); flow.scopes.pop_back();
        } else if (auto staged = std::dynamic_pointer_cast<A::StagedBlockStatement>(s)) statement(staged->body, flow);
        else if (auto staged = std::dynamic_pointer_cast<A::StagedStatement>(s)) {
            statement(staged->declaration, flow); statement(staged->block, flow); expression(staged->expression, flow);
        }
        // Race/slice proofs and bounds remain MemoryChecker responsibilities.
    }
public:
    explicit Analyzer(std::shared_ptr<A::Program> p, const std::set<std::string>& intrinsics) : program(std::move(p)), facts(std::make_shared<SemanticFacts>()), intrinsic_names(intrinsics) {
        if (program->ownership_facts) facts->parameters = program->ownership_facts->parameters;
    }
    std::shared_ptr<SemanticFacts> run() {
        // Analyze each declaration once in its defining module's lexical environment.
        // Import aliases select declaration identities, not a second interpretation of a body.
        auto modules = Frontend::ModuleManager::getInstance().get_all_modules();
        std::vector<std::shared_ptr<A::Program>> programs;
        for (const auto& name : Frontend::ModuleManager::getInstance().get_topological_order()) {
            auto found = modules.find(name);
            if (found == modules.end() || !found->second->ast || found->second->ast == program) continue;
            auto ast = found->second->ast;
            programs.push_back(ast); namespaces[ast.get()] = name + ".";
            if (ast->ownership_facts) for (const auto& [id, params] : ast->ownership_facts->parameters) facts->parameters.try_emplace(id, params);
            active_program = ast.get();
            for (const auto& declaration : ast->statements) collect(declaration, name + ".");
        }
        programs.push_back(program); namespaces[program.get()] = ""; active_program = program.get();
        for (const auto& declaration : program->statements) collect(declaration);
        for (const auto& ast : programs) {
            active_program = ast.get();
            // Some inlined declarations are cloned by module resolution.
            for (const auto& [name, declaration] : ast->imported_symbols) {
                if (!functions.count(identity(*declaration))) collect(declaration);
            }
            auto& env = environments[ast.get()];
            for (const auto& [name, id] : function_names) {
                Value value; value.callables.insert(id); define(env, name, id, value, *ast);
                const auto& prefix = namespaces[ast.get()];
                if (!prefix.empty() && name.starts_with(prefix)) define(env, name.substr(prefix.size()), id, value, *ast);
            }
            for (const auto& [name, id] : constructor_names) {
                Value value; value.constructor = id; define(env, name, id, value, *ast);
                const auto& prefix = namespaces[ast.get()];
                if (!prefix.empty() && name.starts_with(prefix)) define(env, name.substr(prefix.size()), id, value, *ast);
            }
            for (const auto& [name, declaration] : ast->imported_symbols) {
                const auto id = identity(*declaration);
                if (functions.count(id)) {Value value; value.callables.insert(id); define(env, name, id, value, *ast);}
                if (constructors.count(id)) {Value value; value.constructor = id; define(env, name, id, value, *ast);}
                if (auto var = std::dynamic_pointer_cast<A::VarDeclaration>(declaration)) {Value value; value.managed = managed(var->inferred_type); define(env, name, id, value, *ast);}
            }
            for (const auto& declaration : ast->statements) if (auto var = std::dynamic_pointer_cast<A::VarDeclaration>(declaration)) {
                Value value; value.managed = managed(var->inferred_type); define(env, var->name, identity(*var), value, *var);
                global_owners[identity(*var)] = ast.get(); facts->global_bindings.insert(identity(*var));
                auto module_name = namespaces[ast.get()]; if (!module_name.empty()) module_name.pop_back();
                if (!module_name.empty()) facts->module_initializations[module_name].insert(identity(*var));
            }
        }
        for (auto& [ast, env] : environments) {
            env.module_bindings = std::make_shared<const std::map<std::string, Identity>>(std::move(env.scopes.front()));
            env.scopes.front().clear();
            for (auto it = env.states.begin(); it != env.states.end();) {
                if (functions.count(it->first) || constructors.count(it->first)) it = env.states.erase(it); else ++it;
            }
        }
        globals = environments.at(program.get()); active_program = program.get();
        // Monotone interprocedural propagation, including recursive call SCCs.
        bool changed;
        struct SummaryCache {
            Callable callable;
            SemanticEffects summary;
            std::map<Identity, SemanticEffects> inputs;
        };
        std::map<const A::BlockStatement*, SummaryCache> body_summaries;
        do {
            changed = false;
            // Imported declaration clones share a body and its lexical owner.
            // Reuse only identical formal contracts with unchanged observed
            // callees. Captured environments are invocation-dependent and are
            // always reanalyzed. Diagnostic recording below never uses this cache.
            for (auto i = functions.begin(); i != functions.end(); ++i) {
                auto cached = body_summaries.find(i->second.body.get());
                bool identical = cached != body_summaries.end() && cached->second.callable.owner == i->second.owner &&
                    cached->second.callable.parameters == i->second.parameters && cached->second.callable.captures.empty() &&
                    i->second.captures.empty() && !closure_environments.count(i->first);
                if (identical) for (const auto& [callee, observed] : cached->second.inputs)
                    if (facts->functions.at(callee) != observed) {identical = false; break;}
                SemanticEffects inferred;
                if (identical) inferred = cached->second.summary;
                else {
                    std::map<Identity, SemanticEffects> inputs;
                    inference_inputs = &inputs;
                    inferred = infer(i->first);
                    inference_inputs = nullptr;
                    body_summaries.insert_or_assign(i->second.body.get(), SummaryCache{i->second, inferred, std::move(inputs)});
                }
                auto& old = facts->functions[i->first];
                for (size_t p = 0; p < inferred.parameters.size(); ++p) inferred.parameters[p] |= old.parameters[p];
                inferred.return_aliases.insert(old.return_aliases.begin(), old.return_aliases.end());
                inferred.return_projections.insert(old.return_projections.begin(), old.return_projections.end());
                inferred.unknown_result |= old.unknown_result;
                inferred.captures_read.insert(old.captures_read.begin(), old.captures_read.end());
                inferred.captures_consumed.insert(old.captures_consumed.begin(), old.captures_consumed.end());
                inferred.captures_opaque.insert(old.captures_opaque.begin(), old.captures_opaque.end());
                inferred.returned_callables.insert(old.returned_callables.begin(), old.returned_callables.end());
                inferred.returned_globals.insert(old.returned_globals.begin(), old.returned_globals.end());
                inferred.returned_capture_parameters.insert(old.returned_capture_parameters.begin(), old.returned_capture_parameters.end());
                if (inferred != old) { old = std::move(inferred); changed = true; }
            }
        } while (changed);
        recording = true;
        std::map<const A::BlockStatement*, Callable> recorded_bodies;
        for (auto i = functions.begin(); i != functions.end(); ++i) {
            auto recorded = recorded_bodies.find(i->second.body.get());
            bool identical = recorded != recorded_bodies.end() && recorded->second.owner == i->second.owner &&
                recorded->second.parameters == i->second.parameters && recorded->second.captures.empty() && i->second.captures.empty();
            // Deferred callback effects do not exempt a declaration's own body
            // from ownership validation. Concrete calls specialize the effects;
            // local transfers and reads must be checked even for unused bodies.
            if (i->second.body && !identical) {
                (void)infer(i->first);
                recorded_bodies.insert_or_assign(i->second.body.get(), i->second);
            }
        }
        for (const auto& ast : programs) {
            active_program = ast.get(); auto flow = environments.at(ast.get());
            for (const auto& [id, state] : initialized_globals) flow.states.try_emplace(id, state);
            for (const auto& declaration : ast->statements) if (auto var = std::dynamic_pointer_cast<A::VarDeclaration>(declaration)) flow.states[identity(*var)].unavailable = true;
            for (const auto& declaration : ast->statements) statement(declaration, flow);
            for (const auto& declaration : ast->statements) if (auto var = std::dynamic_pointer_cast<A::VarDeclaration>(declaration)) initialized_globals[identity(*var)] = flow.states.at(identity(*var));
            ast->ownership_facts = facts;
        }
        for (const auto& [id, info] : facts->nodes) if (info.binding && info.managed && info.unknown_origin) facts->reference_bindings.insert(info.binding);
        facts->verified = facts->errors.empty();
        program->ownership_facts = facts;
        return facts;
    }
};
} // namespace
std::shared_ptr<SemanticFacts> analyze_ownership(const std::shared_ptr<Frontend::AST::Program>& program, const std::set<std::string>& intrinsics) {
    return Analyzer(program, intrinsics).run();
}
} // namespace LM::Memory
