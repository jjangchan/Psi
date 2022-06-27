//
// Created by jjangchan on 2021/09/24.
//

#ifndef PSI_EX6COMPLEX_H
#define PSI_EX6COMPLEX_H

#include <iostream>
#include <string>

class Complex{
private:
    double real, img;
public:
    Complex(double real, double img):real(real), img(img){std::cout << "constructor : " << this << std::endl;}
    Complex(const Complex& c){real = c.real; img = c.img; std::cout << "copy constructor  : " << this << std::endl; std::cout << "c : " << &c << std::endl; }
    Complex(const char* str) {
        int begin = 0, end = strlen(str);
        img = 0.0;
        real = 0.0;

        //search i
        int pos_i = -1;
        for(int i = 0; i < end; i++) if(str[i] == 'i'){
                pos_i = i;
                break;
            }

        //only real
        if(pos_i == -1){
            real = GetNumber(str, begin, end-1);
            return;
        }

        // if "i" exists,
        real = GetNumber(str, begin, pos_i-1);
        img = GetNumber(str, pos_i+1, end-1);

        if(pos_i >= 1 && str[pos_i-1] == '-') img *= -1.0;
    }
    ~Complex(){}

    //-- 외부함수가 private 접근할 수 있게 friend 키워드 사용
    friend Complex operator+(const Complex& a, const Complex& b);
    friend Complex operator-(const Complex& a, const Complex& b);
    friend Complex operator*(const Complex& a, const Complex& b);
    friend Complex operator/(const Complex& a, const Complex& b);
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    // --

    Complex& operator=(const Complex& c){
        real = c.real;
        img = c.img;
        return *this;
    }

    Complex& operator+=(const Complex& c){
        (*this) = (*this) + c;
        return *this;
    }

    Complex& operator-=(const Complex& c){
        (*this) = (*this) - c;
        return *this;
    }

    Complex& operator/=(const Complex& c){
        (*this) = (*this) / c;
        return *this;
    }

    Complex& operator*=(const Complex& c){
        (*this) = (*this) * c;
        return *this;
    }

    void println() const{
        std::cout << "( " << real << " , " << img << " )" << std::endl;
    }

private:
    double GetNumber(const char* str, int from, int to) const{
        bool minus = false;
        if(from > to) return 0;
        if(str[from] == '-') minus = true;
        if(str[from] == '-' || str[from] == '+') from++;

        double num = 0.0;
        double decimal = 1.0;

        bool integer_part = true;
        for(int i = from; i <= to; i++){
            if(isdigit(str[i]) && integer_part){
                num *= 10.0;
                num += (str[i] - '0');
            }else if(str[i] == '.') integer_part = false;
            else if(isdigit(str[i]) && !integer_part){
                decimal /= 10.0;
                num += ((str[i] - '0')*decimal);
            }else break;
        }
        if(minus) num *= -1.0;
        return num;
    }
};

// 자기 자신을 리턴 하지 않는 operator는 외부함수로 선언 !!
Complex operator+(const Complex& a , const Complex& b) {
    Complex temp(a.real+b.real, a.img+b.img);
    return temp;
}
Complex operator-(const Complex& a, const Complex& b) {
    Complex temp(a.real-b.real, a.img-b.img);
    return temp;
}
Complex operator*(const Complex& a, const Complex& b) {
    Complex temp(a.real * b.real - a.img * b.img, a.real * b.img + a.img * b.real);
    return temp;
}
Complex operator/(const Complex& a, const Complex& b) {
    Complex temp(
            (a.real * b.real + a.img * b.img) / (b.real * b.real + b.img * b.img),
            (a.img * b.real - a.real * b.img) / (b.real * b.real + b.img * b.img));
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Complex& c){
    os << " (  " << c.real << " , " << c.img << " ) ";
    return os;
}

#endif //PSI_EX6COMPLEX_H
