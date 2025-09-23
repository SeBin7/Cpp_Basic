
#include <iostream>

#include "practices.hpp"



// Simple demonstration for Cpp_Basic chapter 01

void helloworld() {

    int num = 20;
    std::cout << "Hello World!" << std::endl;
    std::cout << "Hello" << "World" << std::endl;
    std::cout << num << ' ' << "A";
    std::cout << ' ' << 3.14 << std::endl;


    // Add small demos here: auto, range-based for, etc.

}

void simple_adder() {
    int val1;
    std::cout << "첫 번째 숫자입력: ";
    std::cin >> val1;

    int val2;
    std::cout << "두 번째 숫자입력: ";
    std::cin >> val2;

    int result = val1 + val2;
    std::cout << "덧셈결과: " << result << std::endl;

}