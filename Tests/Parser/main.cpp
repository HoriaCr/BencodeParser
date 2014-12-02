#include <iostream>
#include "integer_test.hpp"
#include "bytestring_test.hpp"

int main() {
    IntegerTest test1; 
    std::cout <<  test1.runTests() << "\n";
    BytestringTest test2;
    std::cout <<  test2.runTests() << "\n";

    return 0;
}
