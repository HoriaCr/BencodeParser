#include <vector>
#include <iostream>
#include <functional>
#include <cstring>

#pragma once

class Test {

    protected:
        std::vector< std::function<bool()> > test;
    
    public:

        virtual std::string getType() {
            return "Generic";
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
