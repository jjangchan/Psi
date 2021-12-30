#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>
#include <map>
#include <algorithm>

long elapsed_time1;
long elapsed_time2;

class ResultPrint{
private:
    std::vector<std::string> v;
public:
    ResultPrint(std::vector<std::string> v) : v(v){}
    ResultPrint(const ResultPrint& result): v(result.v){}
    ~ResultPrint(){}
    friend std::ostream& operator<<(std::ostream& os, const ResultPrint& result);
};

std::ostream &operator<<(std::ostream &os, const ResultPrint &result) {
    std::unordered_map<std::string, int> m;
    for(auto &s : result.v)m[s]++; // v.size + v.size = 2(v.size)
    std::vector<std::string> not_overlap;
    std::vector<std::string> overlap;
    not_overlap.reserve(m.size());
    overlap.reserve(m.size());
    for(auto &pair : m) { // m.size
        if(pair.second == 1) not_overlap.push_back(pair.first); // m.size + (1 * m.size) = 2(m.size)
        else overlap.push_back(pair.first);
    }
    // 2(v.size) + 2(m.size)
    // Big-O = O(v.size + m.size)
    for(auto &s : not_overlap) os << s << std::endl;
    os << "=========================================" << std::endl;
    for(auto &s : overlap) os << s << std::endl;
    return os;
}

void Test1(std::vector<std::string> v){
    auto start = std::chrono::steady_clock::now();
    std::map<std::string, int> m1;
    std::map<std::string, int> m2;
    std::map<std::string, int> m3;
    for(auto &str : v){
        if(m1.find(str) == m1.end()){
            m1[str]++;
            m2[str]++;
        }else{
           m3[str]++;
           if(m2.find(str) != m2.end()){
               m2.erase(str);
           }
        }
    }
    for(auto &pair : m2) std::cout << pair.first << std::endl;
    std::cout << "=============================================" << std::endl;
    for(auto &pair : m3) std::cout << pair.first << std::endl;
    auto end = std::chrono::steady_clock::now();
    elapsed_time1 = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

}

void Test2(std::vector<std::string> v){
    auto start = std::chrono::steady_clock::now();
    std::unordered_map<std::string, int> m;
    for(auto &s : v)m[s]++;
    std::vector<std::string> not_overlap;
    std::vector<std::string> overlap;
    for(auto &pair : m) {
        if(pair.second == 1) not_overlap.push_back(pair.first);
        else overlap.push_back(pair.first);
    }
    for(auto &s : not_overlap) std::cout << s << std::endl;
    std::cout << "=========================================" << std::endl;
    for(auto &s : overlap) std::cout << s << std::endl;
    auto end = std::chrono::steady_clock::now();
    elapsed_time2 = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
}

int main() {
    std::vector<std::string> v;
    for(int i = 0; i < 100000; i++)
        v.push_back("aaaaaaaaaaaaaaaaa"+std::to_string(i));
    for(int i =0; i < 100000; i++)
        if(i%5 == 0) v[i] = "aaaaaaaaaaaaaaaaa"+std::to_string(1);
    Test1(v);
    Test2(v);
    std::cout << "[TEST1] elapsed time : " << elapsed_time1 << std::endl;
    std::cout << "[TEST2] elapsed time : " << elapsed_time2 << std::endl;
    //ResultPrint result(v);
    //std::cout << result;

}
