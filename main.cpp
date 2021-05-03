#include <iostream>
#include "Example/Ex1_Reference.h"
#include "Example/Ex2_New_Delete.h"

using namespace std;

int main() {
    Data *data = new Data();

    data->SetData(2020, 12, 31);

    delete data;
    data = nullptr;
    return 0;
}
