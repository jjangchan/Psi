//
// Created by momantic03 on 2021-10-01.
//

#ifndef EX2_NEW_DELETE_H_EX7_ARRAY_H
#define EX2_NEW_DELETE_H_EX7_ARRAY_H

class Array{
private:
    Array *array_number;
    int data;
    int n;
    int size;
    int capacity;


public:
    Array(int n ):n(n){
        array_number = new Array(n);
    }
    Array(const Array& array):n(array.n){}
    ~Array(){
        delete array_number;
    }
    Array& operator[](const int n1){
        std::cout << "call : " << n1 << std::endl;
        return *this;
    }
private:
};

#endif //EX2_NEW_DELETE_H_EX7_ARRAY_H
