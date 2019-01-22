/**************************************************************************
 * File       [ main.cpp ]
 * Author     [ wlkb83 ]
 * Synopsis   [ demonstration for the usage of parser.h ]
 * Usage      [ ./parser [inputfileName] ]
 * Date       [ 2014/12/28 created ]
/**************************************************************************/
#include <fstream>
#include <sstream>
#include <algorithm>
#include "parser.h"
#include "router.h"
using namespace std;

bool mycompare(pair<int, int> p1, pair<int, int> p2){
    return p1.second < p2.second;
}

int main(int argc, char **argv)
{
    if( argc < 3 ){ cout << "Usage: ./router [input_file_name] [output_file_name]" << endl; return 1; }

    AlgParser parser;
    Router router;
    vector<pair<int, int>> order;
    // read the file in the first argument
    if( ! parser.read( argv[1] ) ) { return 1; }

    int h = parser.gNumHTiles();
    int v = parser.gNumVTiles();
    int c = parser.gCapacity();
    router.buildGraph(h, v, c);
    
    for (int idNet = 0; idNet < parser.gNumNets(); ++idNet){
        pair<int, int> posS = parser.gNetStart( idNet );
        pair<int, int> posE = parser.gNetEnd( idNet );
        int len = abs(posE.first - posS.first) + abs(posE.second - posS.second);
        pair<int, int> p = make_pair(idNet, len);
        order.push_back(p);
    }
    sort(order.begin(), order.end(), mycompare);
    fstream ofs(argv[2], ios::out);
    for (int i = 0; i < order.size(); ++i){
        stringstream ss;
        int length = 0;
        int idNet = order[i].first;
        pair<int, int> posS = parser.gNetStart( idNet );
        pair<int, int> posE = parser.gNetEnd( idNet );
        router.Dijkstra(posS.first, posS.second);
        router.traceback(posE.first, posE.second, length, ss);
        ofs << idNet << ' ' << length << '\n';
        ofs << ss.str();
    }

    // show the information of the input
    // fstream ofs(argv[2], ios::out);
    // for (int idNet = 0; idNet < parser.gNumNets(); ++idNet){
    //     stringstream ss;
    //     int length = 0;
    //     pair<int, int> posS = parser.gNetStart( idNet );
    //     pair<int, int> posE = parser.gNetEnd( idNet );
    //     router.Dijkstra(posS.first, posS.second);
    //     router.traceback(posE.first, posE.second, length, ss);
    //     ofs << idNet << ' ' << length << '\n';
    //     ofs << ss.str();
    // }
    return 0;
}

