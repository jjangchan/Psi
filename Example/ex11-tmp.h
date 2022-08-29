//
// Created by jjangchan on 2022/07/26.
//

#ifndef MAIN_CPP_EX11_TMP_H
#define MAIN_CPP_EX11_TMP_H

template<int N>
struct Factorial{
    static const int result = N*Factorial<N-1>::result;
};

template<>
struct Factorial<1>{
    static const int result = 1;
};

template<int A, int B>
struct gcd{
    static const int result = gcd<B,A%B>::result;
};

template<int A>
struct gcd<A,0>{
    static const int result = A;
};

template<int N, int D = 1>
struct Ratio{
    typedef Ratio<N, D> type;
    static const int num = N;
    static const int den= D;
};

template <class R1, class R2>
struct _Ratio_add{
    typedef Ratio<R1::num*R2::den+R2::num*R1::num, R1::num*R2::num> type;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1,R2>::type{};

template <int N>
struct fibonacci{
    static const int value = (fibonacci<N-2>::value+fibonacci<N-1>::value)%1234567;
};

template<>
struct fibonacci<1>{
   static const int value = 1;
};

template<>
struct fibonacci<2>{
    static const int value = 1;
};

#endif //MAIN_CPP_EX11_TMP_H
