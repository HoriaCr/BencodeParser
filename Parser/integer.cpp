// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "integer.hpp"

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

bool Integer::operator == (const long long& value) const {
    return data == value;
}

bool Integer::operator == (const Integer& other) const { 
    return data == other.data;
}

bool Integer::operator != (const Integer& other) const { 
    return !(*this == other);
}



bool Integer::parse(char *buffer,int &index, const int& length) {
    if (buffer[index] != 'i') {
        return false;
    }
    index++;
    if (index == length) {
        return false;
    }
    int sgn = 1;
    if (buffer[index] == '-') {
        sgn = -1;
        index++;
        // not allowed
        if (index < length && buffer[index] == '0') {
            return false;
        }
    }
    
    if (index >= length || !isdigit(buffer[index])) {
        return false;
    }
    
    // not sure if zeroes allowed in front of the number
    data = 0;
    while (index < length && isdigit(buffer[index])) {
        data = data * 10 + (buffer[index++] - '0');
    }

    // check for invalid bencode format
    if (index >= length || buffer[index] != 'e') {
        return false;
    }
    index++;
    
    data *= sgn;

    return true;
}

BencodeType* Integer::clone() {
    return new Integer(*this);
}   

long long Integer::getValue() const {
    return data;
}   

