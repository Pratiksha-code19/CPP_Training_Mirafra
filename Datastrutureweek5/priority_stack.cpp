#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

class PriorityStack {
private:
    // Vector to hold elements and their associated priorities
    vector<pair<int, int>> stack;

public:
    // Push element along with its priority
    void push(int element, int priority) {
        stack.push_back({element, priority});
    }

    // Pop the element with the highest priority
    int pop() {
        if (stack.empty()) {
            cout << "Stack is empty!" << endl;
            return -1;  // Indicating empty stack
        }

        // Find the index of the element with the highest priority
        auto max_priority_elem = max_element(stack.begin(), stack.end(), 
            [](const pair<int, int>& a, const pair<int, int>& b) {
                return a.second < b.second;  // Compare based on priority (second value)
            });

        // Get the element with the highest priority
        int element = max_priority_elem->first;

        // Remove the element with the highest priority
        stack.erase(max_priority_elem);

        return element;
    }

    // Peek at the element with the highest priority without removing it
    int peek() {
        if (stack.empty()) {
            cout << "Stack is empty!" << endl;
            return -1;  // Indicating empty stack
        }

        // Find the element with the highest priority
        auto max_priority_elem = max_element(stack.begin(), stack.end(), 
            [](const pair<int, int>& a, const pair<int, int>& b) {
                return a.second < b.second;  // Compare based on priority (second value)
            });

        return max_priority_elem->first;
    }

    // Display all elements in the stack with their priorities
    void display() {
        if (stack.empty()) {
            cout << "Stack is empty!" << endl;
            return;
        }

        cout << "Current Stack (Element, Priority):" << endl;
        for (const auto& elem : stack) {
            cout << "(" << elem.first << ", " << elem.second << ")" << endl;
        }
    }

    // Check if the stack is empty
    bool isEmpty() {
        return stack.empty();
    }
};

int main() {
    PriorityStack ps;

    ps.push(1, 3);  // Element 1 with priority 3
    ps.push(2, 1);  // Element 2 with priority 1
    ps.push(3, 2);  // Element 3 with priority 2
    ps.push(4,3);

    // Display the current state of the stack
    ps.display();

    cout << "Peek: " << ps.peek() << endl;  // Should show 1 (highest priority)

    // Pop elements based on highest priority
    cout << "Popped: " << ps.pop() << endl;  // Should pop 1
    ps.display();  // Display remaining stack

    cout << "Popped: " << ps.pop() << endl;  // Should pop 3
    ps.display();  // Display remaining stack

    cout << "Popped: " << ps.pop() << endl;  // Should pop 2
    ps.display();  // Display remaining stack

    // Try popping from an 
}