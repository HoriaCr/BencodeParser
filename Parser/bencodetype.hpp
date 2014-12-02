// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>

#pragma once


class BencodeType {
    
    public:
    
        BencodeType();

        virtual bool parse(char*,int&, const int&);

        virtual ~BencodeType();
        
        virtual BencodeType* clone();
    
};



