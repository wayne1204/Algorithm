#include <iostream>
#include "maxPlanarSubset.h"
using namespace std;

int main(int argc, char** argv){
    if(argc != 3)
        return -1;
    MPS* mgr = new MPS();
    if(!mgr->parse(argv[1]))
        return -1;
    mgr->assign();
    mgr->output(argv[2]);
    return 0;
}