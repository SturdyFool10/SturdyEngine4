#pragma once
#include <cstdint>
//==============================================================================
// SE OS macros (presence-style: #ifdef SE_OS_WINDOWS)
// - You may also define any SE_OS_* macro yourself via the build system to
//   override autodetection (useful for consoles/SDKs).
//==============================================================================

// If none are pre-set by the build system, we attempt autodetect.
#if !defined(SE_OS_WINDOWS) && !defined(SE_OS_LINUX) && !defined(SE_OS_UNIX) && \
    !defined(SE_OS_POSIX) && !defined(SE_OS_FREEBSD) && !defined(SE_OS_IOS) && \
    !defined(SE_OS_ANDROID) && !defined(SE_OS_XBOX) && !defined(SE_OS_PLAYSTATION) && \
    !defined(SE_OS_SWITCH)

// Windows
#  if defined(_WIN32) || defined(_WIN64)
#    define SE_OS_WINDOWS
#  endif

// Android (treat as its own OS; do NOT also define SE_OS_LINUX)
#  if defined(__ANDROID__)
#    define SE_OS_ANDROID
#  endif

// Linux (non-Android)
#  if defined(__linux__) && !defined(__ANDROID__)
#    define SE_OS_LINUX
#  endif

// FreeBSD
#  if defined(__FreeBSD__)
#    define SE_OS_FREEBSD
#  endif

// iOS (Apple platforms)
#  if defined(__APPLE__)
#    include <TargetConditionals.h>
#    if defined(TARGET_OS_IPHONE) && (TARGET_OS_IPHONE == 1)
#      define SE_OS_IOS
#    endif
#  endif

// Unix / POSIX families (independent “category” flags)
#  if defined(__unix__) || defined(__unix) || defined(unix)
#    define SE_OS_UNIX
#  endif
#  if defined(_POSIX_VERSION)
#    define SE_OS_POSIX
#  endif

// Consoles: SDKs differ; define these in your build system (or add detection later)
//   -DSE_OS_XBOX
//   -DSE_OS_PLAYSTATION
//   -DSE_OS_SWITCH

#endif // autodetect guard

// Hard gate for now: only Windows + (non-Android) Linux supported.
#if !defined(SE_OS_WINDOWS) && !defined(SE_OS_LINUX)
#  error "SturdyEngine: platform detected but not supported yet. Supported: Windows, Linux. (Remove/adjust this #error when adding platforms.)"
#endif

//==============================================================================
// SE compiler macros (presence-style)
//==============================================================================

#if defined(__INTEL_LLVM_COMPILER)
#  define SE_COMPILER_INTEL_LLVM
#elif defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ICL)
#  define SE_COMPILER_INTEL_CLASSIC
#elif defined(__clang__)
#  define SE_COMPILER_CLANG
#  if defined(_MSC_VER)
#    define SE_COMPILER_CLANG_CL // clang in MSVC-compat mode (clang-cl)
#  endif
#elif defined(_MSC_VER)
#  define SE_COMPILER_MSVC
#elif defined(__GNUC__)
#  define SE_COMPILER_GCC
#else
#  error "SturdyEngine: unknown/unsupported compiler."
#endif

//==============================================================================
// SE architecture macros (presence-style)
//==============================================================================

// WebAssembly (varies; __wasm__ is common, __EMSCRIPTEN__ indicates Emscripten)
#if defined(__wasm__) || defined(__wasm32__) || defined(__wasm64__) || defined(__EMSCRIPTEN__)
#  define SE_ARCH_WASM
#  if defined(__wasm64__)
#    define SE_ARCH_WASM64
#  else
#    define SE_ARCH_WASM32
#  endif

// x86_64 / AMD64
#elif defined(_M_X64) || defined(_M_AMD64) || defined(__x86_64__) || defined(__amd64__) || defined(__amd64)
#  define SE_ARCH_X64

// x86 32-bit
#elif defined(_M_IX86) || defined(__i386__) || defined(__i386) || defined(i386)
#  define SE_ARCH_X86

