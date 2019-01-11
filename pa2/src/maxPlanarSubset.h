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
    void traverse(treeNode* n, fstream& fs);
    void output(const char* fname);

private:
    int _npoint;
    int** _table;
    treeNode** _trace;
    unordered_map<int, int> _coord;
};
