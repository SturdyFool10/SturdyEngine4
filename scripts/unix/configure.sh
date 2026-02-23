#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE="${1:-Debug}"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
BUILD_DIR="${ROOT}/build"

mkdir -p "${BUILD_DIR}"

cmake -S "${ROOT}" -B "${BUILD_DIR}" -G Ninja \
  -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
