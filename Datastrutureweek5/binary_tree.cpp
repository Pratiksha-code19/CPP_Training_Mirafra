#include <iostream>
using namespace std;

// Node structure for the binary tree
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor to create a new node
    Node(int key) {
        data = key;
        left = right = nullptr;
    }
};

// Function to insert a node in the binary tree (First available spot)
Node* insert(Node* root, int key) {
    // If the tree is empty, create a new node and return it as the root
    if (root == nullptr) {
        return new Node(key);
    }

    // Recursively insert the node in the left subtree first, if possible
    if (root->left == nullptr) {
        root->left = new Node(key);
        return root;
    } else {
        // If the left child is not empty, recursively insert in the right subtree
        if (root->right == nullptr) {
            root->right = new Node(key);
            return root;
        } else {
            // If both children are not empty, recursively insert in left and right subtrees
            insert(root->left, key);
        }
    }
    return root;
}

// Function to print the Inorder Traversal of the binary tree
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);  // Traverse left subtree
        cout << root->data << " ";  // Print root data
        inorder(root->right);  // Traverse right subtree
    }
}

// Main function to test the binary tree insertion
int main() {
    Node* root = nullptr;

    // Inserting nodes into the binary tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 70);

    // Print the Inorder traversal of the tree
    cout << "Inorder Traversal: ";
    inorder(root);  // Output: 10 20 30 40 50 60 70
    cout << endl;

    return 0;
}
