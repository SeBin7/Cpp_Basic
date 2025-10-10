#include <iostream>
#include <cstdlib>
using namespace std;

class Point {
private:
    int xpos, ypos;
public:
    Point(int x = 0, int y = 0) : xpos(x), ypos(y) {}

    // Declare only; define once outside the class
    friend ostream& operator<<(ostream& os, const Point& pos);
};

// Single out-of-class definition (friend gives access to private members)
ostream& operator<<(ostream& os, const Point& pos) {
    os << '[' << pos.xpos << ", " << pos.ypos << ']' << '\n';
    return os;
}

class BoundCheckPointArray {
private:
    Point* arr;
    int arrlen;

    // If you don't want copying, delete them explicitly
    BoundCheckPointArray(const BoundCheckPointArray&) = delete;
    BoundCheckPointArray& operator=(const BoundCheckPointArray&) = delete;

public:
    explicit BoundCheckPointArray(int len) : arr(new Point[len]), arrlen(len) {}

    Point& operator[](int idx) {
        if (idx < 0 || idx >= arrlen) {
            cout << "Array index out of bound exception" << '\n';
            exit(1);
        }
        return arr[idx];
    }

    const Point& operator[](int idx) const {
        if (idx < 0 || idx >= arrlen) {
            cout << "Array index out of bound exception" << '\n';
            exit(1);
        }
        return arr[idx];
    }

    int GetArrLen() const { return arrlen; }

    ~BoundCheckPointArray() { delete[] arr; }
};

void StablePointObjArray() {
    BoundCheckPointArray arr(3);
    arr[0] = Point(1, 2);
    arr[1] = Point(3, 4);
    arr[2] = Point(5, 6);

    for (int i = 0; i < arr.GetArrLen(); i++) {
        cout << arr[i]; // uses operator<<(ostream&, const Point&)
    }
}
