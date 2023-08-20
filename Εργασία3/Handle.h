// This file connects the main function with the function handling the pipes and the child processes
#ifndef HANDLE
#define HANDLE
#include <iostream>
#include <string>

using namespace std;

// Takes control of the program after working with the run command arguments in the main function
// Returns the line an error occured or 0 if it worked properly
int handle(int numProcesses, int numSemaphores, float k);

#endif