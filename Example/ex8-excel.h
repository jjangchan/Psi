//
// Created by jjangchan on 2021-10-21.
//

#ifndef MAIN_CPP_EX8_EXCEL_H
#define MAIN_CPP_EX8_EXCEL_H
#include <string>
#include <sstream>
#include <algorithm>
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
        if(data_base[row][col] != nullptr){
            delete data_base[row][col];
        }
        data_base[row][col] = c;
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
        std::string total_table;
        int *col_max_arr = new int[col_size];
        for(int i = 0; i < col_size; i++){
            unsigned int col_max = 2;
            for(int j = 0; j < row_size; j++){
                if(data_base[j][i] != nullptr){
                    unsigned int col_size = data_base[j][i]->stringify().length();
                    col_max = std::max(col_max, col_size);
                }
            }
            col_max_arr[i] = col_max;
        }

        int *row_max_arr = new int[row_size];
        for(int i = 0; i < row_size; i++){
            unsigned int row_max = 1;
            for(int j = 0; j < col_size; j++){
                if(data_base[i][j] != nullptr){
                    unsigned int row_size = find_count(data_base[i][j]->stringify(), '\n');
                    row_max = std::max(row_max, row_size);
                }
            }
            row_max_arr[i] = row_max;
        }

        //1행 데이터 쌓기
        total_table += "    ";
        int total_width = 4;
        for(int i = 0; i < col_size; i++){
            std::string str_col = col_num_to_str(i);
            std::string repeat = repeat_char(col_max_arr[i]-str_col.size(), ' ');
            total_table += " | "+str_col+repeat;
            total_width += 3+col_max_arr[i];
        }
        // 나머지 행 쌓기
        total_table += "\n";
        for(int i = 0; i < row_size; i++){
            total_table += repeat_char(total_width, '-')+'\n';
            int max_row = row_max_arr[i];
            for(int e = 0; e < max_row; e++){
                total_table += std::to_string(i+1)+ repeat_char(4-std::to_string(i+1).size(), ' ');
                for(int j = 0; j < col_size; j++){
                    int max_col = col_max_arr[j];
                    std::string str = "";
                    if(data_base[i][j] != nullptr) {
                        std::string data = data_base[i][j]->stringify();
                        str = find_str(data, '\n', e);
                    }
                    //std::cout << str << std::endl;
                    total_table += " | "+str+repeat_char(max_col-str.length(), ' ');
                }
                total_table += '\n';
            }
        }
        return total_table;
    }

private:
    std::string repeat_char(int n, char c){
        std::string str = "";
        for(int i = 0; i < n; i++) str.push_back(c);
        return str;
    }
    std::string col_num_to_str(int n){
        std::string str = "";
        if(n < 26) {
           char a = 'A'+n;
           str.push_back(a);
        }
        else{
           char first = 'A'+n/26-1;
           char second = 'A'+n%26;
           str.push_back(first);
           str.push_back(second);
        }
        return str;
    }

    int find_count(const std::string& str, char c){
        int count = 1;
        for(int i = 0; i < str.length(); i++) if(str[i] == c){
            count++;
        }
        return count;
    }

    std::string find_str(const std::string& data, char c, int index){
        std::string s = "";
        int count = 0;
        for(int i = 0; i < data.length(); i++){
            if(data[i] == c){
                count++;
                continue;
            }
           if(count == index) s.push_back(data[i]);
        }
        return s;
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
