#include "../../Parser/integer.hpp"
#include <iostream>
#include <functional>
#include <cstring>

class IntegerTester {
    
        Integer value;
        std::vector< std::function<bool()> > test;

    public:

        IntegerTester() {
            test = {
                [&]() -> bool {
                    return decode("i42e") == std::make_pair(true, 42LL);
                },
                [&]() -> bool {
                   return decode("i0e") == std::make_pair(true, 0LL);   
                },
                [&]() -> bool {
                   return decode("i-5e") == std::make_pair(true, -5LL);
                },
                [&]() -> bool {
                   return decode("i-5").first == false;
                },
                [&]() -> bool {
                   return decode("ie").first == false;
                },
                [&]() -> bool {
                   return decode("ie").first == false;
                },
                [&]() -> bool {
                   return decode("le").first == false;
                },
                [&]() -> bool {
                   return decode("l--e").first == false;
                },
                [&]() -> bool {
                   return decode("l-0e").first == false;
                },
                [&]() -> bool {
                   return decode("i100e") == std::make_pair(true, 100LL);   
                },
                [&]() -> bool {
                   return decode("i-369e") == std::make_pair(true, -369LL);
                },
                [&]() -> bool {
                   return decode("-5").first == false;
                }
            };

         
        }

        std::pair<bool, long long> decode(const std::string& encoded) {
            char *buffer  = new char[encoded.size()];
            int index = 0;
            int length = static_cast<int>(encoded.size());
            memcpy(buffer, encoded.c_str(), encoded.size());
            bool ret = value.parse(buffer, index, length);
            return std::make_pair(ret, value.getValue());
        }

        int runTests() {

           int testsPassed = 0;
            for (size_t i = 0; i < test.size(); i++) {
                if (!test[i]()) {
                    std::cerr << "Failed Integer Test # " << i << "\n";
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

