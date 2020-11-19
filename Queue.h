#ifndef Queue_H
#define Queue_H
#include "DoubleLinkedList.h"
#include <iostream>
template <class T>

class Queue{
public:
    //Constructor
    Queue(){
        myQueue = new DoubleLinkedList<T>();
    }
    //Destructor
    ~Queue(){
    }

    // Checks if the queue is empty
    bool isEmpty(){
        return (myQueue->listSize() == 0);
    }

    // Returns the queue size
    int listSize(){
        return myQueue->listSize();
    }

    // Returns the data at the front of the queue
    T peek(){
        return myQueue-> front->data;
    }

    // Inserts data at the end of the queue
    void insert(T data){
        myQueue->insertAtBack(data);
    }

    // Removes the data at the front of the queue
    T remove(){
        T c = myQueue->removeFromFront();
        return c;
    }

private:
    DoubleLinkedList<T> *myQueue;
};
#endif
