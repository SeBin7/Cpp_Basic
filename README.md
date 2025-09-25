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
