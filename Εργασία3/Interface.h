// This is the file that has useful functions for many modules
#ifndef INTERFACE
#define INTERFACE

#include <iostream>
#include "Semaphore.h"

using namespace std;

// compares processes by arrival times
int compareArrivalTimes(void *i1, void *i2);

// visits to print processes
void visit_process(void *process);

#endif