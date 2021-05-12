#include <iostream>
#include "Example/Ex1_Reference.h"
#include "Example/Ex2_New_Delete.h"

using namespace std;

int main() {
    Date*date= new Date();


    date->SetDate(2011, 11, 29);
    date->AddDay(520);

    delete date;
    date = nullptr;
    return 0;
}
