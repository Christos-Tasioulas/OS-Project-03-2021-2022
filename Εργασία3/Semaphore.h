#ifndef SEMAPHORE
#define SEMAPHORE

#include "Heap.h"
#include "Process.h"
#include <cstdlib>

class Semaphore
{
private:
    // The id exists to seperate each semaphore from the others
    int id; 
    // value starts with 1
    int value;
    // the process that downed the semaphore's value to 0
    Process* CurrentProcess;
    // a queue with processes that have been blocked
    Heap* ProcessQueue;

public:
    // Constructor
    Semaphore(int n);
    // Destructor
    ~Semaphore();
    // Down: returns true if successful
    bool down(Process* P, int* total_blocking_time);
    // Up
    void up();
    // Returns the id of the semaphore
    int get_id();
    // Returns the current process of the semaphore
    Process* getCurrentProcess();
    // Returns the priority queue with all the blocked processes 
    Heap* getProcessQueue();
};


#endif