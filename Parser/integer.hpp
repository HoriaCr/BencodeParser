// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "bencodetype.hpp"

#pragma once

class Integer : public BencodeType {
        long long data;

    public: 
        
        Integer();

        ~Integer();

        Integer(const Integer&);

        Integer& operator = (const Integer&);

        bool parse(char*,int&,const int&);

        BencodeType *clone();
};
    
Integer::Integer() {
    data = 0;
}

Integer::~Integer() { 

}

Integer::Integer(const Integer& other) {
    data = other.data;
}


Integer& Integer::operator = (const Integer& other) {
    if (&other == this) {
        return *this;
    }

    data = other.data;

    return *this;
}

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

BencodeType* Integer::clone() {
    return new Integer(*this);
}   
