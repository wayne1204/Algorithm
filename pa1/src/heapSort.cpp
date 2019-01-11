#include <iostream>
#include <vector>
#include "parser.h"
#include "stringClass.h"
using namespace std;

vector<stringClass*> _totalString;
void max_heapify(const int&, int i);

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    AlgParser p;
    AlgTimer t;
    p.Parse(argv[1]);
    t.Begin();

    // init
    stringClass* tmp;
    _totalString.push_back(tmp);
    for(int i = 0; i < p.QueryTotalStringCount(); ++i){
        stringClass *s = new stringClass(i + 1, p.QueryString(i));
        _totalString.push_back(s);
    }

    // build max heap
    int size = _totalString.size();
    for (int i = size / 2; i >= 1; --i)
        max_heapify(size, i);

    // heap sort
    for (int i = _totalString.size() -1; i >= 2; --i)
    {
        tmp = _totalString[1];
        _totalString[1] = _totalString[i];
        _totalString[i] = tmp;
        max_heapify(--size, 1);
    }

    fstream file;
    file.open(argv[2], ios::out);
    if (!file)
    {
        cerr << "[Error] Cant open file!\n";
    }
    file << _totalString.size() - 1 << '\n';
    for(int i = 1; i < _totalString.size(); ++i){
        _totalString[i]->show(file);
    }
    cout << "Total time spent:" << t.End() << '\n';
}

void max_heapify(const int& _size, int i){
    int left = i*2;
    int right = i*2+1;
    int largest = i;
    stringClass *tmp;

    if (left < _size )
        largest = _totalString[left]->larger(_totalString[i]) ? left : i;
    
    if (right < _size)
        largest = _totalString[right]->larger(_totalString[largest]) ? right : largest;

    if (largest != i){
        tmp = _totalString[largest];
        _totalString[largest] = _totalString[i];
        _totalString[i] = tmp;
        max_heapify(_size, largest);
    }
}