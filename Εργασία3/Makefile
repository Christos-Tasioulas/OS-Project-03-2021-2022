# sample Makefile that you can quickly adapt to your needs
# set compiler options here
CPPFLAGS=-g -Wall -g3 -std=c++11 -pthread -lpthread -lrt

# set the name of the executable file to compile here
program=simulator

# list object files needed to compile the program
# objects=main.o Process.o  Solution.o
objects=main.o Handle.o Simulator.o Process.o Semaphore.o Heap.o CompleteBinaryTree.o BinaryTree.o Queue.o List.o AssistantFunctions.o 

# arguments to run the program
args = 22 0.75 3

# this makes the program. It's the first rule so it will be executed if you give just 'make'
$(program) : $(objects)
	g++ $(CPPFLAGS) $(objects) -o $(program)

# list .h dependencies for each .o (dependency on .c is automatically set by make!)
main.o : Handle.h
Handle.o : Handle.h Process.h
Simulator.o : Simulator.h 
Process.o : Process.h
Semaphore.o : Semaphore.h
Heap.o: Heap.h
CompleteBinaryTree.o: CompleteBinaryTree.h
BinaryTree.o: BinaryTree.h
Queue.o: Queue.h
List.o: List.h
AssistantFunctions.o: Interface.h

# this allows to quickly remove all generated files with 'make clean'
clean:
	rm $(program) $(objects)

# run the program with 'make run'. Sometimes useful to avoid rewriting long commands.
run: $(program)
	./$(program) $(args)	

valgrind: $(program)
	valgrind --track-origins=yes ./$(program) $(args)