
cmake_minimum_required(VERSION 3.22)

project(Cpp_Basic LANGUAGES CXX)



set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)



# Strong warnings

if (MSVC)

  add_compile_options(/W4 /permissive-)

else()

  add_compile_options(-Wall -Wextra -Wpedantic -Werror=return-type)

endif()



# Chapter 01 example target

add_executable(ch01_basics

  "chapters/00_practices/src/practices.cpp"
  "chapters/01_basics/src/basics.cpp"
  src/main.cpp

 )


target_include_directories(ch01_basics PRIVATE chapters/00_practices/include)
target_include_directories(ch01_basics PRIVATE chapters/01_basics/include)


# Tips:

# - Duplicate add_executable for ch02_memory, ch03_oop, ... with their files

