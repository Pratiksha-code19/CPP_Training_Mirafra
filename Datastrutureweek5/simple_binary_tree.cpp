#include <iostream>
using namespace std;

// Define the structure for a node in the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor to create a new node
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// BinaryTree class to manage tree operations
class BinaryTree {
public:
    Node* root;

    // Constructor to initialize the tree
    BinaryTree() {
        root = nullptr;
    }

    // Method to print tree in-order (just for visualization here)
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
};

int main() {
    BinaryTree tree;

    // Manually creating nodes
    tree.root = new Node(1);        // Root node
    tree.root->left = new Node(2);  // Left child of root
    tree.root->right = new Node(3); // Right child of root
    
    tree.root->left->left = new Node(4);  // Left child of node 2
    tree.root->left->right = new Node(5); // Right child of node 2
    
    tree.root->right->left = new Node(6); // Left child of node 3
    tree.root->right->right = new Node(7); // Right child of node 3

    // Manually inserting nodes into the binary tree
    // You can set `left` and `right` pointers directly here to build the tree.

    // Print the tree in-order to check the structure
    cout << "In-order traversal: ";
    tree.inorder(tree.root); // Expected output: 4 2 5 1 6 3 7
    cout << endl;

    return 0;
}