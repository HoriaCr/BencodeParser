// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include <iostream>
#include "integer_test.hpp"
#include "bytestring_test.hpp"
#include "list_test.hpp"
#include "dictionary_test.hpp"

int main() {
    std::vector< Test*> tests = {
        new IntegerTest(), new BytestringTest(), new ListTest(),  new DictionaryTest() 
    };

    bool testsFailed = false;
    for (auto& test : tests) {
        if (test->runTests() != test->size()) {
            testsFailed = false;
        }
    }
    if (testsFailed == false) {
        std::cout << "Tests Passed\n";
    }
    return 0;
}
