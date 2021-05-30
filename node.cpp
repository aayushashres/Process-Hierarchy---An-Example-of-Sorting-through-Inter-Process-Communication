#include "node.h"
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;


node::node(int r, char fn[100], char ln[100], int nd, float i, int p){
    rid=r;
    strcpy(fname,fn);
    strcpy(lname,ln);
    num_dependants = nd;
    income=i;
    postalcode=p;
}

//methods to write the node as a string with necessary delimiters, sorter number, and time taken - all to be used in merger
//in string to make it possible to use in pipes
char* node:: node_to_string(int index, float timetaken){

    char* record = new char[600];

    string str_index = to_string(index);
    char* index_inchar = const_cast<char*>(str_index.c_str());

    string str_rid = to_string(rid);
    char* rid_inchar = const_cast<char*>(str_rid.c_str());

    string str_numdep = to_string(num_dependants);
    char* nd_inchar = const_cast<char*>(str_numdep.c_str());

    string str_income = to_string(income);
    char* income_inchar = const_cast<char*>(str_income.c_str());

    string str_postal = to_string(postalcode);
    char* postal_inchar = const_cast<char*>(str_postal.c_str());

    //reference to get float as string: https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
    char timeinstring[80];
    sprintf(timeinstring, "%f", timetaken);

    strcat(record, strcat(index_inchar, " "));
    strcat(record, strcat(rid_inchar, " "));
    strcat(record, strcat(fname, " "));
    strcat(record, strcat(lname, " "));
    strcat(record, strcat(nd_inchar, " "));
    strcat(record, strcat(income_inchar, " "));
    strcat(record, strcat(postal_inchar, " "));
    strcat(record, strcat(timeinstring, "\n"));

    return record;
}

//string format to write to the final file
char* node:: node_in_string_format(){

    char* record = new char[600];

    string str_rid = to_string(rid);
    char* rid_inchar = const_cast<char*>(str_rid.c_str());

    string str_numdep = to_string(num_dependants);
    char* nd_inchar = const_cast<char*>(str_numdep.c_str());

    string str_income = to_string(income);
    char* income_inchar = const_cast<char*>(str_income.c_str());

    string str_postal = to_string(postalcode);
    char* postal_inchar = const_cast<char*>(str_postal.c_str());

    strcat(record, strcat(rid_inchar, " "));
    strcat(record, strcat(fname, " "));
    strcat(record, strcat(lname, " "));
    strcat(record, strcat(nd_inchar, " "));
    strcat(record, strcat(income_inchar, " "));
    strcat(record, strcat(postal_inchar, "\n"));

    return record;
}

//display function
void node::display(){
    printf("%d %s %s %d %f %d\n", rid, fname, lname, num_dependants, income, postalcode);
}

//get functions for convenience
int node::getrid(){
    return rid;
}

int node::getnum_dependants(){
    return num_dependants;
}

float node:: getincome(){
    return income;
}

int node:: getpostalcode(){
    return postalcode;
}