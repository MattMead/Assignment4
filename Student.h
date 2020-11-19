#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "Queue.h"
using namespace std;

class Student{
public:
  
    //Variables
    int arrivalTime;
    int waitTime;
    int windowTime;

    //Constructor
    Student();

    //Overloaded Constructor
    Student(int arrival, int windowT);

    //method for wait time
    void waitingTime(int wait);

};
#endif
