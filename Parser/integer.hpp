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
        
        bool operator == (const long long&) const;

        bool parse(char*,int&,const int&);

        BencodeType *clone();

        long long getValue() const;
};
    

