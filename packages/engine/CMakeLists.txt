# Engine package
# Builds all .cpp/.c/.cc/.cxx under packages/engine/src

file(GLOB_RECURSE SE_ENGINE_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hh"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h++"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxxm"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ccm"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c++m"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ixx"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.mpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.mpl"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ipp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.tpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)

add_library(engine STATIC ${SE_ENGINE_SOURCES})

target_compile_features(engine PUBLIC cxx_std_23)

target_include_directories(engine PUBLIC
  "${SE_PUBLIC_INCLUDE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
