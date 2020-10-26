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
    for(int i = 0; i < _npoint; ++i){
        vector<int> row(_npoint, 0);
        vector<int> casee(_npoint, -1);
        _table.push_back(row);
        _case.push_back(casee);
        _coord.resize(_npoint, 0);
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
    //     if(n2 - n1 == 1){
    //         _table[n1][n2] = 1;
    //         _case[n1][n2] = n1;
    //     }

    //     if(n1 - n2 == 1){
    //         _table[n2][n1] = 1;
    //         _case[n2][n1] = n2;
    //     }
    }
    return true;
}

void MPS::assign(){
    int sum, idx, k;
    for(int j = 0; j < _npoint; ++j){
        k = _coord[j];

        for(int i = 0; i < j; ++i){
            _table[i][j] = _table[i][j-1];

            if(k >= i && k <= j-1){
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
void MPS::traverse(int n1, int n2, fstream& fs){
    if(n1 >= n2)
        return;
    int k = _case[n1][n2];
    if(k != -1){
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