#!/usr/bin/env bash
set -euo pipefail

BUILD_TYPE="${1:-Debug}"

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"

"${ROOT}/scripts/unix/build.sh" "${BUILD_TYPE}" SturdyRuntime

EXE="${ROOT}/build/bin/SturdyRuntime"
if [[ ! -x "${EXE}" ]]; then
  echo "Expected runtime executable not found or not executable: ${EXE}" >&2
  exit 1
fi

exec "${EXE}"
