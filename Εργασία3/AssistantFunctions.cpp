#include "Interface.h"

using namespace std;

// compares processes by arrival times
int compareArrivalTimes(void *i1, void *i2)
{
    Process* p1 = (Process *) i1;
    Process* p2 = (Process *) i2;

    double d1 = p1->get_arrival_time();
    double d2 = p2->get_arrival_time();

    // using integers to describe decimal results
    if(d1 == d2)
    {
        return 0;
    }
        
    if(d1 < d2)
    {
        return -1;
    }
        
    return 1;
}

// visits to print processes
void visit_process(void *process)
{
    Process* P = ((Process *) process);
    P->printProcess();
}