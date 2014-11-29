// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.



#include "integer.hpp"
#include "bytestring.hpp"

class List : public BencodeType  {
        
        std::vector<BencodeType*> data;

    public: 
        List();

        ~List();

        List(const List&);

        List& operator = (const List&);

        void push(BencodeType*);

        BencodeType *clone();
};


List::List() {

}

List::~List() {
    
    for (size_t i = 0; i < data.size(); i++) {
        delete data[i];    
    }

    data.clear();
}

List::List(const List& other) {
    data.resize(other.data.size());
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = other.data[i]->clone();
    }
}

List& List::operator = (const List& other) {
    if (&other == this) {
        return *this;
    }
    
    this->~List();
    
    data.resize(other.data.size());
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = other.data[i]->clone();
    }

    return *this;
}
    

void List::push(BencodeType *value) {
    data.push_back(value);
}


BencodeType* List::clone() {
    return new List(*this);
}
