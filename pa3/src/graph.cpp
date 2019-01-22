#include <limits.h>
#include <set>
#include <iostream>
#include "graph.h"
using namespace std;

void Vertex::push_back(int weight, Vertex* node){
    EdgeNode* newNode = new EdgeNode(weight, node);

    if(edge == NULL){
        edge = newNode;
        return;
    }

    EdgeNode* cur = edge;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = newNode;
}

void my_queue::min_heapify(int index){
    int l = index * 2 + 1;
    int r = index * 2 + 2;
    int min;

    if(l < A.size() and A[l]->smaller(A[index]) ){
        min = l;
    }else
        min = index;
    if(r < A.size() and A[r]->smaller(A[min]) ){
        min = r;
    }
    if (min != index){
        swap(A[index], A[min]);
        min_heapify(min);
    }
}

void my_queue::insert(Vertex* v){
    A.push_back(v);
    int index = A.size()-1;
    while(index > 0 and v->smaller(A[(index-1)/2]) ){
        A[index] = A[(index-1)/2];
        index = (index-1)/2;
    }
    A[index] = v;
}

Vertex* my_queue::extract_min(){
    if(A.empty())
        return NULL;
    Vertex* min = A[0];
    A[0] = A.back();
    A.pop_back();
    min_heapify(0);

    return min;
}


void my_queue::decrease_key(Vertex* v){
    for(int i = 0; i < A.size(); ++i){
        if(v == A[i]){
            while(i > 0 and v->smaller(A[(i-1)/2]) ){
                A[i] = A[(i-1)/2];
                i = (i-1)/2;
            }
            A[i] = v;
        }
    }
}