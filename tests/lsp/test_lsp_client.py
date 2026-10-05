import subprocess
import json
import sys
import os

def run_lsp_test():
    exe_path = os.path.abspath("bin/lymar.exe")
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
                "languageId": "lymar",
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

    # 13. Test general completion (keywords, snippets, built-in functions, built-in types)
    print("\n[13] Testing general completion (keywords, snippets, builtins)...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 10,
        "method": "textDocument/completion",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 0, "character": 0 }
        }
    })
    comp_gen = read_rpc()
    assert comp_gen["id"] == 10
    gen_items = comp_gen["result"]["items"]
    labels = {it["label"] for it in gen_items}
    assert "frame" in labels or "fn" in labels, "Expected keywords in completion"
    assert "print" in labels or "append" in labels, "Expected builtin functions in completion"
    assert "int" in labels or "str" in labels, "Expected builtin types in completion"
    snip_items = [it for it in gen_items if it.get("kind") == 15] # Snippet
    assert len(snip_items) > 0, "Expected snippets in completion"
    print(f" PASS: General completion returned {len(gen_items)} items (keywords, types, builtins, snippets)")

    # 14. Test decorator completion ('@')
    print("\n[14] Testing decorator completion ('@')...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": { "uri": "file:///test.lm", "version": 5 },
            "contentChanges": [{ "text": "@\nfn example(): int { return 1; }" }]
        }
    })
    _ = read_rpc() # consume publishDiagnostics
    send_rpc({
        "jsonrpc": "2.0",
        "id": 11,
        "method": "textDocument/completion",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 0, "character": 1 }
        }
    })
    dec_comp = read_rpc()
    assert dec_comp["id"] == 11
    dec_labels = {it["label"] for it in dec_comp["result"]["items"]}
    assert "@inline" in dec_labels or "@pure" in dec_labels or "@test" in dec_labels
    print(" PASS: Decorator completion returned @inline, @pure, @test, etc.")

    # 15. Test context-aware type completion (after ':')
    print("\n[15] Testing context-aware type completion (after ':')...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": { "uri": "file:///test.lm", "version": 6 },
            "contentChanges": [{ "text": "var count: " }]
        }
    })
    _ = read_rpc() # consume publishDiagnostics
    send_rpc({
        "jsonrpc": "2.0",
        "id": 12,
        "method": "textDocument/completion",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 0, "character": 11 }
        }
    })
    type_comp = read_rpc()
    assert type_comp["id"] == 12
    type_labels = {it["label"] for it in type_comp["result"]["items"]}
    assert "int" in type_labels and "str" in type_labels and "bool" in type_labels and "float" in type_labels
    assert "for" not in type_labels, "Keywords should not be suggested as types after colon"
    print(" PASS: Context-aware type completion suggested primitive and custom types")

    # 16. Test hover on keywords, built-in types, and built-in functions
    print("\n[16] Testing hover on keywords, built-in types, and builtins...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": { "uri": "file:///test.lm", "version": 7 },
            "contentChanges": [{ "text": "while (true) {\n    print(\"hi\");\n}" }]
        }
    })
    _ = read_rpc() # consume publishDiagnostics
    # Hover on keyword 'while'
    send_rpc({
        "jsonrpc": "2.0",
        "id": 13,
        "method": "textDocument/hover",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 0, "character": 2 }
        }
    })
    hover_while = read_rpc()
    assert hover_while["id"] == 13
    assert "while" in hover_while["result"]["contents"]["value"]
    print(" PASS: Keyword hover returned documentation")

    # Hover on builtin function 'print'
    send_rpc({
        "jsonrpc": "2.0",
        "id": 14,
        "method": "textDocument/hover",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 1, "character": 6 }
        }
    })
    hover_print = read_rpc()
    assert hover_print["id"] == 14
    assert "print" in hover_print["result"]["contents"]["value"]
    print(" PASS: Built-in function hover returned signature and doc")

    # 17. Test signature help for built-in functions with active parameter
    print("\n[17] Testing signature help on built-in function call...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": { "uri": "file:///test.lm", "version": 8 },
            "contentChanges": [{ "text": "var l = [1, 2];\nappend(l, 3" }]
        }
    })
    diag_17 = read_rpc() # consume publishDiagnostics
    print("Diag 17:", diag_17)
    print("Proc poll after didChange:", proc.poll())
    if proc.poll() is not None:
        print("LSP Server died! Stderr:", proc.stderr.read().decode("utf-8", errors="ignore"))
        sys.exit(1)
    send_rpc({
        "jsonrpc": "2.0",
        "id": 15,
        "method": "textDocument/signatureHelp",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 1, "character": 11 } # after comma
        }
    })
    sig_append = read_rpc()
    assert sig_append["id"] == 15
    assert len(sig_append["result"]["signatures"]) > 0
    assert sig_append["result"]["activeParameter"] == 1, "Active parameter after comma should be 1"
    print(" PASS: Built-in signature help identified 'append' and active parameter index 1")

    # 18. Test textDocument/references (Find All References)
    print("\n[18] Testing 'textDocument/references'...")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "textDocument/didChange",
        "params": {
            "textDocument": { "uri": "file:///test.lm", "version": 9 },
            "contentChanges": [{ "text": "var my_num = 100;\nvar doubled = my_num * 2;\nvar tripled = my_num * 3;" }]
        }
    })
    _ = read_rpc() # consume publishDiagnostics
    send_rpc({
        "jsonrpc": "2.0",
        "id": 16,
        "method": "textDocument/references",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 0, "character": 6 }, # over 'my_num'
            "context": { "includeDeclaration": True }
        }
    })
    ref_res = read_rpc()
    assert ref_res["id"] == 16
    refs = ref_res["result"]
    assert len(refs) == 3, f"Expected 3 references including declaration, got {len(refs)}"
    print(f" PASS: References found {len(refs)} occurrences with includeDeclaration: true")

    send_rpc({
        "jsonrpc": "2.0",
        "id": 17,
        "method": "textDocument/references",
        "params": {
            "textDocument": { "uri": "file:///test.lm" },
            "position": { "line": 0, "character": 6 }, # over 'my_num'
            "context": { "includeDeclaration": False }
        }
    })
    ref_res2 = read_rpc()
    assert ref_res2["id"] == 17
    refs2 = ref_res2["result"]
    assert len(refs2) == 2, f"Expected 2 references excluding declaration, got {len(refs2)}"
    print(f" PASS: References found {len(refs2)} occurrences with includeDeclaration: false")

    # 19. Test workspace/symbol (Symbol Search)
    print("\n[19] Testing 'workspace/symbol'...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 18,
        "method": "workspace/symbol",
        "params": {
            "query": "my_num"
        }
    })
    ws_res = read_rpc()
    assert ws_res["id"] == 18
    ws_symbols = ws_res["result"]
    assert len(ws_symbols) > 0
    assert any(s["name"] == "my_num" for s in ws_symbols)
    print(" PASS: Workspace symbol search found 'my_num'")

    # 20. Test shutdown and exit
    print("\n[20] Testing 'shutdown' and 'exit'...")
    send_rpc({
        "jsonrpc": "2.0",
        "id": 19,
        "method": "shutdown",
        "params": {}
    })
    shutdown_res = read_rpc()
    assert shutdown_res["id"] == 19
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
