import os

os.makedirs('src/frontend/type_checker', exist_ok=True)

with open('src/frontend/type_checker.cpp.bak', 'r', encoding='utf-8') as f:
    lines = f.readlines()

header = '#include "../type_checker.hh"\n\nusing namespace LM::Frontend;\nusing namespace LM::Error;\n\n'

splits = {
    'core': (0, 803),
    'statements': (803, 1459),
    'expressions': (1459, 2997),
    'types': (2997, 3846),
    'patterns': (3846, 4097),
    'declarations': (4097, len(lines))
}

for name, (start, end) in splits.items():
    content = ''.join(lines[start:end])
    if name != 'core':
        content = header + content
    filepath = f'src/frontend/type_checker/{name}.cpp'
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f'Created {name}.cpp')
