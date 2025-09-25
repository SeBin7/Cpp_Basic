#include <iostream>
#include <cstring>
using namespace std;

class Gun {
private:
	int bullet;
public:
		Gun(int bnum) : bullet(bnum) { }
		void Shot() {
			cout << "BBANG!" << endl;
			bullet--;
		}
};

class Police : public Gun {
private:
	int handcuff;
public:
	Police(int bnum, int bcuff) : Gun(bnum), handcuff(bcuff) {}
	void PutHandcuff() {
		cout << "SNAP!" << endl;
		handcuff--;
	}
};

void hasinheritance() {
	Police pman(5, 3);
	pman.Shot();
	pman.PutHandcuff();
}