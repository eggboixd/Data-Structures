#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int x) {
        if (node == nullptr) return new TreeNode(x);
        if (x < node->val) node->left = insert(node->left, x);
        else if (x > node->val) node->right = insert(node->right, x);
        return node;
    }

    void inOrderTraversal(TreeNode* node, vector<int>& elements) {
        if (node == nullptr) return;
        inOrderTraversal(node->left, elements);
        elements.push_back(node->val);
        inOrderTraversal(node->right, elements);
    }

    TreeNode* search(TreeNode* node, int y) {
        if (node == nullptr || node->val == y) return node;
        if (y < node->val) return search(node->left, y);
        return search(node->right, y);
    }

    void printPreOrder(TreeNode* node) {
        if (node == nullptr) return;
        cout << node->val << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

public:
    BST() : root(nullptr) {}

    void hook(int x) {
        root = insert(root, x);
    }

    void coconut() {
        vector<int> elements;
        inOrderTraversal(root, elements);
        for (size_t i = 0; i < elements.size(); ++i) {
            cout << elements[i];
            if (i != elements.size() - 1) cout << " ";
        }
        cout << endl;
    }

    void fish(int y) {
        TreeNode* subtreeRoot = search(root, y);
        if (subtreeRoot == nullptr) {
            cout << "ups no \"i can tree\" here" << endl;
        } else {
            printPreOrder(subtreeRoot);
            cout << endl;  // Ensure the output format ends with a newline
        }
    }
};

int main() {
    BST bst;
    string command;
    while (true) {
        cin >> command;
        if (command == "FIN") break;
        if (command == "HOOK") {
            int x;
            cin >> x;
            bst.hook(x);
        } else if (command == "COCONUT") {
            bst.coconut();
        } else if (command == "FISH") {
            int y;
            cin >> y;
            bst.fish(y);
        }
    }
    return 0;
}
