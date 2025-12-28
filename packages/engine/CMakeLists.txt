# Engine package (currently header-only scaffolding).
# If/when you add .cpp files, switch this to STATIC/SHARED and list sources.

add_library(engine INTERFACE)

target_compile_features(engine INTERFACE cxx_std_23)

target_include_directories(engine INTERFACE
  "${SE_PUBLIC_INCLUDE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
