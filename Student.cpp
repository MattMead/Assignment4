#include <iostream>
#include "Student.h"
using namespace std;

//Constructor
Student::Student(){
    windowTime = 0;
    arrivalTime = 0;
    waitTime = 0;
}

//Overloaded Constructor
Student::Student(int arrival, int windowT){
    windowTime = windowT;
    arrivalTime = arrival;
    waitTime = 0;
}

// Setting the wait time for students at the registrar
void Student::waitingTime(int wait){
    waitTime = wait;
}
