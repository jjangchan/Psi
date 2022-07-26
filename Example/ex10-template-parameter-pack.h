//
// Created by jjangchan on 2022/07/11.
//

#ifndef MAIN_CPP_EX10_TEMPLATE_PARAMETER_PACK_H
#define MAIN_CPP_EX10_TEMPLATE_PARAMETER_PACK_H

#include <iostream>
#include <vector>
#include <string>

// ======================================================= None-type template argument
template<typename Cont, typename Comp>
void merge_sort(Cont& cont, const Comp& comp){
    if(cont.size() > 1){
        int center = cont.size()/2;
        Cont l_cont(cont.begin(), cont.begin()+center);
        Cont r_cont(cont.begin()+center, cont.end());
        merge_sort(l_cont, comp);
        merge_sort(r_cont, comp);
        int l_c = 0, r_c =0 , d_c = 0;
        while(l_c < l_cont.size() && r_c < r_cont.size()){
            if(comp(l_cont[l_c], r_cont[r_c])){
                cont[d_c] = l_cont[l_c];
                l_c++;
            }else{
                cont[d_c] = r_cont[r_c];
                r_c++;
            }
            d_c++;
        }
        Cont& temp = (l_c < l_cont.size()) ? l_cont : r_cont;
        for(int i = (l_c < l_cont.size()) ? l_c : r_c; i < temp.size(); i++, d_c++)
            cont[d_c] = temp[i];
    }
}

template<typename T>
struct Compare{
    bool operator()(const T& a, const T&b){return a<b;}
};

// ======================================================= default template argument
template<typename T, typename Comp = Compare<T>>
T min(T a, T b){
    Comp comp;
    return comp(a,b) ? a : b;
}

// ======================================================= variadic template
template<typename T>
void print(T arg){
    std::cout << arg << std::endl;
}

template<typename T, typename... Ts>
void print(T arg, Ts... args){
    std::cout << arg << ", ";
    print(args...);
}

// ======================================================= variadic template
size_t GetStrSize(const char* c){return strlen(c);}
size_t GetStrSize(const std::string* s){return s->size();}

template<typename String, typename... Ss>
size_t GetStrSize(const String& s, Ss... ss){
    return GetStrSize(s)+ GetStrSize(ss...);
}

void AppendStr(const std::string* target){return;}

template<typename String, typename... Ss>
void AppendStr(std::string* target, const String& s, Ss... ss){
    target->append(s);
    AppendStr(target, ss...);
}

template<typename String, typename... Ss>
std::string StrCat(const String& s, Ss... ss){
    int all_size = GetStrSize(s, ss...);
    std::string str;
    str.reserve(all_size);
    str = s;
    AppendStr(&str, ss...);
    return str;
}

// ======================================================= sizeof...

int Sum(int num){return num;}

template<typename... NUMS>
int Sum(int num, NUMS... ns){
    return num + Sum(ns...);
}

template<typename... NUMS>
double Average(NUMS... ns){
    return static_cast<double>(Sum(ns...))/sizeof...(ns);
}

// ======================================================= fold expression
template<typename... Ints>
int FoldSum(Ints... ints){
    return (...+ints);
}

class A{
public:
        void print(int x) const{
            std::cout << "x : " << x << std::endl;
        }
};

template<typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums){
    (t.print(nums) ,...);
}


#endif //MAIN_CPP_EX10_TEMPLATE_PARAMETER_PACK_H
