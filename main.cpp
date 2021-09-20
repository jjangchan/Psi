#include "Example/Ex5MyString.h"

template <typename T>
void println(T *t, int data_size)
{
    for(int i = 0; i < data_size; i++) std::cout << t[i] << std::endl;
}
int main() {
    double *d = new double[100];
    for(int i = 0; i < 100; i++) d[i] = i;
    println(d, 100);

    delete d;
    return 0;
}