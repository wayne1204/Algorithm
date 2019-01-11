#include <iostream>
#include <string>
#include <fstream>
#include "maxPlanarSubset.h"
using namespace std;

bool MPS::parse(const char* fname){
    int n1, n2;
    string line, token;
    fstream fs(fname, ios::in);
    if(!fs.is_open()){
        return false;
    }

    // init table
    getline(fs, line);
    _npoint = stoi(line);
    _table = new int*[_npoint];
    _trace = new treeNode*[_npoint];
    for(int i = 0; i < _npoint; ++i){
        _table[i] = new int [_npoint];
        _trace[i] = new treeNode[_npoint];
        _table[i][i] = 0;
        for(int j = 0; j < _npoint; ++j){
            _trace[i][j].n1 = i;
            _trace[i][j].n2 = j;
        }
    }
    
    // parse chords
    while(getline(fs, line)){
        if(line == "0")
            break;
        size_t pos = line.find(' ');
        n1 = stoi(line.substr(0, pos));
        n2 = stoi(line.substr(pos+1));
        _coord.emplace(n1, n2);
        _coord.emplace(n2, n1);
    }
    return true;
}

void MPS::assign(){
    int sum;
    for(int j = 0; j < _npoint; ++j){
        int k = -1;
        unordered_map<int, int>::iterator it = _coord.find(j);
        if(it != _coord.end())
            k = it->second;

        for(int i = 0; i < j; ++i){
            if(k == i){
                _table[i][j] = _table[i+1][j-1] + 1;
                _trace[i][j].right = &_trace[i+1][j-1];
            }
            else if(k <= j-1 && k > i){
                sum = _table[i][k-1] + _table[k+1][j-1] + 1;
                if(sum > _table[i][j-1]){
                    _table[i][j] = sum;
                    _trace[i][j].left = &_trace[i][k-1];
                    _trace[i][j].right = &_trace[k+1][j-1];
                }
                else{
                    _table[i][j] = _table[i][j-1];
                    _trace[i][j].left = &_trace[i][j-1];
                }
            }
            else{    
                _table[i][j] = _table[i][j-1];
                _trace[i][j].left = &_trace[i][j-1];
            }
        }
    }
}
void MPS::traverse(treeNode* n, fstream& fs){
    if(n->left != NULL)
        traverse(n->left, fs);
    if(n->right != NULL){
        fs << n->right->n1-1 << ' ' << n->right->n2+1 << '\n';  
        traverse(n->right, fs);
    }
}

void MPS::output(const char* fname){
    fstream fs(fname, ios::out);
    fs << _table[0][_npoint-1] << '\n';
    traverse(&_trace[0][_npoint-1], fs);
    for(int i = 0; i < _npoint; ++i){
        delete[] _table[i];
        delete[] _trace[i];
    }
    delete[] _table;
    delete[] _trace;
}