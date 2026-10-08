#!/usr/bin/env bash
# Run with Bash (including MSYS2 on Windows). No fixed checkout location required.
set -euo pipefail
repo_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)
prefix=${LYMAR_PREFIX:-"${HOME}/.local"}
jobs=${LYMAR_JOBS:-4}
install_cxx=${CXX:-g++}
install_cc=${CC:-gcc}
install_ar=${AR:-ar}
precompile_stdlib=0
while (($#)); do
    case "$1" in
        --prefix) prefix=$2; shift 2 ;;
        --jobs) jobs=$2; shift 2 ;;
        --precompile-stdlib) precompile_stdlib=1; shift ;;
        --help) echo 'Usage: bash scripts/install.sh [--prefix DIR] [--jobs N] [--precompile-stdlib]'; exit 0 ;;
        *) echo "Unknown option: $1" >&2; exit 2 ;;
    esac
done
[[ $jobs =~ ^[1-9][0-9]*$ ]] || { echo 'Jobs must be a positive integer' >&2; exit 2; }
for tool in git make "$install_cc" "$install_cxx" "$install_ar" python3; do
    command -v "$tool" >/dev/null || { echo "Required tool missing: $tool (Windows: use MSYS2 MinGW64)" >&2; exit 1; }
done
cd "$repo_root"
dependency_prefix=${LYMAR_DEPENDENCY_PREFIX:-"$repo_root/.cache/lymar-deps"}
if [[ -d $dependency_prefix/usr/include ]]; then
    for include_dir in "$dependency_prefix/usr/include" "$dependency_prefix/usr/include/"*; do
        [[ ! -d $include_dir ]] || export CPATH="$include_dir${CPATH:+:$CPATH}"
    done
    for library_dir in "$dependency_prefix/usr/lib" "$dependency_prefix/usr/lib/"*; do
        [[ ! -d $library_dir ]] || export LIBRARY_PATH="$library_dir${LIBRARY_PATH:+:$LIBRARY_PATH}"
    done
fi
git submodule update --init --recursive
# Check the headers/libraries without changing system package configuration.
probe_dir=$(mktemp -d)
trap 'rm -rf "$probe_dir"' EXIT
printf '#include <ffi.h>\n#include <openssl/ssl.h>\n#include <zlib.h>\nint main(void) { ffi_cif c; return ffi_prep_cif(&c, FFI_DEFAULT_ABI, 0, &ffi_type_void, 0) != FFI_OK; }\n' > "$probe_dir/deps.c"
"$install_cc" "$probe_dir/deps.c" -lffi -lssl -lcrypto -lz -o "$probe_dir/deps" || {
    echo 'Install libffi, OpenSSL, and zlib development packages, or set CPATH/LIBRARY_PATH to their prefix.' >&2
    exit 1
}
"$probe_dir/deps"
# Build-directory names include HEAD so branch switches do not reuse incompatible objects.
revision=$(git rev-parse --short HEAD)
make -j"$jobs" CXX="$install_cxx" CC="$install_cc" AR="$install_ar" OBJ_DIR="build/install-$revision-deps/obj" RSP_DIR="build/install-$revision-deps/rsp"
exe=lymar
[[ -f bin/lymar.exe ]] && exe=lymar.exe
if ((precompile_stdlib)); then
    export LYMAR_NATIVE_CXX=${LYMAR_NATIVE_CXX:-$install_cxx}
    case "$(uname -s)" in
        Darwin) module_ext=.dylib ;;
        MINGW*|MSYS*|CYGWIN*) module_ext=.dll ;;
        *) module_ext=.so ;;
    esac
    for module in collections font; do
        "bin/$exe" build -shared "std/$module/index.lm" -o "bin/lib$module$module_ext"
    done
fi
mkdir -p "$prefix/bin" "$prefix/share/lymar/bin"
prefix=$(cd "$prefix" && pwd)
cp "bin/$exe" "$prefix/share/lymar/bin/$exe"
[[ ! -f bin/liblymar_aot.a ]] || cp bin/liblymar_aot.a "$prefix/share/lymar/bin/"
cp -R std "$prefix/share/lymar/"
for name in lymar_ssl stb_image collections font; do
    for extension in .so .dll .dylib; do
        for suffix in '' .meta; do
            lib="bin/lib$name$extension$suffix"
            [[ ! -f $lib ]] || cp "$lib" "$prefix/share/lymar/bin/"
        done
    done
done
# The executable remains beside its native libraries; a launcher sets module discovery.
python3 - "$prefix" "$exe" <<'PY'
import pathlib, shlex, sys
prefix, exe = sys.argv[1:]
home = str(pathlib.Path(prefix) / 'share' / 'lymar')
launcher = pathlib.Path(prefix) / 'bin' / 'lymar'
launcher.write_text('#!/usr/bin/env bash\nexport LYMAR_HOME=' + shlex.quote(home) + '\nexec ' + shlex.quote(home + '/bin/' + exe) + ' "$@"\n')
launcher.chmod(0o755)
PY
"$prefix/bin/lymar" run tests/basic/hello.lm
echo "Installed Lymar. Add $prefix/bin to PATH."
