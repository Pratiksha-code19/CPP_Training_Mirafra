#include <bits/stdc++.h>
using namespace std;
template <class T>
class Node
{
public:
    T data;
    Node<T> *next;

    Node(T data)
    {
        this->data = data;
    }
};

template <class T>
class Stack
{
public:
    int size;
    Node<T> *top;
    Stack()
    {
        top = NULL;
        size = 0;
    }

    void push(T data)
    {
        Node<T> *newstack = new Node<T>(data);

        newstack->next = top;
        top = newstack;

        size++;
    }

    void pop(){
        if(top == NULL){
            cout<<"Stack Underflow "<<endl;
        }
        else{
            Node<T>* temp = top;
            top = top->next;
            delete temp;

        }
    }

    T peek(){
        return top->data;
    }

    void display()
    {
        Node<T> *temp = top;
        while (temp != NULL)
        {
            cout << temp->data << endl <<" | "<<endl;
            temp = temp->next;
        }
        cout << endl;
    }
};
int main()
{

    Stack<int> s;
    s.push(21);
    s.push(2);
    s.push(23);
    s.push(1);
    s.push(41);
    s.push(111);

    s.pop();
    s.display();
    cout<<s.peek()<<endl;
    
    return 0;
}