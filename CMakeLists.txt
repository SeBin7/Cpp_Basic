cmake_minimum_required(VERSION 3.22)

project(Cpp_Basic LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror=return-type)

endif()



# Build chapter-wise like C_Basic

add_subdirectory(chapters/00_practice)

add_subdirectory(chapters/01_basics)

