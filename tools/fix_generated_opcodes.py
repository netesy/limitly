#!/usr/bin/env python3
import re
from pathlib import Path

root = Path('c:/Projects/limitly')
opcode_file = root / 'src' / 'opcodes.hh'
gen_file = root / 'src' / 'lembed_generated.cpp'
parser_file = root / 'src' / 'test_parser.cpp'

# Read opcodes
text = opcode_file.read_text()
m = re.search(r'enum class Opcode\s*\{([\s\S]*?)\};', text)
if not m:
    print('Could not find Opcode enum')
    exit(1)
body = m.group(1)
lines = [l.strip() for l in body.splitlines() if l.strip()]
names = []
for line in lines:
    # Remove comments
    line = re.sub(r'//.*', '', line).strip()
    if not line: continue
    # remove trailing comma
    if line.endswith(','): line = line[:-1]
    line = line.strip()
    if not line: continue
    # Skip if not identifier
    parts = line.split()
    name = parts[0]
    names.append(name)

# Build mapping index->name
index_to_name = {i: names[i] for i in range(len(names))}
print(f'Found {len(names)} opcodes')

# Fix generated file
if gen_file.exists():
    gtext = gen_file.read_text()
    def repl_op(match):
        num = int(match.group(1))
        if num in index_to_name:
            return f'Opcode::{index_to_name[num]}'
        else:
            return f'static_cast<Opcode>({num})'
    gtext = re.sub(r'Opcode::OP_(\d+)', repl_op, gtext)
    # Also replace any I(Opcode::... ) occurrences that used OP_
    gen_file.write_text(gtext)
    print(f'Updated {gen_file}')
else:
    print(f'{gen_file} does not exist, skipping')

# Update test_parser.cpp's OPCODE_NAMES initializer
if parser_file.exists():
    ptext = parser_file.read_text()
    # Find start of OPCODE_NAMES map
    m2 = re.search(r'const std::unordered_map<Opcode, std::string> OPCODE_NAMES = \{([\s\S]*?)\};', ptext)
    if m2:
        new_entries = []
        for name in names:
            new_entries.append(f'    {{Opcode::{name}, "{name}"}},')
        new_block = 'const std::unordered_map<Opcode, std::string> OPCODE_NAMES = {\n' + '\n'.join(new_entries) + '\n};'
        ptext = ptext[:m2.start()] + new_block + ptext[m2.end():]
        parser_file.write_text(ptext)
        print(f'Updated {parser_file}')
    else:
        print('Could not find OPCODE_NAMES map in test_parser.cpp')
else:
    print('test_parser.cpp not found')
