#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include "Student.h"
using namespace std;

class Window{
public:

  //Constructor
  Window();

  // Object that points to the first student
  Student* currStudent;

  // Adds student to a window
  void addStudent(Student* s);

  // Removes a student from a window
  Student* removeStudent();
  
  // Variables
  int busy;
  bool open;
  int idleTime;
};
#endif
