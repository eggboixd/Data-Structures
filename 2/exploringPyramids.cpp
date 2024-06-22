#include <iostream>
#include <algorithm> // for std::max and std::min
#include <bits/stdc++.h>

using namespace std;


class AVLNode {
public:
    int data;
    AVLNode *left, *right;
    int height;

    AVLNode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
private:
    AVLNode *_root;
    unsigned _size;

    AVLNode* _avl_createNode(int value) {
        return new AVLNode(value);
    }

    int _getHeight(AVLNode* node){
        if(node==nullptr)
            return 0; 
        return node->height;
    }

    int _max(int a,int b){
        return std::max(a, b);
    }

    AVLNode* _rightRotate(AVLNode* pivotNode){
        AVLNode* newParent = pivotNode->left;
        pivotNode->left = newParent->right;
        newParent->right = pivotNode;

        pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
        newParent->height = _max(_getHeight(newParent->left), _getHeight(newParent->right)) + 1;
        
        return newParent;
    }

    AVLNode* _leftRotate(AVLNode* pivotNode) {
        AVLNode* newParent = pivotNode->right;
        pivotNode->right = newParent->left;
        newParent->left = pivotNode;

        pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
        newParent->height = _max(_getHeight(newParent->left), _getHeight(newParent->right)) + 1;
        
        return newParent;
    }

    AVLNode* _leftCaseRotate(AVLNode* node){
        return _rightRotate(node);
    }

    AVLNode* _rightCaseRotate(AVLNode* node){
        return _leftRotate(node);
    }

    AVLNode* _leftRightCaseRotate(AVLNode* node){
        node->left = _leftRotate(node->left);
        return _rightRotate(node);
    }

    AVLNode* _rightLeftCaseRotate(AVLNode* node){
        node->right = _rightRotate(node->right);
        return _leftRotate(node);
    }

    int _getBalanceFactor(AVLNode* node){
        if(node==nullptr)
            return 0;
        return _getHeight(node->left) - _getHeight(node->right);
    }

    AVLNode* _insert_AVL(AVLNode* node, int value) {
        if(node==nullptr)
            return _avl_createNode(value);

        if(value < node->data)
            node->left = _insert_AVL(node->left, value);
        else if(value > node->data)
            node->right = _insert_AVL(node->right, value);
        
        node->height = _max(_getHeight(node->left), _getHeight(node->right)) + 1; 

        int balanceFactor = _getBalanceFactor(node);
        
        if(balanceFactor > 1 && value < node->left->data)
            return _leftCaseRotate(node);
        if(balanceFactor > 1 && value > node->left->data)
            return _leftRightCaseRotate(node);
        if(balanceFactor < -1 && value > node->right->data)
            return _rightCaseRotate(node);
        if(balanceFactor < -1 && value < node->right->data)
            return _rightLeftCaseRotate(node);
        
        return node;
    }

    AVLNode* _findMinNode(AVLNode *node) {
        AVLNode *currNode = node;
        while (currNode && currNode->left != nullptr)
            currNode = currNode->left;
        return currNode;
    }

    AVLNode* _remove_AVL(AVLNode* node, int value){
        if(node==nullptr)
            return node;
        if(value > node->data)
            node->right = _remove_AVL(node->right, value);
        else if(value < node->data)
            node->left = _remove_AVL(node->left, value);
        else{
            AVLNode *temp;
            if((node->left==nullptr) || (node->right==nullptr)){
                temp = (node->left == nullptr) ? node->right : node->left;
                
                if(temp==nullptr){
                    temp=node;
                    node=nullptr;
                }
                else
                    *node = *temp;
                
                delete temp;
            }
            else{
                temp = _findMinNode(node->right);
                node->data=temp->data;
                node->right=_remove_AVL(node->right,temp->data);
            }    
        }

        if(node==nullptr) return node;
        
        node->height=_max(_getHeight(node->left), _getHeight(node->right)) + 1;

        int balanceFactor= _getBalanceFactor(node);
        
        if(balanceFactor > 1 && _getBalanceFactor(node->left) >= 0) 
            return _leftCaseRotate(node);

        if(balanceFactor > 1 && _getBalanceFactor(node->left) < 0) 
            return _leftRightCaseRotate(node);
    
        if(balanceFactor < -1 && _getBalanceFactor(node->right) <= 0) 
            return _rightCaseRotate(node);

        if(balanceFactor < -1 && _getBalanceFactor(node->right) > 0) 
            return _rightLeftCaseRotate(node);
        
        return node;
    }

