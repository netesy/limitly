#!/usr/bin/env python3
import json, subprocess, sys

def frame(message):
    payload=json.dumps(message,separators=(",",":"))
    return f"Content-Length: {len(payload)}\r\n\r\n{payload}".encode()

uri="file:///typed-hole.lm"
source="type Positive = int where value > 10000;\nvar existing: Positive = 10001;\nvar answer: Positive = ?;\n"
messages=[
 {"jsonrpc":"2.0","id":1,"method":"initialize","params":{}},
 {"jsonrpc":"2.0","method":"textDocument/didOpen","params":{"textDocument":{"uri":uri,"version":1,"text":source}}},
 {"jsonrpc":"2.0","id":2,"method":"textDocument/completion","params":{"textDocument":{"uri":uri},"position":{"line":2,"character":23}}},
 {"jsonrpc":"2.0","method":"textDocument/didChange","params":{"textDocument":{"uri":uri,"version":2},"contentChanges":[{"range":{"start":{"line":2,"character":23},"end":{"line":2,"character":24}},"text":"10001"}]}},
 {"jsonrpc":"2.0","id":3,"method":"shutdown","params":{}},
 {"jsonrpc":"2.0","method":"exit","params":{}},
]
proc=subprocess.run(["./bin/limitly","-lsp"],input=b"".join(map(frame,messages)),stdout=subprocess.PIPE,stderr=subprocess.PIPE,check=True)
out=proc.stdout
responses=[]
while out:
    head,out=out.split(b"\r\n\r\n",1)
    length=int(head.split(b":",1)[1])
    payload,out=out[:length],out[length:]
    responses.append(json.loads(payload))
completion=next(r for r in responses if r.get("id")==2)
assert any(i["label"]=="10001" and "statically proves" in i["detail"] for i in completion["result"]["items"]), completion
published=[r for r in responses if r.get("method")=="textDocument/publishDiagnostics"]
assert any(any("typed hole: expected" in d["message"] for d in r["params"]["diagnostics"]) for r in published), published
assert published[-1]["params"]["version"]==2 and published[-1]["params"]["diagnostics"]==[], published[-1]
print("incremental LSP and proof-aware typed-hole completion passed")
