// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>

#include "bencodetype.hpp"
#include "list.hpp"
#include "dictionary.hpp"
#include "integer.hpp"
#include "bytestring.hpp"


#pragma once


// class used for parsing bencoded files
class Parser { 
    
    int length;
    char *buffer;

    public:
        
        Parser(const std::string&);
    
        void parse();
    
        ~Parser();
    
        static BencodeType* parseElement(char*,int&,const int&);
};

#endif // PARSER_HPP
