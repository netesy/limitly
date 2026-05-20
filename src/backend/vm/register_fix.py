import sys

content = open('src/backend/vm/register.cpp').read()

# Replace LoadConst block
start_mark = 'case LIR::LIR_Op::LoadConst: {'
end_mark = 'break;' # Find the first break after LoadConst
# This is tricky because there are many breaks.
# Better find the next case.
next_case = 'case LIR::LIR_Op::Add:'

load_const_new = \"\"\"            case LIR::LIR_Op::LoadConst: {
                ValuePtr cv = pc->const_val;
                if (!cv) {
                    registers[pc->dst] = VAL_NIL;
                } else {
                    switch (cv->type->tag) {
                        case TypeTag::Int:
                        case TypeTag::Int64:
                            try { registers[pc->dst] = make_i64(std::stoll(cv->data)); }
                            catch(...) { registers[pc->dst] = make_i128(parse_i128(cv->data)); }
                            break;
                        case TypeTag::UInt:
                        case TypeTag::UInt64:
                            try { registers[pc->dst] = make_u64(std::stoull(cv->data)); }
                            catch(...) { registers[pc->dst] = make_u128(parse_u128(cv->data)); }
                            break;
                        case TypeTag::Int128:
                            registers[pc->dst] = make_i128(parse_i128(cv->data));
                            break;
                        case TypeTag::UInt128:
                            registers[pc->dst] = make_u128(parse_u128(cv->data));
                            break;
                        case TypeTag::Float32:
                        case TypeTag::Float64:
                            try { registers[pc->dst] = make_float(std::stod(cv->data)); } catch(...) { registers[pc->dst] = VAL_NIL; }
                            break;
                        case TypeTag::Bool:
                            registers[pc->dst] = (cv->data == "true") ? VAL_TRUE : VAL_FALSE;
                            break;
                        case TypeTag::String:
                            registers[pc->dst] = BOX_PTR(lm_box_string(cv->data.c_str()));
                            break;
                        default:
                            registers[pc->dst] = VAL_NIL;
                    }
                }
                break;
            }
\"\"\"

idx1 = content.find(start_mark)
idx2 = content.find('case LIR::LIR_Op::Add:', idx1)
if idx1 != -1 and idx2 != -1:
    content = content[:idx1] + load_const_new + content[idx2:]

# Also replace the top level helpers and to_string etc.
# Actually I'll just rewrite the whole file based on my successful one but with correct structure.
