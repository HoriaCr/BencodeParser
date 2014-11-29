// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.



#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>

#include "integer.hpp"
#include "bytestring.hpp"
#include "dictionary.hpp"
#include "list.hpp"

// class used for parsing bencoded files
class Parser { 
    int length;
    char *buffer;

    public:
        
        Parser(const std::string&);
    
        void parse();
    
        ~Parser();
};

Parser::Parser(const std::string& filename) {
    std::ifstream is(filename,std::ifstream::binary);
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
 
void Parser::parse() {
    int index = 0;
    std::vector< BencodeType* > data;
    while (index < length) {
        //data.push_back(parseElement(buffer, index, length));
    }
}

Dictionary* parseDictionary(char*,int&, const int&);
List* parseList(char*,int&,const int&);

BencodeType *parseElement(char *buffer,int &index, const int& length) {
    BencodeType *ret;
    if (isdigit(buffer[index])) {
        ret = new ByteString();
        ret->parse(buffer, index, length);
    } else
    if (buffer[index] == 'i') {
        ret = new Integer();
        ret->parse(buffer, index, length);
    } else
    if (buffer[index] == 'l') {
        ret = parseList(buffer, index, length);
    } else 
    if (buffer[index] == 'd') {
        ret = parseDictionary(buffer, index, length);
    } else {
        // invalid format
        return NULL;
    }   
    
    return ret;
}

Dictionary *parseDictionary(char *buffer,int &index, const int& length)  {

    if (buffer[index] != 'd') {
        std::cerr << "Format Error\n"; 
        return NULL;
    }
    
    index++;
    Dictionary *ret = new Dictionary();

    // parse entries of the dictionary which should have their keys in sorted order
    while (index < length && buffer[index] != 'e') {
        ByteString key;
        if (!key.parse(buffer, index, length)) {
            break;
        }

        BencodeType *value = parseElement(buffer, index, length);
        if (value != NULL) {
            ret->insert(key.toString(), value);
        } else {
            break;
        }
    }

    if (index >= length || buffer[index] != 'e') {
        delete ret;
        return NULL;
    }
    index++;
    return ret;
}

List* parseList(char *buffer,int &index, const int& length)  {
    if (buffer[index] != 'l') {
        std::cerr << "Format Error\n"; 
        return NULL;
    }
    
    index++;
    List *ret = new List();

    // parse entries of the list which should be other bencode types
    while (index < length && buffer[index] != 'e') {
        BencodeType *value = parseElement(buffer, index, length);
        if (value == NULL) {
            break;
        }
        
        ret->push(value);
    }

    if (index >= length || buffer[index] != 'e') {
        delete ret;
        return NULL;
    }
    index++; 
    return ret;
}
