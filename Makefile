all: myhie executable 

myhie: myhie.o node.o coordinator.o insertionsort.o bubblesort.o
	g++ myhie.o node.o coordinator.o insertionsort.o bubblesort.o -o myhie

myhie.o: myhie.cpp node.h coordinator.h insertionsort.h bubblesort.h
	g++ -c myhie.cpp

node.o: node.cpp
	g++ -c node.cpp 

insertionsort.o: insertionsort.cpp
	g++ -c insertionsort.cpp

bubblesort.o: bubblesort.cpp
	g++ -c bubblesort.cpp

executable:executable.o node.o
	g++ executable.o node.o insertionsort.o bubblesort.o -o executable

executable.o: executable.cpp node.h insertionsort.h bubblesort.h 
	g++ -c executable.cpp

coordinator.o: coordinator.cpp
	g++ -c coordinator.cpp

clean:
	rm *.o myhie node executable myfifo outputfile


