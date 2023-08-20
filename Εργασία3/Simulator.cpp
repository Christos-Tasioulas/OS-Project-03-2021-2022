#include "Simulator.h"
#include <cstdlib>
#include <iostream>
#include <time.h>

// counting the time that has passed since the start of the simulation
static double current_time_slot = 0.0;

// Assistant Functions

/*/
 * Compares priorities arrival times and if a process is blocked
 * Prioritizes if the processes are blocked.
 * If both are blocked it returns 0
 * If the first is blocked it returns -1
 * If the second one is blocked it returns 1
 * Secondly, it checks if the processes have arrived
 * If both have not arrived its return doesn't matter
 * If the first one has arrived it returns 1
 * If the second one has arrived it returns -1
 * If both have arrived it returns the difference of their priorities 
/*/
static int compare_priorities_and_arrivals(void* i1, void* i2)
{
    Process* p1 = (Process*) i1;
    Process* p2 = (Process*) i2;

    // case if both the processes are blocked
    if(p1->process_is_blocked() && p2->process_is_blocked()) return 0;
    // case if the first one is blocked
    else if(p1->process_is_blocked()) return -1;
    // case if the second one is blocked
    else if(p2->process_is_blocked()) return 1;

    int priority1 = p1->get_priority();
    int priority2 = p2->get_priority();
    double at1 = p1->get_arrival_time();
    double at2 = p2->get_arrival_time();

    // case if none of the processes have arrived
    if(at1 < current_time_slot && at2 < current_time_slot)
    {
        return priority1 - priority2;
    }
    // case if the first one hasn't arrived yet 
    else if(at1 < current_time_slot) return -1;
    // case if the second one hasn't arrived yet
    else if(at2 < current_time_slot) return 1;
    // case if both processes have arrived
    else return priority1 - priority2;
}

// returns if the process will perform down
bool PerformDown(float k)
{
    // we decide if the process will perform down if the randomizer gives a result less or equal than given k
    float roll = (float) rand()/RAND_MAX;
    return roll <= k;
}

// we choose one of the semaphores in the array randomly
// returns the chosen semaphore
Semaphore* chooseSemaphore(Semaphore** S, int numOfSemaphores)
{
    int semaphore = rand() % numOfSemaphores;
    return S[semaphore];
}

// checks a semaphore if it is time to execute an up
// returns true if an up was executed
bool check_for_ups(Semaphore* S, double down_time, double q)
{
    Process* P = S->getCurrentProcess();
    // we don't need to continue if a down has not been executed yet 
    if(P == NULL) return false;
    double critical_time = P->get_critical_time();
    double remaining_time = P->get_remaining_time();
    // an up will be executed if the process critical time has passed or if it is about to die to avoid deadlocks
    if(current_time_slot >= critical_time + down_time || remaining_time <= q) 
    {
        // up
        S->up();
        // the first failed down can be upped now
        if(S->getProcessQueue()->get_size()) down_time = current_time_slot;
        return true;
    }

    return false;
}

// assistant function to update waiting times for processes
void pre_order1(BinaryTreeNode* node, int* total_wait_time)
{
    if(node != NULL)
    {
        Process* P = (Process*) node->get_value();
        // the waiting time is updated by one timeslot if the process has arrived and it is not blocked 
        if(P->process_is_blocked() == false)
        {
            if(P->get_arrival_time() <= current_time_slot) total_wait_time[P->get_priority()-1]++;
        }
        // update the waiting time for the node's children
        pre_order1(node->get_left_child(), total_wait_time);
        pre_order1(node->get_right_child(), total_wait_time);
    }    
}

// updating waiting times for processes waiting sorted by priority
void update_waiting_times(int* total_wait_time, Heap* priority_processes)
{
    pre_order1(priority_processes->get_root(), total_wait_time);
}

// assistant function to update waiting times for processes
void pre_order2(BinaryTreeNode* node, Semaphore *S, int* total_blocking_time)
{
    if(node != NULL)
    {
        Process* P = (Process*) node->get_value();
        // if the current process inside the queue has smaller priority than the one running we update the timer by a timeslot
        if(S->getCurrentProcess()->get_priority() < P->get_priority()) total_blocking_time[P->get_priority()-1]++;
        // update the blocking time for the node's children
        pre_order2(node->get_left_child(), S, total_blocking_time);
        pre_order2(node->get_right_child(), S, total_blocking_time);
    }
}

// updating times for processes blocked by processes with smaller priority sorted by priority
void update_blocking_times(int* total_blocking_time, Semaphore** S, int numOfSemaphores)
{
    // Checking every semaphore if they have blocked processes in their queues
    for(int i=0; i<numOfSemaphores; i++)
    {
        pre_order2(S[i]->getProcessQueue()->get_root(), S[i], total_blocking_time);
    }
}

// emptying the list of processes and deleting its elements(processes)
void empty_list(List* list)
{
    ListNode* node = list->get_first();
    while(node != NULL)
    {
        Process* P = (Process*) node->get_value();
        delete P;
        node = node->get_next();
    }
}

// Constructor
Simulator::Simulator(double at, double lt, double ct, int processes, float k, int semaphores, Heap* h)
{
    this->avg_process_arrival_time = at;
    this->avg_process_life_time = lt;
    this->avg_execution_time = ct;
    this->max_processes = processes + 1;
    this->probability_of_entry = k;
    this->numOfSemaphores = semaphores;
    this->processes = h; 

    // constructing the semaphores
    this->semaphores = new Semaphore*[this->numOfSemaphores];

    for(int i=0; i<numOfSemaphores; i++)
    {
        this->semaphores[i] = new Semaphore(i);
    }
}

