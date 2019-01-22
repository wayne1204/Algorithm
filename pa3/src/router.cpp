#include <set>
#include <queue>
#include "router.h"
#include <limits.h>
#include <iostream>
#include <cassert>
using namespace std;

void Router::buildGraph(int h, int v, int c){
    horizon = h;
    vertical = v;
    capacity = c;
    graph = new Vertex* [h];
    for(int i = 0; i < h; ++i){
        graph[i] = new Vertex[v]; 
    }

    for(int i = 0; i < h; ++i){
        for(int j = 0; j < v; ++j){
            graph[i][j].setPos(i, j);
            if(i == 0){
                graph[i][j].push_back(c, &graph[i+1][j] );
            }
            else if(i == h-1){
                graph[i][j].push_back(c, &graph[i-1][j] );
            }
            else{
                graph[i][j].push_back(c, &graph[i-1][j] );
                graph[i][j].push_back(c, &graph[i+1][j] );
            }

            if(j == 0){
                graph[i][j].push_back(c, &graph[i][j+1] );
            }
            else if(j == v-1){
                graph[i][j].push_back(c, &graph[i][j-1] );
            }
            else{
                graph[i][j].push_back(c, &graph[i][j-1] );
                graph[i][j].push_back(c, &graph[i][j+1] );
            }
        }
    }
}

void Router::initSingleSource(int start_node){
    for(int i = 0; i < horizon; ++i){
        for(int j = 0; j < vertical; ++j){
            graph[i][j].setDistance(10000);
            graph[i][j].setPre(NULL);
        }
    }
    graph[start_node/vertical][start_node%vertical].setDistance(0);
}


bool Router::relax(Vertex* n1, Vertex* n2, EdgeNode* edge){
    if(n2->getDistance() > n1->getDistance() + edge->getVal() ){
        n2->setDistance(n1->getDistance() + edge->getVal());
        n2->setPre(n1);
        return true;
    }
    return false;
}

void Router::Dijkstra(int sx, int sy){
    int start_node = sx * vertical + sy;
    initSingleSource(start_node);
    my_queue mypq;
    for(int i = 0; i < horizon; ++i){
        for(int j = 0; j < vertical; ++ j){
            mypq.insert(&graph[i][j]);
        }
    }
    
    while(!mypq.empty()){
        Vertex* u = mypq.extract_min();
        // cout << u->getX() << " " << u->getY() << " ===================== "<< u->getDistance()  <<"\n";
        EdgeNode* edge = u->getEdge();
        while(edge != NULL){
            // cout << edge->getNode()->getX() << " " << edge->getNode()->getY() << "\n";
            if(relax(u, edge->getNode() , edge)){
                mypq.decrease_key(edge->getNode());
            }
            edge = edge->getNext();
        }

        // for(int i = 0; i < horizon; ++i){
        //     for(int j = 0; j < vertical; ++j){
        //         cout << graph[i][j].getDistance() << " ";
        //     }
        //     cout <<endl;
        // }
    }
}

void Router::traceback(int x, int y, int& len, stringstream& ss){
    Vertex* v = &graph[x][y];
    if(v->getPre() != NULL){
        traceback(v->getPre()->getX(), v->getPre()->getY(), len, ss);
        ss << v->getPre()->getX() << ' ' << v->getPre()->getY() << ' '; 
        ss << x << ' ' << y << '\n';
        updateEdge(v, v->getPre());
        ++len;
    }
}

void Router::updateEdge(Vertex* v1, Vertex* v2){
    EdgeNode* edge = v1->getEdge();
    while(edge->getNode() != v2){
        edge = edge->getNext();
    }
    edge->update();

    edge = v2->getEdge();
    while(edge->getNode() != v1){
        edge = edge->getNext();
    }
    edge->update();
}