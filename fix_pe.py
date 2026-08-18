import sys

with open('vendor/fyra/src/target/artifact/executable/pe.cpp', 'r') as f:
    content = f.read()

old_str = """                if (r.symbolName == "ExitProcess") {
                    addImport("kernel32.dll", "ExitProcess");
                } else if (r.symbolName == "_write") {
                    addImport("msvcrt.dll", "_write");
                }"""

new_str = """                if (r.symbolName == "ExitProcess") {
                    addImport("kernel32.dll", "ExitProcess");
                } else if (r.symbolName == "_write") {
                    addImport("msvcrt.dll", "_write");
                } else if (r.symbolName == "GetStdHandle") {
                    addImport("kernel32.dll", "GetStdHandle");
                } else if (r.symbolName == "WriteFile") {
                    addImport("kernel32.dll", "WriteFile");
                }"""

if old_str in content:
    content = content.replace(old_str, new_str)
    with open('vendor/fyra/src/target/artifact/executable/pe.cpp', 'w') as f:
        f.write(content)
    print("Success")
else:
    print("Old string not found")
