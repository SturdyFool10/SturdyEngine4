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

# ------------------------------------------------------------------------------
# Vulkan SDK / Linux Vulkan
# ------------------------------------------------------------------------------
if(DEFINED ENV{VULKAN_SDK})
  set(VULKAN_SDK "$ENV{VULKAN_SDK}")
endif()

if(VULKAN_SDK)
  list(PREPEND CMAKE_PREFIX_PATH "${VULKAN_SDK}")
endif()

find_package(Vulkan REQUIRED)

# ------------------------------------------------------------------------------
# GLFW
# ------------------------------------------------------------------------------
option(SE_FETCH_GLFW "Fetch GLFW if not found via find_package" ON)

find_package(glfw3 CONFIG QUIET)
if(NOT glfw3_FOUND)
  find_package(glfw3 QUIET)
endif()

if(NOT glfw3_FOUND AND SE_FETCH_GLFW)
  include(FetchContent)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
  )
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(glfw)
endif()

set(SE_GLFW_TARGET "")
if(TARGET glfw)
  set(SE_GLFW_TARGET glfw)
elseif(TARGET glfw3)
  set(SE_GLFW_TARGET glfw3)
elseif(TARGET glfw::glfw)
  set(SE_GLFW_TARGET glfw::glfw)
endif()

if(NOT SE_GLFW_TARGET)
  message(FATAL_ERROR "GLFW not found. Install glfw dev package or enable SE_FETCH_GLFW=ON.")
endif()

# ------------------------------------------------------------------------------
# GLM (prefer system package; fallback to Vulkan SDK)
# ------------------------------------------------------------------------------
find_package(glm CONFIG QUIET)
if(NOT glm_FOUND)
  find_package(glm QUIET)
endif()

set(SE_GLM_TARGET "")
if(TARGET glm::glm)
  set(SE_GLM_TARGET glm::glm)
else()
  if(VULKAN_SDK)
    if(EXISTS "${VULKAN_SDK}/Include/glm")
      set(_glm_inc "${VULKAN_SDK}/Include")
    elseif(EXISTS "${VULKAN_SDK}/include/glm")
      set(_glm_inc "${VULKAN_SDK}/include")
    endif()

    if(DEFINED _glm_inc)
      add_library(glm_header_only INTERFACE)
      target_include_directories(glm_header_only INTERFACE "${_glm_inc}")
      add_library(glm::glm ALIAS glm_header_only)
      set(SE_GLM_TARGET glm::glm)
    endif()
  endif()
endif()

if(NOT SE_GLM_TARGET)
  message(FATAL_ERROR "GLM not found. Install glm dev package or provide VULKAN_SDK with bundled GLM.")
endif()

# ------------------------------------------------------------------------------
# Slang (library) + slangc (compiler exe)
# ------------------------------------------------------------------------------
set(SLANG_ROOT "" CACHE PATH "Root of a Slang installation (containing lib/, bin/, include/)")
set(SLANGC_EXECUTABLE "" CACHE FILEPATH "Path to slangc executable")

if(SLANG_ROOT)
  list(PREPEND CMAKE_PREFIX_PATH "${SLANG_ROOT}")
endif()

find_package(slang CONFIG QUIET)

if(NOT SLANGC_EXECUTABLE)
  find_program(SLANGC_EXECUTABLE
    NAMES slangc
    HINTS
      "${SLANG_ROOT}/bin"
      "${VULKAN_SDK}/Bin"
      "${VULKAN_SDK}/bin"
  )
endif()

set(SE_SLANG_TARGET "")
if(TARGET slang::slang)
  set(SE_SLANG_TARGET slang::slang)
else()
  find_library(SLANG_LIBRARY
    NAMES slang slangd
    HINTS
      "${SLANG_ROOT}/lib" "${SLANG_ROOT}/lib64"
      "${VULKAN_SDK}/Lib" "${VULKAN_SDK}/lib" "${VULKAN_SDK}/lib64"
  )
  find_path(SLANG_INCLUDE_DIR
    NAMES slang.h slang/slang.h
    HINTS
      "${SLANG_ROOT}/include"
      "${VULKAN_SDK}/Include" "${VULKAN_SDK}/include"
  )

  if(SLANG_LIBRARY AND SLANG_INCLUDE_DIR)
    add_library(slang_manual UNKNOWN IMPORTED)
    set_target_properties(slang_manual PROPERTIES
      IMPORTED_LOCATION "${SLANG_LIBRARY}"
      INTERFACE_INCLUDE_DIRECTORIES "${SLANG_INCLUDE_DIR}"
    )
    add_library(slang::slang ALIAS slang_manual)
    set(SE_SLANG_TARGET slang::slang)
  endif()
endif()

if(NOT SE_SLANG_TARGET)
  message(WARNING "Slang library not found (slang::slang). If you need runtime linking to Slang, set SLANG_ROOT or install Slang.")
endif()

if(NOT SLANGC_EXECUTABLE)
  message(WARNING "slangc not found. Set -DSLANGC_EXECUTABLE=... or ensure slangc is on PATH.")
endif()

# ------------------------------------------------------------------------------
# One dependency target for subprojects
# ------------------------------------------------------------------------------
add_library(SturdyEngineDeps INTERFACE)
add_library(SturdyEngine::deps ALIAS SturdyEngineDeps)

target_link_libraries(SturdyEngineDeps INTERFACE
  Vulkan::Vulkan
  ${SE_GLFW_TARGET}
  ${SE_GLM_TARGET}
)

if(SE_SLANG_TARGET)
  target_link_libraries(SturdyEngineDeps INTERFACE ${SE_SLANG_TARGET})
endif()

set(SE_SLANGC_EXECUTABLE "${SLANGC_EXECUTABLE}" CACHE FILEPATH "Resolved slangc path")

# ------------------------------------------------------------------------------
# Project-wide include roots
# ------------------------------------------------------------------------------
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
