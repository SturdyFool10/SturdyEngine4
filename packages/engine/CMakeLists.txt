cmake_minimum_required(VERSION 3.20)

add_library(SturdyEngineCore SHARED)
add_library(SturdyEngine::core ALIAS SturdyEngineCore)

file(GLOB_RECURSE SE_ENGINE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx"
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
