
#include "tracer.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void sendValueToRemoveHost(const Tracer &) {
    std::cout << "Tracer was sent" << std::endl;
    // Here tracer value should be destroyed - we don't need it now.
}

void test() {

    std::cout << "Start of the main" << std::endl;

    // Example 1 - we want to move, not to copy and not reference!
    Tracer veryBigObject{"Some very very very long string"}; // 10 GB
    sendValueToRemoveHost(veryBigObject);

    // Example 2 - we want to move, not to copy!
    std::vector<Tracer> tracers;
    for (int i = 0; i < 3; ++i) {
        std::stringstream valueName;
        valueName << "value for vector at " << i;

        Tracer value{valueName.str()};

        value.DoSomeAction();

        tracers.push_back(value);
    }

    std::cout << "End of the main" << std::endl;

    // free 10 GB only here
}

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