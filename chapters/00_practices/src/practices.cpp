
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
    std::cout << "ù ��° �����Է�: ";
    std::cin >> val1;

    int val2;
    std::cout << "�� ��° �����Է�: ";
    std::cin >> val2;

    int result = val1 + val2;
    std::cout << "�������: " << result << std::endl;

}