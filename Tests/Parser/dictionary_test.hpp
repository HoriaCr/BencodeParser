// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "../../Parser/dictionary.hpp"
#include "test.hpp"

class DictionaryTest : public Test {
    Dictionary value;

    public:
     
    std::pair<bool, Dictionary> decode(const std::string& encoded) {
        char *buffer  = new char[encoded.size()];
        int index = 0;
        int length = static_cast<int>(encoded.size());
        memcpy(buffer, encoded.c_str(), encoded.size());
        bool ret = value.parse(buffer, index, length);
        return std::make_pair(ret, value);    
    }
    
    
    DictionaryTest() {
        test = {
            [&]() -> bool {
                BencodeType* v = new Integer(3);
                BencodeType* l = new List(std::vector<BencodeType*>{v});
                Dictionary d(std::vector< std::pair<std::string, BencodeType*> > {
                    std::make_pair(std::string("berea"), l)
                });
                return decode("d5:bereali3eee") == std::make_pair(true, d);
            },
            [&]() -> bool {
                BencodeType* v = new Integer(30);
                Dictionary d(std::vector< std::pair<std::string, BencodeType*> > {
                    std::make_pair(std::string("k"), v)
                });
                return decode("d1:ki30ee") == std::make_pair(true, d);
            },

            [&]() -> bool {
                BencodeType* v = new ByteString("b");
                Dictionary d(std::vector< std::pair<std::string, BencodeType*> > {
                    std::make_pair(std::string("fun"), v)
                });
                return decode("d3:fun1:be") == std::make_pair(true,d);
            },
            [&]() -> bool {
                return decode("de").first == true;
            },
            [&]() -> bool {
                return decode("ed").first == false;
            }
 
        };
    }
    
    std::string getType() {
        return "Dictionary";
    }
};

