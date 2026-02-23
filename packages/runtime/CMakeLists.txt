cmake_minimum_required(VERSION 3.20)

add_executable(SturdyRuntime)

file(GLOB_RECURSE SE_RUNTIME_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx"
)

target_sources(SturdyRuntime PRIVATE ${SE_RUNTIME_SOURCES})

target_include_directories(SturdyRuntime
  PRIVATE
    "${SE_PUBLIC_INCLUDE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(SturdyRuntime
  PRIVATE
    SturdyEngine::core
)
