#include "oop.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

namespace oop {

    
// 1) Member initializer list and delegating ctors
class Buffer {
    vector<int> data_;
public:
    // Primary ctor: fully initializes members
    explicit Buffer(size_t n) : data_(n, 0) {
        cout << "Buffer(" << n << ") ctor\n";
    }
    // Delegating ctor: reuses primary ctor
    Buffer() : Buffer(8) {}

    // Dtor: vectors clean up themselves (RAII)
    ~Buffer() {
        cout << "~Buffer (size=" << data_.size() << ")\n";
    }

    size_t size() const noexcept { return data_.size(); }
    int& at(size_t i) { return data_.at(i); }
    const int& at(size_t i) const { return data_.at(i); }
};

// 2) Initialization order demo: members are initialized in declaration order
//    NOT in the order written in the initializer list.
class InitOrder {
    int a_{1};
    int b_{2};
public:
    InitOrder(int x)
        : b_(a_),  // b_ gets value of a_ (which is still 1 at this point)
          a_(x)    // a_ is assigned x AFTER b_ initialization
    {
        std::cout << "InitOrder: a_=" << a_ << " b_=" << b_ << "\n";
    }
};

// 3) Exception during construction: already-built subobjects are destroyed
class Throwy {
    string name_;
public:
    explicit Throwy(string name, bool should_throw) : name_(move(name)) {
        cout << "Throwy(" << name_ << ") ctor\n";
        if (should_throw) {
            cout << "Throwy throws!\n";
            throw runtime_error("ctor failed");
        }
    }
    ~Throwy() {
        cout << "~Throwy(" << name_ << ")\n";
    }
};


class Owner {
    Buffer buf_;
    Throwy a_;
    Throwy b_;
public:
    // If a_ throws, buf_ is destroyed; b_ is never constructed
    Owner()
        : buf_(4), a_("A", /*should_throw*/true), b_("B", false) {
        std::cout << "Owner body\n"; // never reached if a_ throws
    }
    ~Owner() {
        std::cout << "~Owner\n";
    }
};

void run_ctors_dtors() {
    std::cout << "\n[ctors_dtors]\n";

    // 1) Delegating constructors
    Buffer a(4);
    Buffer b; // delegates to Buffer(8)
    std::cout << "a.size=" << a.size() << " b.size=" << b.size() << "\n";

    // 2) Initialization order
    InitOrder io(42); // prints: a_=42 b_=1

    // 3) Exception safety: partial construction unwinds subobjects
    try {
        Owner o; // Throwy("A", true) will throw; buf_ will be destroyed
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
}

}