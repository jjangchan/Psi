//
// Created by jjangchan on 2022/06/27.
//

#ifndef MAIN_CPP_EX9_TEMPLATE_VECTOR_H
#define MAIN_CPP_EX9_TEMPLATE_VECTOR_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

template <typename T>
class Vector{
private:
    T* data;
    int size;
    int capacity;
public:
    Vector(int n = 1) : data(new T[n]), size(0), capacity(n){}
    ~Vector(){
        if(data != nullptr){
            delete[] data;
            data = nullptr;
        }
    }

    void push_back(T d){
        if(size >= capacity){
            T* temp = new T[capacity*2];
            for(int i = 0; i < size; i++) temp[i] = data[i];
            delete[] data;
            data = temp;
            capacity *= 2;
        }
        data[size++] = d;
    }

    void remove(const int x){
        if(x < 0 || x > size) return;
        for(int i = x+1; i < size; i++) data[i-1] = data[i];
        size--;
    }

    T operator[](const int i){
        return data[i];
    }

    int length() const { return size;}

};


template<>
class Vector<bool>{
private:
    unsigned int *data;
    int capacity;
    int length;
public:
    // int(4bite) -> 8*4 = 32, (2^32-1)까지 표현 가능 bool은 1비트 이므로 32개의 공간을 활용할 수 있다.
    Vector(int _capacity = 1): data(new unsigned int[_capacity/32+1]), capacity(_capacity/32+1), length(0){}
    ~Vector(){delete[] data;}
    void push_back(bool d){
        if(length >= capacity*32){
            unsigned int *temp= new unsigned int[capacity*2];
            for(int i = 0; i < length; i++) temp[i] = data[i];
            for(int i = capacity; i < capacity+2; i++) temp[i] = 0;
            delete[] data;
            data = temp;
            capacity *= 2;
        }
        if(d){
            // ex)
            // 0100 1111
            // 1000 0000 (or)
            // 1100 1111
            data[length/32] |= (1 << (length%32));
        }
        length++;
    }

    void remove(const int i){
        for(int x = i+1; x < length; x++){
            int current = x;
            int previous = x-1;
            if(data[current/32] & (1 << (current%32))){
                // current index is true
                data[previous/32] |= (1 << (previous%32));
            }else{
                unsigned int all_ones_except_prev = 0xFFFFFFFF; // 1111 ..~~.. 1111
                all_ones_except_prev ^= (1 << (previous%32));
                data[previous/32] &= all_ones_except_prev;
            }
        }
        length--;
    }

    bool operator[](const int i){ return (data[i/32]&(1 << (i%32))) != 0;}
    int size() const{return length;}
};

#endif //MAIN_CPP_EX9_TEMPLATE_VECTOR_H
