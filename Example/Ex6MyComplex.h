//
// Created by momantic03 on 2021-09-23.
//

#ifndef EX2_NEW_DELETE_H_EX6MYCOMPLEX_H
#define EX2_NEW_DELETE_H_EX6MYCOMPLEX_H
class Complex{
private:
    double real, img;
public:
    Complex(double real, double img): real(real), img(img){}
    Complex(const Complex& c){real = c.real; img = c.img}
    ~Complex(){}

    Complex operator+(const Complex& c) const{
        Complex temp(real+c.real, img+c.img);
        return temp;
    }
};

#endif //EX2_NEW_DELETE_H_EX6MYCOMPLEX_H
