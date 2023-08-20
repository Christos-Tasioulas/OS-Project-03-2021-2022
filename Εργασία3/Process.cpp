#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include "Process.h"

using namespace std;

// Constructor
Process::Process(int id, double at, double lt, double ct, int p, float k)
{
    this->id = id;
    this->arrival_time = at;
    this->life_time = lt;
    this->remaining_time = lt;
    this->critical_time = ct;
    this->priority = p;
    this->probability = k;
    // process starts unblocked and not in critical region
    this->is_blocked = false;
    this->in_critical_region = false;
}

// Destructor
Process::~Process()
{
    // Empty
}

// Returns the id of the process
int Process::get_id()
{
    return this->id;
}

// Returns the time the process will arive
double Process::get_arrival_time()
{
    return this->arrival_time;
}

// Returns the total life time of the process
double Process::get_life_time()
{
    return this->life_time;
}

// Reduces the remaining time of the process by the time given
void Process::reduce_life_time(double time)
{
    this->remaining_time -= time;
}

// Returns the remaining time of the process
double Process::get_remaining_time()
{
    return this->remaining_time;
}

// Returns the time the process will be in critical area
double Process::get_critical_time()
{
    return this->critical_time;
}

// Returns the priority of the process
int Process::get_priority()
{
    return this->priority;
}

// Changes the priority of the process with the priority given 
void Process::set_priority(int p)
{
    this->priority = p;
}

// Blocks the processs (changes is_blocked to true)
void Process::block()
{
    this->is_blocked = true;
}

// Unblocks the processs (changes is_blocked to false)
void Process::unblock()
{
    this->is_blocked = false;
}

// Returns true if the process is blocked and false if it is not
bool Process::process_is_blocked()
{
    return this->is_blocked;
}

// The process has entered the critical regiion so it sets to true the in_critical_region members
void Process::enter_critical_region()
{
    this->in_critical_region = true;
}

// The process has left the critical regiion so it sets to false the in_critical_region member
void Process::leave_critical_region()
{
    this->in_critical_region = false;
}

// Returns true if the process is in critical region, otherwise, it returns false 
bool Process::is_in_critical_region()
{
    return this->in_critical_region;
}

// Prints the process and its main characteristics
void Process::printProcess()
{
    cout << "Process " << this->id << ": " << " ";
    cout << "Arrival time " << this->arrival_time << " ";
    cout << "Life time " << this->remaining_time << " ";
    cout << "Critical Time " << this->critical_time << " ";
    cout << "Priority " << this->priority << " ";
}