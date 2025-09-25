#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "MemMalFree.hpp"
using namespace std;

char* MakeStrAdr(int len) {
	//char* str = (char*)malloc(sizeof(char) * len);
	char* str = new char[len];

	return str;
}

void memmalfree() {
	char* str = MakeStrAdr(20);
	strcpy(str, "I am so happy~");
	cout << str << endl;
	//free(str);
	delete[] str;
}