#include <string>
#include <vector>
#include <fstream>
using namespace std;

class stringClass{
public:
    stringClass(int i, string n) :_index(i), _name(n){
    }
    bool larger(stringClass* c);
    bool smaller(stringClass *c);

    char getChar(const int& i){
        return _name[i];
    }
    string getStr();
    void show(fstream& );
private:
    int _index;
    string _name;
};

// class sortManager{
// public:
//     void insert(stringClass* s){
//         _totalString.push_back(s);
//     }
//     void setElement(const int& i, stringClass* s){
//         _totalString[i] = s;
//     }
//     stringClass* getElement(const int& i){
//         return _totalString[i];
//     }
//     void show();
// private:
//     string output;
//     vector<stringClass*> _totalString;
// };