#include <iostream>
using namespace std;

// Definition of Node structure
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

// Insert a node in the BST
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value); // Create a new node if the root is null
    }

    // Traverse the tree to find the correct position for the new node
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Search for a node in the BST
Node* search(Node* root, int value) {
    if (root == nullptr || root->data == value) {
        return root; // Return root if value is found or if we reach the end (nullptr)
    }

    if (value < root->data) {
        return search(root->left, value); // Search in the left subtree
    } else {
        return search(root->right, value); // Search in the right subtree
    }
}

// Find the minimum value node in a BST
Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left; // Go to the leftmost node
    }
    return root;
}

// Delete a node from the BST
Node* deleteNode(Node* root, int value) {
    if (root == nullptr) {
        return root; // If the tree is empty, return nullptr
    }

    // Traverse the tree
    if (value < root->data) {
        root->left = deleteNode(root->left, value); // Go to the left subtree
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value); // Go to the right subtree
    } else {
        // Node with only one child or no child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root; // Delete the current node
            return temp; // Return the right child
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root; // Delete the current node
            return temp; // Return the left child
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// In-order traversal to print the tree
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    // Inserting nodes
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "In-order traversal of the BST: ";
    inorder(root);
    cout << endl;

    // Searching for a node
    int searchValue = 40;
    Node* result = search(root, searchValue);
    if (result != nullptr) {
        cout << "Node " << searchValue << " found in the BST." << endl;
    } else {
        cout << "Node " << searchValue << " not found in the BST." << endl;
    }

    // Deleting a node
    int deleteValue = 70;
    cout << "Deleting node " << deleteValue << "..." << endl;
    root = deleteNode(root, deleteValue);
    
    // In-order traversal after deletion
    cout << "In-order traversal after deletion: ";
    inorder(root);
    cout << endl;

    return 0;
}
/*Steps for Deleting Node 50:
Find the inorder successor of 50, which is the node with value 60.
Replace node 50 with 60.
Delete node 60, as it's now a duplicate of 50.*/