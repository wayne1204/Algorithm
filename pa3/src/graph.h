#include <vector>
#include <cmath>
using namespace std;

class Vertex; 

class EdgeNode{
public:
    EdgeNode(double x, Vertex* v){
        demand = 0;
        cap = x; 
        node = v;
        next = NULL;
    }

    Vertex* getNode() { return node; }
    EdgeNode* getNext() {return next; }
    void update() { ++demand; }
    double getVal() { return pow(2, demand/cap); }
    friend class Vertex;
    
private:
    double demand;
    double cap;
    EdgeNode* next;
    Vertex* node;
};

class Vertex{  
public:
    Vertex(){
        edge = NULL;
    }
    void setPos(int n1, int n2) {x = n1, y = n2;}
    int getX() {return x; }
    int getY() {return y; }
    EdgeNode* getEdge() {return edge;}
    void push_back(int weight, Vertex* node);
    
    void setDistance(double d) {distance = d; }
    double getDistance() { return distance; }
    bool smaller(Vertex* v) { return distance < v->getDistance(); }
    void setPre(Vertex* v) {pre = v; } 
    Vertex* getPre() {return pre; }
    
private:
    EdgeNode* edge;
    Vertex* pre;
    double distance;
    int x;
    int y;
};

class my_queue
{
public:
    Vertex* extract_min();
    void min_heapify(int index);
    void decrease_key(Vertex* v);
    void insert(Vertex* v);
    bool empty() { return A.empty(); }
private:
    vector<Vertex*> A;
};
