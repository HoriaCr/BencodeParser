// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.



#include <string>
#include <vector>
#include <cstring>
#include <cctype>

#pragma once


class BencodeType {
    
    public:

        virtual bool parse(char*,int&, const int&) {
            return true;    
        }

        virtual ~BencodeType() {

        }
        
        virtual BencodeType* clone() {
            return NULL;
        }
};



