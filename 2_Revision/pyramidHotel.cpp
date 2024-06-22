#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

int height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int balanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Function to insert a node into the AVL tree
Node* insert(Node* root, int data) {
    if (root == nullptr)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    // Left Left Case
    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool search(Node* root, int data, vector<int>& path) {
    if (root == nullptr)
        return false;

    path.push_back(root->data);

    if (data == root->data)
        return true;
    else if (data < root->data)
        return search(root->left, data, path);
    else
        return search(root->right, data, path);
}

int main() {
    int n;
    cin >> n;

    Node* root = nullptr;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        root = insert(root, x);
    }

    int aliceRoom, friendRoom;
    cin >> aliceRoom >> friendRoom;

    vector<int> alicePath;
    vector<int> friendPath;

    search(root, aliceRoom, alicePath);

    bool friendFound = search(root, friendRoom, friendPath);

    for (int room : alicePath)
        cout << room << " ";
    cout << endl;

    if (friendFound)
        cout << "Alice visited her friend's room" << endl;
    else
        cout << "Alice asked her friend through SMS" << endl;

    return 0;
}
