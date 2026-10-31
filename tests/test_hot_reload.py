# Roadmap item 6 verification: Hot reload + LSP/build integration
import json
import os
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BIN = ROOT / "bin" / ("lymar.exe" if os.name == "nt" else "lymar")


def test_cli_watch_loop(temp_dir):
    src = temp_dir / "watch_test.lm"
    src.write_text('fn main(): int {\n    print("watch hello");\n    return 0;\n}\n', encoding="utf-8")

    # Test run --watch
    env = dict(os.environ, LYMAR_WATCH_ONCE="1")
    res = subprocess.run([str(BIN), "run", "--watch", str(src)], capture_output=True, text=True, cwd=temp_dir, env=env)
    if res.returncode != 0:
        print("FAIL: lymar run --watch failed")
        print(res.stdout + res.stderr)
        return False
    if "watch hello" not in res.stdout or "[WATCH]" not in res.stdout:
        print(f"FAIL: unexpected output for lymar run --watch:\n{res.stdout}")
        return False
    print("PASS: CLI run --watch executes and initiates watch mode")

    # Test build --watch
    out_exe = temp_dir / "watch_test.exe"
    res = subprocess.run([str(BIN), "build", "--watch", str(src), "-o", str(out_exe), "--no-cache"],
                         capture_output=True, text=True, cwd=temp_dir, env=env)
    if res.returncode != 0:
        print("FAIL: lymar build --watch failed")
        print(res.stdout + res.stderr)
        return False
    if "[WATCH]" not in res.stdout or "built successfully" not in res.stdout:
        print(f"FAIL: unexpected output for lymar build --watch:\n{res.stdout}")
        return False
    print("PASS: CLI build --watch compiles and initiates watch mode")
    return True


def test_lsp_watched_files(temp_dir):
    src = temp_dir / "lsp_watch.lm"
    src.write_text('fn main(): int {\n    var x: int = 42;\n    return 0;\n}\n', encoding="utf-8")
    uri = "file://" + str(src).replace('\\', '/')
    if not uri.startswith("file:///"):
        uri = "file:///" + str(src).replace('\\', '/').lstrip('/')

    proc = subprocess.Popen([str(BIN), "-lsp"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    def send_rpc(msg):
        payload = json.dumps(msg)
        header = f"Content-Length: {len(payload)}\r\n\r\n"
        proc.stdin.write(header + payload)
        proc.stdin.flush()

    def read_rpc():
        line = proc.stdout.readline()
        while line and not line.lower().startswith("content-length:"):
            line = proc.stdout.readline()
        if not line:
            return None
        length = int(line.split(":")[1].strip())
        # consume empty lines
        while True:
            hdr = proc.stdout.readline()
            if hdr in ("\r\n", "\n", ""):
                break
        payload = proc.stdout.read(length)
        return json.loads(payload)

    # 1. Initialize
    send_rpc({
        "jsonrpc": "2.0",
        "id": 1,
        "method": "initialize",
        "params": {
            "capabilities": {}
        }
    })
    init_res = read_rpc()
    if not init_res or "result" not in init_res:
        print("FAIL: LSP initialize returned no result")
        proc.kill()
        return False
    caps = init_res["result"].get("capabilities", {})
    if "workspace" not in caps or "didChangeWatchedFiles" not in caps["workspace"]:
        print(f"FAIL: LSP did not declare workspace.didChangeWatchedFiles capability:\n{caps}")
        proc.kill()
        return False
    print("PASS: LSP announces workspace.didChangeWatchedFiles capability")

    # 2. Update file on disk and send workspace/didChangeWatchedFiles
    src.write_text('fn main(): int {\n    var y: int = 100;\n    return 0;\n}\n', encoding="utf-8")
    send_rpc({
        "jsonrpc": "2.0",
        "method": "workspace/didChangeWatchedFiles",
        "params": {
            "changes": [
                {
                    "uri": uri,
                    "type": 2
                }
            ]
        }
    })

    # Read diagnostic publication
    diag_msg = read_rpc()
    if not diag_msg or diag_msg.get("method") != "textDocument/publishDiagnostics":
        print(f"FAIL: expected textDocument/publishDiagnostics, got {diag_msg}")
        proc.kill()
        return False
    print("PASS: LSP handles workspace/didChangeWatchedFiles and publishes diagnostics")

    # Shutdown
    send_rpc({"jsonrpc": "2.0", "id": 2, "method": "shutdown", "params": None})
    read_rpc()
    send_rpc({"jsonrpc": "2.0", "method": "exit", "params": None})
    proc.wait(timeout=5)
    return True


def test_dap_reload():
    proc = subprocess.Popen([str(BIN), "-dap"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    def send_dap(msg):
        payload = json.dumps(msg)
        header = f"Content-Length: {len(payload)}\r\n\r\n"
        proc.stdin.write(header + payload)
        proc.stdin.flush()

    def read_dap():
        line = proc.stdout.readline()
        while line and not line.lower().startswith("content-length:"):
            line = proc.stdout.readline()
        if not line:
            return None
        length = int(line.split(":")[1].strip())
        while True:
            hdr = proc.stdout.readline()
            if hdr in ("\r\n", "\n", ""):
                break
        payload = proc.stdout.read(length)
        return json.loads(payload)

    # Initialize DAP
    send_dap({
        "seq": 1,
        "type": "request",
        "command": "initialize",
        "arguments": {"clientID": "test", "adapterID": "lymar"}
    })
    init_res = read_dap()
    if not init_res or not init_res.get("success"):
        print("FAIL: DAP initialize failed")
        proc.kill()
        return False

    # Send custom reload request
    send_dap({
        "seq": 2,
        "type": "request",
        "command": "reload",
        "arguments": {}
    })

    # May receive output event first, followed by reload response
    got_reload_res = False
    for _ in range(5):
        msg = read_dap()
        if not msg:
            break
        if msg.get("type") == "response" and msg.get("command") == "reload":
            if msg.get("success"):
                got_reload_res = True
                break

    if not got_reload_res:
        print("FAIL: DAP did not reply successfully to reload request")
        proc.kill()
        return False
    print("PASS: DAP handled reload request and returned success response")

    # Disconnect
    send_dap({
        "seq": 3,
        "type": "request",
        "command": "disconnect",
        "arguments": {}
    })
    read_dap()
    proc.stdin.close()
    proc.wait(timeout=5)
    return True


def main():
    temp_dir = Path(tempfile.mkdtemp(prefix="lymar_hot_reload_test_"))
    try:
        if not test_cli_watch_loop(temp_dir):
            return 1
        if not test_lsp_watched_files(temp_dir):
            return 1
        if not test_dap_reload():
            return 1
        print("6 verification: ALL PASSED")
        return 0
    finally:
        shutil.rmtree(temp_dir, ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
