#include <iostream>
#include <string>
#include "Example/EX6Complex.h"

int main(){
    Complex a(0, 0);
    a = "-1.1 + i3.923" + a;
    a = a + a;

    Complex b(1, 2);
    b = a + b;

    b.println();
    std::cout << "a 의 값은 : " << a << " 이다. " << std::endl;
    return 0;
}
