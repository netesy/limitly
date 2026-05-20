import sys

with open('src/backend/value.cpp', 'r') as f:
    lines = f.readlines()

new_lines = []
skip = False
for line in lines:
    if '#include "env.hh"' in line:
        new_lines.append(line)
        new_lines.append('#include "vm/register.hh"\n')
        continue

    if 'if (auto valPtr = std::get_if<std::string>(&rv)) {' in line:
        new_lines.append('                        bufferedValue = LM::Backend::VM::Register::register_to_value_ptr(rv);\n')
        skip = True
        continue

    if skip:
        if 'bufferedValue = std::make_shared<Value>(nullType);' in line or 'return std::make_shared<Value>(nullType);' in line:
            skip = False
        continue

    if 'LM::Backend::RegisterValue rv;' in line and 'bool ok = (*chPtr)->poll(rv);' in lines[lines.index(line)+1]:
         # This is the second occurrence in next()
         pass # Handled by the generic 'valPtr' check above if I'm lucky, but let's be more specific

    new_lines.append(line)

# Second pass for the next() function which is slightly different
final_lines = []
skip = False
for line in new_lines:
    if 'if (auto valPtr = std::get_if<std::string>(&rv)) {' in line:
        final_lines.append('                    return LM::Backend::VM::Register::register_to_value_ptr(rv);\n')
        skip = True
        continue
    if skip:
        if 'return std::make_shared<Value>(nullType);' in line:
            skip = False
        continue
    final_lines.append(line)

with open('src/backend/value.cpp', 'w') as f:
    f.writelines(final_lines)
