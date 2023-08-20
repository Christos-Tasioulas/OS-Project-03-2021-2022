#ifndef PROCESS
#define PROCESS

class Process
{
private:
    // Primary key to seperate each process from the others
    int id; 
    // The priority
    int priority;
    // The time in seconds it takes for the process to arrive in the simulator
    double arrival_time;
    // The total life time in seconds of the process
    double life_time;
    // The time in seconds the process has left
    double remaining_time;
    // The time in seconds the process takes to execute an up() after a down()
    double critical_time;
    // The probability that the process will execute a down() in a timeslot 
    float probability;
    // It is true if the process is blocked
    bool is_blocked;
    // It is true if the process has executed a down() and has yet to execute an up()
    bool in_critical_region;

public:
    // Constructor
    Process(int id, double at, double lt, double ct, int p, float k);
    // Destructor
    ~Process();
    // Returns the id of the process
    int get_id();
    // Returns the time the process will arive 
    double get_arrival_time();
    // Returns the total life time of the process
    double get_life_time();
    // Reduces the remaining time of the process by the time given
    void reduce_life_time(double time);
    // Returns the remaining time of the process
    double get_remaining_time();
    // Returns the time the process will be in critical area
    double get_critical_time();
    // Returns the priority of the process
    int get_priority();
    // Changes the priority of the process with the priority given 
    void set_priority(int p);
    // Blocks the processs (changes is_blocked to true)
    void block();
    // Unblocks the processs (changes is_blocked to false)
    void unblock();
    // Returns true if the process is blocked and false if it is not
    bool process_is_blocked();
    // The process has entered the critical regiion so it sets to true the in_critical_region member
    void enter_critical_region();
    // The process has left the critical regiion so it sets to false the in_critical_region member
    void leave_critical_region();
    // Returns true if the process is in critical region, otherwise, it returns false 
    bool is_in_critical_region();
    // Prints the process and its main characteristics
    void printProcess();
};

#endif
