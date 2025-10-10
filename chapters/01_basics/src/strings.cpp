#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

namespace basics {

// Small helper to avoid -Wunused warnings
template <class T>
inline void use(const T&) {}

void run_strings_examples() {
    cout << "=== strings.cpp demos ===\n\n";

    // ------------------------------------------------------------
    // 1) C-string vs std::string
    // ------------------------------------------------------------
    const char* cs = "hello";          // C-string (null-terminated)
    string s1 = "world";               // std::string (owns size + capacity)
    cout << "cs=\"" << cs << "\", s1=\"" << s1 << "\"\n";
    // Convert C-string -> std::string
    string s2(cs);
    // Get C-string view from std::string (lifetime bound to 's1')
    const char* p = s1.c_str();
    cout << "s2=\"" << s2 << "\", s1.c_str()=\"" << p << "\"\n\n";

    // ------------------------------------------------------------
    // 2) Concatenation / append / reserve / resize
    // ------------------------------------------------------------
    string s = "Hello";
    s += ", ";
    s.append("C++ ");            // append
    s.reserve(64);               // reserve capacity to avoid reallocations
    s += "strings!";
    cout << "concat: \"" << s << "\" (size=" << s.size()
         << ", cap~)\n";

    s.resize(7);                 // keep first 7 chars: "Hello, "
    cout << "resize(7): \"" << s << "\"\n";
    s.resize(12, '*');           // grow with fill char
    cout << "resize(12,'*'): \"" << s << "\"\n\n";

    // ------------------------------------------------------------
    // 3) substr / find / rfind / replace
    // ------------------------------------------------------------
    string t = "filepath:/home/se/work/data.csv";
    auto pos_colon = t.find(':');
    auto pos_last_slash = t.rfind('/');
    string scheme = (pos_colon != string::npos) ? t.substr(0, pos_colon) : "";
    string filename = (pos_last_slash != string::npos) ? t.substr(pos_last_slash + 1) : t;
    cout << "scheme=\"" << scheme << "\", filename=\"" << filename << "\"\n";

    // replace extension ".csv" -> ".txt"
    string rep = t;
    const string from = ".csv", to = ".txt";
    auto pos_ext = rep.rfind(from);
    if (pos_ext != string::npos) rep.replace(pos_ext, from.size(), to);
    cout << "replaced ext: \"" << rep << "\"\n\n";

    // ------------------------------------------------------------
    // 4) stoi/stol/stof and to_string
    // ------------------------------------------------------------
    vector<string> tokens = {"42", "  -17", "3.14", "oops"};
    for (const auto& tok : tokens) {
        try {
            // stoi stops at first non-digit, throws on invalid
            int iv = stoi(tok);
            cout << "stoi(\"" << tok << "\") -> " << iv << "\n";
        } catch (const exception& e) {
            cout << "stoi(\"" << tok << "\") failed: " << e.what() << "\n";
        }
    }
    double d = 2.718281828;
    string dstr = to_string(d);  // may contain many decimals
    cout << "to_string(2.718...) -> \"" << dstr << "\"\n\n";

    // ------------------------------------------------------------
    // 5) string_view (non-owning, size-aware view)
    //    - Does not own memory. Do not keep if the source is temporary.
    // ------------------------------------------------------------
    string big = "prefix-CORE-suffix";
    string_view sv = big;                    // view entire string
    string_view core = string_view(big).substr(7, 4); // "CORE"
    cout << "string_view: \"" << sv << "\", core=\"" << core << "\"\n";
    // Beware: lifetime! 'sv' becomes dangling if 'big' is destroyed.

    // ------------------------------------------------------------
    // 6) Tokenization with stringstream (no interactive I/O)
    // ------------------------------------------------------------
    istringstream iss("alice,24; bob,31;   charlie,28");
    string line;
    vector<pair<string,int>> rows;

    // Parse "name,age" separated by ';'
    while (getline(iss, line, ';')) {
        // trim leading spaces
        size_t b = line.find_first_not_of(' ');
        if (b == string::npos) continue;
        line.erase(0, b);

        auto comma = line.find(',');
        if (comma == string::npos) continue;
        string name = line.substr(0, comma);
        string age_str = line.substr(comma + 1);
        try {
            int age = stoi(age_str);
            rows.emplace_back(name, age);
        } catch (...) {
            // ignore malformed
        }
    }
    cout << "parsed rows:\n";
    for (const auto& [name, age] : rows) {
        cout << " - " << setw(8) << left << name << " : " << age << "\n";
    }
    cout << "\n";

    // ------------------------------------------------------------
    // 7) Comparisons and case sensitivity
    // ------------------------------------------------------------
    string A = "Apple", B = "apple";
    cout << "A==B? " << boolalpha << (A == B) << " (case-sensitive)\n";
    // lower-case comparison example
    auto to_lower = [](string v) {
        for (char& c : v) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        return v;
    };
    cout << "lower(A)==lower(B)? " << (to_lower(A) == to_lower(B)) << "\n\n";

    // ------------------------------------------------------------
    // 8) Formatting via stringstream (portable, no <format> dependency)
    // ------------------------------------------------------------
    ostringstream oss;
    oss << fixed << setprecision(2)
        << "name=" << "sebin" << ", score=" << 97.1234;
    cout << "ostringstream: " << oss.str() << "\n";

    // Note on UTF-8: std::string stores bytes; length() counts bytes, not characters.
    // Handling Unicode code points/graphemes requires dedicated libraries.

    cout << "\n=== end of strings.cpp demos ===\n";
}

} // namespace basics
