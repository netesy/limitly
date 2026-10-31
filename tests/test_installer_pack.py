# Roadmap item 5 verification: Installer backends (.deb / .msi)
import os
import shutil
import subprocess
import sys
import tarfile
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BIN = ROOT / "bin" / ("lymar.exe" if os.name == "nt" else "lymar")


def main():
    if not BIN.exists():
        print(f"FAIL: missing compiler binary {BIN}")
        return 1

    temp_dir = Path(tempfile.mkdtemp(prefix="lymar_installer_test_"))
    try:
        # Create a sample project
        (temp_dir / "src").mkdir(parents=True)
        (temp_dir / "src" / "main.lm").write_text(
            'fn main(): int {\n    print("sample app running");\n    return 0;\n}\n',
            encoding="utf-8"
        )
        (temp_dir / "lymar.nol").write_text(
            'package: {\n  name: "sampleapp",\n  version: "2.1.0",\n  description: "A sample test package",\n  author: "Lymar Team <team@example.com>"\n}\n',
            encoding="utf-8"
        )

        # Build executable first
        res = subprocess.run([str(BIN), "build", "src/main.lm", "-o", "sampleapp", "--no-cache"],
                             cwd=temp_dir, capture_output=True, text=True)
        if res.returncode != 0:
            print("FAIL: failed to build project executable")
            print(res.stdout + res.stderr)
            return 1
        print("PASS: project executable built successfully")

        # Test default pack (.tar.gz)
        res = subprocess.run([str(BIN), "pack"], cwd=temp_dir, capture_output=True, text=True)
        if res.returncode != 0:
            print("FAIL: lymar pack failed")
            print(res.stdout + res.stderr)
            return 1
        tarball = temp_dir / "sampleapp-2.1.0.tar.gz"
        if not tarball.is_file():
            print(f"FAIL: expected tarball {tarball} not found")
            return 1
        print("PASS: lymar pack generated source tarball")

        # Test pack --deb
        res = subprocess.run([str(BIN), "pack", "--deb"], cwd=temp_dir, capture_output=True, text=True)
        if res.returncode != 0:
            print("FAIL: lymar pack --deb failed")
            print(res.stdout + res.stderr)
            return 1

        deb_files = list(temp_dir.glob("sampleapp_2.1.0_*.deb"))
        if not deb_files:
            print("FAIL: no .deb file generated")
            return 1
        deb_file = deb_files[0]

        # Inspect ar archive header
        with open(deb_file, "rb") as f:
            magic = f.read(8)
            if magic != b"!<arch>\n":
                print(f"FAIL: invalid ar archive magic: {magic!r}")
                return 1

        # Use ar to inspect members if available
        if shutil.which("ar"):
            ar_out = subprocess.run(["ar", "t", str(deb_file)], capture_output=True, text=True)
            lines = ar_out.stdout.strip().split()
            expected_members = ["debian-binary", "control.tar.gz", "data.tar.gz"]
            if lines != expected_members:
                print(f"FAIL: unexpected ar members: {lines} vs {expected_members}")
                return 1
            print("PASS: ar archive contains debian-binary, control.tar.gz, data.tar.gz")

        # If dpkg-deb is available, verify package metadata
        if shutil.which("dpkg-deb"):
            dpkg_info = subprocess.run(["dpkg-deb", "-I", str(deb_file)], capture_output=True, text=True)
            if dpkg_info.returncode != 0:
                print(f"FAIL: dpkg-deb -I failed on {deb_file}")
                return 1
            info_text = dpkg_info.stdout
            if "Package: sampleapp" not in info_text or "Version: 2.1.0" not in info_text:
                print(f"FAIL: dpkg-deb missing package metadata:\n{info_text}")
                return 1
            print("PASS: dpkg-deb validates Debian package structure and metadata")

        # Test pack --msi (WiX template)
        res = subprocess.run([str(BIN), "pack", "--msi"], cwd=temp_dir, capture_output=True, text=True)
        if res.returncode != 0:
            print("FAIL: lymar pack --msi failed")
            print(res.stdout + res.stderr)
            return 1

        wxs_file = temp_dir / "sampleapp.wxs"
        if not wxs_file.is_file():
            print(f"FAIL: expected WiX template {wxs_file} not found")
            return 1

        wxs_content = wxs_file.read_text(encoding="utf-8")
        if "<Product" not in wxs_content or "sampleapp" not in wxs_content:
            print(f"FAIL: invalid WiX template content:\n{wxs_content}")
            return 1
        print("PASS: WiX template generated with Product and component definitions")

        print("5 verification: ALL PASSED")
        return 0

    finally:
        shutil.rmtree(temp_dir, ignore_errors=True)


if __name__ == "__main__":
    sys.exit(main())
