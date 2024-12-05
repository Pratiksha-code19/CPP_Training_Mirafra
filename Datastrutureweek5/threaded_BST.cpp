#include<bits/stdc++.h>
using namespace std;
class Node{
    public:
        int data;
        Node* right;
        Node* left;
        bool isThreaded;

        Node(int data){
            this->data = data;
            left = nullptr;
            right = nullptr;
            isThreaded = false;

        }
};

class ThreadedBinarySearchTree{
    public:
        Node* root;

        ThreadedBinarySearchTree(){
            root = nullptr;

        }

        void insertNode(int val){
            Node* newnode = new Node(val);
            if(!root){
                root = newnode;
                return;
            }
            Node* curr = root;
            Node* temparent = nullptr;

            while(curr != NULL){
                temparent = curr;
                if(curr->data > val){
                    if(curr->left == NULL){
                        break;
                    }
                    else{
                        curr = curr->left;
                    }
                }
                else{
                    if(curr->right == nullptr || curr->isThreaded ){
                        break;
                    }
                    else{
                        curr = curr->right;
                    }
                }
            }

            if(temparent->data > val){
                temparent->left = newnode;
                newnode->right = temparent;
                newnode->isThreaded = true;
            }
            else{
                if(temparent->isThreaded){
                    newnode->right = temparent->right;
                    temparent->isThreaded = false;
                }
                temparent->right = newnode;
                newnode->isThreaded = true;
            }


        }

        void inorderTraversal(){
            Node* temp = root;

            while(temp != nullptr){
                while(temp->left != nullptr){
                    temp = temp->left;
                }

                cout<<temp->data<<" ";

                while(temp->isThreaded){
                    temp = temp->right;
                    cout<<temp->data<<" ";
                }

                temp = temp->right;
            }
        }
};
int main(){
    ThreadedBinarySearchTree tbst;
    tbst.insertNode(50);
    tbst.insertNode(30);
    tbst.insertNode(70);
    tbst.insertNode(20);
    tbst.insertNode(40);
    tbst.insertNode(60);
    tbst.insertNode(80);

    cout<<"Inorder Traversal (Non-Recursive): "<<endl;
    tbst.inorderTraversal();

    return 0;
}