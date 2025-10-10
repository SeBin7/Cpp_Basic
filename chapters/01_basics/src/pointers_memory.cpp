#include <iostream>
#include <memory>
#include <vector>
#include <span>
#include <cassert>

using namespace std;

namespace basics {

// Small helper to silence -Wunused warnings
template <class T>
inline void use(const T&) {}

static void print_ptr(const void* p, const char* label) {
    cout << label << "=" << p << "\n";
}

// Sum using span (safe pointer+length)
static long long sum_span(span<const int> s) {
    long long acc = 0;
    for (int v : s) acc += v;
    return acc;
}

void run_pointers_examples() {
    cout << "=== pointers_memory.cpp demos ===\n\n";

    // ------------------------------------------------------------
    // 1) Address-of, dereference, const correctness
    // ------------------------------------------------------------
    {
        int x = 42;
        int* px = &x;                // pointer to int
        print_ptr(&x, "&x");
        cout << "*px=" << *px << "\n";
        *px = 100;                   // modifies x
        cout << "x(after *px=100)=" << x << "\n";

        const int* p_to_const = &x;  // cannot modify *p
        // *p_to_const = 1;          // compile error
        int* const const_ptr = &x;   // pointer itself cannot rebind
        *const_ptr = 123;

        const int y = 7;
        // int* p_bad = &y;          // compile error: drop const
        (void)p_to_const; (void)const_ptr;
        cout << "x(final)=" << x << "\n\n";
    }

    // ------------------------------------------------------------
    // 2) Array and pointer decay
    // ------------------------------------------------------------
    {
        int a[5] = {1,2,3,4,5};
        cout << "sizeof(a)=" << sizeof(a) << " bytes, sizeof(*a)=" << sizeof(*a)
             << " -> count=" << sizeof(a)/sizeof(*a) << "\n";
        int* p = a;                  // decay to pointer
        print_ptr(a, "a");
        print_ptr(p, "p (decayed)");

        // pointer arithmetic
        cout << "p[2]=" << p[2] << " *(p+2)=" << *(p+2) << "\n";

        // safer API: span view
        span<int> s{a};  // length-aware
        s[0] = 99;
        cout << "sum_span(a)=" << sum_span(span<const int>(a)) << "\n\n";
    }

    // ------------------------------------------------------------
    // 3) Dynamic allocation (new/delete, new[]/delete[])
    // ------------------------------------------------------------
    {
        int* pi = new int(7);        // allocate one int
        cout << "*pi=" << *pi << "\n";
        delete pi;                   // always pair with delete
        pi = nullptr;                // null after delete to avoid dangling

        int* arr = new int[3]{10,20,30};
        cout << "arr[1]=" << arr[1] << "\n";
        delete[] arr;                // array form
        arr = nullptr;
        cout << "(deleted dynamic memory)\n\n";
    }

    // ------------------------------------------------------------
    // 4) RAII with smart pointers (unique_ptr, shared_ptr, weak_ptr)
    // ------------------------------------------------------------
    {
        // unique ownership
        auto up = make_unique<int>(55);
        cout << "*unique_ptr=" << *up << "\n";

        // unique_ptr for arrays
        auto uarr = make_unique<int[]>(4);
        for (int i = 0; i < 4; ++i) uarr[i] = (i+1)*10;
        cout << "uarr[3]=" << uarr[3] << " (auto-deletes, no delete[])\n";

        // shared ownership
        auto sp1 = make_shared<vector<int>>(initializer_list<int>{1,2,3});
        auto sp2 = sp1; // share ownership
        cout << "shared use_count=" << sp1.use_count() << " size=" << sp1->size() << "\n";

        weak_ptr<vector<int>> wp = sp1; // non-owning observer
        cout << "weak expired? " << boolalpha << wp.expired() << "\n";
        sp2.reset();
        sp1.reset();
        cout << "after reset -> weak expired? " << wp.expired() << "\n\n";
    }

    // ------------------------------------------------------------
    // 5) Dangling pointer & double delete (what NOT to do)
    // (Demonstrated safely via comments / patterns)
    // ------------------------------------------------------------
    {
        // int* p = new int(1);
        // delete p;
        // *p = 2;                  // UB: use-after-free (DON'T)
        // delete p;                // double delete (DON'T)
        // Pattern: set to nullptr after delete and always check.
        cout << "Tip: after delete, set pointer to nullptr to avoid reuse.\n\n";
    }

    // ------------------------------------------------------------
    // 6) Passing buffers: pointer+len vs span
    // ------------------------------------------------------------
    {
        vector<int> v{5,5,5,5};
        // traditional C style
        long long s1 = 0;
        for (size_t i = 0; i < v.size(); ++i) s1 += v[i];

        // modern C++ span
        long long s2 = sum_span(span<const int>(v));
        cout << "sum via loop=" << s1 << " via span=" << s2 << "\n\n";
    }

    cout << "=== end of pointers_memory.cpp demos ===\n";
}

} // namespace basics
