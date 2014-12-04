// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

#include "dictionary.hpp"

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

bool Dictionary::parse(char *buffer,int &index, const int& length)  {

    if (buffer[index] != 'd') {
        std::cerr << "Format Error\n"; 
        return false;
    }
    
    index++;
    // parse entries of the dictionary which should have their keys in sorted order
    while (index < length && buffer[index] != 'e') {
        ByteString key;
        if (!key.parse(buffer, index, length)) {
            break;
        }

        BencodeType *value = Parser::parseElement(buffer, index, length);
        if (value != NULL) {
            insert(key.toString(), value);
        } else {
            break;
        }
    }

    if (index >= length || buffer[index] != 'e') {
        return false;
    }
    index++;
    return true;
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


bool Dictionary::isEqual(const BencodeType& other) const { 
    const Dictionary* dictionary = dynamic_cast<const Dictionary*>(&other);
    return (dictionary != NULL && *this == *dictionary);
}

bool Dictionary::operator == (const Dictionary& other) const {
    if (data.size() != other.data.size()) {
        return false;
    }

    for (size_t i = 0; i < data.size(); i++) {
        if (data[i].first == other.data[i].first && *data[i].second != *other.data[i].second) {
            return false;
        }
    }
    return true;
}

bool Dictionary::operator != (const Dictionary& other) const {
    return !(*this == other);
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
