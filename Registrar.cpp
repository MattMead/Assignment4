#include "Registrar.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

//Constructor
Registrar::Registrar(){
    prevStudents = new DoubleLinkedList<Student*>();
    studentQueue = new Queue<Student*>();
    arrivalTime = 0;
    totalStudents = 0;
    openWindowsCount = 0;

}


// method that calculates the statistics of the registrar simulation
void Registrar::CalcStats(){
  //  array of integers that represent all the window idle times
  int windowIdleTimesArr[openWindowsCount];
  // array of integers with a size that represents the number of students that came to the registrar
  int arrayWaitTimes[prevStudentsCount];


  //START OF WAIT TIME CALCULATIONS

  //going through the prev student list and adding each students wait time to the new array
  for(int i = 0; i < prevStudentsCount; ++i){
    arrayWaitTimes[i] = prevStudents->removeFromFront()->waitTime;
  }
  //using the sort function on the array
  sort(arrayWaitTimes, arrayWaitTimes + prevStudentsCount);


  // Calculate Mean Wait Time
  int waitTimeSum = 0;
  // going through the new array we just made and adding the wait times to the sum
  for(int i = 0; i < prevStudentsCount; ++i){
     waitTimeSum += arrayWaitTimes[i];
  }
  //the mean wait time
  meanWaitTime = waitTimeSum / prevStudentsCount;



  //Calculating the Median Wait Time
  // variable for the middle index
  int middle = prevStudentsCount / 2.0;
  // if the number of students is even
  if(prevStudentsCount % 2 == 0){
     medianWaitTime = (arrayWaitTimes[middle] + arrayWaitTimes[middle + 1]) / 2.0;
  }
  else{
     medianWaitTime = arrayWaitTimes[middle];
  }


  // Calculating Longest Wait Time
  // Longest wait time should be the last value of the wait times array since it was sorted
  longestWaitTime = arrayWaitTimes[prevStudentsCount - 1];



  // Number of Students that Waited Over 10 Minutes
  // iterating through through the wait times array and seeing which are greater than 10
  for(int i = 0; i < prevStudentsCount; ++i){
    if(arrayWaitTimes[i] > 10){
       numOver10++;
    }
  }


  // START OF IDLE TIME CALCULATIONS

  // going through the windows and filling the array with the windows idle time
  for(int i = 0; i < openWindowsCount; ++i){
    windowIdleTimesArr[i] = windows[i].idleTime;
  }
  // Using the sort function on the idle array
  sort(windowIdleTimesArr, windowIdleTimesArr + openWindowsCount);



  // Calculating the Mean Idle Time
  int windowSum = 0;
  //going through the array and adding the idle times to find the sum
  for(int i = 0; i < openWindowsCount; ++i){
     windowSum += windowIdleTimesArr[i];
  }
  //mean idle time
  meanIdle = (windowSum / openWindowsCount)-1;



  //Calculating the Longest Idle Time
  // the longest idle time should be the value of the last element in the array
  longestIdle = windowIdleTimesArr[openWindowsCount - 1] -1;



  // Calculating the Number of Windows with an Idle Time Longer than 5 Minutes

  //going through the array and seeing which elements are greater than 5
  for(int i = 0; i < openWindowsCount; ++i){
    if(windowIdleTimesArr[i] > 5){
      numIdleOver5++;
    }
  }

  //Printing out the stats
  cout << "The mean student wait time: " << meanWaitTime << endl;
  cout << "The median student wait time: " << medianWaitTime << endl;
  cout << "The longest student wait time: " << longestWaitTime << endl;
  cout << "The number of students waiting over 10 minutes: " << numOver10 << endl;
  cout << "The mean window idle time: " << meanIdle << endl;
  cout << "The longest window idle time: " << longestIdle << endl;
  cout << "Number of windows idle for over 5 minutes: " << numIdleOver5 << endl;
}


//Reads from an inputed file and fills the queue
void Registrar::FillQueue(string file){
    ifstream fileStream;
    fileStream.open(file);
    bool emptyFile = false;
    string line;

    //Runtime error if the file cannot be opened
    if(!fileStream)
    {
        throw runtime_error("Could not open inputed file.");
    }
    int numLines = 0;
        //iterating through each line
        while(getline(fileStream, line))
        {
            //Getting the number of open windows from the inputed file
            if(numLines == 0){
                openWindowsCount = stoi(line);
                numLines++;
                continue;
            }

            //Getting the arrival time from the inputed file
            if(numLines == 1){
                arrivalTime = stoi(line);
                numLines++;
                continue;
            }
            // Getting the number of students from the inputed file
            if(numLines == 2){
                totalStudents = stoi(line);
                numLines = 1;

                // going through the number of students to check their window times for their object
                for(int i = 0; i < totalStudents; ++i){
                    getline(fileStream, line);
                    if(fileStream.eof()){
                        emptyFile = true;
                        break;
                    }
                    // created a new student object and then adds it to the queue
                    newStudent = new Student(arrivalTime, stoi(line));
                    studentQueue->insert(newStudent);
                }
                totalStudents = 0;
                continue;
            }
            // reader goes back up to the arrival time to find another student
            if(totalStudents == 0){
                numLines = 1;
            }
            // checks if the file is empty
            if(emptyFile == true){
                break;
            }
        }

}


// Populates the windows
void Registrar::PopWindows(int currTime)
{
    // going through all the windows and seeing if they are open or in use
    for(int i = 0; i < openWindowsCount; ++i){
        if(windows[i].open == true){
            // making sure their are students in the queue
            if(!studentQueue->isEmpty()){
                Student *stu = studentQueue->peek();
                // seeing the student's arrivalTime is less than or equal to the registrars time
                if(stu->arrivalTime <= currTime){
                    // removing student from queue and adding the student to the open window
                    Student *thisStudent = studentQueue->remove();
                    thisStudent->waitingTime(waitTimeTracker - thisStudent->arrivalTime);
                    windows[i].addStudent(thisStudent);
                }
                else{
                    break;
                }
            }
        }
    }
}

// Removes students from the windows puts them at the end of the prevStudents double linked list
void Registrar::DepopWindows(){

    //Going through the open windows removing students if the window is not busy
    for(int i = 0; i < openWindowsCount; ++i){
        if(windows[i].open == false){
            //not busy so student is done
            if(windows[i].busy == 0){
                prevStudents->insertAtBack(windows[i].removeStudent());
                prevStudentsCount++;
            }
        }
    }
}

// fills the windows with the right number of window objects
void Registrar::FillWindows(){
    windows = new Window[openWindowsCount];
}

// Checks to see which windows are empty. Checks by seeing if the window is open
bool Registrar::WindowsEmpty(){
    bool windowEmpty = true;
    for(int i = 0; i < openWindowsCount; ++i){
        if(windows[i].open == false){
            windowEmpty = false;
        }
    }
    return windowEmpty;
}


// Tracks the idle time for the windows
void Registrar::WindowIdleTime(){
    // going through the windows to see which are idle
    for(int i = 0; i < openWindowsCount; ++i){
        if(windows[i].open == true){
            //increment the idel time since it is open
            windows[i].idleTime += 1;
        }
    }
}
