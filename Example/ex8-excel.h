//
// Created by jjangchan on 2021-10-21.
//

#ifndef MAIN_CPP_EX8_EXCEL_H
#define MAIN_CPP_EX8_EXCEL_H
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cmath>
#include <fstream>

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

    std::string peek(){
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
protected:
    friend Table;
    Table* table; // 어느 테이블?
    int x,y; // 테이블 위치
public:
    virtual std::string stringify() = 0;
    virtual double to_numeric() = 0;
    Cell(int _x, int _y, Table* _t) : x(_x), y(_y), table(_t){}
};

class StringCell : public Cell {
private:
    std::string data;
public:
    StringCell(std::string data, int x, int y, Table* t) : data(data), Cell(x, y, t){}
    std::string stringify() override {return data;}
    double to_numeric() override {return 0;}
};

class NumberCell: public Cell {
private:
    double data;
public:
    NumberCell(int data, int x, int y, Table* t) : data(data), Cell(x, y, t){}
    std::string stringify() override {return std::to_string(data);}
    double to_numeric() override {return data;}
};

class DateCell: public Cell{
private:
    time_t data;
public:
    DateCell(std::string s, int x, int y, Table* t) : Cell(x, y, t){
        int year = std::atoi(s.c_str());
        int month = std::atoi(s.c_str()+5);
        int day = std::stoi(s.c_str()+8);

        tm timeinfo;

        timeinfo.tm_year = year- 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = 0;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;

        data = mktime(&timeinfo);
    }

    std::string stringify() override{
        char buf[50];
        tm temp;
        localtime_s(&temp, &data);
        strftime(buf, 50, "%F", &temp);
        return std::string(buf);
    }

    double to_numeric() override {return static_cast<int>(data);}
};

class ExprCell: public Cell{
private:
    std::string data;
    //std::string* parsed_expr;
    Vector expr_v;

    // 연산자 우선순위 반환
    int precedence(char c){
        switch (c) {
            case '(':
            case '[':
            case '{':
                return 0;
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
        }
        return 0;
    }

    // 수식 분석
    void parse_expression(){
        // 수식 전체 () 감싸기
        // 남아있는 연산자 push
        data.insert(0, "(");
        data.push_back(')');

        Stack stack;
        for(int i = 0; i < data.length(); i++){
            if(isalpha(data[i])){
                std::string str = "";
                while(isalpha(data[i]) || isdigit(data[i])){
                    str.push_back(data[i]);
                    i++;
                }
                i--;
                expr_v.push_back(str);
            }else if(isdigit(data[i])){
                int count = is_number(i);
                expr_v.push_back(data.substr(i, count));
                i += count-1;
            }else if(data[i] == '{' || data[i] == '(' || data[i] == '['){
                stack.push(data.substr(i,1));
            }else if(data[i] == '}' || data[i] == ')' || data[i] == ']'){
                std::string str = stack.pop();
                while(str[0] != '{' && str[0] != '(' && str[0] != '['){
                    expr_v.push_back(str);
                    str = stack.pop();
                }
            }else if(data[i] == '*' || data[i] == '+' || data[i] == '-' || data[i] == '/'){
                while(!stack.is_empty() && precedence(stack.peek()[0]) >= precedence(data[i])){
                    expr_v.push_back(stack.pop());
                }
                stack.push(data.substr(i,1));
            }
        }
    }

    int is_number(const int start = 0){
        bool integer_part = true;
        int count = 0;
        for(int i = start; i < data.length(); i++){
            if(integer_part && data[i] == '.'){
                    if(i == 0 || i == data.length()-1) return count;
                    integer_part = false;
            }
            else if(!isdigit(data[i])) return count;
            count++;
        }
        return count;
    }

public:
    ExprCell(std::string data, int x , int y, Table* t) : data(data), Cell(x, y, t){}
    ~ExprCell(){
        //if(parsed_expr != nullptr) delete parsed_expr;
    }

