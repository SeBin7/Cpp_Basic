#include <iostream>
#include <limits>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

namespace basics {

template <class T>
inline void use(const T&) {}

void run_variables_examples() {
    cout << "=== variables.cpp demos ===\n\n";

    // 1) Initialization styles: =, (), {}
    int a1 = 10;        // copy init
    int a2(20);         // direct init
    int a3{30};         // list init (narrowing-safe)
    cout << "a1=" << a1 << " a2=" << a2 << " a3=" << a3 << "\n";

    // Narrowing example
    double pi = 3.14159;
    int ok = static_cast<int>(pi); // explicit cast
    cout << "pi=" << pi << " static_cast<int>(pi)=" << ok << "\n\n";

    // 2) Signed/Unsigned & fixed-width integers
    int32_t  i32 = 42;
    uint32_t u32 = 100u;
    cout << "i32=" << i32 << " u32=" << u32
         << " (sizeof i32=" << sizeof(i32)
         << ", sizeof u32=" << sizeof(u32) << ")\n\n";

    // 3) const vs constexpr
    const int cx = a1 + a2;   // runtime-const
    constexpr int cexp = 64;  // compile-time const
    (void)cx; (void)cexp;

    int fixed_arr[cexp]{};    // zero-initialized
    use(fixed_arr);

    // 4) auto type deduction
    auto v1 = 1;      // int
    auto v2 = 1.0;    // double
    auto v3 = 1.0f;   // float
    auto v4 = 'A';    // char
    auto v5 = 1u;     // unsigned int
    cout << "auto samples: " << v1 << ", " << v2 << ", " << v3
         << ", " << v4 << ", " << v5 << "\n\n";

    // 5) Scope & lifetime (shadowing)
    int value = 10;
    cout << "outer value=" << value << "\n";
    {
        int value = 99; // shadows outer
        cout << "inner value=" << value << " (shadows outer)\n";
    }
    cout << "outer value still=" << value << "\n\n";

    // 6) Static local variable
    auto static_counter = []() -> int& {
        static int counter = 0;  // persists across calls
        return counter;
    };
    static_counter()++;
    static_counter()++;
    cout << "static local counter=" << static_counter() << "\n\n";

    // 7) Strings and literals
    const char* cstr = "hello";
    string s = string(cstr) + " world";
    cout << "cstr=\"" << cstr << "\" s=\"" << s << "\"\n\n";

    // 8) Numeric limits
    cout << "int: min=" << numeric_limits<int>::min()
         << " max=" << numeric_limits<int>::max() << "\n";
    cout << "double: min=" << numeric_limits<double>::min()
         << " max=" << numeric_limits<double>::max()
         << " epsilon=" << numeric_limits<double>::epsilon() << "\n\n";

    // 9) Vectors: list init / fill / zero init
    vector<int> vec1{1,2,3};
    vector<int> vec2(5, 7);
    vector<int> vec3(4);
    cout << "vec1 size=" << vec1.size()
         << " vec2 size=" << vec2.size()
         << " vec3 size=" << vec3.size() << "\n";

    cout << "=== end of variables.cpp demos ===\n";
}

} // namespace basics