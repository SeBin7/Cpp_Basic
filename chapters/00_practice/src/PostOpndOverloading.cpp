#include <iostream>
using namespace std;

class Point {
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) { }
	void ShowPointInfo() const {
		cout << "[" << xpos << ", " << ypos << "]" << endl;
	}
	void ShowPosition() const {
		cout << xpos << ", " << ypos << endl;
	}
	Point& operator++() {
		xpos += 1;
		ypos += 1;
		return *this;
	}
	const Point operator++(int) {
		const Point retobj(xpos, ypos);
		xpos += 1;
		ypos += 1;
		return retobj;
	}
	friend Point& operator--(Point& ref);
	friend const Point operator--(Point& ref, int);
};

