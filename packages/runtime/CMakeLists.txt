# Runtime package

add_executable(runtime
  src/main.cpp
  # Add other runtime source files here...
)

target_compile_features(runtime PRIVATE cxx_std_23)

target_include_directories(runtime PRIVATE
  "${SE_PUBLIC_INCLUDE_DIR}"
  "${CMAKE_SOURCE_DIR}/packages/engine/src"
)

target_link_libraries(runtime PRIVATE
  engine
  Vulkan::Vulkan
)
