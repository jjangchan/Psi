
#include <iostream>
#include "Example/ex11-tmp.h"

int main() {
    std::cout << std::boolalpha;
    std::cout << "Is 2 prime ? :: " << is_prime<2>::result << std::endl;
    std::cout << "Is 10 prime ? :: " << is_prime<10>::result << std::endl;
    std::cout << "Is 11 prime ? :: " << is_prime<11>::result << std::endl;
    std::cout << "Is 61 prime ? :: " << is_prime<61>::result << std::endl;
    return 0;
}
