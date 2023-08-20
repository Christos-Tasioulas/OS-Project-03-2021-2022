#ifndef SIMULATOR
#define SIMULATOR
#include <semaphore.h>
#include "Interface.h"

class Simulator
{
private:
    // the average arrival time of all processes
    double avg_process_arrival_time;
    // the average life time of all processes
    double avg_process_life_time;
    // the average time it takes all processes to execute an up() after a down
    double avg_execution_time;
    // the number of all processes
    int max_processes;
    // the number of semaphores
    int numOfSemaphores;
    // the probability of a process to a execute a down() in a timeslot 
    float probability_of_entry;
    // the heap with the processes sorted by arrival time
    Heap* processes;
    // an array with all the semaphores
    Semaphore** semaphores;

public:
    // Constructor
    Simulator(double at, double lt, double ct, int processes, float k, int semaphores, Heap* h);
    // Destructor
    ~Simulator();
    // Function that runs the simulator
    void run();
};


#endif