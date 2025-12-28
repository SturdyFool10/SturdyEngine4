#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

rm -rf "${ROOT}/build/_cmake" "${ROOT}/build/bin" "${ROOT}/build/lib" "${ROOT}/build/compile_commands.json"
echo "Cleaned build outputs."
