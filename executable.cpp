#include "executable.h"
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <unistd.h> 
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


//function to insert items (as given by the generated ranges into arrays of size specified by range)
//tracking the range and beginning point to avoid redundancy in reading the file
node** insert_into_array(const char* filename, int size, int index, int range, int begin){
    int rid;
    char fname[100];
    char lname[100];
    int num_dependants;
    float income;
    int postalcode;

    FILE* my_file= fopen(filename,"r");

    if (my_file == NULL){
        printf("failed to open file\n");
        exit(EXIT_FAILURE);
    }
        
   
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    //creating sorter array in each child
    node** sorterarray; 
    sorterarray = new node*[range];
    int i=0;
    int count=0;

    //start and end points to read from file
    int start = begin;
    int end = begin + range;
    int j =0;
    
    //reading a file line by line reference: https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
    do{
        fscanf(my_file, "%d %s %s %d %f %d", &rid, fname, lname, &num_dependants, &income, &postalcode);
        if (i>=start && i<end){
            sorterarray[j] = new node(rid, fname, lname, num_dependants, income, postalcode);
            j++;
        }
        i++;
    }while ((read = getline(&line, &len, my_file) != -1) && i<size); //using do while so that we dont skip the first line.

    return sorterarray;
}




int main(int argc, char** argv){
    int LENGTH = 600;

    // ref for time https://stackoverflow.com/questions/1444428/time-stamp-in-the-c-programming-language

    //keeping track of time for each worker
    clock_t c0 = clock();
  
    char filename[1024];
    char output_file[1024];
    char order[1024];

    int attribute_number = atoi(argv[5]);
    int num_workers = atoi(argv[3]);

    int random = atoi(argv[2]);
    int i = atoi(argv[7]);

    char index_of_sorter[100];
    strcpy(index_of_sorter,argv[7]);

    int numentry = atoi(argv[8]);
    int randomrange = atoi(argv[9]);
    int begin = atoi(argv[10]);
    pid_t rootpid = atoi(argv[11]);

    strcpy(filename, argv[1]);
    strcpy(order, argv[4]);
    strcpy(output_file, argv[6]);

    //sorter array to use insertion or bubble sort on
    node** sorterarray = insert_into_array(filename, numentry, i, randomrange, begin);
    //sortED array to store the sorted array from each worker - this is what we send thorugh the pipe
    node** sortedarray;

    //even workers use insertion sort, odd workers use bubble sort
    if (i % 2 ==0){
            sortedarray= insertion_sort(sorterarray, randomrange, order, attribute_number);
        }
        else{
            sortedarray= bubble_sort(sorterarray, randomrange, order, attribute_number);
        }
  
    clock_t c1 = clock();
    double runtime_diff_ms = (c1 - c0) * 1000. / CLOCKS_PER_SEC;


    // printf("TIME TAKEN for worker [%d]:  %f ms\n \n", i, runtime_diff_ms);

    // ------ pipe
    //named pipe to send one record at a time, reference from lab session

    int fd; 
    char * myfifo = "myfifo"; 
    mkfifo(myfifo, 0777); 

    char* arr = new char[600];
    fd = open(myfifo, O_WRONLY);
    for (int item =0;item<randomrange; item++){
        arr= sortedarray[item]->node_to_string(i, runtime_diff_ms);
        write(fd, arr, strlen(arr));   
    }
    close(fd); 


//freeing memory
    for (int i=0;i<randomrange;i++){
        delete[] sorterarray[i];
    }
    delete[] sorterarray;
    kill(rootpid,SIGUSR1);
    return 0;
}
