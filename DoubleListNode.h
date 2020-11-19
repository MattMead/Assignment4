#include<iostream>

using namespace std;
template <class T>
class DoubleListNode{
public:
    T data;
    DoubleListNode<T> *next;
    DoubleListNode<T> *previous;

    //Constructor
    DoubleListNode(){
        data = NULL;
        previous = NULL;
        next = NULL;

    }
    //Overloaded Constructor
    DoubleListNode(T d){
        data = d;
        previous = NULL;
        next = NULL;

    }
    //Destructor
    ~DoubleListNode(){
        if(next == NULL)
            delete next;
            previous = NULL;
    }
};
