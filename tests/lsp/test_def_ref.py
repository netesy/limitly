import subprocess
import json
import os

proc = subprocess.Popen(['bin/limitly.exe', '-lsp'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

def send(msg):
    p = json.dumps(msg).encode('utf-8')
    proc.stdin.write(f"Content-Length: {len(p)}\r\n\r\n".encode('utf-8') + p)
    proc.stdin.flush()

def read():
    cl = None
    while True:
        l = proc.stdout.readline().decode('utf-8')
        if not l: return None
        l = l.strip()
        if not l: break
        if l.lower().startswith('content-length:'): cl = int(l.split(':')[1].strip())
    if cl is None: return None
    return json.loads(proc.stdout.read(cl).decode('utf-8'))

# 1. Initialize
send({'jsonrpc': '2.0', 'id': 1, 'method': 'initialize', 'params': {'capabilities': {}}})
init_res = read()
caps = init_res['result']['capabilities']
print("Capabilities check:")
print(" - definitionProvider:", caps.get('definitionProvider'))
print(" - referenceProvider:", caps.get('referenceProvider'))
print(" - referencesProvider:", caps.get('referencesProvider'))
assert caps.get('definitionProvider') is True
assert caps.get('referenceProvider') is True

send({'jsonrpc': '2.0', 'method': 'initialized', 'params': {}})

# 2. Open document that imports linkedlist
test_code = (
    "import std.collections.linkedlist as linked_list;\n"
    "fn run_test() {\n"
    "    var l = linked_list.LinkedList();\n"
    "    l.push_back(10);\n"
    "    l.push_back(20);\n"
    "}\n"
)

send({
    'jsonrpc': '2.0',
    'method': 'textDocument/didOpen',
    'params': {
        'textDocument': {
            'uri': 'file:///c:/Projects/limitly/tests/collections/list_test.lm',
            'languageId': 'limitly',
            'version': 1,
            'text': test_code
        }
    }
})
diag = read()
print("DidOpen diagnostics count:", len(diag.get('params', {}).get('diagnostics', [])))

# 3. Test Definition on member method: l.push_back
print("\n[Test 1] Go to Definition on 'push_back' (line 3, char 8)...")
send({
    'jsonrpc': '2.0',
    'id': 2,
    'method': 'textDocument/definition',
    'params': {
        'textDocument': {'uri': 'file:///c:/Projects/limitly/tests/collections/list_test.lm'},
        'position': {'line': 3, 'character': 8}
    }
})
def_push = read()
print("Result:", json.dumps(def_push, indent=2))
assert def_push['id'] == 2
assert 'result' in def_push and def_push['result'] is not None
assert 'linkedlist.lm' in def_push['result']['uri'].lower()
print(" PASS: 'push_back' definition jumped to std/collections/linkedlist.lm!")

# 4. Test Definition on module member: linked_list.LinkedList
print("\n[Test 2] Go to Definition on 'LinkedList' (line 2, char 26)...")
send({
    'jsonrpc': '2.0',
    'id': 3,
    'method': 'textDocument/definition',
    'params': {
        'textDocument': {'uri': 'file:///c:/Projects/limitly/tests/collections/list_test.lm'},
        'position': {'line': 2, 'character': 26}
    }
})
def_ll = read()
print("Result:", json.dumps(def_ll, indent=2))
assert def_ll['id'] == 3
assert 'result' in def_ll and def_ll['result'] is not None
assert 'linkedlist.lm' in def_ll['result']['uri'].lower()
print(" PASS: 'LinkedList' definition jumped to std/collections/linkedlist.lm!")

# 5. Test Definition on module alias: linked_list
print("\n[Test 3] Go to Definition on 'linked_list' (line 2, char 14)...")
send({
    'jsonrpc': '2.0',
    'id': 4,
    'method': 'textDocument/definition',
    'params': {
        'textDocument': {'uri': 'file:///c:/Projects/limitly/tests/collections/list_test.lm'},
        'position': {'line': 2, 'character': 14}
    }
})
def_alias = read()
print("Result:", json.dumps(def_alias, indent=2))
assert def_alias['id'] == 4
assert 'result' in def_alias and def_alias['result'] is not None
assert 'linkedlist.lm' in def_alias['result']['uri'].lower()
print(" PASS: 'linked_list' alias definition jumped to module file!")

# 6. Test Definition on local variable: l
print("\n[Test 4] Go to Definition on 'l' (line 3, char 4)...")
send({
    'jsonrpc': '2.0',
    'id': 5,
    'method': 'textDocument/definition',
    'params': {
        'textDocument': {'uri': 'file:///c:/Projects/limitly/tests/collections/list_test.lm'},
        'position': {'line': 3, 'character': 4}
    }
})
def_l = read()
print("Result:", json.dumps(def_l, indent=2))
assert def_l['id'] == 5
assert 'result' in def_l and def_l['result'] is not None
assert def_l['result']['range']['start']['line'] == 2 # 'var l =' is on line 2 (0-indexed)
print(" PASS: 'l' definition jumped to local var declaration on line 2!")

# 7. Test References on local variable 'l'
print("\n[Test 5] Go to References on 'l'...")
send({
    'jsonrpc': '2.0',
    'id': 6,
    'method': 'textDocument/references',
    'params': {
        'textDocument': {'uri': 'file:///c:/Projects/limitly/tests/collections/list_test.lm'},
        'position': {'line': 2, 'character': 8},
        'context': {'includeDeclaration': True}
    }
})
ref_l = read()
print("Result count:", len(ref_l['result']))
print("Locations:", json.dumps(ref_l['result'], indent=2))
assert ref_l['id'] == 6
assert len(ref_l['result']) >= 3 # var l, l.push_back(10), l.push_back(20)
print(f" PASS: References on 'l' returned {len(ref_l['result'])} occurrences!")

# 8. Test References across files on 'push_back'
print("\n[Test 6] Go to References on 'push_back'...")
send({
    'jsonrpc': '2.0',
    'id': 7,
    'method': 'textDocument/references',
    'params': {
        'textDocument': {'uri': 'file:///c:/Projects/limitly/tests/collections/list_test.lm'},
        'position': {'line': 3, 'character': 8},
        'context': {'includeDeclaration': True}
    }
})
ref_pb = read()
print("Result count:", len(ref_pb['result']))
assert ref_pb['id'] == 7
uris = {r['uri'].lower() for r in ref_pb['result']}
print("URIs found:", uris)
assert any('linkedlist.lm' in u for u in uris), "Expected declaration in linkedlist.lm"
assert any('list_test.lm' in u for u in uris), "Expected references in list_test.lm"
print(f" PASS: Cross-file references on 'push_back' found {len(ref_pb['result'])} occurrences spanning both list_test.lm and linkedlist.lm!")

send({'jsonrpc': '2.0', 'id': 8, 'method': 'shutdown', 'params': {}})
read()
send({'jsonrpc': '2.0', 'method': 'exit', 'params': {}})
proc.wait()
print("\n ALL LSP DEFINITION & REFERENCE TESTS PASSED 100%!")
