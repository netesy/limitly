import sys

with open('src/backend/fyra/fyra_builtin_functions.cpp', 'r') as f:
    content = f.read()

content = content.replace(r'\n', '\n')

with open('src/backend/fyra/fyra_builtin_functions.cpp', 'w') as f:
    f.write(content)
print("Done")
