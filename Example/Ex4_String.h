//
// Created by jjangchan on 2021-05-27.
//

#ifndef EX2_NEW_DELETE_H_EX4_STRING_H
#define EX2_NEW_DELETE_H_EX4_STRING_H

#include <string.h>
#include <iostream>

class string{
private:
    char *str;
    int len;

public:
    // 문자 c가 n개 있는 문자열로 정의
    string(char c, int n){
        str = new char[n+1];
        //memset(str, NULL, sizeof(str));
        for(int i=0; i != n; i++){
            str[i] = c;
        }
        len = n;
        PrintData();
    }

    string(const char *s){
        len = 0;
        while(*s){
            s += 1;
            len += 1;
        }
        s -= len;
        str = new char[len+1];

        strcpy(str, s);
        this->len = len;
        PrintData();
        std::cout << "constructor" << std::endl;
    }

    string(const string &s){
        str = new char[s.strlen()+1];
        len = s.strlen();
        strcpy(str, s.str);
        PrintData();
    }

    ~string(){
        DestroyStr();
    }

    // str 뒤에 s를 붙인다.
    void AddString(const string &s){
        int length = s.strlen()+len+1;
        char* des_str = new char[length];
        strcpy_s(des_str, length,str);
        strcpy_s(des_str+len, length-len, s.str);
        DestroyStr();
        len = length-1;
        des_str[len] = 0;
        str = des_str;
        PrintData();
    }

    // str 에 s를 복사한다.
    void CopyString(const string &s){
        DestroyStr();
        str = new char[s.strlen()+1];
        strcpy(str, s.str);
        len = s.strlen();
        PrintData();
    }

    //문자열 길이 리턴
    int strlen() const{
        return len;
    }

private:
    void PrintData(){
        std::cout << "str : " << str << std::endl;
        std::cout << "len : " << len << std::endl;
    }

    void DestroyStr(){
        if(str) {
            delete[] str;
            str = nullptr;
        }
    }
};

#endif //EX2_NEW_DELETE_H_EX4_STRING_H
