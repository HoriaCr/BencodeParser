// Copyright (c) 2014 Horia Cretescu. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.


#include "bencodetype.hpp"


BencodeType::BencodeType() {

}

bool BencodeType::parse(char* buffer,int& index,const int& length) {
    return true;
}

BencodeType::~BencodeType() {

}

BencodeType* BencodeType::clone() {
    return NULL;
}

