#include <iostream>
using namespace std;

template <typename T>
class Node{
public:
    T value;
    Node* left;
    Node* right;
    Node() {
        value = NULL;
        left = right = nullptr;
    }
    Node(T data) {
        value = data;
        left = right = nullptr;     
    }
};

template <typename T>
class BinaryTree {
public:
    Node<T>* root;

    BinaryTree() {
        root = nullptr;
    }

    void insertLeaves(T data, Node<T>*&root1) {
        Node<T>* temp = new Node<T>(data);
        if (root1 == nullptr) {
            root1 = temp;
        }
        else if (root1->left == nullptr) {
            root1->left = temp;
        }
        else if (root1->right == nullptr) {
            root1->right = temp;
        }
        else if(root1->left->left == nullptr || root1->left->right == nullptr){
            insertLeaves(data, root1->left);
        }
        else if (root1->right->left == nullptr || root1->right->right == nullptr) {
            insertLeaves(data, root1->right);
        }
        else {
            insertLeaves(data, root1->left);
        }
    }

    void deleteDeepest(Node<T>*& root1) {
        if (root1 == nullptr)return;
        if (root1->left == nullptr) root1 = nullptr;
        else { 
            deleteDeepest(root1->left);
            deleteDeepest(root1->right);
        }
    }

    void inOrder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        else {
            inOrder(node->left);
            cout << node->value << " ";
            inOrder(node->right);
        }

    }
    void preOrder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        else {
            cout << node->value << " ";
            preOrder(node->left);
            preOrder(node->right);
        }

    }

    void postOrder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        else {
            postOrder(node->left);
            postOrder(node->right);
            cout << node->value << " ";
        }

    }


};

int main()
{
    std::cout << "---------- Binary Tree ----------"<<endl<<endl;

    BinaryTree<int> bt;
    bt.insertLeaves(10, bt.root);
    bt.insertLeaves(20, bt.root);
    bt.insertLeaves(30, bt.root);
    bt.insertLeaves(40, bt.root);
    bt.insertLeaves(50, bt.root);
    bt.insertLeaves(60, bt.root);
    bt.insertLeaves(70, bt.root);
    bt.insertLeaves(80, bt.root);
    bt.insertLeaves(90, bt.root);
    bt.insertLeaves(100, bt.root);
    bt.insertLeaves(110,bt.root);
    cout << "Inorder Traversal : " << endl;
    bt.inOrder(bt.root); cout << endl<<endl;
    cout << "Postorder Traversal : " << endl;
    bt.postOrder(bt.root); cout << endl << endl;
    cout << "Preorder Traversal : " << endl;
    bt.preOrder(bt.root);
    cout << endl << endl;

    return 0;
}