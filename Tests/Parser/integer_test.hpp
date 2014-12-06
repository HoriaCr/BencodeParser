// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "../../Parser/integer.hpp"
#include "test.hpp"

class IntegerTest : public Test {
    
    public:

        IntegerTest() {
            test = {
                [&]() -> bool {
                    return decode<Integer>("i42e") == std::make_pair(true, Integer(42LL));
                },
                [&]() -> bool {
                   return decode<Integer>("i0e") == std::make_pair(true, Integer(0LL));   
                },
                [&]() -> bool {
                   return decode<Integer>("i-5e") == std::make_pair(true, Integer(-5LL));
                },
                [&]() -> bool {
                   return decode<Integer>("i-5").first == false;
                },
                [&]() -> bool {
                   return decode<Integer>("ie").first == false;
                },
                [&]() -> bool {
                   return decode<Integer>("ie").first == false;
                },
                [&]() -> bool {
                   return decode<Integer>("le").first == false;
                },
                [&]() -> bool {
                   return decode<Integer>("l--e").first == false;
                },
                [&]() -> bool {
                   return decode<Integer>("l-0e").first == false;
                },
                [&]() -> bool {
                   return decode<Integer>("i100e") == std::make_pair(true, Integer(100LL));   
                },
                [&]() -> bool {
                   return decode<Integer>("i-369e") == std::make_pair(true, Integer(-369LL));
                },
                [&]() -> bool {
                   return decode<Integer>("-5").first == false;
                }
            };
        }

        std::string getType() {
            return "Integer";
        }
};

