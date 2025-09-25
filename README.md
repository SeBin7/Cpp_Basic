# Cpp_Basic

This repository is for practicing **C++ fundamentals → modern C++ (C++17/20)** with a focus on  
RAII, move semantics, templates, STL, concurrency, and performance tuning.  
It also ships with a **Docker-based development environment** for reproducibility.

---

## Folder Structure 
- `00_practice/` : Small practice snippets
- `01_basics/` : Syntax & types (auto, references, pointers, namespaces), I/O, control flow
- `02_oop/` : Classes, constructors/destructors, RAII, operator overloading
- `03_templates/` : Function/class templates, specialization, concepts (C++20)
- `04_stl/` : Containers, algorithms, iterators, ranges (C++20), string & filesystem
- `05_concurrency/` : Threads, mutex/lock_guard, futures/async, condition_variable

---

## Commit Convention
We follow [Conventional Commits](https://www.conventionalcommits.org/) style:

**Pattern**
```
<type>(<scope>): <subject>
```

### Types
- `feat` – new feature
- `fix` – bug fix
- `docs` – documentation only
- `style` – formatting, code style only (no logic change)
- `refactor` – neither feature nor bug fix
- `test` – add or modify tests
- `chore` – build/config/deps, CI, tooling

### Examples
- `feat(stl): add vector vs deque microbench`
- `feat(oop): implement rule-of-five example`
- `refactor(templates): split constraints into concepts.h`
- `test: add Catch2 cases for string utils`
- `docs: update README with sanitizer guide`

---

## Development Workflow
1. Implement small, focused examples per chapter.
2. Use **CMake** to organize and build executables/libraries.
3. Keep build artifacts in `/build/` or `/out/` (git-ignored).
4. Commit with clear types & scopes.
5. Push, review on GitHub/CI.

---

## Build Instructions (WSL/Ubuntu)
```bash
# Toolchain
sudo apt update && sudo apt install -y build-essential cmake ninja-build clang

# Configure & build (Release by default)
mkdir -p build && cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build . -j
```

### Run executables
```bash
./practice_cpp          # from 00_practice
./chapter_01_basics     # from 01_basics
```

> You can provide one executable per chapter via `add_executable(...)` in each subdir CMakeLists.

---

## Build Instructions (Windows / MSVC)
```powershell
# In "x64 Native Tools Command Prompt for VS"
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release -j
```

---

## Suggested CMake Layout (root `CMakeLists.txt`)
```cmake
cmake_minimum_required(VERSION 3.20)
project(Cpp_Basic LANGUAGES CXX)

# Require C++20 (adjust if you prefer C++17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to Release if not set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Warnings & sanitizers (GCC/Clang)
if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
  # Enable with: -DUSE_ASAN=ON at configure time
  option(USE_ASAN "Enable AddressSanitizer" OFF)
  if(USE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
  endif()
endif()

# Chapters
add_subdirectory(00_practice)
add_subdirectory(01_basics)
# add_subdirectory(02_oop) ...
```

### Example per-chapter `CMakeLists.txt` (e.g., `01_basics/CMakeLists.txt`)
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

## Tooling & Quality
- **clang-tidy**: static analysis & modernization checks  
  ```bash
  cmake -S . -B build -G Ninja -DCMAKE_CXX_CLANG_TIDY="clang-tidy;-warnings-as-errors=*"
  cmake --build build
  ```
- **clang-format**: consistent style (add a `.clang-format` with your preset)
- **Sanitizers (GCC/Clang)**: `-DUSE_ASAN=ON` for AddressSanitizer; consider UBSan/TSan per chapter.
- **Profiling**: `-pg` (gprof) or `perf` on Linux; Windows can use VS Profiler.

---

## Docker Development Environment
A reproducible dev environment is provided with **docker-compose.yml**.

### Run 00_practice
```bash
docker compose up run_practice_cpp
```

### Run 01_basics
```bash
docker compose up run_basics_cpp
```

### Stop containers
```bash
docker compose down
```

### Exit container
```bash
exit
```

> Tip: Prefer `docker compose stop/start` to preserve container state instead of `down` if you want to keep caches.

---

## Testing (optional but recommended)
Choose one:
- **Catch2** (header-only, easy to start)
- **GoogleTest** (feature-rich, widely used)

Example with Catch2 (download via CPM.cmake/vcpkg/conan or vendor it):
```cmake
# tests/CMakeLists.txt
add_executable(unit_tests tests/main.cpp tests/string_utils_tests.cpp)
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)
add_test(NAME all_tests COMMAND unit_tests)
```

Run:
```bash
ctest --output-on-failure
```

---

## Suggested Learning Roadmap
1. **Value vs Reference semantics** → copy elision, move semantics
2. **RAII & Smart pointers** → `unique_ptr`, `shared_ptr`, `weak_ptr`
3. **Templates & Concepts** → constraints, deduction guides, CTAD
4. **STL Mastery** → algorithms + iterators + views/ranges
5. **Concurrency** → data races, lock patterns, atomics, async
6. **Error handling** → exceptions vs `expected`-like; noexcept & strong guarantees
7. **Performance** → ABI, cache-friendly data structures, small-buffer optimization

---

## Coding Guidelines
- Comments **in English only** (consistent with your preference).
- Prefer **.hpp/.cpp** split with small, focused headers (include what you use).
- Avoid raw `new/delete`; prefer RAII and standard facilities.
- Keep functions small; measure before optimizing.
