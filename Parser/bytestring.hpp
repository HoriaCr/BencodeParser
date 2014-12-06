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

        ByteString(const std::string&);

        ByteString& operator = (const ByteString&);
 
        bool isEqual(const BencodeType&) const;

        bool operator == (const ByteString&) const;

        bool operator != (const ByteString&) const;

        int parseLength(char*,int&,const int&);
      
        bool parse(char*,int&, const int&);       
        
        std::string toString();

        BencodeType *clone();
};
