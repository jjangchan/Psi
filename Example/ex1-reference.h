//
// Created by jjangchan on 2021-04-30.
//

#ifndef PSI_EX1_REFERENCE_H
#define PSI_EX1_REFERENCE_H

#include <iostream>

using namespace std;

void ArrayFunction(int (&array)[3])
{
    for(int i=0; i<3; i++)
    {
        cout << array[i] << endl;
    }
}

int ReferFunction(int &a)
{
    a = 3;
    return  a;
}

void Start()
{
    int a = 5;

    int b = ReferFunction(a);

    cout << a << endl;
    cout << b << endl;
}
#endif //PSI_EX1_REFERENCE_H
