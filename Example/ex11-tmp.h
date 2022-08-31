//
// Created by jjangchan on 2022/07/26.
//

#ifndef MAIN_CPP_EX11_TMP_H
#define MAIN_CPP_EX11_TMP_H

//==============================================================================================
// factorial
template<int N>
struct Factorial{
    static const int result = N*Factorial<N-1>::result;
};

template<>
struct Factorial<1>{
    static const int result = 1;
};
//==============================================================================================

//==============================================================================================
// gcd
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
//==============================================================================================

template <class R1, class R2>
struct _Ratio_add{
    typedef Ratio<R1::num*R2::den+R2::num*R1::num, R1::num*R2::num> type;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1,R2>::type{};

//==============================================================================================
// fibonacci
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
//==============================================================================================

//==============================================================================================
// prime

template<int N>
struct INT{
    const static int num = N;
};

template<typename a, typename b>
struct add{
    typedef INT<a::num+b::num> result;
};

template<typename a, typename b>
struct divide{
    typedef INT<a::num/b::num> result;
};

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

template<typename N, typename d>
struct check_div{
    static const bool result = (N::num % d::num == 0) || check_div<N, typename add<d, one>::result>::result;
};

template<typename N>
struct check_div<N, typename divide<N, two>::result>{
   static const bool result = (N::num % (N::num/2) == 0);
};

template<typename N>
struct _is_prime{
    const static bool result = !check_div<N, two>::result;
};

template <>
struct _is_prime<two>{
    const static bool result = true;
};

template <>
struct _is_prime<three>{
    const static bool result = true;
};


template<int N>
struct is_prime{
    const static bool result = _is_prime<INT<N>>::result;
};


//==============================================================================================

#endif //MAIN_CPP_EX11_TMP_H
