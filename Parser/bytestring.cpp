// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "bytestring.hpp"

ByteString::ByteString() {
    strLength = 0;
    data = NULL;
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
    int digits = 0;
    while (index < length && isdigit(buffer[index])) {
        strLen = strLen * 10 + (buffer[index++] - '0');
        digits++;
    }   

    if (!digits) {
        return -1;
    }

    return strLen;
}

bool ByteString::parse(char *buffer,int &index, const int& length) {
   if (strLength > 0) {
        strLength = 0;
        delete[] data;
   }
   strLength = parseLength(buffer, index, length);
   if (strLength == -1 || index + strLength >= length || buffer[index] != ':') {
       strLength = 0;
       return false;
   }
   index++;
   data = new char[strLength];
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
