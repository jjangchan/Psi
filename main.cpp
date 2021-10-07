#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

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
    for(auto &s : result.v)m[s]++;
    std::vector<std::string> not_overlap;
    std::vector<std::string> overlap;
    for(auto &pair : m) {
        if(pair.second == 1) not_overlap.push_back(pair.first);
        else overlap.push_back(pair.first);
    }
    for(auto &s : not_overlap) os << s << std::endl;
    os << "=========================================" << std::endl;
    for(auto &s : overlap) os << s << std::endl;
    return os;
}

int main() {
    std::vector<std::string> v = {"abc", "aaaa", "avasd", "cdsff", "aaaa", "dasdfff", "cdsff"};
    ResultPrint result(v);
    std::cout << result;

    //시간복잡도
    // v.size x 1  + m.size + not_overlap.size + overlap.size

    return 1;
}
