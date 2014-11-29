// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.



#include "integer.hpp"
#include "bytestring.hpp"

class List : public BencodeType  {
        
        std::vector<BencodeType*> data;

    public: 


        void push(BencodeType*);
};



void List::push(BencodeType *value) {
    data.push_back(value);
}
