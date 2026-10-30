"""Test that documentSymbol returns valid containment."""
import subprocess, json, time

def send(proc, msg):
    body = json.dumps(msg)
    header = f'Content-Length: {len(body)}\r\n\r\n'
    proc.stdin.write((header + body).encode())
    proc.stdin.flush()

def recv(proc):
    # Skip non-protocol lines (e.g. startup messages on stderr leaking)
    while True:
        line = proc.stdout.readline().decode().strip()
        if not line:
            continue
        if line.startswith('Content-Length:'):
            cl = int(line.split(':')[1].strip())
            break
    proc.stdout.readline()  # \r\n separator
    return json.loads(proc.stdout.read(cl).decode())

proc = subprocess.Popen(['bin/lymar.exe', '-lsp'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)

# Initialize
send(proc, {'jsonrpc':'2.0','id':1,'method':'initialize','params':{'capabilities':{}}})
resp = recv(proc)
print(f"Initialize response id={resp.get('id')}")

# Open a simple test file inline
simple = 'frame TestFrame {\n    pub x: int;\n    pub fn greet(): str {\n        return "hello";\n    }\n}\n\nfn helper(): int {\n    return 42;\n}\n'

uri = 'file:///test_inline.lm'
send(proc, {'jsonrpc':'2.0','method':'textDocument/didOpen','params':{'textDocument':{'uri':uri,'languageId':'lymar','version':1,'text':simple}}})

# Give server time to parse
time.sleep(1)

# Check if process is still alive
if proc.poll() is not None:
    print(f"ERROR: LSP process died with code {proc.returncode}")
    proc.terminate()
    exit(1)

# Request document symbols
send(proc, {'jsonrpc':'2.0','id':2,'method':'textDocument/documentSymbol','params':{'textDocument':{'uri':uri}}})

# The response might come after diagnostics notifications, so read until we get id=2
for _ in range(10):
    result = recv(proc)
    if result.get('id') == 2:
        break
    # skip notifications like publishDiagnostics

def validate(sym):
    """Check selectionRange is contained in range."""
    r = sym['range']
    sr = sym['selectionRange']
    if sr['start']['line'] < r['start']['line']:
        return False, f"{sym['name']}: sel start line {sr['start']['line']} < range start {r['start']['line']}"
    if sr['start']['line'] == r['start']['line'] and sr['start']['character'] < r['start']['character']:
        return False, f"{sym['name']}: sel start char < range start char"
    if sr['end']['line'] > r['end']['line']:
        return False, f"{sym['name']}: sel end line {sr['end']['line']} > range end {r['end']['line']}"
    if sr['end']['line'] == r['end']['line'] and sr['end']['character'] > r['end']['character']:
        return False, f"{sym['name']}: sel end char {sr['end']['character']} > range end char {r['end']['character']}"
    for child in sym.get('children', []):
        ok, msg = validate(child)
        if not ok:
            return False, msg
    return True, "ok"

syms = result.get('result', [])
print(f"Got {len(syms)} top-level symbols")
all_ok = True
for s in syms:
    ok, msg = validate(s)
    status = "PASS" if ok else "FAIL"
    print(f"  [{status}] {s['name']} (children: {len(s.get('children',[]))}): {msg}")
    if not ok:
        all_ok = False

if all_ok and len(syms) > 0:
    print("\nAll documentSymbol containment checks PASSED")
elif len(syms) == 0:
    print("\nWARNING: 0 symbols returned - parser might not have parsed the file")
else:
    print("\nSome checks FAILED")

proc.terminate()
