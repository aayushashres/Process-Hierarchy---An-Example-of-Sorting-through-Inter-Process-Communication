#include "coordinator.h"
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <unistd.h> 
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

using namespace std;


//reference: page 1201 in The Linux Programming inTerface A Linux and UNIX® System Programming Handbook by Michael Kerrisk
ssize_t
readLine(int fd, char *buffer, size_t n)
{
    ssize_t numRead; //the number of bytes of the last read
    size_t totRead; //the total bytes read
    char *buf;
    char ch;

    if (n<=0 || buffer==NULL){
        errno =EINVAL;
        return -1;
    }
    buf = buffer;
    totRead=0;
    for(;;){
        numRead=read(fd,&ch,1);

        if (numRead== -1){ //restarts the read
            if(errno==EINTR){
                continue;
            }else{
                return -1;
            }
        }else if(numRead==0){ //reached the end of file
            if(totRead==0){
                return 0;
            }
            else{
                break; //goes to \0 so end of line is added
            }
        }else{
            if (totRead<n-1){ //adding to buf
                totRead++;
                *buf++=ch;
            }
            if(ch=='\n'){  //delimiter 
                break;
            }
        }
    }
    *buf='\0';
    return totRead;
}



void coordinator(char filename[1024] ,char random1[24], char num_worker1[1024], char order[1024], char attribute_number1[1024], char output_file[1024], int numentry ){

    int random = atoi(random1);
    int num_workers = atoi(num_worker1);
    int attribute_number = atoi(attribute_number1);

    pid_t rootpid = getppid();

    int randomranges[num_workers];
    int random_range=numentry;
    int random_size;
    int startplacearray[num_workers];
    
    //variables to get time taken by merger
    double runtime_diff_ms;
    clock_t c0;
    clock_t c1;

    for (int i =0;i<num_workers;i++){
         // generating random numbers for random ranges: https://www.cplusplus.com/reference/cstdlib/rand/
         if (random==1){
             srand (time(NULL));
             random_size= rand() % random_range +1;
             randomranges[i]=random_size;
         }
         else{ //if not random, generating even sizes
             random_size= numentry/num_workers;
             randomranges[i]=random_size;
         }

         if (i==num_workers-1){ //making sure all elements fall into a range - not to miss out on the last bunch
             randomranges[i]=random_range;
         }

         random_range-=random_size; 
    }
    
    for (int i=0;i<num_workers;i++){ //list of beginning points (in the main file) for each sorter array - convenient when reading from file into sorter arrays
        int startat=0;
        for(int l=0; l<i;l++){
            startat+= randomranges[l];
        }
        startplacearray[i]=startat;
    }

    //MERGER NODE HERE
    if(fork()==0){
        // printf("Reached merger with pid %d\n", getpid());
        int fd1; 
  
        // FIFO file path : reference: recitation sessions
        char * myfifo = "myfifo"; 
    
        mkfifo(myfifo, 0777); 
    
        int LENGTH = 600;
        char str1[LENGTH]; 

        //array to get all sorted arrays
        node** mergerarray;
        mergerarray = new node*[numentry];

        //the final sorted array
        node** finalarray;
        finalarray = new node*[numentry];

        int rid;
        int num_dependants, postalcode;
        float income;
        char fname[100];
        char lname[100];
        char readline[1000];
        int index=0;
        int i;
        float timetaken;
        float timearray[numentry];

        //starting timer
        c0 = clock();
        fd1 = open(myfifo, O_RDONLY); 

        FILE* filedirectory;
        filedirectory = fopen(output_file, "w");
        fclose(filedirectory);

        

        //reading sorted arrays from each worker through pipe and putting it into array of size n (n is number of entries)
        while(index<numentry){
            if (readLine(fd1, str1, LENGTH)==0){
                continue;
            }
            sscanf(str1, "%d %d %s %s %d %f %d %f", &i, &rid, fname, lname, &num_dependants, &income, &postalcode, &timetaken);
            mergerarray[index] = new node(rid, fname, lname, num_dependants, income, postalcode);
            
            timearray[i] = timetaken;
            index++;
        }
        
        close(fd1);

        //writing the time taken by each worker to the outputfile
        char timeinstring[100];
        filedirectory = fopen(output_file, "a");
        for (int n=0;n<num_workers;n++){
            sprintf(timeinstring, "%f", timearray[n]);
            
            fprintf(filedirectory, "Time taken by worker [%d] : %s ms\n", n, timeinstring);
            printf("TIME TAKEN by worker [%d]:  %f ms\n \n", n, timearray[n]);

            
        }
        fclose(filedirectory);
        
        //sorting the array
        finalarray = insertion_sort(mergerarray, numentry, order, attribute_number);
        
        //displaying sorted array
        for (int i=0;i<numentry;i++){
            printf("[%d] ", i);
            finalarray[i]->display();
        }

        //writing sorted array to the file
        char records[600];
        filedirectory = fopen(output_file, "a");
        for (int n=0;n<numentry;n++){
            //reference: https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
            sprintf(records, "%s", finalarray[n]->node_in_string_format());
            fprintf(filedirectory, "%s", records);
            
        }
        fclose(filedirectory);

        //writing time to merger
        c1 = clock();
        runtime_diff_ms = (c1 - c0) * 1000. / CLOCKS_PER_SEC;
        printf("TIME TAKEN BY [MERGER]: %f ms \n", runtime_diff_ms);

         //calculating time
    
        char totaltime[100];
        sprintf(totaltime, "%f", runtime_diff_ms);
        filedirectory = fopen(output_file, "a");
        fprintf(filedirectory, "TIME TAKEN BY MERGER: %s ms \n\n", totaltime);
        fclose(filedirectory);
  

    //freeing memory
        for (int i =0;i<num_workers;i++){
            delete[] mergerarray[i];       
        }
        delete[] mergerarray;

        //sending signal to root
        kill(rootpid,SIGUSR2);
        exit(0);
    }
   


    //creating worker processes
    pid_t execpid;
    int s;
    pid_t child_pids[num_workers];
    // refernce: for creating n children from same parent: recitation sessions and the link below
    //https://www.geeksforgeeks.org/create-n-child-process-parent-process-using-fork-c/ 
    for(int i=0;i<num_workers;i++) // loop will run n times  
    { 
        if((execpid = fork()) == 0) 
           
        { 
            //ref for getting cwd: https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program

            // printf("[child] pid %d from [parent] pid %d\n",getpid(),getppid()); 
            child_pids[i]=getpid();

            long path_max;
            size_t size;
            char *buf;
            char *ptr;


            path_max = pathconf(".", _PC_PATH_MAX);
            if (path_max == -1){size = 1024;}
                
            else if (path_max > 10240){size = 10240;}
                
            else{size = path_max;}
            
            
            char cwd[path_max];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
            } else {
                perror("getcwd() error");
                exit(EXIT_FAILURE);
            }
            
            //path+/executable
            strcat(cwd, "/executable");

            //passing beginning along with range
            int begin=0;
            for(int l = 0; l < i; l++){
                begin+= randomranges[l];
            }
            
            //reference to convert int to string https: //stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
            //https://www.techiedelight.com/convert-std-string-char-cpp/

            //converting to string to send in exec
            string stri = to_string(i);
            char* i_inchar = const_cast<char*>(stri.c_str());

            string strnumentry =to_string(numentry);
            char* numentry_inchar = const_cast<char*>(strnumentry.c_str());
            
            string strrandomrange = to_string(randomranges[i]);
            char* randomrange_inchar = const_cast<char*>(strrandomrange.c_str());

            string strbegin = to_string(begin);
            char* begin_inchar = const_cast<char*>(strbegin.c_str());

            string strrootpid = to_string(rootpid);
            char* rootpid_inchar = const_cast<char*>(strrootpid.c_str());

            //arguments to pass to exec call
            char * argTmp[] = {"./executable", filename, random1, num_worker1, order, attribute_number1, output_file, i_inchar, numentry_inchar, randomrange_inchar, begin_inchar, rootpid_inchar, NULL};
            execv(cwd, argTmp); 
            exit(0); 
        } 
        // waitpid(execpid, &s, 0);
    } 


    
    for(int i=0;i<num_workers+1;i++){
        wait(NULL);
        if (i==num_workers){
            printf("waiting for MERGER ...\n\n");
        }else{
         printf("waiting for worker [%d] ...\n\n",i);

        }
    } 


}

