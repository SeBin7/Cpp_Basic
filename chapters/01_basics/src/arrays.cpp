#include <array>
#include <vector>
#include <span>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstring>   // memset (for C array demo)
#include <cassert>
using namespace std;

namespace {

// ---------- Utilities ----------
template <class Range>
void print_range(const Range& r, const char* label) {
    cout << label << " [";
    bool first = true;
    for (const auto& v : r) {
        if (!first) cout << ", ";
        cout << v;
        first = false;
    }
    cout << "]\n";
}

// Overload for C arrays (deduces size)
template <class T, size_t N>
void print_c_array(const T (&arr)[N], const char* label) {
    cout << label << " [";
    for (size_t i = 0; i < N; ++i) {
        cout << arr[i] << (i + 1 < N ? ", " : "");
    }
    cout << "] (size=" << N << ")\n";
}

int sum_with_pointer(const int* p, size_t n) {
    // Pointer + length (classic C style)
    int s = 0;
    for (size_t i = 0; i < n; ++i) s += p[i];
    return s;
}

int sum_with_span(span<const int> sp) {
    // Modern C++: span carries pointer+size safely
    int s = 0;
    for (int v : sp) s += v;
    return s;
}

} // namespace

namespace basics {

void run_arrays_examples() {
    cout << "=== arrays.cpp demos ===\n\n";

    // ---------------------------------------------------------------------
    // 1) C-style array (fixed size, lives on stack)
    // ---------------------------------------------------------------------
    {
        int a[5] = {1, 2, 3, 4, 5};
        print_c_array(a, "C array a");

        // sizeof works at compile time here (not after decay!)
        size_t count = sizeof(a) / sizeof(a[0]);
        cout << "sizeof(a) elements = " << count << "\n";

        // Fill with 0 using memset (only safe for trivially copyable types)
        memset(a, 0, sizeof(a));
        print_c_array(a, "C array a after memset");
        cout << "\n";
    }

    // ---------------------------------------------------------------------
    // 2) Pointer decay (arrays decay to pointer to first element)
    // ---------------------------------------------------------------------
    {
        int b[4] = {10, 20, 30, 40};
        // Decays to int*
        int* pb = b;
        // But we must pass the length explicitly in C-style APIs
        int s1 = sum_with_pointer(pb, 4);
        cout << "sum_with_pointer(b, 4) = " << s1 << "\n";

        // Use span to avoid passing length separately
        int s2 = sum_with_span(span<const int>(b, 4));
        cout << "sum_with_span(span(b,4)) = " << s2 << "\n\n";
    }

    // ---------------------------------------------------------------------
    // 3) array (fixed-size container with STL friendliness)
    // ---------------------------------------------------------------------
    {
        array<int, 5> arr {5, 4, 3, 2, 1};
        print_range(arr, "array arr");

        // size(), at(), fill(), begin()/end() are available
        cout << "arr.size() = " << arr.size() << "\n";
        arr[0] = 42;
        arr.at(1) = 99; // bounds-checked
        arr.fill(7);
        print_range(arr, "arr after fill(7)");

        // Sort range
        sort(arr.begin(), arr.end());
        print_range(arr, "arr after sort");

        // span view over array
        span<int> sp{arr};
        sp[0] = 123;
        print_range(arr, "arr after span write (sp[0]=123)");
        cout << "\n";
    }

    // ---------------------------------------------------------------------
    // 4) vector (dynamic size, heap storage)
    // ---------------------------------------------------------------------
    {
        vector<int> v;
        v.reserve(8);              // avoid reallocation for small pushes
        for (int i = 1; i <= 6; ++i) v.push_back(i * 10);
        print_range(v, "vector v");

        cout << "v.size()=" << v.size()
                  << " v.capacity()=" << v.capacity() << "\n";

        // Insert/erase
        v.insert(v.begin() + 2, 999);
        v.erase(v.begin() + 4);
        print_range(v, "v after insert/erase");

        // Algorithms
        sort(v.begin(), v.end(), greater<int>());
        print_range(v, "v after sort desc");

        // span view over contiguous vector storage
        span<int> sp{v};
        int total = accumulate(sp.begin(), sp.end(), 0);
        cout << "accumulate(v) = " << total << "\n\n";
    }

    // ---------------------------------------------------------------------
    // 5) Multidimensional arrays
    //    - C-style: int m[rows][cols];
    //    - array-of-array for safer semantics
    // ---------------------------------------------------------------------
    {
        // C-style 2D array (contiguous row-major memory)
        int m[2][3] = {
            {1, 2, 3},
            {4, 5, 6}
        };
        cout << "C 2D m[2][3]:\n";
        for (int r = 0; r < 2; ++r) {
            for (int c = 0; c < 3; ++c) {
                cout << m[r][c] << (c + 1 < 3 ? " " : "");
            }
            cout << "\n";
        }

        // array-of-array (still contiguous, STL-friendly)
        array<array<int, 3>, 2> mm {{
            {{10, 20, 30}},
            {{40, 50, 60}}
        }};
        cout << "array 2D mm:\n";
        for (const auto& row : mm) {
            for (int x : row) cout << x << " ";
            cout << "\n";
        }

        // Flatten view with span (reinterpret_cast not needed since contiguous)
        // Take care: construct span over the underlying contiguous buffer
        span<int> flat{&mm[0][0], mm.size() * mm[0].size()};
        sort(flat.begin(), flat.end());
        cout << "mm after sort(flat):\n";
        for (const auto& row : mm) {
            for (int x : row) cout << x << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    // ---------------------------------------------------------------------
    // 6) span parameter demo (safe view type)
    // ---------------------------------------------------------------------
    {
        array<int, 4> a{7, 1, 9, 3};
        int c[4] = {8, 6, 4, 2};
        vector<int> v{5, 5, 5, 5};

        auto demo_sum = [](span<const int> s, const char* tag) {
            int ssum = accumulate(s.begin(), s.end(), 0);
            cout << "sum(" << tag << ") = " << ssum << "\n";
        };

        demo_sum(span<const int>(a), "array");
        demo_sum(span<const int>(c, 4), "C array");
        demo_sum(span<const int>(v), "vector");
        cout << "\n";
    }

    cout << "=== end of arrays.cpp demos ===\n";
}

} // namespace basics
