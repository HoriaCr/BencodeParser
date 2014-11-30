#include <iostream>
#include "integer_test.hpp"


int main() {
    IntegerTester tester;
    
    int testsPassed = tester.runTests();
    std::cout << testsPassed << "\n";
    
    return 0;
}
