#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <type_traits>
#include <iomanip>

using namespace std;

namespace basics {

// ------------------------------------------------------------------
//  Helpers for printing
// ------------------------------------------------------------------
struct Point {
    int x{0}, y{0};                 // default member initializers

    Point() = default;              // generate default ctor
    Point(int x_, int y_) : x(x_), y(y_) {}  // member init-list

    int manhattan() const { return (x >= 0 ? x : -x) + (y >= 0 ? y : -y); }

    // friend output
    friend ostream& operator<<(ostream& os, const Point& p) {
        return os << '(' << p.x << ", " << p.y << ')';
    }

    // equality to compare two Points
    friend bool operator==(const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }
};

// A small aggregate (no custom ctor): aggregate initialization demo
struct Person {
    string name;
    int age;
    // no user-provided constructors → aggregate type
};

// ------------------------------------------------------------------
//  Enums: unscoped vs scoped(enum class), underlying types
// ------------------------------------------------------------------
enum Direction { North, East, South, West };              // unscoped (injects names)
enum class Axis : uint8_t { X = 1, Y = 2, Z = 4 };        // scoped, fixed width

// ------------------------------------------------------------------
//  Enum class bitmask pattern (for flags)
// ------------------------------------------------------------------
enum class Perm : uint8_t { None=0, Read=1<<0, Write=1<<1, Exec=1<<2 };

// Enable bitwise ops for Perm
constexpr Perm operator|(Perm a, Perm b) {
    using U = underlying_type_t<Perm>;
    return static_cast<Perm>(static_cast<U>(a) | static_cast<U>(b));
}
constexpr Perm operator&(Perm a, Perm b) {
    using U = underlying_type_t<Perm>;
    return static_cast<Perm>(static_cast<U>(a) & static_cast<U>(b));
}
constexpr Perm operator^(Perm a, Perm b) {
    using U = underlying_type_t<Perm>;
    return static_cast<Perm>(static_cast<U>(a) ^ static_cast<U>(b));
}
constexpr Perm operator~(Perm a) {
    using U = underlying_type_t<Perm>;
    return static_cast<Perm>(~static_cast<U>(a));
}
inline Perm& operator|=(Perm& a, Perm b) { return a = (a | b); }
inline Perm& operator&=(Perm& a, Perm b) { return a = (a & b); }
inline Perm& operator^=(Perm& a, Perm b) { return a = (a ^ b); }

// Pretty print for Perm
static string perm_to_string(Perm p) {
    string s;
    if ((p & Perm::Read)  != Perm::None)  s += 'R';
    if ((p & Perm::Write) != Perm::None)  s += 'W';
    if ((p & Perm::Exec)  != Perm::None)  s += 'X';
    if (s.empty()) s = "-";
    return s;
}

// ------------------------------------------------------------------
//  Demo entry
// ------------------------------------------------------------------
void run_structs_enums_examples() {
    cout << "=== structs_enums.cpp demos ===\n\n";

    // 1) Struct basics: initialization, member functions, operators
    {
        Point a;                 // (0,0)
        Point b{3, -2};         // aggregate-style init uses user ctor here
        cout << "Point a=" << a << " manhattan=" << a.manhattan() << "\n";
        cout << "Point b=" << b << " manhattan=" << b.manhattan() << "\n";
        cout << "a == b ? " << boolalpha << (a == b) << "\n\n";
    }

    // 2) Aggregate type: no custom ctor → simple brace init in field order
    {
        Person p1{"Alice", 24};
        Person p2{"Bob",   31};
        cout << "Person: " << p1.name << " (" << p1.age << ")\n";
        cout << "Person: " << p2.name << " (" << p2.age << ")\n\n";
        // Note: designated initializers are C++20, but compilers vary; brace order is most portable.
    }

    // 3) Enums: unscoped vs enum class
    {
        Direction d = North;          // unscoped: names in the enclosing scope
        cout << "Direction North as int = " << static_cast<int>(d) << "\n";

        Axis ax = Axis::Y;            // scoped: must qualify with Axis::
        using U = underlying_type_t<Axis>;
        cout << "Axis::Y underlying=" << static_cast<int>(static_cast<U>(ax)) << "\n\n";
    }

    // 4) Enum class as bitmask (flags)
    {
        Perm user = Perm::None;
        user |= Perm::Read;
        user |= Perm::Write;
        cout << "user perms: " << perm_to_string(user) << "\n";

        // clear Write, toggle Exec
        user &= ~Perm::Write;
        user ^= Perm::Exec;
        cout << "after ops: " << perm_to_string(user) << "\n";

        // test a flag
        bool can_exec = (user & Perm::Exec) != Perm::None;
        cout << "can_exec? " << boolalpha << can_exec << "\n\n";
    }

    // 5) Struct copying and assignment (Rule of Zero)
    {
        Point p1{1,2};
        Point p2 = p1;           // copy (memberwise OK here)
        p2.x = 9;
        cout << "p1=" << p1 << " p2=" << p2 << " (independent copies)\n\n";
    }

    cout << "=== end of structs_enums.cpp demos ===\n";
}

} // namespace basics
