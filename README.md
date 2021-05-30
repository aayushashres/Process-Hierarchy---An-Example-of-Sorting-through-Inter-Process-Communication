# Process-Hierarchy---An-Example-of-Sorting-through-Inter-Process-Communication
Program to create a hierarchy of processes to have nodes accomplish potentially diverse tasks. Incorporating the use of pipes for inter-process communication. For class on Operating Systems.

myhie is an application to create a process hierarchy in order to sort datarecords based on a given attribute.
The data records can be sorted based on the given attribute number and also in either ascending or descending order.
The user can enter the attribute number, order, and also the specify the number of workers or processes that will do the sorting. Additionally, the user can also specify whether they want the sorters to be of a unifrom size or random sizes.
(A more detailed description can be found on teh assignment pdf)

The program can be run on macOS.

For safety, make clean before making the executables.
make to create the required executables: myhie and exectuable

After creating the executables. we can invoke the program as:
./myhie -i InputFile -k NumOfWorkers -r -a AttributeNumber -o Order -s OutputFile

For example:
./myhie -i Data4Project2/1batch-1000.csv -k 5 -a 4 -o descending -s outputfile -r
will sort the 1batch-1000.csv file by creating 5 workrs with random sizes and sort in descending order to putput the results into outputfile
Please remember to ensure that the file path for the input file is correct.
