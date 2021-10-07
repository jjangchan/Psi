#include <iostream>
#include <chrono>
#include "Example/ex7-array.h"

class Base{
public:
    std::string s1;
public:
    Base() : s1("base"){ std::cout << "base class" << std::endl;}
    void println() const {std::cout << s1 << std::endl;}

};

class Derived : public Base{
private:
    std::string s;
public:
    Derived() : Base(), s("derived") {
        std::cout << "derived class" << std::endl;
    }
    void println() const {std::cout << s << std::endl;}
};

int main() {
    Base b;
    Derived d;

    Base* p_b = &d;
    Derived* p_d= static_cast<Derived*>(p_b);

    p_d->println();

    //Array array;
    //array[2][2][3]; // -> array.operator[](2),operator[](2).operator[](3);
    return 1;
}
