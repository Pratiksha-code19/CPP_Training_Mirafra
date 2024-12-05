#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;
    int top;
    int capacity;

public:
    Stack(int size) {
        arr = new int[size];
        capacity = size;
        top = -1;
    }

    void push(int x) {
        if (top == capacity - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = x;
    }

    void pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return;
        }
        top--;
    }
  void display()
  {
    for (int i = 0; i <= top; i++) {
    cout << arr[i] << " ";
}

  }

    int peek() {
        if (top == -1) {
            cout << "Stack is Empty\n";
            return -1;  // Return an invalid value if the stack is empty
        }
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }

    int size() {
        return top + 1;
    }

    ~Stack() {
        delete[] arr;
    }
};

int main() {
    Stack s(5);  // Stack with capacity 5

    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    s.push(60);
    s.push(80);
   s.display();
   cout<<endl;
    cout << "Top element: " << s.peek() << endl;  // Output: 30

    s.pop();
    cout << "Top element after pop: " << s.peek() << endl;  // Output: 20

    return 0;
}
