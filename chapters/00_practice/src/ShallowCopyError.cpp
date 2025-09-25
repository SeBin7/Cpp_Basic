#include <iostream>
#include <cstring>
using namespace std;

class Person {
private:
	char* name;
	int age;
public:
	Person(char* myname, int myage) {
		int len = strlen(myname) +1;
		name = new char[len];
		strcpy(name, myname);
		age = myage;
	}
	void ShowPersonInfo() {
		cout << "name: " << name << endl;
		cout << "age: " << age << endl;
	}
	~Person() {
		delete[] name;
		cout << "called destructor!" << endl;
	}
};

void shallowcopyerror() {
	Person man1((char*)"LEE", 20);
	Person man2 = man1; // default shallow copy
	man1.ShowPersonInfo();
	man2.ShowPersonInfo();
}
