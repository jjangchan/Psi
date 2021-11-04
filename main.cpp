#include <string>
#include <iostream>
#include <fstream>
#include "Example/ex8-excel.h"

int main() {

    TextTable table(5, 5);
    std::ofstream out("test.txt");

    table.reg_cell(new Cell("Hello~\n~~", 0, 0, &table), 0, 0);
    table.reg_cell(new Cell("C++", 0, 1, &table), 0, 1);

    table.reg_cell(new Cell("Programming", 1, 1, &table), 1, 1);
    std::cout << std::endl << table;
    //out << table;
    return 1;
}
