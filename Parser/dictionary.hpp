// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "bytestring.hpp"
#include "integer.hpp"

class Dictionary : public BencodeType {
        // keys must appear in lexicographical order 
        std::vector<std::pair<std::string,BencodeType*> > data; 

    public:

       Dictionary();
        
       Dictionary(const Dictionary& other);

       ~Dictionary();

       void insert(const std::string&, BencodeType*); 
    
       BencodeType *query(const std::string&) const;

       Dictionary& operator = (const Dictionary& other);

       BencodeType *clone();
};

Dictionary::Dictionary() {

}

void Dictionary::insert(const std::string& key, BencodeType* value) {
    data.push_back(make_pair(key, value));
}

BencodeType* Dictionary::query(const std::string& key) const {
    if (data.empty()) {
        return NULL;
    }

    unsigned int pos = 0;
    for (unsigned int step = 1 << 10; step; step >>= 1) {
        if (pos + step < data.size() && key <= data[pos + step].first) {
            pos += step;
        }
    }

    return data[pos].first == key ? data[pos].second : NULL;
}


Dictionary::Dictionary(const Dictionary& other) {
    data.resize(other.data.size());
    for (size_t i = 0; i < other.data.size(); i++) {
        data[i].first = other.data[i].first;
        data[i].second = other.data[i].second->clone();
    }
}

Dictionary::~Dictionary() {
    for (size_t i = 0; i < data.size(); i++) {
        delete data[i].second;
    }
    data.clear();
}

Dictionary& Dictionary::operator = (const Dictionary& other) {
    if (&other == this) {
        return *this;
    }

    for (size_t i = 0; i < data.size(); i++) {
        delete data[i].second;
    }
    
    data.resize(other.data.size());
    for (size_t i = 0; i < other.data.size(); i++) {
        data[i].first = other.data[i].first;
        data[i].second = other.data[i].second->clone();
    }
    return *this;
}

BencodeType* Dictionary::clone() {
    Dictionary *ret = new Dictionary();
    ret->data.resize(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        ret->data[i].first = data[i].first;
        ret->data[i].second = data[i].second->clone();
    }

    return ret;
}
