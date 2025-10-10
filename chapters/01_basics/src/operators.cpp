#include <iostream>
#include <bitset>
#include <iomanip>
#include <cstdint>
#include <cmath>

using namespace std;

namespace basics {

// Print 8-bit pattern helper
static void print_bits8(uint8_t x, const char* label) {
    cout << label;
    if (label[0] != '\0') cout << ' ';
    cout << bitset<8>(x) << " (" << static_cast<int>(x) << ")\n";
}

void run_operators_examples() {
    cout << "=== operators.cpp demos ===\n\n";

    // ------------------------------------------------------------
    // 1) Arithmetic operators
    // ------------------------------------------------------------
    int a = 7, b = 3;
    cout << "a+b=" << a + b
         << " a-b=" << a - b
         << " a*b=" << a * b << "\n";
    cout << "a/b (int)=" << a / b
         << " a% b=" << a % b << "\n";
    cout << "a/(double)b=" << a / static_cast<double>(b) << "\n\n";

    // ------------------------------------------------------------
    // 2) Pre/post increment
    // ------------------------------------------------------------
    int i = 0;
    cout << "i=" << i
         << " ++i=" << ++i
         << " i++ returns " << i++
         << " now i=" << i << "\n\n";

    // ------------------------------------------------------------
    // 3) Assignment chaining
    // ------------------------------------------------------------
    int x, y, z;
    x = y = z = 5;
    cout << "x=" << x << " y=" << y << " z=" << z << "\n\n";

    // ------------------------------------------------------------
    // 4) Comparisons, short-circuit
    // ------------------------------------------------------------
    cout << boolalpha;
    cout << "(3<5)=" << (3 < 5)
         << " (3==3)=" << (3 == 3)
         << " (3!=4)=" << (3 != 4) << "\n";
    auto risky = []() {
        cout << "[risky called]\n";
        return true;
    };
    bool sc1 = (false && risky()); // not called
    bool sc2 = (true  || risky()); // not called
    cout << "short-circuit: sc1=" << sc1 << " sc2=" << sc2 << "\n\n";

    // ------------------------------------------------------------
    // 5) Bitwise operators
    // ------------------------------------------------------------
    uint8_t m = 0b0000'1100; // 12
    uint8_t n = 0b0011'0010; // 50
    print_bits8(m, "m");
    print_bits8(n, "n");
    print_bits8(static_cast<uint8_t>(m & n), "m & n");
    print_bits8(static_cast<uint8_t>(m | n), "m | n");
    print_bits8(static_cast<uint8_t>(m ^ n), "m ^ n");
    print_bits8(static_cast<uint8_t>(~m),    "~m");
    print_bits8(static_cast<uint8_t>(n << 1),"n << 1");
    print_bits8(static_cast<uint8_t>(n >> 2),"n >> 2");
    cout << "\n";

    // Bit mask example
    uint8_t flags = 0;
    constexpr uint8_t READ  = 1u << 0;
    constexpr uint8_t WRITE = 1u << 1;
    constexpr uint8_t EXEC  = 1u << 2;

    flags |= static_cast<uint8_t>(READ | WRITE); // set
    bool can_read = (flags & READ) != 0;
    bool can_exec = (flags & EXEC) != 0;
    cout << "flags set: "; print_bits8(flags, "");
    cout << "can_read=" << can_read << " can_exec=" << can_exec << "\n";

    flags &= static_cast<uint8_t>(~WRITE);       // clear WRITE
    cout << "after clear WRITE: "; print_bits8(flags, "");
    cout << "\n";

    // ------------------------------------------------------------
    // 6) Precedence pitfalls
    // ------------------------------------------------------------
    int p = 1, q = 2;
    int wrong = p + q << 1;      // '+' before '<<' -> (p+q)<<1 (looks fine but be explicit)
    int want  = (p + q) << 1;    // explicit grouping
    cout << "precedence: wrong=" << wrong << " want=" << want << "\n";

    bool L = true, R = false;
    cout << "L || R=" << (L || R)
         << " L | R="  << (L | R)  // '|' is bitwise on bool
         << " (|| is logical)\n\n";

    // ------------------------------------------------------------
    // 7) Floating-point comparison
    // ------------------------------------------------------------
    double f = 0.1 + 0.2;        // ≈ 0.30000000000000004
    double eps = 1e-12;
    cout << setprecision(17);
    cout << "f=" << f
         << " close_to_0_3=" << (fabs(f - 0.3) < eps) << "\n";

    cout << "\n=== end of operators.cpp demos ===\n";
}

} // namespace basics