#include <string>
#include <iostream>
#include <fstream>
#include "Example/ex8-excel.h"

int main() {
    CSVTable table(5,5);
    std::ofstream out("test.csv");
    table.reg_cell(new Cell("H""ello~", 0, 0, &table));
    table.reg_cell(new Cell("C++", 0, 1, &table));
    table.reg_cell(new Cell("Programming", 1, 1, &table));
    out << table;
    return 1;
}
