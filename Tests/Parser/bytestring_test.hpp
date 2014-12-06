// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "../../Parser/bytestring.hpp"
#include "test.hpp"

class BytestringTest : public Test {

    public:
    
        BytestringTest() {
            test = {
                [&]() -> bool {
                    return decode<ByteString>("5:berea") == std::make_pair(true,ByteString(std::string("berea")));
                },
                [&]() -> bool {
                    return decode<ByteString>("1:k") == std::make_pair(true,ByteString(std::string("k")));
                },

                [&]() -> bool {
                    return decode<ByteString>("3:fun") == std::make_pair(true,ByteString(std::string("fun")));
                },

                [&]() -> bool {
                    return decode<ByteString>("3fun").first == false;
                },
                [&]() -> bool {
                    return decode<ByteString>("5:fun").first == false;
                }
     
            };
        }

        std::string getType() {
            return "ByteString";
        }

};
