// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "../../Parser/dictionary.hpp"
#include "test.hpp"

class DictionaryTest : public Test {

    public:   
    
        DictionaryTest() {
            test = {
                [&]() -> bool {
                    BencodeType* v = new Integer(3);
                    BencodeType* l = new List(std::vector<BencodeType*>{v});
                    Dictionary d(std::vector< std::pair<std::string, BencodeType*> > {
                        std::make_pair(std::string("berea"), l)
                    });
                    return decode<Dictionary>("d5:bereali3eee") == std::make_pair(true, d);
                },
                [&]() -> bool {
                    BencodeType* v = new Integer(30);
                    Dictionary d(std::vector< std::pair<std::string, BencodeType*> > {
                        std::make_pair(std::string("k"), v)
                    });
                    return decode<Dictionary>("d1:ki30ee") == std::make_pair(true, d);
                },

                [&]() -> bool {
                    BencodeType* v = new ByteString("b");
                    Dictionary d(std::vector< std::pair<std::string, BencodeType*> > {
                        std::make_pair(std::string("fun"), v)
                    });
                    return decode<Dictionary>("d3:fun1:be") == std::make_pair(true,d);
                },
                [&]() -> bool {
                    return decode<Dictionary>("de").first == true;
                },
                [&]() -> bool {
                    return decode<Dictionary>("ed").first == false;
                }
     
            };
        }
        
        std::string getType() {
            return "Dictionary";
        }
};

