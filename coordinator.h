#ifndef COORDINATOR
#define COORDINATOR

#include "node.h"
#include "insertionsort.h"
#include "bubblesort.h"

int createSorterArray(int random, int num_workers, char order[1024], int attribute_number, char output_file[1024], int index, node** taxPayersArray, int numentry, int* randomranges);
void coordinator(char filename[1024] ,char random1[24], char num_worker1[1024], char order[1024], char attribute_number1[1024], char output_file[1024], int numentry );
#endif