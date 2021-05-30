#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <unistd.h> 
#include<signal.h>
#include <sys/wait.h>
#include "coordinator.h"
#include "node.h"
#include "myhie.h"


using namespace std;

//to keep track of number of signals received by root
int SIGNALCOUNT=0;

void signalHandler(int signal)
{
    SIGNALCOUNT++;
	printf("Root node received signal %d!\n\n",signal);
	if (signal==SIGCHLD) {
		// printf("Child ended\n");
		wait(NULL);
	}
}


int main(int argc, char** argv)
{
    
    char filename[1024];
    char output_file[1024];
    char order[1024];
    char attribute_number[1024];
    char num_workers[1024];
    char random[24];
    strcpy(random, "0"); //random initializd as 0 when r is not there

    signal(SIGUSR1,signalHandler); //for worker processes
    signal(SIGUSR2, signalHandler); //for merger process


    for (int i=0; i<argc-1; i++) //reading the command line to determine arduments (what follows each flag)
	{
		if (strcmp((argv[i]),"-i")==0 && (i+1<argc)) 
		{
			strcpy (filename,(argv[i+1]));
		}
        if (strcmp((argv[i]),"-r")==0 || strcmp((argv[i+1]),"-r")==0) 
		{
			strcpy(random,"1");
		}
        if (strcmp((argv[i]),"-k")==0 && (i+1<argc)) 
		{
            strcpy(num_workers, argv[i+1]);
		}
        if (strcmp((argv[i]),"-a")==0 && (i+1<argc)) 
		{
            strcpy(attribute_number, argv[i+1]);
		}
        if ((strcmp((argv[i]),"-o")==0 && (i+1<argc))) 
		{
			strcpy(order,(argv[i+1]));
		}
        if (strcmp((argv[i]),"-s")==0 && (i+1<argc)) 
		{
			strcpy(output_file,(argv[i+1]));
		}
	}

    //reading the file to count number of entries
    FILE* my_file= fopen(filename,"r");

    if (my_file == NULL){
        printf("failed to open file\n");
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    int i=0;
    int numentry=0;

    
    //reading a file line by line reference: https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
    do{
        i++;
    }while ((read = getline(&line, &len, my_file) != -1)); //using do while so that we dont skip the first line.

    numentry=i-1;
    
    //root node is current prg, fork creates child which is coordinator
    pid_t pid;

    //referenec: lab sessions in recitation
    switch (pid = fork()) { //fork creates coordinator node
        case -1:
        // On error fork() returns -1.
        perror("fork failed");
        exit(EXIT_FAILURE);
        case 0:
        coordinator(filename, random, num_workers, order, attribute_number, output_file, numentry);
        break;
        default:
        printf("ROOT NODE CREATED WITH PID [%d]\n\n", getpid());
        wait(NULL);
        printf("NUMBER OF SIGNALS RECEIVED BY ROOT NODE: : %d\n\n", SIGNALCOUNT);
        exit(EXIT_SUCCESS);
    }


    return 0;
}