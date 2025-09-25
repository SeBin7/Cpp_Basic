#include <iostream>
#include "FunctionOverlading.hpp"
#include "HelloWorld.hpp"
#include "SimpleAdder.hpp"
#include "DefaultValue1.hpp"
#include "NameSp1.hpp"
#include "RefArrElem.hpp"
#include "RefSwap.hpp"
#include "MemMalFree.hpp"
#include "Car.hpp"
#include "Point.hpp"
#include "Rectangle.hpp"
#include "PointerThis.hpp"
#include "ShallowCopyError.hpp"

int main() {

    /* HelloWorld.cpp */
    helloworld();

    /* SimpleAdder.cpp */
    //simpleadder();

    /* FunctionOverloading.cpp */
    MyFunc();
    MyFunc('A');
    MyFunc(12, 13);

    /* DefaultValue1.cpp */
    std::cout << Adder() << std::endl;
    std::cout << Adder(5) << std::endl;
    std::cout << Adder(3, 5) << std::endl;

    /* NameSp1.cpp */
    BestComImpl::SimpleFunc();
    ProgComImpl::SimpleFunc();

    refarrelem();

    refswap();

    memmalfree();

    /* Car */
    Car run99;
    run99.InitMembers((char*)"run99", 100);
    run99.Accel();
    run99.Accel();
    run99.Accel();
    run99.ShowCarState();
    run99.Break();
    run99.ShowCarState();

    //Rectangle rec(1, 1, 5, 5);
    //rec.ShowRecInfo();

	pointerthis();

    //shallowcopyerror();

    return 0;

}

