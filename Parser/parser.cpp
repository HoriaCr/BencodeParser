// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "parser.hpp"


Parser::Parser(const std::string& filename) {
    std::ifstream is(filename.c_str(),std::ifstream::binary);
    is.seekg(0, is.end);
    length = is.tellg();
    is.seekg(0, is.beg);
    try {
        buffer = new char[length];
        is.read(buffer, length);
        if (is) {
            throw 1;
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}

Parser::~Parser() {
    delete[] buffer;
}
 

BencodeType* Parser::parseElement(char *buff,int &index, const int& len) {
    BencodeType *ret;
    // bytestring
    if (isdigit(buff[index])) {
        ret = new ByteString();
    } else
    // integer
    if (buff[index] == 'i') {
        ret = new Integer();
    } else
    // list
    if (buff[index] == 'l') {
        ret = new List();
    } else 
    // dictionary
    if (buff[index] == 'd') {
        ret = new Dictionary();
    } else 
    // invalid format
    {
        return NULL;
    }   
    
    // failed parsing
    if (!ret->parse(buff, index, len)) {
        return NULL;
    }
    
    return ret;
}

void Parser::parse() {
    int index = 0;
    std::vector< BencodeType* > data;
    while (index < length) {
        data.push_back(parseElement(buffer, index, length));
    }
}
