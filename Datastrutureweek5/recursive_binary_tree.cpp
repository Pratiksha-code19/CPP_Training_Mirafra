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

    // Function to insert a new node in the binary tree
    void insert(int value) {
        root = insertRec(root, value);
    }

    // Function to perform in-order traversal of the tree
    void inorder() {
        inorderRec(root);
        cout << endl;
    }

    // Function to perform pre-order traversal of the tree
    void preorder() {
        preorderRec(root);
        cout << endl;
    }

    // Function to perform post-order traversal of the tree
    void postorder() {
        postorderRec(root);
        cout << endl;
    }

private:
    // Recursive function to insert a new node
    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        // Insert to the left child if it is empty
        if (node->left == nullptr) {
            node->left = new Node(value);
        }
        // Otherwise, insert to the right child if it is empty
        else if (node->right == nullptr) {
            node->right = new Node(value);
        }
        // If both left and right children are occupied, recursively insert in left or right subtrees
        else {
            insertRec(node->left, value);  // Insertion to left first if both children are occupied
        }

        return node;
    }

    // Recursive function for in-order traversal
    void inorderRec(Node* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    // Recursive function for pre-order traversal
    void preorderRec(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    // Recursive function for post-order traversal
    void postorderRec(Node* node) {
        if (node == nullptr) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }
};

int main() {
    BinaryTree tree;

    // Insert elements into the binary tree
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    // Print the tree traversals
    cout << "In-order traversal: ";
    tree.inorder(); // Expected output: 4 2 5 1 6 3 7

    cout << "Pre-order traversal: ";
    tree.preorder(); // Expected output: 1 2 4 5 3 6 7

    cout << "Post-order traversal: ";
    tree.postorder(); // Expected output: 4 5 2 6 7 3 1

    return 0;
}