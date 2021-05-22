#include <iostream>
//#include "Example/Ex1_Reference.h"
//#include "Example/Ex2_New_Delete.h"

using namespace std;

double Calculate(const double x,
                 const int end,
                 const double weight,
                 const double value = 0){
    if(x >= end)
        return value;
    double numerator = 1;
    double calculate_x = pow(x, 2);
    double denominator = calculate_x + 1;
    double fx = numerator/denominator;
    return Calculate(x+weight, end, weight,value+(weight*fx));
}

int main() {
    int a = 0;
    int b = 1;
    double emphasis = 1.0/2.0;

    for(int n=5; n<=100; n++){
        double weight = (double)(b-a)/(double)n;
        double x = weight*emphasis;
        weight = x * 2.0;
        double value = Calculate(x, b, weight);
        cout << value << endl;
    }

    //Data *data = new Data();
    //data->SetData(2020, 12, 31);
    //delete data;
    //data = nullptr;
    //return 0;
}
