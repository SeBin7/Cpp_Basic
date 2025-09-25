
add_executable(basics

  src/main.cpp

  src/variables.cpp

  src/operators.cpp

  src/strings.cpp

  src/arrays.cpp

  src/functions.cpp

  src/pointers_memory.cpp

  src/structs_enums.cpp

)

target_include_directories(basics PRIVATE include)

