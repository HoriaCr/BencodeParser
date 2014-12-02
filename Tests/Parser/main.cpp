// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


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
