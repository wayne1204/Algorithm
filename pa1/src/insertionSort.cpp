#include <iostream>
#include <vector>
#include <fstream>
#include "parser.h"
#include "stringClass.h"

using namespace std;

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    AlgParser p;
    AlgTimer t;
    p.Parse(argv[1]);
    t.Begin();
    // call STL
    // vector<string> _store;
    // for(int i = 0; i < p.QueryTotalStringCount(); ++i){
    //     _store.push_back(p.QueryString(i));
    // }
    // stable_sort(_store.begin(), _store.end());

    // cout << _store.size() << endl;
    // for(int i = 0; i < _store.size(); ++i){
    //     cout << _store[i] << '\n';
    // }

    vector<stringClass*> _totalString;
    stringClass *s = new stringClass(1, p.QueryString(0));
    _totalString.push_back(s);
    
    // sort
    for(int i = 1; i < p.QueryTotalStringCount(); ++i){
        stringClass *s = new stringClass(i + 1, p.QueryString(i));
        _totalString.push_back(s);
        int j = i - 1;
        while(_totalString[j]->larger(s)){
            _totalString[j + 1] = _totalString[j];
            if(--j < 0)
                break;
        }
        _totalString[j + 1] = s;
    }

    fstream file;
    file.open(argv[2], ios::out);
    if (!file){
        cerr << "[Error] Cant open file!\n";
    }
    file << _totalString.size() << endl;
    for(int i = 0; i < _totalString.size(); ++i){
        _totalString[i]->show(file);
    }

    cout << "Total time spent:" << t.End() << '\n';
}