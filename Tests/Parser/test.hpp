// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include <vector>
#include <iostream>
#include <functional>
#include <cstring>

#pragma once

class Test {

    protected:
        std::vector< std::function<bool()> > test;
   
        template<class DataType> 
        std::pair<bool,DataType> decode(const std::string& encoded) {
            DataType value;
            char *buffer  = new char[encoded.size()];
            int index = 0;
            int length = static_cast<int>(encoded.size());
            memcpy(buffer, encoded.c_str(), encoded.size()); 
            bool ret = value.parse(buffer, index, length); 
            return std::make_pair(ret, value);    
        }
 
    public:

        virtual std::string getType() {
            return "Generic";
        }

        unsigned int size() const {
            return test.size();
        }

        unsigned int runTests() {
            unsigned int testsPassed = 0;
            for (size_t i = 0; i < test.size(); i++) {
                if (!test[i]()) {
                    std::cerr << "Failed " << getType() << " Test # " << i << "\n";
                } else {
                    testsPassed++;
                }
            }

            return testsPassed;
        }

        bool runTest(const unsigned int& index) {
            return (index < test.size() && test[index]());
        }
};
