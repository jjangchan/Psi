#include "Example/ex8-excel.h"
#include <vector>
#include <iostream>
#include <map>
#include <string>


int main() {
    std::multimap<int, int> m;
    m.insert(std::make_pair(1,1));
    m.insert(std::make_pair(1,2));
    m.insert(std::make_pair(1,3));
    m.insert(std::make_pair(1,1));
    m.insert(std::make_pair(2,1));
    std::multimap<int, int>::iterator range = m.equal_range(1).first;
    for(; range != m.equal_range(1).second; ++range)
        std::cout << range->first << " : " << range->second << std::endl;



    return 0;
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
