#include <sstream>
#include "graph.h"

class Router{
public:
    void buildGraph(int h, int v, int c);
    void initSingleSource(int);
    bool relax(Vertex* n1, Vertex* n2, EdgeNode* edge);
    void Dijkstra(int, int);
    void traceback(int, int, int&, stringstream&);
    void updateEdge(Vertex* v1, Vertex* v2);

private:
    int horizon;
    int vertical;
    int capacity;
    Vertex** graph;
};