#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE="${1:-Debug}"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
BUILD_DIR="${ROOT}/build/_cmake"

mkdir -p "${BUILD_DIR}"

cmake -S "${ROOT}" -B "${BUILD_DIR}" -G Ninja \
  -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

if [[ -f "${BUILD_DIR}/compile_commands.json" ]]; then
  mkdir -p "${ROOT}/build"
  cp -f "${BUILD_DIR}/compile_commands.json" "${ROOT}/build/compile_commands.json"
fi
