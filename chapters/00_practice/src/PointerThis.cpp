#include <iostream>
#include <cstring>
using namespace std;

class sosimple {
private:
	int num;
public:
	sosimple(int n) : num(n) {
		cout << "num =" << num << endl;
		cout << "address =" << this << endl;
	}
	void showsimpledata() {
		cout << "num: " << num << endl;
	}
	sosimple* getThisPointer() {
		return this;
	}

};

void pointerthis(void) {
	sosimple sim(100);
	sosimple* ptr = sim.getThisPointer();
	cout << "ptr address: " << ptr << endl;
	ptr->showsimpledata();

	sosimple sim2(200);
	sosimple* ptr2 = sim2.getThisPointer();
	cout << "ptr address: " << ptr2 << endl;
	ptr2->showsimpledata();
}