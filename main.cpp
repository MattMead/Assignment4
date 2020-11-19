
#include "Registrar.h"
#include <iostream>
using namespace std;

// Checks if the registrat simulation is done
bool ContinueRunning(Registrar* registrar){
  if(registrar->WindowsEmpty() != true){
    return true;
  }
  if(!registrar->studentQueue->isEmpty()){
    return true;
  }
  return false;
}

// Main method
int main(int argc, char** argv)
{
  //seeing if a file was included in the command line argument
  if(argc <= 1){
    cout << "You didn't enter a file!" << endl;
    return 0;
  }

  string file = argv[1];
  int time = 0;
  bool keepGoing = true;
  Registrar* registrar = new Registrar();
  registrar->FillQueue(file);
  registrar->FillWindows();

  // taking the list queue size and assigning it to currentSize
  int currentSize = registrar->studentQueue->listSize();

  while(keepGoing){
    registrar->DepopWindows();
    registrar->PopWindows(time);
    registrar->WindowIdleTime();
    ++time;
    ++registrar->waitTimeTracker;
    keepGoing = ContinueRunning(registrar);
    // going through the windows and decrmenting the windows busy variable if it is not equal to 0
    for (int i = 0; i < registrar->openWindowsCount; ++i){
      if(registrar->windows[i].busy != 0){
        registrar->windows[i].busy--;
      }
    }
  }
  // Calculating stats after everything is done
  registrar -> CalcStats();
  return 0;

}