    std::string stringify() override{
        parse_expression();
        data = std::to_string(to_numeric());
        return data;
    }
    double to_numeric() override;

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

    void reg_cell(Cell *c){
        if(c->x >= row_size || c->y >= col_size) return;
        if(data_base[c->x][c->y] != nullptr){
            delete data_base[c->x][c->y];
        }
        data_base[c->x][c->y] = c;
    }

    double to_numeric(const std::string& s){
        int index = 0;
        int array[s.length()];
        for(int i = 0; i < s.length(); i++){
            if(!isalpha(s[i])) break;
            array[i] = s[i]-'A'+1;
            index++;
        }
        int col = 0;
        for(int i = 0; i < index; i++) col += (static_cast<int>(array[i]*std::pow(26, index-(i+1))));
        col -= 1;
        int row = atoi(s.c_str()+index)-1;
        if(col < col_size && row < row_size){
            if(data_base[row][col] != nullptr) return data_base[row][col]->to_numeric();
        }
        return 0;
    }

    double to_numeric(int row, int col){
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

        // col 최대 사이즈 체크
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

        // row 최대 사이즈 체크
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
            for(int e = 0; e < max_row; e++){ // row 최대 사이즈 만큼 for 문 돌림
                std::string str_num = (e != 0) ? "" : std::to_string(i+1);
                total_table += str_num+ repeat_char(4-str_num.size(), ' ');
                for(int j = 0; j < col_size; j++){
                    int max_col = col_max_arr[j];
                    std::string str = "";
                    if(data_base[i][j] != nullptr) {
                        std::string data = data_base[i][j]->stringify();
                        str = find_str(data, '\n', e); // 개행문자 끊기
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
        std::string s = "";
        for (int i = 0; i < row_size; i++) {
            for (int j = 0; j < col_size; j++) {
                if (j >= 1) s += ",";
                // CSV 파일 규칙에 따라 문자열에 큰따옴표가 포함되어 있다면 "" 로
                // 치환하다.
                std::string temp;
                if (data_base[i][j]) temp = data_base[i][j]->stringify();

                for (int k = 0; k < temp.length(); k++) {
                    if (temp[k] == '"') {
                        // k 의 위치에 " 를 한 개 더 집어넣는다.
                        temp.insert(k, 1, '"');

                        // 이미 추가된 " 를 다시 확인하는 일이 없게 하기 위해
                        // k 를 한 칸 더 이동시킨다.
                        k++;
                    }
                }
                temp = '"' + temp + '"';
                s += temp;
            }
            s += '\n';
        }
        return s;
    }
};
class HTMLTable : public Table {
public:
    HTMLTable(const int row_size, const int col_size): Table(row_size, col_size){}
    std::string print_table() override {
        std::string table = "<table border='1' cellpadding='10'>";
        for(int i = 0; i < row_size; i++){
            table += "<tr>";
            for(int j = 0; j < col_size; j++){
                table += "<td>";
                if(data_base[i][j] != nullptr) table += data_base[i][j]->stringify();
                table += "</td>";
            }
            table += "</tr>";
        }
        table += "</table>";
        return table;
    }
};

double ExprCell::to_numeric() {
    NumStack stack;
    for(int i = 0; i < expr_v.size(); i++){
        std::string str = expr_v[i];

        //Cell(A1, B1...)
        if(isalpha(str[0])) stack.push(table->to_numeric(str));
        // Number 일 경우
        else if(isdigit(str[0])) stack.push(atof(str.c_str()));
        else{
            double y = stack.pop();
            double x = stack.pop();
            switch (str[0]) {
                case '+':
                    stack.push(x+y);
                    break;
                case '-':
                    stack.push(x-y);
                    break;
                case '*':
                    stack.push(x*y);
                    break;
                case '/':
                    stack.push(x/y);
                    break;
            }
        }
    }
    return stack.pop();
}

#endif //MAIN_CPP_EX8_EXCEL_H
