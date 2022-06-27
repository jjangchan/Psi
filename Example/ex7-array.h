//
// Created by jjangchan on 2021-10-01.
//

#ifndef EX2_NEW_DELETE_H_EX7_ARRAY_H
#define EX2_NEW_DELETE_H_EX7_ARRAY_H

#include <iostream>

namespace MyArray {
    // 선언 순서 지켜야함.
    class Array;
    class Int;
    class Array {
    private:
        friend Int;
        const int dimension;
        int *size;
        struct Address {
            int level;
            void *next;
        };
        Address *top;
    public:
        class Iterator{
        private:
            int* location;
            Array* array;
            friend Int;
        public:
            Iterator(Array* _array, int* _location = nullptr): array(_array){
                location = new int[array->dimension];
                for(int i = 0; i < array->dimension; i++) location[i] = (_location != nullptr) ? _location[i] : 0;
            }

            Iterator(const Iterator& iter): array(iter.array){
                location = new int[array->dimension];
                for(int i = 0; i < array->dimension; i++) location[i] = iter.location[i];
            }

            ~Iterator(){delete[] location;}

            Iterator& operator++(){
                if(location[0] >= array->size[0]) return (*this);
                bool up = false;
                int i = array->dimension-1;
                do{
                    location[i]++;
                    if(location[i] >= array->size[i] && i > 0){
                        location[i] -= array->size[i];
                        up = true;
                        i--;
                    }else up = false;

                } while (i >= 0 && up);
            }

            Iterator operator++(int){
                Iterator temp(*this);
                ++(*this);
                return temp;
            }

            bool operator!=(const Iterator& iter){
                if(array->dimension != iter.array->dimension) return false;
                for(int i = 0; i != array->dimension; i++){
                    if(location[i] != iter.location[i]) return true;
                }
                return false;
            }

            Iterator& operator=(const Iterator& iter){
                array = iter.array;
                if(location != nullptr){
                    std::cout << "delete : " << &location << std::endl;
                    delete[] location;
                    location = nullptr;
                }
                location = new int[array->dimension];
                for(int i = 0; i < array->dimension; i++) location[i] = iter.location[i];
                return *this;
            }

            Int operator*();

        };

    public:
        Array(int dimension, int *array_size) : dimension(dimension) {
            size = new int[dimension];
            for (int i = 0; i < dimension; i++) size[i] = array_size[i];
            top = new Address;
            top->level = 0;
            InitializeAddress(top);
        }

        Array(const Array &array) : dimension(array.dimension) {
            size = new int[dimension];
            for (int i = 0; i < dimension; i++) size[i] = array.size[i];

            top = new Address;
            top->level = 0;

            InitializeAddress(top);
            CopyAddress(top, array.top);
        }

        ~Array() {
            DeleteAddress(top);
            if (size != nullptr) {
                delete[] size;
                size = nullptr;
            }
        }

        Int operator[](const int index);

        Iterator begin(){
            int *location = new int[dimension];
            for(int i =0; i < dimension; i++) location[i] = 0;
            Iterator temp(this, location);
            delete[] location;
            return temp;
        }

        Iterator end(){
            int *location = new int[dimension];
            location[0] = size[0];
            for(int i =1; i < dimension; i++) location[i] = 0;
            Iterator temp(this, location);
            delete[] location;
            return temp;
        }

    private:
        // create object(top - down)
        void InitializeAddress(Address *current) {
            /**
             * [array node]
             * example) [1][3][2]
             *
             *       0               - top (Address*)
             *       |
             *       0               - level 1 (Address*) : [1][x][x]
             *       |
             *  0    0    0          - level 2 (Address*) : [x][3][x]
             *  |    |    |
             * 0 0  0 0  0 0         - level 3 (int*) : [x][x][2]
             *
             * **/
            if (current == nullptr) return;
            if (current->level == dimension - 1) {
                current->next = new int[size[current->level]];
                return;
            }
            current->next = new Address[size[current->level]];
            // DFS Search
            for (int i = 0; i != size[current->level]; i++) {
                (static_cast<Address *>(current->next) + i)->level = current->level + 1;
                InitializeAddress(static_cast<Address *>(current->next) + i);
            }
        }
        // delete object(down - top)
        void DeleteAddress(Address *current) {
            if (current == nullptr) return;
            for (int i = 0; current->level < dimension - 1 && i < size[current->level]; i++) {
                DeleteAddress(static_cast<Address *>(current->next) + i);
            }
            if (current->level == dimension - 1) {
                delete[] static_cast<int *>(current->next);
            } else {
                delete[] static_cast<Address *>(current->next);
            }
        }

        // int* 원소들 copy
        void CopyAddress(Address *dst, Address *src) {
            if (dst->level == dimension - 1) {
                for (int i = 0; i < size[dst->level]; i++)
                    static_cast<int *>(dst->next)[i] = static_cast<int *>(src->next)[i];
                return;
            }
            for (int i = 0; i != size[dst->level]; i++) {
                Address *new_dst = static_cast<Address *>(dst->next) + i;
                Address *new_src = static_cast<Address *>(src->next) + i;
                CopyAddress(new_dst, new_src);
            }
        }

    };

    class Int {
    private:
        void* data;
        int level;
        Array* array;
    public:
        Int(int index, int _level = 0, void* _data = nullptr, Array* _array = nullptr):level(_level), data(_data), array(_array){
            if(level < 1 || index > array->size[level-1]){
                data = nullptr;
                return;
            }
            if(level == array->dimension){
                data = static_cast<void*>(static_cast<int*>(static_cast<Array::Address*>(data)->next)+index);
            }else{
               data = static_cast<void*>(static_cast<Array::Address*>(static_cast<Array::Address*>(data)->next)+index);
            }
        }

        // 만약 data 가 중간산물(Address*) 이면 next level 로 리턴
        Int operator[](const int index){
            if(data == nullptr) return 0;
            return Int(index, level+1, data, array);
        }

        Int& operator=(const int& result){
            if(data != nullptr) *static_cast<int*>(data) = result;
            return *this;
        }

        // 만약 data 가 int를 가리키는 주소이면 타임 변환 연산자로 인해 int 변수처럼 대입이 수행
        operator int(){
            if(data == nullptr) return 0;
            return *static_cast<int*>(data);
        }


    };

    // Int 생성자를 생성하려면 컴파일 단계에서 Int 내부코드를 다 읽어야함, 따라서 클래스 밖에서 선언
    Int Array::operator[](const int index) {
        return Int(index, 1, static_cast<void*>(top), this);
    }

    Int Array::Iterator::operator*() {
        Int start = array->operator[](location[0]);
        for(int i = 1; i < array->dimension; i++)
            start = start.operator[](location[i]);
        return start;
    }

}

#endif //EX2_NEW_DELETE_H_EX7_ARRAY_H
