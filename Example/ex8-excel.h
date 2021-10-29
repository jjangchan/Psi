//
// Created by jjangchan on 2021-10-21.
//

#ifndef MAIN_CPP_EX8_EXCEL_H
#define MAIN_CPP_EX8_EXCEL_H
#include <string>
#include <sstream>
#include <iostream>

class Vector{
private:
    std::string* data;
    int capacity;
    int length;

public:
    Vector(int n = 1): data(new std::string[n]), capacity(n), length(0){}
    Vector(const Vector& t){
        if(data != nullptr) delete[] data;
        data = new std::string[t.length];
        length = t.length;
        capacity = t.capacity;
    }
    ~Vector(){
        if (data != nullptr) delete[] data;

    }

    void push_back(std::string s) {
        if(capacity <= length){
            std::string *temp = new std::string[capacity*2];
            for(int i =0; i < length; i++) temp[i] = data[i];
            delete[] data;
            data = nullptr;
            data = temp;
            capacity *= 2;
        }
        data[length] = s;
        length++;
    }

    void remove(int x){
        if(x < 0 || x >= length) return;
        for(int i = x+1; i < length; i++) data[i-1] = data[i];
        --length;
    }

    std::string operator[](int i) const {return data[i];}
    int size() const{return length;}
};

class Stack{
private:
    struct Node{
        Node* previous_node;
        std::string data;
        Node(Node* prev, std::string data):previous_node(prev), data(data){}
    };
    Node start;
    Node* current;

public:
    Stack(): start(NULL, ""){current = &start;}
    ~Stack(){
        while(current != &start){
            Node* prev = current->previous_node;
            delete current;
            current = prev;
        }
    }

    void push(std::string data){
        Node* node = new Node(current, data);
        current = node;
    }

    std::string pop(){
        if(current == &start) return "";
        std::string str = current->data;
        Node* prev = current->previous_node;
        delete current;
        current = prev;
        return str;
    }

    std::string peak(){
        return current->data;
    }

    bool is_empty(){
        return current == &start;
    }

};

class NumStack{
private:
    struct Node{
        Node* previous_node;
        double data;
        Node(Node* prev, double data):previous_node(prev), data(data){}
    };
    Node start;
    Node* current;

public:
    NumStack(): start(NULL, 0){current = &start;}
    ~NumStack(){
        while(current != &start){
            Node* prev = current->previous_node;
            delete current;
            current = prev;
        }
    }

    void push(double data){
        Node* node = new Node(current, data);
        current = node;
    }

    double pop(){
        if(current == &start) return 0;
        double str = current->data;
        Node* prev = current->previous_node;
        delete current;
        current = prev;
        return str;
    }

    double peak(){
        return current->data;
    }

    bool is_empty(){
        return current == &start;
    }

};

class Table;
class Cell{
private:
    friend Table;
    Table* table; // 어느 테이블?
    std::string data;
    int x,y; // 테이블 위치
public:
    Cell(std::string _data, int _x, int _y, Table* _t) : data(_data), x(_x), y(_y), table(_t){}
    virtual std::string stringify(){return data;}
    virtual int to_numeric(){return 0;}

private:
};


class Table{
protected:
    Cell *** data_base;
    const int row_size;
    const int col_size;
public:
    Table(const int row_size, const int col_size):row_size{row_size}, col_size(col_size){
        data_base = new Cell**[row_size];
        for(int i =0; i < row_size; i++){
            data_base[i] = new Cell*[col_size];
            for(int j = 0; j < col_size; j++) data_base[i][j] = nullptr;
        }
    }
    ~Table(){
        for(int i = 0; i < row_size; i++) for(int j = 0; j < col_size; j++){
            if(data_base[i][j] != nullptr) delete data_base[i][j];
        }
        for(int i = 0; i < row_size; i++) delete[] data_base[i];
        delete[] data_base;
    }
    virtual std::string print_table() = 0;

    void reg_cell(Cell *c, int row, int col){
        if(row >= row_size || col >= col_size) return;
        if(data_base[row-1][col-1] != nullptr){
            delete data_base[row-1][col-1];
        }
        data_base[row-1][col-1] = c;
    }

    int to_numeric(const std::string& s){
        int col = s[0] - 'A';
        int row = atoi(s.c_str()+1)-1;
        if(col < col_size && row < row_size){
            if(data_base[row][col] != nullptr) return data_base[row][col]->to_numeric();
        }
        return 0;
    }

    int to_numeric(int row, int col){
        if(col < col_size && row < row_size){
            if(data_base[row][col] != nullptr) return data_base[row][col]->to_numeric();
        }
        return 0;
    }

    std::string stringify(const std::string& s){
        int col = s[0] - 'A';
        int row = atoi(s.c_str()+1)-1;
        if(col < col_size && row < row_size){
            if(data_base[row][col] != nullptr) return data_base[row][col]->stringify();
        }
        return "";
    }

    std::string stringify(int row, int col){
        if(col < col_size && row < row_size){
            if(data_base[row][col] != nullptr) return data_base[row][col]->stringify();
        }
        return "";
    }
};

std::ostream& operator<<(std::ostream& os, Table& table){
    os << table.print_table();
    return os;
}

class TextTable : public Table {
private:
public:
    TextTable(const int row_size, const int col_size): Table(row_size, col_size){}
    std::string print_table() override{
        return "";
    }
};
class CSVTable : public Table {
public:
    CSVTable(const int row_size, const int col_size): Table(row_size, col_size){}
    std::string print_table() override{
        return "";
    }
};
class HTMLTable : public Table {
    const std::string table_name = "TextTable";
public:
    HTMLTable(const int row_size, const int col_size): Table(row_size, col_size){}
    std::string print_table() override {
        return "";
    }
};


#endif //MAIN_CPP_EX8_EXCEL_H
