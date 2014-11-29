// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.



#include "bencodetype.hpp"

#pragma once


class ByteString : public BencodeType {
        int strLength;
        char *data;    

    public: 
        
        ByteString();

        ~ByteString();

        ByteString(const ByteString&);

        ByteString& operator = (const ByteString&);

        int parseLength(char*,int&,const int&);
      
        bool parse(char*,int&, const int&);       
        
        std::string toString();

        BencodeType *clone();
};

ByteString::ByteString() {

}

ByteString::~ByteString() {
    if (data != NULL) {
        delete[] data;
    }
}

ByteString::ByteString(const ByteString& other) {
    strLength = other.strLength;
    data = new char[strLength];
    memcpy(data, other.data, strLength);
}

ByteString& ByteString::operator = (const ByteString& other) {
    if (&other == this) {
        return *this;
    }

    if (data != NULL) {
        delete data;
    }

    strLength = other.strLength;
    data = new char[strLength];
    memcpy(data, other.data, strLength);

    return *this;
}

int ByteString::parseLength(char *buffer,int &index, const int& length) {
    int strLen = 0;
    while (index < length && isdigit(buffer[index])) {
        strLen = strLen * 10 + (buffer[index++] - '0');
    }   
    return strLen;
}

bool ByteString::parse(char *buffer,int &index, const int& length) {
   strLength = parseLength(buffer, index, length);
   if (index + strLength >= length || buffer[index] != ':') {
       return false;
   }
   index++;
   memcpy(data, buffer + index, strLength);
   index += strLength;
   return true;
}

std::string ByteString::toString() {
    return std::string(data, data + strLength);
}

BencodeType* ByteString::clone() {
    return new ByteString(*this);
}
