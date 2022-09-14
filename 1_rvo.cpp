#include "tracer.hpp"

#include <iostream>

Tracer makeRvoSimpleTracer(const char* name) {
     return Tracer{name};
 }

Tracer makeNrvoSimpleTracer(const char *name) {
    Tracer tracer{name};

    return tracer;
}

Tracer makeNrvoSimpleConstTracer(const char *name) {
    const Tracer tracer{name};

    return tracer; // NOLINT
    
    //                ^^^^^^ the comment disables linter warning
    //                       about copy ctor (move ctor maybe couldn't be used)
}

Tracer makeRvoMediumTracer(const char *name, const int foo) {
    if (foo % 2 == 0) {
        return Tracer{name};
    }

    return Tracer{"other"};
}

Tracer makeNrvoMediumTracer(const char *name, const int foo) {
    if (foo % 2 == 0) {
        Tracer result1{name};

        return result1;
    }
    
    Tracer result2{"other"};
    
    return result2;
}

void test(const int foo) {

    {
        std::cout << "Example 1 \"RVO simple example\":" << std::endl;

        Tracer tracer = makeRvoSimpleTracer("RVO simple tracker");
    }

    {
        std::cout << std::endl;
        std::cout << "Example 2.1 \"NRVO simple example\":" << std::endl;

        Tracer tracer2 = makeNrvoSimpleTracer("NRVO simple tracker");
    }
    
    {
        std::cout << std::endl;
        std::cout << "Example 2.2 \"NRVO simple example with CONST\":" << std::endl;

        Tracer tracer2 = makeNrvoSimpleConstTracer("NRVO simple with CONST tracker");
    }

    {
        std::cout << std::endl;
        std::cout << "Example 3 \"RVO medium\":" << std::endl;

        Tracer tracer3 = makeRvoMediumTracer("RVO medium tracer", foo);
    }

    {
        std::cout << std::endl;
        std::cout << "Example 4 \"NRVO medium\":" << std::endl;

        Tracer tracer4 = makeNrvoMediumTracer("NRVO medium tracer", foo);
    }

    std::cout << std::endl;
    std::cout << "End of the main" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main(const int argc, char *[]) {
    try {
        test(argc);
    } catch (...) {
        std::cout << "Unexpected error" << std::endl;

        return 1;
    }

    return 0;
}