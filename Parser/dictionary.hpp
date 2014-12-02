// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#ifndef DICTIONARY_HPP_
#define DICTIONARY_HPP_

#include "parser.hpp"

class Dictionary : public BencodeType {
        // keys must appear in lexicographical order 
        std::vector<std::pair<std::string,BencodeType*> > data; 

    public:

       Dictionary();
        
       Dictionary(const Dictionary& other);

       ~Dictionary();

       void insert(const std::string&, BencodeType*); 

       bool parse(char*,int&,const int&);

       BencodeType *query(const std::string&) const;

       Dictionary& operator = (const Dictionary& other);

       BencodeType *clone();
};


#endif // DICTIONARY_HPP
