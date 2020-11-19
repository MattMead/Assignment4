#include <iostream>
#include "Window.h"
using namespace std;

// Constructor
Window::Window(){
    open = true;
    busy = 0;
    idleTime = 0;
    currStudent = NULL;

}

// Removes a student from a window
Student* Window::removeStudent(){
    open = true;
    Student* thisStudent = currStudent;
    currStudent = NULL;
    return thisStudent;
}

// Adds a student to a window
void Window::addStudent(Student* stud){
    currStudent = stud;
    busy = stud->windowTime;
    open = false;
}
