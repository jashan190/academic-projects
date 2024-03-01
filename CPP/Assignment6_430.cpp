#include <iostream>
#include <list>
#include <vector>

using namespace std;

// Define the structure for the tree node
struct TreeNode {
    char data;
    TreeNode *left, *right;

    TreeNode(char value) {
        data = value;
        left = right = nullptr;
    }
};

// Function to insert a new node in the BST
TreeNode* insert(TreeNode* root, char value) {
    int numValue = value - '0'; 
    if (root == nullptr) {
        return new TreeNode(value);
    }

    int rootValue = root->data - '0'; 
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Inorder traversal
void inOrder(TreeNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

// Preorder traversal
void preOrder(TreeNode* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Postorder traversal
void postOrder(TreeNode* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

// Main function
int main() {
    TreeNode* root = nullptr;
    root = insert(root, '4');
    root = insert(root, '2');
    root = insert(root, '6');
    root = insert(root, '1');
    root = insert(root, '3');
    root = insert(root, '5');
    root = insert(root, '7');

    cout << "Inorder Traversal: ";
    inOrder(root);
    cout << endl;

    cout << "Preorder Traversal: ";
    preOrder(root);
    cout << endl;

    cout << "Postorder Traversal: ";
    postOrder(root);
    cout << endl;

    return 0;
}
