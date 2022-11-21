# Banker's Algorithm for Deadlock Avoidance | KSU OS Class Assignment #2

## Banker's algorithm runs processes in a sequence which avoids deadlock

In this program, there are five processes and three resource types. There are 10 instances of resource type A, 5 of type B and 7 of type C. Each of the five processes need various quantities of each resource type in order to run and complete. At the beginning, there are some resources already allocated to each of processes
and the rest are available to use. 

The program will cycle through the processes and see whether the amount of available resources will satisfy the processes needs. If the available resources is enough for the process, then the needed amount is taken out of available and given to the process. This process then runs, completes, and finally releases all of the resources it was holding and makes them available for the other processes. The program ensures that the system remains in a safe state.

The processes will run in an order that keeps the system in a safe state and avoids deadlock. After the last of the processes run, the sequence in which the processes ran (safe sequence) will be printed to the console.

## How to run

modifying the input file is not recommended as it will likely break the program

Run the following commands:
1. g++ bankerMain.cpp
2. ./a.out


