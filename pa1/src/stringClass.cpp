#include <iostream>
#include <fstream>
#include <string>
#include "stringClass.h"
using namespace std;

bool stringClass::larger(stringClass* c){
    int len = min(_name.size(), c->_name.size());
    for(int i = 0; i < len; ++i){
        if(_name[i] > c->getChar(i)){
            return true;
        }
        if (_name[i] < c->getChar(i))
            return false;
    }
    return _name.size() > c->_name.size();
}

bool stringClass::smaller(stringClass *c){
    int len = min(_name.size(), c->_name.size());
    for(int i = 0; i < len; ++i){
        if(_name[i] < c->getChar(i)){
            return true;
        }
        if (_name[i] > c->getChar(i))
            return false;
    }
    return _name.size() < c->_name.size();
}

void stringClass::show(fstream& fs){
    fs << _name << ' ' << _index << '\n';
    // cout << _name << '\n';
}

string stringClass::getStr(){
    return _name + ' ' + to_string(_index) + '\n';
}
