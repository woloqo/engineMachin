#!/usr/bin/env bash
set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$PROJECT_DIR"

rm -rf out
cmake --preset "Custom configure preset"
cmake --build out/build/"Custom configure preset"

printf '\nCache limpiado y proyecto reconstruido correctamente.\n'
