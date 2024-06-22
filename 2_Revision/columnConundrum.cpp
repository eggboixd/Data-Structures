#include <iostream>
#include <algorithm> // for std::max and std::min
#include <bits/stdc++.h>
#include <map>
#include <queue>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
    int height;

    Node(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
private:
    Node<T>* root;

    int height(Node<T>* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int balanceFactor(Node<T>* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    Node<T>* rightRotate(Node<T>* y) {
        Node<T>* x = y->left;
        Node<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node<T>* leftRotate(Node<T>* x) {
        Node<T>* y = x->right;
        Node<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node<T>* insert(Node<T>* node, T data) {
        if (node == nullptr) return new Node<T>(data);

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node; // Duplicate keys not allowed

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node<T>* deleteNode(Node<T>* root, T data) {
        if (root == nullptr) return root;

        if (data < root->data)
            root->left = deleteNode(root->left, data);
        else if (data > root->data)
            root->right = deleteNode(root->right, data);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                Node<T>* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node<T>* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr) return root;

        root->height = 1 + std::max(height(root->left), height(root->right));

        int balance = balanceFactor(root);

        // Left Left Case
        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void inorderTraversal(Node<T>* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node<T>* node) {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(Node<T>* node) {
        if (node == nullptr) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->data << " ";
    }

    bool isEqual(Node<T>* node1, Node<T>* node2) {
        if (node1 == nullptr && node2 == nullptr)
            return true;
        if (node1 == nullptr || node2 == nullptr)
            return false;
        return (node1->data == node2->data &&
                isEqual(node1->left, node2->left) &&
                isEqual(node1->right, node2->right));
    }

    bool isSymmetric(Node<T>* left, Node<T>* right) {
        if (left == nullptr && right == nullptr)
            return true;
        if (left == nullptr || right == nullptr)
            return false;
        return (left->data == right->data &&
                isSymmetric(left->left, right->right) &&
                isSymmetric(left->right, right->left));
    }

    T findMin(Node<T>* node) {
        if (node == nullptr)
            throw std::invalid_argument("Tree is empty");
        while (node->left != nullptr)
            node = node->left;
        return node->data;
    }

    T findMax(Node<T>* node) {
        if (node == nullptr)
            throw std::invalid_argument("Tree is empty");
        while (node->right != nullptr)
            node = node->right;
        return node->data;
    }

    Node<T>* reverse(Node<T>* node) {
        if (node == nullptr)
            return nullptr;
        std::swap(node->left, node->right);
        reverse(node->left);
        reverse(node->right);
        return node;
    }

    T sum(Node<T>* node) {
        if (node == nullptr) return 0;
        return node->data + sum(node->left) + sum(node->right);
    }

    Node<T>* search(Node<T>* node, T key) {
        if (node == nullptr || node->data == key)
            return node;
        if (key < node->data)
            return search(node->left, key);
        return search(node->right, key);
    }

    void columnSums(Node<T>* root, map<int, int>& colSumMap) {
        if (root == nullptr) return;
        queue<pair<Node<T>*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            Node<T>* node = p.first;
            int hd = p.second;

            colSumMap[hd] += node->data;

            if (node->left != nullptr)
                q.push({node->left, hd - 1});
            if (node->right != nullptr)
                q.push({node->right, hd + 1});
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T data) {
        root = insert(root, data);
    }

    void remove(T data) {
        root = deleteNode(root, data);
    }

    void inorder() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void preorder() {
        preorderTraversal(root);
        std::cout << std::endl;
    }

    void postorder() {
        postorderTraversal(root);
        std::cout << std::endl;
    }

    bool isEqual(AVLTree<T>& other) {
        return isEqual(root, other.root);
    }

    bool isSymmetric() {
        if (root == nullptr) return true;
        return isSymmetric(root->left, root->right);
    }

    T findMin() {
        return findMin(root);
    }

    T findMax() {
        return findMax(root);
    }

    void reverse() {
        root = reverse(root);
    }

    T sum() {
        return sum(root);
    }

    Node<T>* search(T key) {
        return search(root, key);
    }

    void solve() {
        map<int, int> colSumMap;
        columnSums(root, colSumMap);
        for (auto& pair : colSumMap) {
            cout << pair.second << " ";
        }
        cout << endl;
    }
};

int main() {
    AVLTree<int> tree;
    int n;
    cin >> n;
    int val;
    string cmd; 
    for(int i = 0; i < n; i++) {
        cin >> cmd;
        if (cmd == "insert") {
            cin >> val;
            tree.insert(val);
        } else if (cmd == "solve") {
            tree.solve();
        }
    }
    return 0;
}
