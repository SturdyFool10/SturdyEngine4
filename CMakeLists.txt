cmake_minimum_required(VERSION 3.20)

project(SturdyEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put all compiled output in <repo>/build
set(SE_BUILD_ROOT "${CMAKE_SOURCE_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${SE_BUILD_ROOT}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${SE_BUILD_ROOT}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${SE_BUILD_ROOT}/lib")

# Vulkan SDK (expected to be set in the environment)
if(DEFINED ENV{VULKAN_SDK})
  set(VULKAN_SDK "$ENV{VULKAN_SDK}")
endif()

# Prefer a proper Vulkan package config when available; otherwise fall back to env var hints.
find_package(Vulkan QUIET)

if(NOT Vulkan_FOUND)
  if(DEFINED VULKAN_SDK)
    set(Vulkan_INCLUDE_DIR "${VULKAN_SDK}/Include")
    set(Vulkan_LIBRARY "${VULKAN_SDK}/Lib/vulkan-1.lib")
  endif()
  find_package(Vulkan REQUIRED)
endif()

# Project-wide include roots
set(SE_PUBLIC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(packages/engine)
add_subdirectory(packages/runtime)

# Convenience: copy compile_commands.json into <repo>/build/compile_commands.json when generated
if(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
  file(COPY_FILE
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${SE_BUILD_ROOT}/compile_commands.json"
    ONLY_IF_DIFFERENT
  )
endif()
