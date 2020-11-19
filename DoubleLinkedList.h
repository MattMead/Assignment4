#include "DoubleListNode.h"
using namespace std;
template <class T>
class DoubleLinkedList{
public:

    DoubleListNode<T> *front;
    DoubleListNode<T> *back;
    unsigned int size;

    //Constructor
    DoubleLinkedList(){
        front = NULL;
        back = NULL;
        size = 0;
    }
    //Destructor
    ~DoubleLinkedList(){
    }

    //checks to see if the list is empty
    bool isEmpty(){
        if(size == 0)
            return true;
        else
            return false;
    }

    //returns the size of the list
    unsigned int listSize(){
        return size;
    }

    //print data of the list
    void printAll(){
        DoubleListNode<T> *current = front;
        while (*current != NULL){
            cout << current->data << endl;
            current = current->next;
        }
    }

    //searches for data
    T search(T d){
        int index = 0;
        DoubleListNode<T> *current = front;

        while(current != NULL){
            if(current -> data == d){
                break;
            }
            index++;
            current = current -> next;
        }

        if(current == NULL){
            index = -1;
        }
        return index;
    }

    //returns the data at a specific index
    T getIndex(int index){
        DoubleListNode<T> *current = front;
        for(int i = 0; i < index; ++i){
            current = current -> next;
        }
        return current->data;
    }

    //Insert node at the front of the list
    void insertAtFront(T d){
        DoubleListNode<T> *node = new DoubleListNode<T>(d);
        if(isEmpty()){
            back = node;
        }
        else{
            front -> previous = node;
            node -> next = front;
        }
        front = node;
        size++;
    }

    //Inserting at the back of the list
    void insertAtBack(T d){
        DoubleListNode<T> *node = new DoubleListNode<T>(d);
        //first want to check if the list is empty
        if(isEmpty()){
            front = node;
            back = node;
        }
        else{
            back-> next = node;
            node-> previous = back;
        }

        back = node;
        size++;
    }

    //Removes the node at the front
    T removeFromFront(){
        DoubleListNode<T> *frontNode = front;
        //checking to see if the list is empty
        if(front->next == NULL){
            back = NULL;
        }
        else{
            front->next->previous = NULL;
        }
        //updating the new front node and getting rid of the original front node
        front = front->next;
        T temp = frontNode -> data;
        frontNode->next = NULL;
        size--;
        delete frontNode;
        return temp;
    }

    //Deletes a node at a specific position
    T deletePosition(T position){
        int index = 0;
        DoubleListNode<T> *current = front;
        DoubleListNode<T> *previous = front;

        //checking until we find the particular position
        while (index != position){
            previous = current;
            current = current->next;
            index++;
        }
        previous->next = current-> next;
        current->next = NULL;
        T temp = current->data;
        delete current;
        size--;
        return temp;
    }
};
