#include "Window.h"
#include <iostream>

using namespace std;

class Registrar{
public:

    // Constructor
    Registrar();

    // makes a new student
    Student* newStudent;

    // makes a window
    Window* windows;

    // statistics varibales
    double meanWaitTime;
    double medianWaitTime;
    int longestWaitTime;
    int numOver10;
    double meanIdle;
    int longestIdle;
    int numIdleOver5;

    // tracks wait time
    int waitTimeTracker;

    //count how many students go to the registrar
    int prevStudentsCount = 0;

    // the number of open windows
    int openWindowsCount;

    // Queue that holds student objects
    Queue<Student*> *studentQueue;

    //DoubleLinked List that contains all the students finished at the registrar
    DoubleLinkedList<Student*>* prevStudents;

    // takes in a file and fills the student queue
    void FillQueue(string file);

    // fills all the windows with the right number of window objects
    void FillWindows();

    // increments the idle time for the windows
    void WindowIdleTime();

    // checks to see if a window is empty
    bool WindowsEmpty();

    // populates an open window with a student
    void PopWindows(int currTime);

    // depopulates students from windows once they are done with their registrar visit
    void DepopWindows();

    // calculates the stats for the assignment
    void CalcStats();




private:
    Window* newWindow;
    unsigned int arrivalTime;
    int totalStudents;


};
