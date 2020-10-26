#include <iostream>
#include "maxPlanarSubset.h"
#include <time.h> 
using namespace std;

int main(int argc, char** argv){
    time_t start, end;
    start = time(NULL);
    if(argc != 3)
        return -1;
    MPS* mgr = new MPS();
    if(!mgr->parse(argv[1]))
        return -1;
    end = time(NULL);
    printf("parse Time = %f\n", difftime(end, start));
    mgr->assign();
    mgr->output(argv[2]);
    end = time(NULL);
    printf("Time = %f\n", difftime(end, start));
    return 0;
}