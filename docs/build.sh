#!/usr/bin/env bash
# ==============================================================================
# Limitly Build Script (Delegates to root Makefile)
# ==============================================================================

set -e
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

echo "[BUILD] Building Limitly via root Makefile..."
cd "${ROOT_DIR}"
make "$@"
echo "[OK] Build completed successfully. Output in bin/"
