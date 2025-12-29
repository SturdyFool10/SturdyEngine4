# Engine package
# Builds all .cpp/.c/.cc/.cxx under packages/engine/src

file(GLOB_RECURSE SE_ENGINE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

add_library(engine STATIC ${SE_ENGINE_SOURCES})

target_compile_features(engine PUBLIC cxx_std_23)

target_include_directories(engine PUBLIC
  "${SE_PUBLIC_INCLUDE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
