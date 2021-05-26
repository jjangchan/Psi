#include "Example/Ex3_Math.h"


int Factorial(int value, int num){
    if(num <= 1) return  value;
    return Factorial(value*(--num), num);
}


int CalculateN(const int n, const int r, const int value = 1){
    if(0 >= r) return  value;
    return CalculateN(n-1, r-1, value*n);
}

int Combination(int n, int r){
    int rum = r;
    return CalculateN(n, r)/ Factorial(rum, rum);
}


int main() {
    Point point1 = Point(0, 0);
    Point point2 = Point(3, 4);
    Point point3 = Point(2, 5);
    Point point4 = Point(10, 5);
    Point point5 = Point(15, 5);
    Geometry *geometry = new Geometry();
    geometry->AddPoint(point1);
    geometry->AddPoint(point2);
    geometry->AddPoint(point3);
    geometry->AddPoint(point4);
    geometry->AddPoint(point5);
    //geometry->PrintDistance();

    geometry->PrintNumMeets();
    return 0;
}
