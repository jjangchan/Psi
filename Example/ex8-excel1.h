//
// Created by momantic03 on 2021-10-21.
//

#ifndef MAIN_CPP_EX8_EXCEL1_H
#define MAIN_CPP_EX8_EXCEL1_H
#include <string>
#include <sstream>
#include <iostream>

class Table;
class Cell{
private:
    friend Table;
    Table* table; // 어느 테이블?
    std::string data;
    int x,y; // 테이블 위치
public:
    Cell(std::string _data, int _x, int _y, Table* _t) : data(_data), x(_x), y(_y), table(_t){
    }
    Cell& operator=(const Cell& c){
        x = c.x;
        y = c.y;
        return *this;
    }

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
        for(int i = 0; i < col_size; i++) {
            data_base[i] = new Cell*[col_size];
            for(int j = 0; j < col_size; j++) data_base[i][j] = nullptr;
        }

    }
    virtual std::string PrintTable() = 0;

    void RegisterCell(Cell *c, int row, int col){
        if(row > row_size || col > col_size) return;
        if(data_base[row-1][col-1] != nullptr){
            std::cout << "delete cell" << std::endl;
            delete data_base[row-1][col-1];
        }
        std::cout << "insert " << std::endl;
        data_base[row-1][col-1] = c;
    }

    std::string GetCell(int row, int col){
        if(data_base[row][col] == nullptr) return "";
        return  data_base[row][col]->data;
    }  // 해당 위치의 Cell 데이터를 얻는다

};

class TextTable : public Table {
private:
public:
    TextTable(const int row_size, const int col_size): Table(row_size, col_size){}
    std::string PrintTable() override{
        std::ostringstream oss;
        for(int i = 0; i < row_size; i++ ) {
            for (int j = 0; j < col_size; j++) {
                oss << GetCell(i, j) << " | ";
            }
            oss << std::endl;
        }
        return oss.str();
    }
};
class CSVTable : public Table {
public:
    CSVTable(const int row_size, const int col_size): Table(row_size, col_size){}
    std::string PrintTable() override{
        return "";
    }
};
class HTMLTable : public Table {
    const std::string table_name = "TextTable";
public:
    HTMLTable(const int row_size, const int col_size): Table(row_size, col_size){}
    std::string PrintTable() override{
        return "";
    }
};


#endif //MAIN_CPP_EX8_EXCEL1_H
