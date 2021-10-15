#include <iostream>
#include <chrono>
#include "Example/ex7-array.h"

class Test{
private:
    int *arr;
    int length;
public:
    Test(int *_arr, int _length) : length(_length){
        std::cout<< "constructor : " << this << std::endl;
        arr = new int[length];
        for(int i = 0; i != length; i++) arr[i] = _arr[i];
    }
    Test(const Test& t) : length(t.length){
        std::cout<< "copy constructor : " << this << std::endl;
        arr = new int[length];
        for(int i = 0; i != length; i++) arr[i] = t.arr[i];
    }
    ~Test(){delete[] arr;}
    Test& operator=(const Test& t){
        std::cout<< "operator=(this) : " << this << std::endl;
        std::cout<< "operator=(lvalue) : " << &t << std::endl;
        if(arr != nullptr){
            std::cout << "delete..." << std::endl;
            delete[] arr;
            arr = nullptr;
        }
        length = t.length;
        arr = new int[length];
        for(int i = 0; i < length; i++) arr[i] = t.arr[i];
        return *this;
    }
};

int main() {
    int size[] = {2, 3, 4};
    MyArray::Array arr(3, size);

    MyArray::Array::Iterator itr = arr.begin();
    for (int i = 0; itr != arr.end(); itr++, i++) (*itr) = i;
    for (itr = arr.begin(); itr != arr.end(); itr++)
        std::cout << *itr << std::endl;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                arr[i][j][k] = (i + 1) * (j + 1) * (k + 1) + arr[i][j][k];
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 4; k++) {
                std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
                          << std::endl;
            }
        }
    }
    return 1;
}
