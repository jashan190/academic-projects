//DynamicStackDataStructure.cpp
//Jashandeep Singh, CISP 400
//12/15/2023

/*Using your knowledge of dynamic memory, create a dynamic stack data structure (DS) on the heap. This DS will grow by 1 with the Add() method (and add data to the DS), shrink by 1 with the Pop() method (and return the data removed). Unlike an array, this DS is designed only to be accessed through the Add() and Pop() methods (no [] with an index number). A Size() method will be helpful for debugging. Create a test rig to add and remove several elements. You can make this whatever base type you wish.*/

#include <iostream>
#include <stdexcept>
using namespace std;

class Node {
public:
    int value;
    Node* nextNode;

    Node(int value) : value(value), nextNode(nullptr) {}
};

class CustomStack {
private:
    Node* topNode;
    int stackSize;

public:
    CustomStack() : topNode(nullptr), stackSize(0) {}

    ~CustomStack() {
        ClearStack();
    }

    void Push(int value) {
        Node* newNode = new Node(value);
        newNode->nextNode = topNode;
        topNode = newNode;
        stackSize++;
    }

    int Pop() {
        if (topNode == nullptr) {
            throw runtime_error("Attempt to pop from an empty stack.");
        }
        int value = topNode->value;
        Node* tempNode = topNode;
        topNode = topNode->nextNode;
        delete tempNode;
        stackSize--;
        return value;
    }

    int Top() const {
        if (topNode == nullptr) {
            throw runtime_error("Attempt to peek on an empty stack.");
        }
        return topNode->value;
    }

    void ClearStack() {
        while (topNode != nullptr) {
            Pop();
        }
    }

    int CurrentSize() const {
        return stackSize;
    }

    void Display() const {
        Node* currentNode = topNode;
        cout << "Stack contents (Top to Bottom): ";
        while (currentNode != nullptr) {
            cout << currentNode->value << " ";
            currentNode = currentNode->nextNode;
        }
        cout << endl;
    }
};

int main() {
    CustomStack myStack;

    // Enhanced Test Rig
    cout << "Adding elements: 10, 20, 30" << endl;
    myStack.Push(10);
    myStack.Push(20);
    myStack.Push(30);
    myStack.Display();

    cout << "Current stack size: " << myStack.CurrentSize() << endl;

    cout << "Top element: " << myStack.Top() << endl;

    cout << "Popping elements: ";
    while (myStack.CurrentSize() > 0) {
        cout << myStack.Pop() << " ";
    }
    cout << endl;

    cout << "The stack size after popping: " << myStack.CurrentSize() << endl;

    cout << "Trying to pop from an empty stack..." << endl;
    try {
        myStack.Pop();
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}