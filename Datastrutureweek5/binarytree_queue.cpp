#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int key) {
        data = key;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;
    BinaryTree() {
        root = nullptr;
    }

    void insert(int key) {
        Node* newNode = new Node(key);
        if (root == nullptr) {
            root = newNode;
            return;
        }
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* node = q.front();
            q.pop();

            if (node->left == nullptr) {
                node->left = newNode;
                return;
            } else {
                q.push(node->left);
            }

            if (node->right == nullptr) {
                node->right = newNode;
                return;
            } else {
                q.push(node->right);
            }
        }
    }

    void levelOrderTraversal() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            cout << node->data << " ";
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }
};

int main() {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    cout << "Level order traversal of the binary tree:" << endl;
    tree.levelOrderTraversal();

    return 0;
}
