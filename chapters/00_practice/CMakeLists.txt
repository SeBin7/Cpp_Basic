add_executable(practice
  src/main.cpp
  src/SimpleAdder.cpp
  src/HelloWorld.cpp
 src/FunctionOverlading.cpp 
 src/DefaultValue1.cpp "src/NameSp1.cpp" "src/RefArrElem.cpp" "src/RefSwap.cpp" "src/MemMalFree.cpp" "src/Car.cpp" "src/PointerThis.cpp" "src/ShallowCopyError.cpp" "src/MyFriendClass.cpp" "src/HASInheritance.cpp" "src/PostOpndOverloading.cpp" "src/FirstOperationOverloading.cpp" "src/ArrayClass.cpp" "src/StablePointObjArray.cpp" "src/SmartPointer.cpp" "src/AddFunctionTemplate.cpp")

target_include_directories(practice PRIVATE include)

