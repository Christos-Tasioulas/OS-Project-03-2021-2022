#include <cstdlib>
#include "Handle.h"

int main(int argc, char* argv[])
{
    // Checking if we have the right number of arguments
    if(argc != 4)
    {
        cout << "Usage: ./simulator numProcesses k numSemaphores" << endl;
        return -1;
    }

    // this are the variables we will use instead of the argv array
    int numProcesses = atoi(argv[1]);
    float k = atof(argv[2]);
    int numSemaphores = atoi(argv[3]);

    // this is where the program starts creating processes
    int line = handle(numProcesses, numSemaphores, k);
    if(line)
    {
        cout << "Error at line " << line << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}