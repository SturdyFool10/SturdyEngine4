cmake_minimum_required(VERSION 3.20)

# If this is your top-level CMakeLists.txt, keep this here.
# If it's a subdir, you can also set this in the root.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(SturdyEngineCore SHARED)
add_library(SturdyEngine::core ALIAS SturdyEngineCore)

# Ensure the target is compiled as C++23
target_compile_features(SturdyEngineCore PUBLIC cxx_std_23)

# ---- Sources (include module interface/impl units too) ----
file(GLOB_RECURSE SE_ENGINE_SOURCES CONFIGURE_DEPENDS
  # C/C++
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cp"

  # Headers
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h++"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hp"

  # C++ modules
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxxm"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ccm"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++m"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ixx"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.mpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.mpl"

  # Inline/template impls
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ipp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.tpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)

target_sources(SturdyEngineCore PRIVATE ${SE_ENGINE_SOURCES})

target_include_directories(SturdyEngineCore
  PUBLIC
    "${SE_PUBLIC_INCLUDE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(SturdyEngineCore
  PUBLIC
    SturdyEngine::deps
)

set_target_properties(SturdyEngineCore PROPERTIES
  OUTPUT_NAME "sturdy_engine_core"
)

if(WIN32)
  set_target_properties(SturdyEngineCore PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# ---- Optional: CMake modules support ----
# This doesn't magically make modules "work" on all toolchains, but helps when supported.
if(POLICY CMP0169)
  cmake_policy(SET CMP0169 NEW)
endif()

# If you want to force clang/clang++ for better module tooling, do it at top-level, not here.
