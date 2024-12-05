#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node(int data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }





};

class DoublyLinkedList {
private:
    Node* head;
public:
    DoublyLinkedList() {
        head = nullptr;
    }

    void insertAtEnd(int data) {
        Node* newnode = new Node(data);
        if (head == nullptr) {
            head = newnode;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->prev = temp;
        cout << "NODE ADDED AT END IN DOUBLY LINKED LIST " << endl;
    }

    void insertBegin(int data) {
        Node* newnode = new Node(data);
        if (head == NULL) {
            newnode->prev = head;
            head = newnode;
        }

        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }

    void insertAtPos(int pos, int data) {
        Node* newnode = new Node(data);
        int n = sizeOfLinkedList(head);
        if (pos > n) {
            return;
        }
        Node* temp = head;
        int i = 0;
        while (i < pos - 1) {
            temp = temp->next;
            i++;
        }

        newnode->next = temp->next;
        newnode->prev = temp;
        temp->next->prev = newnode;
        temp->next = newnode;
        cout << "Node Inserted at specific position " << endl;
    }

    int sizeOfLinkedList(Node* head) {
        Node* temp = head;
        int count = 0;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void deleteAtBegin() {
        if (head == NULL) {
            cout << "Linked List is Empty" << endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        head->prev = NULL;
        delete temp;
    }

    void deleteByData(int data){
        if(head == NULL){
            return;
        }

        Node* temp = head;
        while(temp->next != NULL){
            if(temp->data == data){
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                break;
            }
            else{
                temp = temp->next;
            }
        }
        cout<<"Node Deleted according to the data"<<endl;
    }

    void display() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << "<->";
            temp = temp->next;
        }
        cout << "NULL" << endl;
        cout << endl;
    }




};
int main() {
    int ch;
    int data;
    DoublyLinkedList Dll;
    char choice;
    cout << "MAIN MENU" << endl;
    cout << "1. INSERT AT END" << endl;
    cout << "2. DELETE ACCORDING TO THE DATA" << endl;
    cout << "3. DISPLAY LIST" << endl;
    cout << "4. INSERT AT START" << endl;
    cout << "5. REVERSE A LINKED LIST" << endl;
    cout << "6. REVERSE IN GROUP " << endl;
    cout << "7. INSERT AT POSITION " << endl;
    cout << "8. DELETE AT BEGIN" << endl;
    cout << "9. DELETE AT LAST" << endl;
    cout << "10. SORT LINKED LIST" << endl;
    cout << endl;

    do {
        cout << "Enter the choice from main menu: " << endl;
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "Enter the data you want to add at end in Linked List: " << endl;
            cin >> data;
            Dll.insertAtEnd(data);
            cout << "Node added successfully at the end." << endl;
            break;

            case 2:
                cout << "Enter the data you want to delete: " << endl;
                cin >> data;
                Dll.deleteByData(data);
                break;

        case 3:
            Dll.display();
            break;
        case 4:
            cout << "Enter the data you want to add At begin " << endl;
            cin >> data;
            Dll.insertBegin(data);
            break;

            // case 5:
            //     Dll.reverseALinkedList();
            //     cout<<"Linked List Reversed "<<endl;
            //     break;

            // case 6:
            //     Dll.reverseALinkedListInGroup(3);
            //     cout<<"Linked List Reversed According to the group Value "<<endl;
            //     break;

        case 7:
            int pos;
            cout << "Enter the Position and data you want to add in Linked List" << endl;
            cin >> pos >> data;
            Dll.insertAtPos(pos, data);
            break;

        case 8:
            Dll.deleteAtBegin();
            break;

            // case 9:
            //     Dll.deleteAtEnd();
            //     break;
            // case 10:
            //     Dll.SortLinkedList();
            //     break;


        }




        cout << "Do you want to continue : " << endl;
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    return 0;
}