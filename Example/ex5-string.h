//
// Created by jjangchan on 2021-09-10.
//

#ifndef EX2_NEW_DELETE_H_EX5_STRING_H
#define EX2_NEW_DELETE_H_EX5_STRING_H

#include <iostream>

class MyString{
private:
    char *string_content;
    int string_length;
    int memory_capacity;

public:
    MyString(const char a){
        string_content = new char[1];
        string_length = 1;
        memory_capacity = 1;
        string_content[0] = a;

    }

    MyString(const MyString &string){
        std::cout << "copy constructor : " << this << std::endl;
        string_length = string.string_length;
        memory_capacity = string.string_length;
        string_content = new char[string_length];
        for(int i = 0; i < string_length; i++){
            string_content[i] = string.string_content[i];
        }
    }

    MyString(const char *string){
        std::cout << "constructor : " << this << std::endl;
        string_length = Getlen(string);
        memory_capacity = string_length;
        string_content = new char[string_length];
        for(int i = 0; i < string_length; i++){
            string_content[i] = string[i];
        }
    }

    ~MyString(){
        delete[] string_content;
    }


    friend  MyString operator+(const MyString& str1, const MyString& str2);

    MyString& operator+=(const MyString& str){
        std::cout << "operator+=" << std::endl;
        (*this) = (*this) + str;
        return (*this);
    }

    MyString& operator=(const MyString& string){
        std::cout << "operator=" << std::endl;
        string_length = string.string_length;
        if(string.string_length > memory_capacity){
            memory_capacity = (memory_capacity*2 > string.string_length+string_length) ? memory_capacity*2 :  string_length+string.string_length;
            delete []string_content;
            string_content = new char[string.string_length];
        }
        for(int i = 0; i < string_length; i++){
            string_content[i] = string.string_content[i];
        }
        return *this;
    }

    char& operator[](const int index){
        return string_content[index];
    }

    int length() const{
       return string_length;
    }

    int capacity() const{
        return memory_capacity;
    }

    void print() const{
        for(int i = 0; i < string_length; i++)
            std::cout << string_content[i];
    }

    void println() const{
        for(int i = 0; i < string_length; i++)
            std::cout << string_content[i];
        std::cout << std::endl;
    }

    void reserve(const int size){
        // memory initialization and reallocation
        if(size > memory_capacity){
            char *temp_str = string_content;
            string_content = new char[size];
            memory_capacity = size;
            for(int i = 0; i < string_length; i++){
                string_content[i] = temp_str[i];
            }
            delete[] temp_str;
        }
    }

    char at(const int i) const {
        if(i < 0 || i >= string_length) // out of range
            return NULL;
        else
            return string_content[i];
    }

    MyString& assign(const char * string){
        int des_length = Getlen(string);
        if(des_length > memory_capacity){
            // memory init
            delete[] string_content;
            string_content = new char[des_length];
            memory_capacity = des_length;
        }
        //memory assign
        for(int i = 0; i < des_length; i++)
            string_content[i] = string[i];
        string_length = des_length;
        return *this;
    }

    MyString& assign(const MyString& string){
        int des_length = string.string_length;
        if(des_length > memory_capacity){
            // memory init
            delete[] string_content;
            string_content = new char[des_length];
            memory_capacity = des_length;
        }
        // memory assign
        for(int i = 0; i < des_length; i++)
            string_content[i] = string.string_content[i];
        string_length = des_length;
        return *this;

    }

    MyString& insert(const int loc, const MyString &string){
        // out of range
        if(loc < 0 || loc > string_length) return *this;
        if(string.string_length + string_length > memory_capacity){
            // memory init and insert
            memory_capacity = (memory_capacity*2 > string.string_length+string_length) ? memory_capacity*2 : string_length+string.string_length;
            char * temp_string = string_content;
            string_content = new char[memory_capacity];
            for(int i = 0; i < string_length + string.string_length; i++)
                string_content[i] = (i >= loc && i < loc+string.string_length) ? string.string_content[i-loc] : temp_string[(i < loc) ? i : i-loc];
            delete[] temp_string;
            string_length += string.string_length;
            return *this;
        }
        // only insert
        for(int i = string.string_length+string_length-1; loc <= i; i--)
            string_content[i] = (loc+string.string_length <= i) ? string_content[i-loc] : string.string_content[i-loc];
        string_length = string.string_length + string_length;
        return  *this;
    }

    MyString& insert(const int loc, const char* string){
        MyString temp(string);
        return insert(loc, temp);
    }

    MyString& insert(const int loc, const char a){
        MyString temp(a);
        return insert(loc, temp);
    }

    MyString& erase(const int loc, const int num){
        // out of range
        if(loc < 0 || num < 0 || loc >= string_length) return *this;
        if(loc+num < string_length){
            for(int i = loc+num; i < string_length; i++) string_content[i-num] = string_content[i];
            string_length -= num;
        }
        else string_length = 0;
        return *this;
    }

    int find(const int start, const MyString& string)
    {
        return -1;
    }

    int find(const int start, const char* string){
        MyString temp(string);
        return find(start, temp);
    }

    int find(const int start, const char c){
        MyString temp(c);
        return find(start, temp);
    }

    int compare(const MyString& string) const{
        for(int i = 0; i < std::min(string_length, string.string_length); i++){
            if(string_content[i] > string.string_content[i]) return 1;
            else if(string_content[i] < string.string_content[i]) return -1;
        }
        if(string_length == string.string_length) return 0;
        else if(string_length > string.string_length) return 1;
        return -1;
    }


private:
    int Getlen(const char *string) const{
        int length = 0;
        while(*string)
        {
          string++;
          length++;
        }
        string -= length;
        return length;
    }

};

MyString operator+(const MyString &str1, const MyString &str2) {
    std::cout << "operator+" << std::endl;
    int length = str1.string_length+str2.string_length;
    char* str_temp = new char[length+1];

    for(int i =0; i < length; i++){
        str_temp[i] = (i < str1.string_length) ? str1.string_content[i] : str2.string_content[i-str1.string_length];
    }
    str_temp[length] = 0;
    MyString temp(str_temp);
    delete []str_temp;
    return temp;
}


#endif //EX2_NEW_DELETE_H_EX5_STRING_H
