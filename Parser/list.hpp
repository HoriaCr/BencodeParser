// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef LIST_HPP_
#define LIST_HPP_

#include "parser.hpp"


class List : public BencodeType  {
        
        std::vector<BencodeType*> data;

    public: 
        List();

        List(const std::vector<BencodeType*>&);

        ~List();

        List(const List&);

        List& operator = (const List&);

        bool isEqual(const BencodeType&) const;
        
        bool operator == (const List&) const;
        
        bool operator != (const List&) const;

        bool parse(char*,int&,const int&);

        void push(BencodeType*);

        BencodeType *clone();
};



#endif //LIST_HPP_
