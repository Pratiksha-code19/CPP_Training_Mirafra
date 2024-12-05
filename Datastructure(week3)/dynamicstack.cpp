#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;       // Pointer to the array that holds the stack elements
    int top;        // Index of the top element in the stack
    int capacity;   // Maximum capacity of the stack

public:
    // Constructor to initialize the stack with an initial capacity
    Stack(int size) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }

    // Push function to add an element to the stack
    void push(int x) {
        if (top == capacity - 1) {
            // Stack is full, so resize it
            cout << "Stack Overflow! Resizing stack...\n";
            resize();
        }
        arr[++top] = x;
    }

    // Pop function to remove the top element from the stack
    void pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }

    // Function to display all elements in the stack
    void display() {
        if (top == -1) {
            cout << "Stack is empty\n";
            return;
        }
        for (int i = 0; i <= top; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Function to get the top element of the stack without removing it
    int peek() {
        if (top == -1) {
            cout << "Stack is Empty\n";
            return -1;  // Return an invalid value if the stack is empty
        }
        return arr[top];
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        return top == -1;
    }

    // Function to get the current size of the stack
    int size() {
        return top + 1;
    }

    // Function to resize the stack array when the stack is full
    void resize() {
        // Double the capacity
        capacity *= 2;
        int* newArr = new int[capacity];
        
        // Copy existing elements to the new array
        for (int i = 0; i <= top; i++) {
            newArr[i] = arr[i];
        }

        // Delete the old array and point to the new array
        delete[] arr;
        arr = newArr;
    }

    // Destructor to clean up the dynamically allocated memory
    ~Stack() {
        delete[] arr;
    }
};

int main() {
    Stack s(5);  // Stack with initial capacity 5

    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);  // At this point, the stack is full

    // Trying to push more elements to test dynamic resizing
    s.push(60);  // This should trigger a resize

    s.display();  // Display all elements in the stack
    cout << "Top element: " << s.peek() << endl;  // Output: 60

    s.pop();
    cout << "Top element after pop: " << s.peek() << endl;  // Output: 50

    return 0;
}
