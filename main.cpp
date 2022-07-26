#include <string>
#include <iostream>
#include "Example/ex11-tmp.h"

int main() {
    typedef Ratio<2,3> r1;
    typedef Ratio<3,2> r2;
    typedef Ratio_add<r1, r2> r3;
    std::cout << r3::num << " / " << r3::den;

}
