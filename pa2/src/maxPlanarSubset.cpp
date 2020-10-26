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
    _table.reserve(_npoint);
    _case.reserve(_npoint);
    _coord.resize(_npoint, 0);
    for(int i = 0; i < _npoint; ++i){
        _table.push_back(vector<int>(_npoint, -1));
        _case.push_back(vector<bool> (_npoint, false));
    }
    
    // parse chords
    while(getline(fs, line)){
        if(line == "0")
            break;
        size_t pos = line.find(' ');
        n1 = stoi(line.substr(0, pos));
        n2 = stoi(line.substr(pos+1));
        _coord[n1] = n2;
        _coord[n2] = n1;
        if(n2 - n1 == 1){
            _table[n1][n2] = 1;
            _case[n1][n2] = true;
        }

        if(n1 - n2 == 1){
            _table[n2][n1] = 1;
            _case[n2][n1] = true;
        }
    }
    return true;
}


void MPS::assign(){
    // botUp();
    topDown(0, _npoint-1);
}

void MPS::botUp(){
    int sum, idx, k;
    for(int i = 0; i < _npoint; ++i){
        _table[i][i] = 0;
    }
    
    for(int j = 0; j < _npoint; ++j){
        k = _coord[j];

        for(int i = 0; i < j; ++i){
            _table[i][j] = _table[i][j-1];

            if(k >= i && k < j){
                idx = max(0, k-1);
                // split case
                sum = _table[i][idx] + _table[k+1][j-1] + 1;
                if(sum > _table[i][j-1]){
                    _table[i][j] = sum;
                    _case[i][j] = k;
                }
            }
        }
    }
}


int MPS::topDown(int i, int j){
    // cout << i << " " << j << endl;
    if(i >= j)
        return 0;

    if(_table[i][j] != -1)
        return _table[i][j];

    int sum, prev, idx, k = _coord[j];

    if( k == i){
        _table[i][j] = topDown(i+1, j-1) + 1;
        _case[i][j] = true;
    }
    else if(k > i && k < j){ // [i, j-1]
        idx = max(0, k-1);
        sum = topDown(i, idx) + topDown(k+1, j-1) + 1;
        prev = topDown(i, j-1);

        if(sum > prev){
            _table[i][j] = sum;
            _case[i][j] = true;
        }else{
            _table[i][j] = prev;
        }
    }
    else{
        _table[i][j] = topDown(i, j-1);
    }
    return _table[i][j];
}

void MPS::traverse(int n1, int n2, fstream& fs){
    if(n1 >= n2)
        return;
    if(_case[n1][n2]){
        int k = _coord[n2];
        traverse(n1, k-1, fs);
        fs << k << ' ' << n2 << '\n';  
        traverse(k+1, n2-1, fs);
    }else{
        traverse(n1, n2-1, fs);
    }
}

void MPS::output(const char* fname){
    fstream fs(fname, ios::out);
    fs << _table[0][_npoint-1] << '\n';
    traverse(0, _npoint-1, fs);
}