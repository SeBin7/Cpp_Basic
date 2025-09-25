# Cpp_Basic (Compact)

Practice **C++ fundamentals ¡æ modern C++ (C++17/20)** with a tight scope:
**syntax, OOP/RAII, templates, STL, concurrency**. Minimal but practical.

---

## Folder Structure (00 ~ 05 only)
- `00_practice/` : Small practice snippets
- `01_basics/` : Syntax & types (auto, references, pointers, namespaces), I/O, control flow
- `02_oop/` : Classes, constructors/destructors, RAII, operator overloading
- `03_templates/` : Function/class templates, specialization, concepts (C++20)
- `04_stl/` : Containers, algorithms, iterators, ranges (C++20), string & filesystem
- `05_concurrency/` : Threads, mutex/lock_guard, futures/async, condition_variable

> Keep examples **small & runnable**. One executable per chapter is enough.

---

## Quick Start

### Toolchain (WSL/Ubuntu)
```bash
sudo apt update && sudo apt install -y build-essential cmake ninja-build clang
mkdir -p build && cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
```

### Toolchain (Windows / MSVC)
```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release -j
```

### Run (examples)
```bash
./practice_cpp          # 00_practice
./chapter_01_basics     # 01_basics
```

---

## CMake (Recommended)

### Root `CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.20)
project(Cpp_Basic LANGUAGES CXX)

# Use C++20 by default (adjust to 17 if needed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(00_practice)
add_subdirectory(01_basics)
add_subdirectory(02_oop)
add_subdirectory(03_templates)
add_subdirectory(04_stl)
add_subdirectory(05_concurrency)
```

### Per-chapter `CMakeLists.txt` (example: `01_basics/`)
```cmake
add_executable(chapter_01_basics
  src/main.cpp
  src/namespaces.cpp
  src/references.cpp
  include/namespaces.hpp
  include/references.hpp
)
target_include_directories(chapter_01_basics PRIVATE include)
```

---

## Coding Guidelines
- Comments **in English only** (consistent with your preference).
- Prefer RAII; avoid raw `new/delete`.
- Keep headers (`.hpp`) small; include what you use.
- Favor `const`, `auto`, `constexpr`, and range-based loops.
- Measure before optimizing; write tiny benchmarks when unsure.

---

## Minimal Docker (Optional)
Use a single service to build & run any chapter.
```yaml
# docker-compose.yml
services:
  cpp_dev:
    image: gcc:14
    working_dir: /work
    volumes:
      - ./:/work
    command: bash -lc "apt-get update && apt-get install -y cmake ninja-build clang &&                        mkdir -p build && cd build && cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release &&                        cmake --build . -j"
```
Run:
```bash
docker compose up
```

---

## Learning Roadmap (Laser-focused)
1. **Basics** ¡æ value vs reference, pointer vs reference, namespaces
2. **OOP/RAII** ¡æ rule of zero/five, ownership, smart pointers
3. **Templates** ¡æ function/class templates, type deduction, **concepts**
4. **STL** ¡æ containers + algorithms + iterators (+ ranges views)
5. **Concurrency** ¡æ thread basics, RAII locks, futures/async patterns

---

## Commit Convention (Short)
```
<type>(<scope>): <subject>
```
- `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`

Examples:
```
feat(basics): add references vs pointers demo
feat(templates): introduce requires-concepts example
refactor(stl): split vector helpers into header
```
