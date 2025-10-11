#include "oop.hpp"
#include <iostream>
#include <string>
#include <utility>
using namespace std;

namespace oop {

// 1) Simple POD-like type (all public) — convenient but no invariants
struct Point {
    int x{0};
    int y{0};
    void translate(int dx, int dy) { x += dx; y += dy; }
};

// 2) Encapsulated class (private state + public API)
//    - Default member initializers
//    - Delegating constructor
//    - const-correct methods
//    - this-pointer usage
//    - static member to track live instances
class Person {
private:
    string name_{"unknown"};
    int age_{0};

    // C++17 inline static: one definition across TUs, no separate .cpp needed
    inline static int s_live_count_{0};

public:
    // Primary constructor
    Person(string name, int age) : name_(move(name)), age_(age) {
        ++s_live_count_;
    }

    // Delegating constructor
    Person() : Person("unknown", 0) {}

    // Destructor
    ~Person() { --s_live_count_; }

    // Getters (const)
    const string& name() const noexcept { return name_; }
    int age() const noexcept { return age_; }

    //Mutators
    void rename(string new_name) { this-> name_ = move(new_name); }

    //Simple validation example
    bool set_age(int a) {
        if (a < 0 || a > 150) return false;
        age_ = a;
        return true;
    }

    //Behavior
    void birthday() { ++ age_; }

    void greet() const {
        cout << "Hi, I'm " << name_ << " (" << age_ << ")\n";
    }

    //Static utility (no object required)
    static int live_count() noexcept { return s_live_count_; }
};

void run_class_basics() {
    cout << "\n[class_basics]\n";

    // --- Struct vs Class quick contrast ---
    Point p{1, 2};           // aggregate init
    p.translate(3, -1);
    cout << "Point: (" << p.x << "," << p.y << ")\n";

    // --- Encapsulated class usage ---
    cout << "Live persons: " << Person::live_count() << "\n";
    Person alice{"Alice", 30};
    alice.greet();
    cout << "Live persons: " << Person::live_count() << "\n";

    // const-correct getter
    const Person& cref = alice;
    cout << "const view -> name=" << cref.name() << ", age=" << cref.age() << "\n";

    // mutation through non-const instance
    alice.birthday();
    alice.rename("Alice Kim");
    cout << "after birthday+rename -> ";
    alice.greet();

    // validation example
    Person bob; // uses delegating ctor
    if (!bob.set_age(200)) {
        cout << "Reject invalid age; keeping " << bob.age() << "\n";
        bob.set_age(28);
    }
    bob.rename("Bob");
    bob.greet();

    cout << "Live persons: " << Person::live_count() << "\n";

    // temporary scope to show destructor/live_count behavior
    {
        Person temp{"Temp", 1};
        cout << "Inside block live persons: " << Person::live_count() << "\n";
    }
    cout << "After block live persons: " << Person::live_count() << "\n";
}

} // namespace rv::oop