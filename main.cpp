#include "Example/ex8-excel.h"

int main() {
    TextTable table(5, 5);
    table.reg_cell(new NumberCell(2, 1, 1, &table));
    table.reg_cell(new NumberCell(3, 1, 2, &table));

    table.reg_cell(new NumberCell(4, 2, 1, &table));
    table.reg_cell(new NumberCell(5, 2, 2, &table));
    table.reg_cell(new ExprCell("B2+B3*(C2+C3-2)", 3, 2, &table));
    table.reg_cell(new StringCell("B2 + B3 * ( C2 + C3 - 2 ) = ", 3, 1, &table));

    std::cout << table;
    return 1;
}
