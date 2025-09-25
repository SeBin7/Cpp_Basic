#include <iostream>
#include "NameSp1.hpp"

namespace BestComImpl {
	void SimpleFunc(void) {
		std::cout << "BestCom이 정의한 함수" << std::endl;
	}
}

namespace ProgComImpl {
	void SimpleFunc(void) {
		std::cout << "ProgCom이 정의한 함수" << std::endl;
	}
}
