#include <iostream>
using namespace std;

class Queue {
private:
    int* queue;    // Pointer to the array that stores the queue elements
    int front;     // Index of the front element in the queue
    int rear;      // Index of the rear element in the queue
    int size;      // Maximum size of the queue
    int capacity;  // Capacity of the queue

public:
    // Constructor to initialize the queue with the given capacity
    Queue(int capacity) {
        this->capacity = capacity;
        queue = new int[capacity]; // Dynamically allocate memory for the array
        front = -1;
        rear = -1;
        size = 0;
    }

    // Destructor to free the allocated memory
    ~Queue() {
        delete[] queue;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return size == 0;
    }

    // Check if the queue is full
    bool isFull() {
        return size == capacity;
    }

    // Enqueue operation: Add an element to the rear of the queue
    void enqueue(int item) {
        if (isFull()) {
            cout << "Queue is full!" << endl;
            return;
        }
        if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % capacity;  // Circular increment
        queue[rear] = item;
        size++;
        cout << "Enqueued " << item << endl;
    }

    // Dequeue operation: Remove an element from the front of the queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        int item = queue[front];
        if (front == rear) { // Only one element was in the queue
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;  // Circular increment
        }
        size--;
        cout << "Dequeued " << item << endl;
        return item;
    }

    // Peek operation: Return the element at the front of the queue
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return queue[front];
    }

    // Display the queue elements
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }

        cout << "Queue elements: ";
        int i = front;
        while (i != rear) {
            cout << queue[i] << " ";
            i = (i + 1) % capacity;  // Circular increment
        }
        cout << queue[rear] << endl;
    }
};

int main() {
    Queue q(5);  // Create a queue of size 5

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);

    q.display(); // Display the queue

    q.dequeue();
    q.dequeue();

    q.display(); // Display the queue after dequeuing

    q.enqueue(60);
    cout << "Front element: " << q.peek() << endl;

    return 0;
}
