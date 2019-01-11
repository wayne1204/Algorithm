#include <iostream>
#include <vector>
#include "parser.h"
#include "stringClass.h"
using namespace std;

vector<stringClass*> _totalString;
void quickSort(const int& p, const int& r);
int partition(const int &p, const int &r);

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    AlgParser p;
    AlgTimer t;
    p.Parse(argv[1]);
    t.Begin();

    // init
    for (int i = 0; i < p.QueryTotalStringCount(); ++i)
    {
        stringClass *s = new stringClass(i + 1, p.QueryString(i));
        _totalString.push_back(s);
    }

    quickSort(0, _totalString.size()-1);
    fstream file;
    file.open(argv[2], ios::out);
    if (!file){
        cerr << "[Error] Cant open file!\n";
    }
    file << _totalString.size() << '\n';
    for(int i = 0; i < _totalString.size(); ++i){
        _totalString[i]->show(file);
    }
    cout << "Total time spent:" << t.End() << '\n';
}

void quickSort(const int& p, const int& r){
    if(p < r){
        int q = partition(p, r);
        quickSort(p, q);
        quickSort(q+1, r);
    }
}

int partition(const int& p, const int& r){
    stringClass* middle = _totalString[p];
    int i = p - 1, j = r + 1;
    while(true) {
        while(_totalString[--j]->larger(middle)){
        }
        while(_totalString[++i]->smaller(middle)){
        }

        if(i < j){
            stringClass *tmp = _totalString[i];
            _totalString[i] = _totalString[j];
            _totalString[j] = tmp;
        }
        
        else{
            return j;
        }

    }
}