#include "Handle.h"
#include "Simulator.h"
#include <random>
#include <time.h>

// returns an array with exponentially distributed values
double* ed(int rolls, float lambda)
{
    default_random_engine generator;
    exponential_distribution<double> distribution(lambda);

    double *p = new double[rolls];

    for (int i=0; i<rolls; ++i) {
        double number = distribution(generator);
        p[i] = number;
    }

    return p;
}

// returns an array with uniformally distributed values
int* ud(int rolls)
{
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1,7);

    int *p = new int[rolls];

    for (int i=0; i<rolls; ++i) {
        int number = distribution(generator);
        p[i] = number;
    }

    return p;
}

// returns the average of the array members
double average(double* array, int array_size)
{
    double sum = 0.0;
    for(int i=0; i<array_size; i++)
    {
        sum += array[i];
    }
    return sum/((double) array_size);
}

// Takes control of the program after working with the run command arguments in the main function
// Returns the line an error occured or 0 if it worked properly
int handle(int numProcesses, int numSemaphores, float k)
{
    srand( (unsigned)time( NULL ) );

    // we have to maintain that life time of a process is greater than its critical time so the second lambda is 25 times smaller than the third one
    double* arrival_times = ed(numProcesses, 0.075);
    double* life_times = ed(numProcesses, 0.025);
    double* critical_times = ed(numProcesses, 0.0625);
    int* priorities = ud(numProcesses);
    
    // calculating the average times for each process
    double avg_arrival_time = average(arrival_times, numProcesses);
    double avg_life_time = average(life_times, numProcesses);
    double avg_critical_time = average(critical_times, numProcesses);

    // printing the average times
    cout << "Average arrival time: " << avg_arrival_time << endl;
    cout << "Average life time: " << avg_life_time << endl;
    cout << "Average critical time: " << avg_critical_time << endl << endl;
    
    // creating a heap to insert the processes sorted by arrival time
    Heap* processes = new Heap();

    for(int i=0; i<numProcesses; i++)
    {
        // each process takes the times corresponding to its id as index
        Process* P = new Process(i, arrival_times[i], life_times[i], critical_times[i], priorities[i], k);
        processes->HeapInsert(P, compareArrivalTimes);
    }

    // creating and running the simulator
    Simulator* S = new Simulator(avg_arrival_time, avg_life_time, avg_critical_time, numProcesses, k, numSemaphores, processes);

    S->run();


    // delete functions
    delete processes;
    delete S;
    delete[] priorities;
    delete[] arrival_times;
    delete[] life_times;
    delete[] critical_times;

    return 0;
}