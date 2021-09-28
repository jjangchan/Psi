#include <iostream>
#include <cstring>

class Test{
private:
    int a;
public:
    Test(int a) : a(a){}
    Test(const Test& t): a(t.a){std::cout <<"copy : " << this << std::endl;}
    ~Test(){}
    Test& operator++() {
        a++;
        return *this;
    }
    Test operator++(int){
        Test temp(*this);
        a++;
        return temp;
    }
    Test& operator=(const Test& t){
        a = t.a;
        return *this;
    }
};

int main() {
    return 0;
}