// Destructor
Simulator::~Simulator()
{
    // deleting the semaphores but not the heap, it is an outside element
    for(int i=0; i<numOfSemaphores; i++)
    {
        delete this->semaphores[i];
    }
    delete[] this->semaphores;
    
}

// Function that runs the simulator
void Simulator::run()
{
    // the timeslot is 0.1s
    double q = 0.1;

    // initializing arrays
    // array that counts processes with a certain priority, each index for a particular priority
    int process_with_priority[7] = {0, 0, 0, 0, 0, 0, 0};
    // array that counts processes total waiting time sorted by priority
    int total_wait_time[7] = {0, 0, 0, 0, 0, 0, 0};
    // array that counts processes total blocking time by processes with smaller priority sorted by priority
    int total_blocking_time[7] = {0, 0, 0, 0, 0, 0, 0};
    // array that counts the time the last successful down was performed for each semaphore
    double down_times[numOfSemaphores];

    // initializing the time for each semaphore
    for(int i = 0; i<numOfSemaphores; i++)
    {
        down_times[i] = 0.0;
    }

    // a heap that sorts processes by blocking, priority and arrival
    Heap* prioritized_processes = new Heap();
    // a list that contains all the processes
    List* process_list = new List();

    /*/
     * transferring the processes from the initial heap to the new one and the list
     * we also count the processes according to their priority
    /*/
    while(this->processes->get_size())
    {
        Process* P;

        P = (Process*) this->processes->get_min();
        this->processes->RemoveMin(compareArrivalTimes);

        process_with_priority[P->get_priority() - 1]++;
        
        prioritized_processes->HeapInsert(P, compare_priorities_and_arrivals);

        process_list->ListInsertLast(P);
    }

    // counting the processes we completed for debugging reasons
    int completed = 0;

    // we examine each process until all of them finish
    while(prioritized_processes->get_size())
    {
        // we take the first process
        Process* P;
    
        P = (Process*) prioritized_processes->get_min();

        double at = P->get_arrival_time();

        // case the process has not arrived 
        if(at > current_time_slot)
        {
            // increasing time
            current_time_slot = current_time_slot + q;
            // reorganizing the heap because arrivals have changed 
            prioritized_processes->heapify_all(compare_priorities_and_arrivals);
            continue;
        }

        // we don't need the process right now inside the heap
        prioritized_processes->RemoveMin(compare_priorities_and_arrivals);

        // the process must not be blocked or in critical region (after executing down() and before executing up()) or about to die
        if(!(P->process_is_blocked()) && !(P->is_in_critical_region()) && (P->get_remaining_time() > q))
        {
            // the process will perform down
            if(PerformDown(this->probability_of_entry))
            {
                // choosing the semaphore to execute down() in
                Semaphore* S = chooseSemaphore(this->semaphores, numOfSemaphores);

                // down happens
                bool down = S->down(P, total_blocking_time);

                // if down is successful we store the time it happened
                if(down) down_times[S->get_id()] = current_time_slot;
                // if it failed we reorganize the heap since the current process is blocked
                else prioritized_processes->heapify_all(compare_priorities_and_arrivals);
            }
        }

        // we check each semaphore if an up can be performed
        for(int i=0; i<numOfSemaphores; i++)
        {
            bool up = check_for_ups(this->semaphores[i], down_times[i], q);
            // if an up is successful the heap must be reorganised because some processes will be unblocked
            if(up) prioritized_processes->heapify_all(compare_priorities_and_arrivals);
        }
        
        // we update waiting times and blocking times for all processes sorted by priority
        update_waiting_times(total_wait_time, prioritized_processes);
        update_blocking_times(total_blocking_time, this->semaphores, numOfSemaphores);

        // case if the process will die in the timeslot
        if(P->get_remaining_time() <= q) 
        {
            completed++;
            current_time_slot = current_time_slot +  q;
            // reorganizing the heap since arrivals might have changed
            prioritized_processes->heapify_all(compare_priorities_and_arrivals);
            continue;
        }

        // reducing the life time of a process if it is not blocked
        if(!(P->process_is_blocked())) 
        {
            P->reduce_life_time(q);   
        } 

        // the process has not finished so the process will be inserted back in the heap
        prioritized_processes->HeapInsert(P, compare_priorities_and_arrivals);
        // increasing the time
        current_time_slot = current_time_slot + q;
        // reorganizing the heap since arrivals might have changed
        prioritized_processes->heapify_all(compare_priorities_and_arrivals);
        
    }

    cout << completed << " processes completed " << endl << endl;

    // Calculating and printing the average waiting times of all processes sorted by priority
    cout << "Average waiting time" << endl;
    for(int priority = 0; priority <7; priority++)
    {
        // we can't divide by zero
        if(process_with_priority[priority])
        {
            float average_waiting_time = ((float) total_wait_time[priority]) / ((float) process_with_priority[priority]);
            cout << average_waiting_time << " timeslots for processes with priority " << priority+1 << endl;
        }
        
    }

    // Calculating and printing the average blocking times by processes with smaller priority of all processes sorted by priority
    cout << endl << "Average blocking time by smaller priority" << endl;
    for(int priority = 0; priority <7; priority++)
    {
        // we can't divide by zero
        if(process_with_priority[priority])
        {
            float average_blocking_time = ((float) total_blocking_time[priority]) / ((float) process_with_priority[priority]);
            cout <<  average_blocking_time << " timeslots for processes with priority " << priority+1 << endl;
        }
        
    }

    // deleting the processes
    empty_list(process_list);
    // deleting the new heap and the new list
    delete prioritized_processes;
    delete process_list;
}

