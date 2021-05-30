#include "insertionsort.h"
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <unistd.h> 


//refernce from https://www.geeksforgeeks.org/insertion-sort/ 
//returns sorted array
node** insertion_sort(node** sorterarray, int n, char order[1024], int attribute_number){ 
    int i, j;
    if (attribute_number==0 && (strcmp(order, "ascending")==0)){
        for (i=1; i<n;i++){
        node* temp = sorterarray[i];
        j = i-1;
        while (j>=0 && sorterarray[j]->getrid() >temp->getrid()){
            sorterarray[j+1]=sorterarray[j]; 
            j-=1;

        }
        sorterarray[j+1]=temp;
        }
    }
    else if (attribute_number==0 && (strcmp(order, "descending")==0)){
        for (i=1; i<n;i++){
        node* temp = sorterarray[i];
        j = i-1;
        while (j>=0 && sorterarray[j]->getrid() < temp->getrid()){
            sorterarray[j+1]=sorterarray[j]; 
            j-=1;

        }
        sorterarray[j+1]=temp;
        }
    }
    else if (attribute_number==3 && (strcmp(order, "ascending")==0)){
        for (i=1; i<n;i++){
        node* temp = sorterarray[i];
        j = i-1;
        while (j>=0 && sorterarray[j]->getnum_dependants() > temp->getnum_dependants()){
            sorterarray[j+1]=sorterarray[j]; 
            j-=1;

        }
        sorterarray[j+1]=temp;
        }
    }
    else if (attribute_number==3 && (strcmp(order, "descending")==0)){
        for (i=1; i<n;i++){
        node* temp = sorterarray[i];
        j = i-1;
        while (j>=0 && sorterarray[j]->getnum_dependants() < temp->getnum_dependants()){
            sorterarray[j+1]=sorterarray[j]; 
            j-=1;

        }
        sorterarray[j+1]=temp;
        }
    }
    else if (attribute_number==5 && (strcmp(order, "ascending")==0)){
        for (i=1; i<n;i++){
        node* temp = sorterarray[i];
        j = i-1;
        while (j>=0 && sorterarray[j]->getpostalcode() > temp->getpostalcode()){
            sorterarray[j+1]=sorterarray[j]; 
            j-=1;

        }
        sorterarray[j+1]=temp;
        }
    }
    else if (attribute_number==5 && (strcmp(order, "descending")==0)){
        for (i=1; i<n;i++){
        node* temp = sorterarray[i];
        j = i-1;
        while (j>=0 && sorterarray[j]->getpostalcode() < temp->getpostalcode()){
            sorterarray[j+1]=sorterarray[j]; 
            j-=1;

        }
        sorterarray[j+1]=temp;
        }
    }
    else if (attribute_number==4 && (strcmp(order, "ascending")==0)){
        for (i=1; i<n;i++){
        node* temp = sorterarray[i];
        j = i-1;
        while (j>=0 && sorterarray[j]->getincome() > temp->getincome()){
            sorterarray[j+1]=sorterarray[j]; 
            j-=1;

        }
        sorterarray[j+1]=temp;
        }
    }
    else if (attribute_number==4 && (strcmp(order, "descending")==0)){
        for (i=1; i<n;i++){
        node* temp = sorterarray[i];
        j = i-1;
        while (j>=0 && sorterarray[j]->getincome() < temp->getincome()){
            sorterarray[j+1]=sorterarray[j]; 
            j-=1;

        }
        sorterarray[j+1]=temp;
        }
    }
    return sorterarray;
}