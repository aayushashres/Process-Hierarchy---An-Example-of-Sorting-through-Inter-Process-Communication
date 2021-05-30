#include "bubblesort.h"
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <unistd.h> 

// reference https://www.geeksforgeeks.org/bubble-sort/
//returns sorted array
node** bubble_sort(node** sorterarray, int n, char order[1024], int attribute_number){ 
   int i, j; 
   node* temp;
   bool swapped; 
   if (attribute_number==0 && (strcmp(order, "ascending")==0)){
      for (i = 0; i < n-1; i++) { 
      
         swapped = false; 
         for (j = 0; j < n-i-1; j++) { 
            if (sorterarray[j]->getrid() > sorterarray[j+1]->getrid()){ 
                  temp = sorterarray[j];
                  sorterarray[j]=sorterarray[j+1];
                  sorterarray[j+1]=temp;
                  swapped = true; 
            } 
         } 
      
         // IF no two elements were swapped by inner loop, then break 
         if (swapped == false) 
            break;   
      }

   }
   else if (attribute_number==0 && (strcmp(order, "descending")==0)){
      for (i = 0; i < n-1; i++) { 
     
         swapped = false; 
         for (j = 0; j < n-i-1; j++) { 
            if (sorterarray[j]->getrid() < sorterarray[j+1]->getrid()){ 
                  temp = sorterarray[j];
                  sorterarray[j]=sorterarray[j+1];
                  sorterarray[j+1]=temp;
                  swapped = true; 
            } 
         } 
      
         // IF no two elements were swapped by inner loop, then break 
         if (swapped == false) 
            break; 
      }

   }
   else if (attribute_number==3 && (strcmp(order, "ascending")==0)){
      for (i = 0; i < n-1; i++) { 
         swapped = false; 
         for (j = 0; j < n-i-1; j++) { 
            if (sorterarray[j]->getnum_dependants() > sorterarray[j+1]->getnum_dependants()){ 
                  temp = sorterarray[j];
                  sorterarray[j]=sorterarray[j+1];
                  sorterarray[j+1]=temp;
                  swapped = true; 
            } 
         } 
   
      // IF no two elements were swapped by inner loop, then break 
         if (swapped == false) 
            break; 
      }

   }
   else if (attribute_number==3 && (strcmp(order, "descending")==0)){
      for (i = 0; i < n-1; i++) { 
     
         swapped = false; 
         for (j = 0; j < n-i-1; j++) { 
            if (sorterarray[j]->getnum_dependants() < sorterarray[j+1]->getnum_dependants()){ 
                  temp = sorterarray[j];
                  sorterarray[j]=sorterarray[j+1];
                  sorterarray[j+1]=temp;
                  swapped = true; 
            } 
         } 
   
         // IF no two elements were swapped by inner loop, then break 
         if (swapped == false) 
            break; 
      }

   }
   else if (attribute_number==4 && (strcmp(order, "ascending")==0)){
      for (i = 0; i < n-1; i++) { 
     
         swapped = false; 
         for (j = 0; j < n-i-1; j++) { 
            if (sorterarray[j]->getincome() > sorterarray[j+1]->getincome()){ 
                  temp = sorterarray[j];
                  sorterarray[j]=sorterarray[j+1];
                  sorterarray[j+1]=temp;
                  swapped = true; 
            } 
         } 
         // IF no two elements were swapped by inner loop, then break 
         if (swapped == false) 
            break; 
      }
   }
   else if (attribute_number==4 && (strcmp(order, "descending")==0)){
      for (i = 0; i < n-1; i++) { 
     
         swapped = false; 
         for (j = 0; j < n-i-1; j++) { 
            if (sorterarray[j]->getincome() < sorterarray[j+1]->getincome()){ 
                  temp = sorterarray[j];
                  sorterarray[j]=sorterarray[j+1];
                  sorterarray[j+1]=temp;
                  swapped = true; 
            } 
         } 
      
         // IF no two elements were swapped by inner loop, then break 
         if (swapped == false) 
            break; 
         }

   }
   else if (attribute_number==5 && (strcmp(order, "ascending")==0)){
      for (i = 0; i < n-1; i++) { 
     
         swapped = false; 
         for (j = 0; j < n-i-1; j++) { 
            if (sorterarray[j]->getpostalcode() > sorterarray[j+1]->getpostalcode()){ 
                  temp = sorterarray[j];
                  sorterarray[j]=sorterarray[j+1];
                  sorterarray[j+1]=temp;
                  swapped = true; 
            } 
         } 
      
         // IF no two elements were swapped by inner loop, then break 
         if (swapped == false) 
            break; 
      }

   }
   else if (attribute_number==5 && (strcmp(order, "descending")==0)){
      for (i = 0; i < n-1; i++) { 
     
         swapped = false; 
         for (j = 0; j < n-i-1; j++) { 
            if (sorterarray[j]->getpostalcode() < sorterarray[j+1]->getpostalcode()){ 
                  temp = sorterarray[j];
                  sorterarray[j]=sorterarray[j+1];
                  sorterarray[j+1]=temp;
                  swapped = true; 
            } 
         } 
      
         // IF no two elements were swapped by inner loop, then break 
         if (swapped == false) 
            break; 
      }

   }
    
   
   return sorterarray;
} 