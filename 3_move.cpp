#include "tracer.hpp"

#include <iostream>
#include <string>
#include <vector>

// Move medium
void moveMedium() {
    std::cout << "Move medium:" << std::endl;
    
    std::string value{"Aha-a-a-a-a-a!"};

    std::string value2 = std::move(value);

    std::cout << "  value is: \"" << value << "\" at #" << &value << std::endl; // NOLINT
    
    //                                                   the comment disables linter ^^^^^^
    //                                                   warning about variable usage
    //                                                   after moving

    std::cout << "  value2 is: \"" << value2 << "\" at #" << &value2 << std::endl;
}

#if 0
// Possible implementation of std::move
template <typename T>
typename std::remove_reference<T>::type && move(T &&arg) {
    // Move doesn't move!

    return static_cast<typename std::remove_reference<T>::type &&>(arg);
}
#endif


void handleBigObjectFunc(const std::string &bigObject) {
    // just a reference here - it is not an "temporary" or "moved" object
    
    std::cout << "    handleBigObjectFunc(std::string &) <-- reference" << std::endl;
    std::cout << "       object value: \"" << bigObject << "\"" << std::endl;
    std::cout << "       object address: #" << &bigObject << std::endl;
}


void handleBigObjectFunc(std::string &&bigObject) {
    // r-value reference here - it is a "temporary" or "moved" object
    // r-value - "right" (r) in the name because all it can do is stand on the right
    
    std::cout << "    handleBigObjectFunc(std::string &&) <-- r-value" << std::endl;
    std::cout << "       object value: \"" << bigObject << "\"" << std::endl;
    std::cout << "       object address: #" << &bigObject << std::endl;

    auto local = std::move(bigObject);
    local += "more and more";
}

Tracer makeNrvoMediumTracer(const char* name, const int foo) {
    if (foo % 2 == 0) {
        Tracer result1{name};
        
        return result1;
    }

    Tracer result2{"other"};
        
    return result2;
}


void test(const int foo) {
    std::cout << "Start of the main" << std::endl;

    moveMedium();

    {
        std::cout << "Overload:" << std::endl;
        // Move basic
        std::string bigString{"very very big string"}; // 10 GB!
    
        handleBigObjectFunc(bigString);
        handleBigObjectFunc(std::move(bigString));
        
        std::cout << "    Repeating!" << std::endl;
        handleBigObjectFunc(bigString); // NOLINT
        handleBigObjectFunc(std::move(bigString));
        
        std::cout << "  \"True\" r-value:" << std::endl;
        handleBigObjectFunc("\"true\" r-value content");
    }

    {
        std::cout << "Big:" << std::endl;
        
        Tracer bigTracer{"bigTracer1"}; // 10 GB again here!
        Tracer otherTracer{"otherTracer"};  // Small object

        otherTracer = bigTracer; // Already 20 GB here!

        otherTracer = std::move(bigTracer); // maybe only 10 GB here

        const Tracer moveTracer = makeNrvoMediumTracer("moveTracer", foo);
    }
   
    std::cout << "In vector:" << std::endl;
   
    std::vector<Tracer> vector;
    
    vector.emplace_back("1 (emplace_back)");
    vector.emplace_back("2 (emplace_back)");
    
    vector.push_back(Tracer("3 (push back)")); // NOLINT
    vector.push_back(Tracer("4 (push back)")); // NOLINT
    vector.push_back(Tracer("5 (push back)")); // NOLINT

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