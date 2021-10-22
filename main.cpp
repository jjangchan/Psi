#include "Example/ex8-excel1.h"
#include <iostream>

int main() {
    Table *csv = new TextTable(2, 2);
    Cell* c1 = new Cell("b", 2, 2, csv);
    Cell* c2 = new Cell("a", 1, 1, csv);
    csv->RegisterCell(c1, 2, 2);
    csv->RegisterCell(c2, 1, 1);
    std::cout << csv->PrintTable();
    return 1;
}
