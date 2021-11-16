#include <string>
#include <iostream>
#include <fstream>
#include "Example/ex8-excel.h"

int main() {
    std::string s = "2021-11-16";
    int year = std::atoi(s.c_str());
    int month = std::atoi(s.c_str()+5);
    int day = std::stoi(s.c_str()+8);
    std::cout << year << " " << month << " " << day << std::endl;
    return 0;
    CSVTable table(5,5);
    std::ofstream out("test.csv");
    table.reg_cell(new StringCell("Hello~", 0, 0, &table));
    table.reg_cell(new StringCell("C++", 0, 1, &table));
    table.reg_cell(new StringCell("Programming", 1, 1, &table));
    out << table;
    return 1;
}
