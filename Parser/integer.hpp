// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "bencodetype.hpp"

#pragma once

class Integer : public BencodeType {
        long long data;

    public: 

        bool parse(char*,int&,const int&);
};


bool Integer::parse(char *buffer,int &index, const int& length) {
    int sgn = 1;
    if (buffer[index] == '-') {
        sgn = -1;
        index++;
    }
    
    data = 0;

    while (index < length && isdigit(buffer[index])) {
        data = data * 10 + (buffer[index++] - '0');
    }

    // invalid bencode format
    if (index == length) {
        return false;
    }
    
    data *= sgn;

    return true;
}
