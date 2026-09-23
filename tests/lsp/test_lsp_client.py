import subprocess
import json
import sys
import os

def run_lsp_test():
    exe_path = os.path.abspath("bin/limitly.exe")
    print(f"Testing LSP server at: {exe_path}")

    proc = subprocess.Popen(
        [exe_path, "-lsp"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        bufsize=0
    )

    def send_rpc(msg_obj):
        payload = json.dumps(msg_obj).encode("utf-8")
        header = f"Content-Length: {len(payload)}\r\n\r\n".encode("utf-8")
        proc.stdin.write(header + payload)
        proc.stdin.flush()

    def read_rpc():
        # Read header lines until empty line
        content_length = None
        while True:
            line = proc.stdout.readline().decode("utf-8")
            if not line:
                return None
            line = line.strip()
            if not line:
                break
            if line.lower().startswith("content-length:"):
                content_length = int(line.split(":")[1].strip())
        
        if content_length is None:
            return None
        chunks = []
        remaining = content_length
        while remaining > 0:
            chunk = proc.stdout.read(remaining)
            if not chunk:
                break
            chunks.append(chunk)
            remaining -= len(chunk)
        body = b"".join(chunks).decode("utf-8")
        return json.loads(body)

    # 1. Test initialize
    print("\n[1] Testing 'initialize' request...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 1,
        "method": "initialize",
        "params": {
            "processId": None,
            "rootUri": "file:///workspace",
            "capabilities": {}
        }
    })
    init_res = read_rpc()
    print("Initialize Response:", json.dumps(init_res, indent=2))
    assert init_res["id"] == 1
    assert "capabilities" in init_res["result"]
    assert init_res["result"]["capabilities"]["textDocumentSync"] == 1
    print(" PASS: initialize capability handshake ok")

    # 2. Test initialized notification
    print("\n[2] Testing 'initialized' notification...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "initialized",
        "params": {}
    })

    # 3. Test textDocument/didOpen (valid code)
    print("\n[3] Testing 'textDocument/didOpen' with valid code...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didOpen",
        "params": {
            "textDocument": {
                "uri": "file:///test.lm",
                "languageId": "limitly",
                "version": 1,
                "text": "var x: int = 100;\nfn get_num(): int { return x; }"
            }
        }
    })
    diag_open = read_rpc()
    print("Diagnostics after didOpen:", json.dumps(diag_open, indent=2))
    assert diag_open["method"] == "textDocument/publishDiagnostics"
    assert len(diag_open["params"]["diagnostics"]) == 0
    print(" PASS: Clean document has 0 diagnostics")

    # 4. Test textDocument/didChange (type mismatch)
    print("\n[4] Testing 'textDocument/didChange' introducing type error...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": {
                "uri": "file:///test.lm",
                "version": 2
            },
            "contentChanges": [
                {
                    "text": "var x: int = \"mismatched_str\";"
                }
            ]
        }
    })
    diag_change = read_rpc()
    print("Diagnostics after didChange:", json.dumps(diag_change, indent=2))
    assert diag_change["method"] == "textDocument/publishDiagnostics"
    assert len(diag_change["params"]["diagnostics"]) > 0
    first_diag = diag_change["params"]["diagnostics"][0]
    print(f"Reported error diagnostic: {first_diag['message']}")
    assert "type mismatch" in first_diag["message"]
    print(" PASS: publishDiagnostics correctly caught type mismatch")

    # 5. Test textDocument/completion (proof-aware hole)
    print("\n[5] Testing 'textDocument/completion' with typed hole '?'...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": {
                "uri": "file:///test.lm",
                "version": 3
            },
            "contentChanges": [
                {
                    "text": "var target: int = 42;\nvar chosen: int = ?;"
                }
            ]
        }
    })
    # Consume publishDiagnostics
    _ = read_rpc()

    send_rpc({
        "jsonrpc": "2.0",
        "id": 2,
        "method": "textDocument/completion",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 1, "character": 19 }
        }
    })
    comp_res = read_rpc()
    print("Completion Response:", json.dumps(comp_res, indent=2))
    assert comp_res["id"] == 2
    items = comp_res["result"]["items"]
    target_items = [it for it in items if it["label"] == "target"]
    assert len(target_items) > 0
    print("Target completion item:", target_items[0])
    assert "proven" in target_items[0]["detail"]
    print(" PASS: Proof-aware completion returned proven candidates")

    # 6. Test textDocument/hover
    print("\n[6] Testing 'textDocument/hover'...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 3,
        "method": "textDocument/hover",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 0, "character": 6 } # over 'target'
        }
    })
    hover_res = read_rpc()
    print("Hover Response:", json.dumps(hover_res, indent=2))
    assert hover_res["id"] == 3
    assert "contents" in hover_res["result"]
    assert "target" in hover_res["result"]["contents"]["value"]
    print(" PASS: Hover returns markdown signature")

    # 7. Test member / dot-access completion on frame instance
    print("\n[7] Testing member / dot-access completion on frame instance ('rect.')...")
    frame_code = (
        "frame Rectangle {\n"
        "    pub width: int;\n"
        "    pub height: int;\n"
        "    pub fn area(): int {\n"
        "        return self.width * self.height;\n"
        "    }\n"
        "    pub fn scale(factor: int): int {\n"
        "        return self.width * factor;\n"
        "    }\n"
        "}\n"
        "var rect: Rectangle = Rectangle { width: 10, height: 20 };\n"
        "var a = rect."
    )
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": { "uri": "file:///test.lm", "version": 4 },
            "contentChanges": [{ "text": frame_code }]
        }
    })
    _ = read_rpc() # consume publishDiagnostics

    send_rpc({
        "jsonrpc": "2.0",
        "id": 4,
        "method": "textDocument/completion",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 11, "character": 13 } # right after 'rect.'
        }
    })
    comp_dot_res = read_rpc()
    print("Member Completion Response:", json.dumps(comp_dot_res, indent=2))
    assert comp_dot_res["id"] == 4
    dot_items = comp_dot_res["result"]["items"]
    labels = [it["label"] for it in dot_items]
    print("Completion labels for 'rect.':", labels)
    assert "width" in labels, "Expected 'width' field in completion"
    assert "height" in labels, "Expected 'height' field in completion"
    assert "area" in labels, "Expected 'area' method in completion"
    assert "scale" in labels, "Expected 'scale' method in completion"
    print(" PASS: Member completion correctly resolved fields and methods of Rectangle")

    # 8. Test signature help on method call
    print("\n[8] Testing 'textDocument/signatureHelp' on method call ('rect.scale(')...")
    call_code = frame_code.replace("var a = rect.", "var a = rect.scale(")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": { "uri": "file:///test.lm", "version": 5 },
            "contentChanges": [{ "text": call_code }]
        }
    })
    _ = read_rpc() # consume publishDiagnostics

    send_rpc({
        "jsonrpc": "2.0",
        "id": 5,
        "method": "textDocument/signatureHelp",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 11, "character": 19 } # inside 'rect.scale('
        }
    })
    sig_res = read_rpc()
    print("Signature Help Response:", json.dumps(sig_res, indent=2))
    assert sig_res["id"] == 5
    sigs = sig_res["result"]["signatures"]
    assert len(sigs) > 0
    assert "scale" in sigs[0]["label"]
    assert len(sigs[0]["parameters"]) == 1
    assert "factor" in sigs[0]["parameters"][0]["label"]
    print(" PASS: Signature help correctly identified method and parameters")

    # 9. Test hover on member and frame
    print("\n[9] Testing 'textDocument/hover' on member 'scale'...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 6,
        "method": "textDocument/hover",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 11, "character": 16 } # over 'scale'
        }
    })
    hover_member_res = read_rpc()
    print("Member Hover Response:", json.dumps(hover_member_res, indent=2))
    assert hover_member_res["id"] == 6
    assert "scale" in hover_member_res["result"]["contents"]["value"]
    print(" PASS: Member hover returned correct signature")

    # 10. Test definition jump to member
    print("\n[10] Testing 'textDocument/definition' on 'scale'...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 7,
        "method": "textDocument/definition",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 11, "character": 16 } # over 'scale'
        }
    })
    def_res = read_rpc()
    print("Definition Response:", json.dumps(def_res, indent=2))
    assert def_res["id"] == 7
    assert def_res["result"]["range"]["start"]["line"] == 6 # 'pub fn scale' is on line 6 (0-indexed)
    print(" PASS: Definition jumped to method declaration line")

    # 11. Test document symbols
    print("\n[11] Testing 'textDocument/documentSymbol'...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 8,
        "method": "textDocument/documentSymbol",
        "params": {
            "textDocument": { "uri": "file:///test.lm" }
        }
    })
    sym_res = read_rpc()
    print("Document Symbols Response:", json.dumps(sym_res, indent=2))
    assert sym_res["id"] == 8
    sym_names = [s["name"] for s in sym_res["result"]]
    print("Document symbol names:", sym_names)
    assert "Rectangle" in sym_names
    rect_sym = [s for s in sym_res["result"] if s["name"] == "Rectangle"][0]
    child_names = [c["name"] for c in rect_sym.get("children", [])]
    print("Rectangle children symbols:", child_names)
    assert "width" in child_names
    assert "height" in child_names
    assert "area" in child_names
    assert "scale" in child_names
    print(" PASS: Document symbols returned complete symbol tree")

    # 12. Test document formatting
    print("\n[12] Testing 'textDocument/formatting'...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 9,
        "method": "textDocument/formatting",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "options": { "tabSize": 4, "insertSpaces": True }
        }
    })
    fmt_res = read_rpc()
    print("Formatting Response:", json.dumps(fmt_res, indent=2))
    assert fmt_res["id"] == 9
    edits = fmt_res["result"]
    assert isinstance(edits, list) and len(edits) > 0
    print(" PASS: Document formatting produced valid text edits")

    # 13. Test shutdown and exit
    print("\n[13] Testing 'shutdown' and 'exit'...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 10,
        "method": "shutdown",
        "params": {}
    })
    shutdown_res = read_rpc()
    assert shutdown_res["id"] == 10
    assert shutdown_res["result"] is None
    print(" PASS: shutdown ok")

    send_rpc({
        "jsonrpc": "2.0",
        "method": "exit",
        "params": {}
    })
    proc.wait(timeout=3)
    print(" PASS: Server exited cleanly with code", proc.returncode)

    print("\n ALL LSP JSON-RPC 2.0 PROTOCOL TESTS PASSED WITH 100% SUCCESS!")

if __name__ == "__main__":
    run_lsp_test()
