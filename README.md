# LLVM Peephole Optimization Pass 🛠️

A custom optimization pass for the LLVM compiler framework written in C++. This pass performs a simple peephole optimization to eliminate redundant arithmetic instructions, specifically targeting addition with zero.

This project is a practical demonstration of extending a modern compiler's functionality and showcases an understanding of LLVM's Intermediate Representation (IR) and pass management system.

---

## ## Features

-   **Redundant Code Elimination**: Identifies and removes `add` instructions where one of the operands is the constant integer zero.
-   **IR Transformation**: Directly transforms the LLVM IR by replacing all uses of the redundant instruction's result with the non-zero operand.
-   **Dynamic Plugin**: Built as a shared library (`.so`) that can be dynamically loaded by `clang` at compile-time to inject the optimization into the standard compilation pipeline.

---

## ## Prerequisites

Before you begin, ensure you have the following installed:

-   **LLVM & Clang** (Version 15 recommended for compatibility)
-   **CMake** (Version 3.10 or higher)
-   **A C++ Compiler** (like `g++` or `clang++`)

On a Debian/Ubuntu system, you can install these with:
```bash
sudo apt-get install -y llvm-15-dev libllvm15 llvm-15-tools clang-15 cmake build-essential
