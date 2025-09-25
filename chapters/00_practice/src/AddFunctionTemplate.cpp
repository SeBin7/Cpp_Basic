#include <iostream>
using namespace std;

template <typename T>
T Add(T a, T b) {
	return a + b;
}

void AddFunctionTemplate() {
	cout << Add<int>(3, 5) << endl;
	cout << Add<double>(3.5, 5.2) << endl;
	cout << Add<string>("Hello ", "World") << endl;
}