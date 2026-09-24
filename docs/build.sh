#!/usr/bin/env bash
# ==============================================================================
# Lymar Build Script (Delegates to root Makefile)
# ==============================================================================

set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

echo "[BUILD] Building Lymar via root Makefile..."
cd "${ROOT_DIR}"
make "$@"
echo "[OK] Build completed successfully. Output in bin/"
