# How to make SturdyEngine Compile
  your comprehensive guide to getting this working

---
- ## Install the Vulkan SDK
this should also create an enviornment variable: `VULKAN_SDK`, the engine's build scripts use this to locate the SDK

**[IMPORTANT]**: Make sure you selected to install the GLM headers and the Vulkan allocator during install

- ## Install CLANG
we use CLANG because it is the most cross-platform compatible and consistently awesome compiler, ensure it is on your
`PATH` enviornment variable, if you are in your terminal you should be able to invoke it with `clang` and `clang++`

- ## Install CMAKE
you will need CMake 4.2 or above and it needs to be on your `PATH` enviornment variable, this means that you should be able to invoke it using `cmake` in your terminal

- ## On Windows Install Ninja
we use Ninja on windows under CMake

- ## On Linux Install Make
CMake uses make under the hood on Linux

- ## Install other Deps
you will need to install GLFW by copying its include directory into `/include/GLFW` relative to the project root, and copying either the static library(*.so, or *.lib depending on platform) into `./libs` relative to the project root, these objects are part of our gitignore so we get more accurate stats on the composition of the engine, and it makes the repo quicker to clone
