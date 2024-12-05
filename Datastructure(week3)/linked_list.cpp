//#include <bits/stdc++.h>
#include<iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    void insertAtEnd(int data) {
        Node* newNode = new Node(data);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    void display() {
        if (head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << "->";
            temp = temp->next;
        }
        cout<<"NULL"<<endl;
        cout << endl;
    }

    void deleteByData(int data) {
        if (head == nullptr) {
            cout << "No element to delete!" << endl;
            return;
        }

        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Node with data " << data << " deleted." << endl;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != data) {
            temp = temp->next;
        }

        if (temp->next != nullptr) {
            Node* dele = temp->next;
            temp->next = temp->next->next;
            delete dele;
            cout << "Node with data " << data << " deleted." << endl;
        }
        else {
            cout << "Node with data " << data << " not found!" << endl;
        }
    }

    void inserttBegin(int data){
        Node* newNode = new Node(data);
        if(head == nullptr){
            head = newNode;
            return;
        }

        newNode->next  = head;
        head = newNode;
        cout<<"Node Inserted At Begin"<<endl;
    }

    void reverseALinkedList(){
        Node* nextnode = head;
        Node* currentnode = head;
        Node* prevnode = NULL;

        while(nextnode != NULL){
            nextnode = nextnode->next;
            currentnode->next = prevnode;
            prevnode = currentnode;
            currentnode = nextnode;
        }

        head = prevnode;

    }

    Node* reverseALinkedListInGroup(Node* head , int k){
         Node* nextnode = head;
         Node* currentnode = head;
         Node* prevnode = NULL;
         int count = 0;
         while(nextnode != NULL && count < k){
            nextnode = nextnode->next;
            currentnode->next = prevnode;
            prevnode = currentnode;
            currentnode = nextnode;
            count++;
         }

         if(nextnode!= NULL){
            Node * temp;
            head->next = reverseALinkedListInGroup(nextnode , k);
         }
         return prevnode;
    }

    void reverseALinkedListInGroup(int k){
        head = reverseALinkedListInGroup(head,k);
    }

    void insertAtPos(int pos,int data){
        int n = sizeOfLinkedList(head);
        if(n < pos){
            return;
        }
        Node* temp = head;
        int i = 1;
        while(i < pos-1){
            temp = temp->next;
            i++;
        }
        Node* newnode = new Node(data);
        newnode->next = temp->next;
        temp->next = newnode;
        cout<<"Node Inserted At Position:  "<<pos<<"with Data "<<data<<endl;

    }

    int sizeOfLinkedList(Node* head){
        Node* temp = head;
        int count = 0;
        while(temp != NULL){
            count++;
            temp = temp->next;
        }
        return count;
    }

    void deleteAtBegin(){
        if(head == NULL){
            cout<<"Linked List is Empty"<<endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void deleteAtEnd(){
        if(head == NULL){
            cout<<"Linked List is Empty"<<endl;
            return;
        }

        Node* temp = head;
        while(temp->next->next != NULL){
            temp = temp->next;
        }

        temp->next = NULL;
        cout<<"Node Deleted At End"<<endl;

    }

    void SortLinkedList(){
        Node* i = head;

        while(i != NULL){
            Node* j = i->next;
            while(j != NULL){
                if(i->data > j->data){
                    int temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                    
                }
                        j = j->next;
            }
            i=i->next;
        }
        cout<<"LINKED LIST SORTED "<<endl;
    }
};

int main() {
    int ch;
    int data;
    LinkedList ll;
    char choice;
    cout << "MAIN MENU" << endl;
    cout << "1. INSERT AT END" << endl;
    cout << "2. DELETE ACCORDING TO THE DATA" << endl;
    cout << "3. DISPLAY LIST" << endl;
    cout << "4. INSERT AT START" << endl;
    cout<<"5. REVERSE A LINKED LIST"<<endl;
    cout<<"6. REVERSE IN GROUP "<<endl;
    cout<<"7. INSERT AT POSITION "<<endl;
    cout<<"8. DELETE AT BEGIN"<<endl;
    cout<<"9. DELETE AT LAST"<<endl;
    cout<<"10. SORT LINKED LIST"<<endl;
    cout << endl;

    do {
        cout << "Enter the choice from main menu: " << endl;
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "Enter the data you want to add at end in Linked List: " << endl;
            cin >> data;
            ll.insertAtEnd(data);
            cout << "Node added successfully at the end." << endl;
            break;

        case 2:
            cout << "Enter the data you want to delete: " << endl;
            cin >> data;
            ll.deleteByData(data);
            break;

        case 3:
            ll.display();
            break;
        case 4:
            cout << "Enter the data you want to add At begin " << endl;
            cin >> data;
            ll.inserttBegin(data);
            break;
        
        case 5:
            ll.reverseALinkedList();
            cout<<"Linked List Reversed "<<endl;
            break;
        
        case 6:
            ll.reverseALinkedListInGroup(3);
            cout<<"Linked List Reversed According to the group Value "<<endl;
            break;

        case 7:
            int pos;
            cout<<"Enter the Position and data you want to add in Linked List"<<endl;
            cin>>pos>>data;
            ll.insertAtPos(pos,data);
            break;
        
        case 8:
            ll.deleteAtBegin();
            break;

        case 9:
            ll.deleteAtEnd();
            break;
        case 10:
            ll.SortLinkedList();
            break;
        

        }




        cout << "Do you want to continue : " << endl;
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    return 0;
}