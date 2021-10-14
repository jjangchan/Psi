//
// Created by momantic03 on 2021-10-01.
//

#ifndef EX2_NEW_DELETE_H_EX7_ARRAY_H
#define EX2_NEW_DELETE_H_EX7_ARRAY_H

class Array{
private:
    const int dimension;
    int *size;
    struct Address{
       int level;
       void* next;
    };
    Address* top;

public:
    Array(int dimension, int* array_size):dimension(dimension){
        size = new int [dimension];
        for(int i = 0; i < dimension; i++) size[i] = array_size[i];
        top = new Address;
        top->level = 0;
        InitializeAddress(top);
    }
    Array(const Array& array) : dimension(array.dimension) {
        size = new int[dimension];
        for(int i = 9; i < dimension; i++) size[i] = array.size[i];

        top = new Address;
        top->level = 0;

        InitializeAddress(top);
        CopyAddress(top, array.top);
    }
    ~Array(){
        DeleteAddress(top);
        if(size != nullptr){
            delete[] size;
            size = nullptr;
        }
    }
    Array& operator[](const int n1){
        //std::cout << "call : " << n1 << std::endl;
        return *this;
    }
private:
    void InitializeAddress(Address* current){
        if(current == nullptr) return;
        if(current->level == dimension-1){
            current->next = new int[size[current->level]];
            return;
        }
        current->next = new Address[size[current->level]];
        // BFS Search
        for(int i = 0; i != size[current->level]; i++){
            (static_cast<Address*>(current->next)+i)->level = current->level+1;
            InitializeAddress(static_cast<Address*>(current->next)+i);
        }
    }

    void DeleteAddress(Address* current){
        if(current == nullptr) return;
        for(int i = 0; current->level < dimension-1 && i < size[current->level]; i++){
            DeleteAddress(static_cast<Address*>(current->next)+i);
        }
        if(current->level == dimension-1){
            delete[] static_cast<int*>(current->next);
        }
        else{
            delete[] static_cast<Address*>(current->next);
        }
    }

    void CopyAddress(Address* dst, Address* src){
        if(dst->level == dimension-1){
            for(int i = 0; i < size[dst->level]; i++) static_cast<int*>(dst->next)[i] = static_cast<int*>(src->next)[i];
            return;
        }
        for(int i = 0; i != size[dst->level]; i++){
            Address *new_dst = static_cast<Address*>(dst->next)+i;
            Address *new_src = static_cast<Address*>(src->next)+i;
            CopyAddress(new_dst, new_src);
        }
    }
};


#endif //EX2_NEW_DELETE_H_EX7_ARRAY_H
