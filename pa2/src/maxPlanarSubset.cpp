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
    _coord.resize(_npoint, 0);
    // _table = new int *[_npoint];
    // _case  = new bool *[_npoint];

    for(int i = 0; i < _npoint; ++i){
        // _table[i] = new int [_npoint];
        // _case[i]  = new bool [_npoint];
        _table.push_back(vector<int>(_npoint, 0));
        _table.push_back(vector<int>(_npoint, -1)); // for top-down
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
    }
    return true;
}


void MPS::assign(){
    botUp();
    // topDown(_npoint-1, 0);
}

void MPS::botUp(){
    int sum, idx, k;
    for(int i = 0; i < _npoint; ++i){
        _table[i][i] = 0;
    }
    
    for(int i = 0; i < _npoint; ++i){
        k = _coord[i];

        for(int j = 0; j < i; ++j){
            _table[i][j] = _table[i-1][j];

            // if (k == 0){
            //     _table[i][j] = _table[i-1][1] +1 ;
            //     _case[i][j] = true;
            // }
            if(k >= j && k < i){
                idx = max(0, k-1);
                // split case
                sum = _table[i-1][k+1] + _table[idx][j] + 1;
                if(sum > _table[i-1][j]){
                    _table[i][j] = sum;
                    _case[i][j] = true;
                }
            }
        }
    }
}

// i > j
int MPS::topDown(int i, int j){
    if(j >= i)
        return 0;

    if(_table[i][j] != -1)
        return _table[i][j];

    int sum, prev, idx, k = _coord[i];

    if( k == j){
        _table[i][j] = topDown(i-1, j+1) + 1;
        _case[i][j] = true;
    }
    else if(k > j && k < i){ // [j-1, i]
        sum = topDown(i-1, k+1) + topDown(k-1, j) + 1;
        prev = topDown(i-1, j);

        if(sum > prev){
            _table[i][j] = sum;
            _case[i][j] = true;
        }else{
            _table[i][j] = prev;
        }
    }
    else{
        _table[i][j] = topDown(i-1, j);
    }
    return _table[i][j];
}

// [n2 < n1]
void MPS::traverse(int n1, int n2, fstream& fs){
    if(n1 <= n2)
        return;
    if(_case[n1][n2]){
        int k = _coord[n1];
        traverse(k-1, n2, fs);
        fs << k << ' ' << n1 << '\n';  
        traverse(n1-1, k+1, fs);
    }else{
        traverse(n1-1, n2, fs);
    }
}

void MPS::output(const char* fname){
    fstream fs(fname, ios::out);
    fs << _table[_npoint-1][0] << '\n';
    traverse(_npoint-1, 0, fs);
	// for (int i = 0; i < _npoint; ++i) {
	// 	delete[] _table[i]; 
	// 	delete[] _case[i];
	// }	
    // delete[] _table;
	// delete[] _case;
}