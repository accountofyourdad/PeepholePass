cmake_minimum_required(VERSION 3.10)
project(Peephole)

# Find the LLVM package
find_package(LLVM 15 REQUIRED CONFIG)

# Set common flags
set(CMAKE_CXX_STANDARD 17)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

# Define our pass as a shared library
add_library(Peephole MODULE
  Peephole.cpp
)

# Link against the necessary LLVM components
link_libraries(${LLVM_LIBRARIES})