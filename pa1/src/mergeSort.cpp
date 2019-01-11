#include <iostream>
#include <vector>
#include "parser.h"
#include "stringClass.h"
using namespace std;

vector<stringClass *> _totalString;
void MergeSort(int p, int r);
void Merge(int p, int q, int r);

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    AlgParser p;
    AlgTimer t;
    p.Parse(argv[1]);
    t.Begin();

    // init
    for(int i = 0; i < p.QueryTotalStringCount(); ++i){
        stringClass *s = new stringClass(i + 1, p.QueryString(i));
        _totalString.push_back(s);
    }
    MergeSort(0, _totalString.size()-1);

    fstream file;
    file.open(argv[2], ios::out);
    if (!file)
    {
        cerr << "[Error] Cant open file!\n";
    }
    file << _totalString.size() << '\n';
    for(int i = 0; i < _totalString.size(); ++i){
        _totalString[i]->show(file);
    }
    cout << "Total time spent:" << t.End() << '\n';
}

void MergeSort(int p, int r){
    if(p < r){
        int q = (p+r)/2;
        MergeSort(p, q);
        MergeSort(q+1, r);
        Merge(p, q, r);
    }
}

void Merge(int p, int q, int r){
    int len1 = q - p + 1, len2 = r - q;
    int i = 0, j = 0;
    stringClass* inf = new stringClass(-1, "~~~");
    vector<stringClass*> L;
    vector<stringClass*> R;

    for(int i = 0; i < len1; ++i){
        L.push_back(_totalString[p + i]);
    }
    for(int i = 0; i < len2; ++i){
        R.push_back(_totalString[q+i+1]);
    }
    L.push_back(inf);
    R.push_back(inf);
    for(int k = p; k <= r; ++k){
        if(L[i]->larger(R[j])){
            _totalString[k] = R[j];
            ++j;
        }
        else{
            _totalString[k] = L[i];
            ++i;
        }
    }
}