// ARM64
#elif defined(_M_ARM64) || defined(__aarch64__)
#  define SE_ARCH_ARM64

// ARM 32-bit
#elif defined(_M_ARM) || defined(__arm__) || defined(__arm)
#  define SE_ARCH_ARM32

// PowerPC 64-bit
#elif defined(__ppc64__) || defined(__PPC64__) || defined(__powerpc64__)
#  define SE_ARCH_PPC64

// RISC-V (basic 64-bit detect)
#elif defined(__riscv) && (defined(__riscv_xlen) && (__riscv_xlen == 64))
#  define SE_ARCH_RISCV64

#else
#  error "SturdyEngine: unknown/unsupported target architecture."
#endif

// Convenience width flags
#if defined(SE_ARCH_X64) || defined(SE_ARCH_ARM64) || defined(SE_ARCH_PPC64) || defined(SE_ARCH_RISCV64) || defined(SE_ARCH_WASM64)
#  define SE_ARCH_64BIT
#else
#  define SE_ARCH_32BIT
#endif

//==============================================================================
// Export / import macro (SEAPI)
//==============================================================================
//
// Shared build:
//   Engine build:   -DSE_SHARED -DSE_BUILDING_ENGINE
//   Consumer build: -DSE_SHARED
//
#if defined(SE_SHARED)

#  if defined(SE_OS_WINDOWS)
#    if defined(SE_BUILDING_ENGINE)
#      define SEAPI __declspec(dllexport)
#    else
#      define SEAPI __declspec(dllimport)
#    endif
#  else
#    if defined(__GNUC__) || defined(__clang__)
#      define SEAPI __attribute__((visibility("default")))
#    else
#      define SEAPI
#    endif
#  endif

#else
#  define SEAPI
#endif

//==============================================================================
// Rust-like primitive type aliases
//==============================================================================


///8 Bit Unsigned Int, size guranteed by assertion
using u8  = std::uint8_t;
///16 Bit Unsigned Int, size guranteed by assertion
using u16 = std::uint16_t;
///32 Bit Unsigned Int, size guranteed by assertion
using u32 = std::uint32_t;
///64 Bit Unsigned Int, size guranteed by assertion
using u64 = std::uint64_t;
///8 Bit Signed Int, size guranteed by assertion
using i8  = std::int8_t;
///16 Bit Signed Int, size guranteed by assertion
using i16 = std::int16_t;
///32 Bit Signed Int, size guranteed by assertion
using i32 = std::int32_t;
///64 Bit Signed Int, size guranteed by assertion
using i64 = std::int64_t;
//32 Bit float, size guranteed by assertion
using f32 = float;
///64 Bit Float, size guranteed by assertion
using f64 = double;

// 1-byte boolean for packed/serialized storage (not the same as C++ bool semantics)
using b8 = std::uint8_t;

static_assert(sizeof(u8)  == 1, "u8 must be 1 byte");
static_assert(sizeof(u16) == 2, "u16 must be 2 bytes");
static_assert(sizeof(u32) == 4, "u32 must be 4 bytes");
static_assert(sizeof(u64) == 8, "u64 must be 8 bytes");
static_assert(sizeof(i8)  == 1, "i8 must be 1 byte");
static_assert(sizeof(i16) == 2, "i16 must be 2 bytes");
static_assert(sizeof(i32) == 4, "i32 must be 4 bytes");
static_assert(sizeof(i64) == 8, "i64 must be 8 bytes");
static_assert(sizeof(f32) == 4, "f32 must be 4 bytes");
static_assert(sizeof(f64) == 8, "f64 must be 8 bytes");
static_assert(sizeof(b8)  == 1, "b8 must be 1 byte");

#ifndef SE_B8_TRUE
#  define SE_B8_TRUE  static_cast<b8>(1)
#endif
#ifndef SE_B8_FALSE
#  define SE_B8_FALSE static_cast<b8>(0)
#endif