    void _inorder(AVLNode *node) {
        if (node) {
            _inorder(node->left);
            std::cout << node->data << " ";
            _inorder(node->right);
        }
    }

    void _postorder(AVLNode *node) {
        if (node) {
            _postorder(node->left);
            _postorder(node->right);
            std::cout << node->data << " ";
        }
    }

    void _preorder(AVLNode *node) {
        if (node) {
            std::cout << node->data << " ";
            _preorder(node->left);
            _preorder(node->right);
        }
    }

    int _sumTree(AVLNode *node) {
        if (node == nullptr)
            return 0;
        return node->data + _sumTree(node->left) + _sumTree(node->right);
    }

    AVLNode* _reverseTree(AVLNode* node) {
        if (node == nullptr)
            return nullptr;
        std::swap(node->left, node->right);
        _reverseTree(node->left);
        _reverseTree(node->right);
        return node;
    }

    int _findMinValue(AVLNode* node) {
        if (node == nullptr)
            return -1; // Or throw an exception
        while (node->left != nullptr)
            node = node->left;
        return node->data;
    }

    int _findMaxValue(AVLNode* node) {
        if (node == nullptr)
            return -1; // Or throw an exception
        while (node->right != nullptr)
            node = node->right;
        return node->data;
    }

    int _findLevel(AVLNode* node, int value, int level) {
        if (node == nullptr)
            return -1; // Value not found
        if (node->data == value)
            return level;
        int downlevel = _findLevel(node->left, value, level + 1);
        if (downlevel != -1)
            return downlevel;
        return _findLevel(node->right, value, level + 1);
    }

public:
    AVL() : _root(nullptr), _size(0U) {}

    bool isEmpty() {
        return _root == nullptr;
    }

    bool find(int value) {
        return _search(_root, value) != nullptr;
    }

    void insert(int value) {
        if (!find(value)) {
            _root = _insert_AVL(_root, value);
            _size++;
        }
    }

    void remove(int value) {
        if (find(value)) {
            _root = _remove_AVL(_root, value);
            _size--;
        }
    }

    void inorder() {
        _inorder(_root);
        std::cout << std::endl;
    }

    void postorder() {
        _postorder(_root);
        std::cout << std::endl;
    }

    void preorder() {
        _preorder(_root);
        std::cout << std::endl;
    }

    int sumTree() {
        return _sumTree(_root);
    }

    void reverseTree() {
        _reverseTree(_root);
    }

    int findMinValue() {
        return _findMinValue(_root);
    }

    int findMaxValue() {
        return _findMaxValue(_root);
    }

    int findLevel(int value) {
        return _findLevel(_root, value, 1);
    }
};

int main() {
    AVL set;

    /*
    set.insert(6);
    set.insert(611);
    set.insert(7);
    set.insert(612);
    set.insert(12);
    set.insert(4);

    std::cout << "Inorder traversal: ";
    set.inorder();

    std::cout << "Postorder traversal: ";
    set.postorder();

    std::cout << "Preorder traversal: ";
    set.preorder();

    std::cout << "Sum of the tree: " << set.sumTree() << std::endl;

    std::cout << "Minimum value of the tree: " << set.findMinValue() << std::endl;
    std::cout << "Maximum value of the tree: " << set.findMaxValue() << std::endl;

    int valueToFind = 611;
    int level = set.findLevel(valueToFind);
    if (level != -1)
        std::cout << "The level of value " << valueToFind << " is: " << level << std::endl;
    else
        std::cout << "Value " << valueToFind << " not found in the tree." << std::endl;
        */
    int n;
    cin >> n;

    int room;
    for(int i = 0; i < n; i++){
        cin >> room;
        tree.insert(room);
    }
    
    int val = set.findLevel();

    if(val >= 1 && val <= 3){
        cout << "You can use the rope" << endl;
    } else if(val >= 4 && val <= 6){
        cout << "You can use the paraglider" << endl;
    } else {
        cout << "You should call for the helicopter" << endl;
    }

    return 0;
}
