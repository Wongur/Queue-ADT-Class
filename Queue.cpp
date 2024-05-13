/* 
 * Queue.cpp - Does not work well!
 *
 * Description: Array-based implementation of Queue as an ADT class
 * Class Invariant: Queue maintained in FIFO order
 *
 * Author: Kyle Wong   
 * Date: February 15th, 2024
 */
 
#include <iostream>
#include "Queue.h"

using std::cout;
using std::endl;

// Description: Constructor
Queue::Queue() {

    // Initializes all values
    elementCount = 0;
    backindex = 0;
    frontindex = 0;

    capacity = INITIAL_CAPACITY;

    // dymanically allocates array
    elements = new int[INITIAL_CAPACITY];
}

// Description: Desctructor
Queue::~Queue()
{
    delete[] elements;
}

// Description: Inserts newElement at the back of Queue
// Time Efficiency: O(1)
void Queue::enqueue(int newElement) {

    // CASE 1: Queue is empty
    // Solution: Sets front and back index to zero 
    if (isEmpty())
    {
        frontindex = 0;
        backindex = 0;
    }
    // CASE 2: Queue is full
    // Solution: Creates new array that is double the size and copies elements to it.  
    else if (isFull())
    {
        // creates new array
        int newCapacity = capacity * 2;
        int *newArray = new int[newCapacity];

        // copies elements to new array
        for (unsigned int index = 0; index < capacity; index++)
        {
            newArray[index] = elements[(frontindex + index) % capacity];
        }

        // deletes old array
        delete[] elements;

        // changes elements pointer so that it points to the new array
        elements = newArray;
        backindex = elementCount;
        frontindex = 0;
        capacity = newCapacity;
    }
    // CASE 3: array isn't full and isn't empty and we want to insert a new element
    // Solution: updates back index
    else
    {
        backindex = (backindex + 1) % capacity;  
    }

    // inserts element at the back
    elements[backindex] = newElement;

    // updates element count
    elementCount++;
      
    return;
} 

// Description: Removes the frontmost element
// Precondition: Queue not empty
// Time Efficiency: O(1)
void Queue::dequeue() {

    // CASE 1: Queue is empty
    // Solution: return nothing and exit the function
    if (isEmpty())
    {
        return;
    }
    // CASE 2: Queue is less than 1/4 capacity
    // Solution: Creates new array that is half the size and copies elements to it.  
    else if (capacity > INITIAL_CAPACITY && (elementCount < (capacity /4 )))
    {
        int newCapacity = capacity / 2;

        // makes sure newCapacity isn't less than original condition for minimum capacity
        if (newCapacity < INITIAL_CAPACITY)
        {
            newCapacity = INITIAL_CAPACITY;
        }

        // creates new smaller array
        int *newArray = new int[newCapacity];

        // copies elements to new array
        for (unsigned int index = 0; index < elementCount; index++)
        {
            newArray[index] = elements[(frontindex + index) % capacity];
        }

        // deletes old array
        delete[] elements;

        // changes elements pointer so that it points to the new array
        elements = newArray;
        backindex = elementCount-1;
        capacity = newCapacity;
        frontindex = (frontindex + 1) % capacity; 
        
    }
    // CASE 3: array isn't empty and isn't less than 1/4 full
    // Solution: updates front index
    else
    {
        frontindex = (frontindex + 1) % capacity;  
    }

    // updates element count
    elementCount--;
      
    return;
} 

// Description: Returns a copy of the frontmost element
// Precondition: Queue not empty
// Time Efficiency: O(1)
int Queue::peek() const {
    return elements[frontindex];    
} 

// Description: Returns true if and only if Queue empty
// Time Efficiency: O(1)
bool Queue::isEmpty() const {
    return elementCount == 0;
}

 // Description: Returns true if and only if Queue is full
 // Time Efficiency: O(1)
bool Queue::isFull(){
    if ((backindex + 1) % capacity == frontindex)
    {
        return true;
    }
    else return false;
}
