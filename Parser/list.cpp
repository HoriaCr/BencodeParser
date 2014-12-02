#include "list.hpp"

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

bool List::parse(char *buffer,int &index, const int& length)  {
    if (buffer[index] != 'l') {
        std::cerr << "Format Error\n"; 
        return false;
    }
    
    index++;

    // parse entries of the list which should be other bencode types
    while (index < length && buffer[index] != 'e') {
        BencodeType *value = Parser::parseElement(buffer, index, length);
        if (value == NULL) {
            break;
        }
        
        push(value);
    }

    if (index >= length || buffer[index] != 'e') {
        return false;
    }
    index++; 
    return true;
}

void List::push(BencodeType *value) {
    data.push_back(value);
}


BencodeType* List::clone() {
    return new List(*this);
}
