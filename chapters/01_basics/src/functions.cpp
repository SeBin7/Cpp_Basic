#include <iostream>
#include <string>
#include <vector>
#include <span>
#include <utility>     // std::move
#include <type_traits> // std::decay_t

using namespace std;

namespace basics {

// Small helper to silence -Wunused-* warnings
template <class T>
inline void use(const T&) {}

// -------------------------------
// 1) Passing styles
// -------------------------------
static void pass_by_value(int x) { // copies the value
    cout << "[value] before: x=" << x << " -> ";
    x += 10;                       // modifies the local copy only
    cout << "after: x=" << x << "\n";
}

static void pass_by_ref(int& x) {  // alias to the original
    cout << "[ref]   before: x=" << x << " -> ";
    x += 10;                       // modifies caller's variable
    cout << "after: x=" << x << "\n";
}

static void pass_by_const_ref(const string& s) {
    // read-only, no copy when argument is lvalue; can bind to temporaries
    cout << "[const&] s=\"" << s << "\" (length=" << s.size() << ")\n";
}

static void pass_by_ptr(int* p) {
    if (!p) { cout << "[ptr] null pointer\n"; return; }
    cout << "[ptr]   before: *p=" << *p << " -> ";
    *p += 5;
    cout << "after: *p=" << *p << "\n";
}

// -------------------------------
// 2) Default arguments
// -------------------------------
static string join(string a, string b = "world", char sep = ' ') {
    // pass by value: cheap small-string optimization; enables move from args
    string out = a;
    out += sep;
    out += b;
    return out;
}

// -------------------------------
// 3) Overloading (by parameter types)
// -------------------------------
static int    area(int w, int h)       { return w * h; }
static double area(double w, double h) { return w * h; }

// -------------------------------
// 4) Function template (generic add)
// -------------------------------
template <class A, class B>
auto add(A a, B b) -> decltype(a + b) { // return type deduced from operator+
    return a + b;
}

// -------------------------------
// 5) Sum over a contiguous range (span)
// -------------------------------
static long long sum(span<const int> xs) {
    long long s = 0;
    for (int v : xs) s += v;
    return s;
}

// -------------------------------
// 6) Move semantics demo
// -------------------------------
static string consume_and_tag(string s) { // takes by value; can move in
    s += " [consumed]";
    return s; // NRVO/move
}

void run_functions_examples() {
    cout << "=== functions.cpp demos ===\n\n";

    // 1) Passing styles
    int v = 5;
    pass_by_value(v);     // does not change v
    cout << "caller v=" << v << "\n";
    pass_by_ref(v);       // modifies v
    cout << "caller v=" << v << "\n";
    pass_by_ptr(&v);      // modifies v via pointer
    cout << "caller v=" << v << "\n";
    pass_by_ptr(nullptr); // null-safe

    cout << "\n";

    // const reference (binds to lvalue and temporary)
    string name = "Sebin";
    pass_by_const_ref(name);             // lvalue
    pass_by_const_ref(string("Temp"));   // temporary

    cout << "\n";

    // 2) Default arguments
    cout << "join(\"hello\") -> \"" << join("hello") << "\"\n";
    cout << "join(\"hello\",\"cpp\",\"-\") -> \"" << join("hello", "cpp", '-') << "\"\n";

    cout << "\n";

    // 3) Overloading
    cout << "area(3,4)        -> " << area(3, 4) << " (int)\n";
    cout << "area(3.5, 4.2)   -> " << area(3.5, 4.2) << " (double)\n";

    cout << "\n";

    // 4) Function template
    cout << "add(10, 2.5)     -> " << add(10, 2.5) << "\n";
    cout << "add(string,\"!\")-> " << add(string("Hi"), string("!")) << "\n";

    cout << "\n";

    // 5) span-based sum
    int arr[5] = {1,2,3,4,5};
    vector<int> vec{10,20,30};
    cout << "sum(arr)         -> " << sum(span<const int>(arr, 5)) << "\n";
    cout << "sum(vec)         -> " << sum(span<const int>(vec)) << "\n";

    cout << "\n";

    // 6) Move semantics
    string big = "LargeText";
    string out1 = consume_and_tag(big);            // copies (big is kept)
    string out2 = consume_and_tag(std::move(big)); // moves (big may become empty)
    cout << "out1=\"" << out1 << "\"\n";
    cout << "out2=\"" << out2 << "\"\n";
    cout << "big(after move) size=" << big.size() << "\n";

    cout << "\n=== end of functions.cpp demos ===\n";
}

} // namespace basics
