#include <unordered_map>
// #include <map>
#include <vector>
#include <string>
using namespace std;

struct treeNode{
    treeNode(): left(NULL), right(NULL) {}
    int n1;
    int n2;
    treeNode* left;
    treeNode* right;
};

class MPS{
public:
    bool parse(const char* fname);
    void assign();
    void assign();
    void traverse(int n1, int n2, fstream& fs);
    void output(const char* fname);

private:
    int  _npoint;
    vector< vector<int> > _table;
    vector< vector<int> > _case; // [i,j]  == [i,k-1] + [k+1,j]
    vector<int> _coord;
};
