
#include "tracer.hpp"

#include <iostream>
#include <string>
#include <vector>

void testFunc(const int testNo, const std::string &) {
    std::cout << testNo << " reference: testFunc(std::string &)" << std::endl;
}

void testFunc(const int testNo, std::string &&) {
    std::cout << testNo << " r-value: testFunc(std::string &&)" << std::endl;
}

void test() {
    std::string var = "some variable value";

    auto varCopy = var; // std::string
    testFunc(1, varCopy);

    const auto &varRef = var; // std::string &
    testFunc(2, varRef);

    auto &&varRvalue = var;
    testFunc(3, varRvalue);

    testFunc(4, std::move(var));

    auto &&varMove = std::move(varCopy);

    testFunc(5, varMove);
    
    testFunc(6, std::forward<std::string>(varMove));
}

#if 0
// Possible implementation of std::forward
template<typename T>
T && forward(remove_reference_t<T> &arg) {
    return static_cast<T &&>(arg);
}
#endif

////////////////////////////////////////////////////////////////////////////////

int main(const int, char *[]) {
    try {
        test();
    } catch (...) {
        std::cout << "Unexpected error" << std::endl;

        return 1;
    }

    return 0;
}
