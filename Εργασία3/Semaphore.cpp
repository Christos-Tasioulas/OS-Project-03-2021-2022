#include "Semaphore.h"

// Assistant function that the blocking process inherits the priority of the blocked one if its own priority is smaller than the one of the blocked process
void priority_inversion(Process* new_process, Process* blocking_process, int* total_blocking_time)
{
    int p1 = new_process->get_priority();
    int p2 = blocking_process->get_priority();

    if(p1 < p2)
    {
        // starting the blocking time
        total_blocking_time[p1-1]++;
        new_process->set_priority(p2);
        blocking_process->set_priority(p1);
    }
}

// comapres the processes based on their priorities
int compare_priorities(void* i1, void* i2)
{
    Process* p1 = (Process *) i1;
    Process* p2 = (Process *) i2;
    
    int priority_1 = p1->get_priority();
    int priority_2 = p2->get_priority();

    return priority_1-priority_2;
}

// Constructor 
// the semaphore's id is passed as an argument
Semaphore::Semaphore(int n)
{
    this->id = n;
    this->value = 1;
    this->CurrentProcess = NULL;
    // creating the heap
    this->ProcessQueue = new Heap();
}

// Destructor
Semaphore::~Semaphore()
{
    this->CurrentProcess = NULL;
    // deleting the heap
    delete this->ProcessQueue;
}

// Down: returns true if successful
bool Semaphore::down(Process* P, int* total_blocking_time)
{
    // decreasing the value
    value--;
    // if the value equals 0
    if (value == 0) {
        
        // the process has entered the critical region
        this->CurrentProcess = P;
        P->enter_critical_region();
    }
    else if(value <= 0)
    {
        // the process has been blocked 
        this->ProcessQueue->HeapInsert(P, compare_priorities);
        P->block();

        // checking if it is a case of priority inversion
        priority_inversion(P, this->CurrentProcess, total_blocking_time);

        return false;
    }

    return true;

}

// Up
void Semaphore::up()
{
    // increasing the value
    value++;
    // the process has left the critical region
    if(this->CurrentProcess != NULL) this->CurrentProcess->leave_critical_region();
    // case if the value is less than 1
    if (value <= 0) {
        // the first process of the queue has been unblocked and it has entered the critical region
        this->CurrentProcess = (Process*) this->ProcessQueue->get_min();
        this->CurrentProcess->unblock();
        this->CurrentProcess->enter_critical_region();
        this->ProcessQueue->RemoveMin(compare_priorities);
        
    }
    // or the semaphore has no processes left
    else this->CurrentProcess = NULL;

}

// Returns the id of the semaphore
int Semaphore::get_id()
{
    return this->id;
}

// Returns the current process of the semaphore
Process* Semaphore::getCurrentProcess()
{
    return this->CurrentProcess;
}

// Returns the priority queue with all the blocked processes
Heap* Semaphore::getProcessQueue()
{
    return this->ProcessQueue;
}