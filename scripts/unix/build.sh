#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE="${1:-Debug}"
TARGET="${2:-}"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
BUILD_DIR="${ROOT}/build"

if [[ ! -f "${BUILD_DIR}/CMakeCache.txt" ]]; then
  "${ROOT}/scripts/unix/configure.sh" "${BUILD_TYPE}"
fi

if [[ -z "${TARGET}" ]]; then
  cmake --build "${BUILD_DIR}" --config "${BUILD_TYPE}"
else
  cmake --build "${BUILD_DIR}" --config "${BUILD_TYPE}" --target "${TARGET}"
fi
