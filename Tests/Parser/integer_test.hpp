// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "../../Parser/integer.hpp"
#include "test.hpp"

class IntegerTest : public Test {
    
        Integer value;
    
    public:

        IntegerTest() {
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

        std::string getType() {
            return "Integer";
        }
};

