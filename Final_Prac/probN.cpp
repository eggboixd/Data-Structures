#include <bits/stdc++.h>

using namespace std;

struct AVLNode {
    int key;
    int value;
    AVLNode *left, *right;
    int height;
};

struct AVL
{
private:
    AVLNode *_root;
    unsigned _size;

    AVLNode* _avl_createNode(int key, int value) {
        AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
        newNode->key = key;
        newNode->value = value;
        newNode->height = 1;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    AVLNode* _search(AVLNode *root, int key) {
        while (root != NULL) {
            if (key < root->key)
                root = root->left;
            else if (key > root->key)
                root = root->right;
            else
                return root;
        }
        return root;
    }

    int _getHeight(AVLNode* node) {
        if (node == NULL)
            return 0; 
        return node->height;
    }

    int _max(int a, int b) {
        return (a > b) ? a : b;
    }

    AVLNode* _rightRotate(AVLNode* pivotNode) {
        AVLNode* newParrent = pivotNode->left;
        pivotNode->left = newParrent->right;
        newParrent->right = pivotNode;

        pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
        newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

        return newParrent;
    }

    AVLNode* _leftRotate(AVLNode* pivotNode) {
        AVLNode* newParrent = pivotNode->right;
        pivotNode->right = newParrent->left;
        newParrent->left = pivotNode;

        pivotNode->height = _max(_getHeight(pivotNode->left), _getHeight(pivotNode->right)) + 1;
        newParrent->height = _max(_getHeight(newParrent->left), _getHeight(newParrent->right)) + 1;

        return newParrent;
    }

    AVLNode* _leftCaseRotate(AVLNode* node) {
        return _rightRotate(node);
    }

    AVLNode* _rightCaseRotate(AVLNode* node) {
        return _leftRotate(node);
    }

    AVLNode* _leftRightCaseRotate(AVLNode* node) {
        node->left = _leftRotate(node->left);
        return _rightRotate(node);
    }

    AVLNode* _rightLeftCaseRotate(AVLNode* node) {
        node->right = _rightRotate(node->right);
        return _leftRotate(node);
    }

    int _getBalanceFactor(AVLNode* node) {
        if (node == NULL)
            return 0;
        return _getHeight(node->left) - _getHeight(node->right);
    }

    AVLNode* _insert_AVL(AVLNode* node, int key, int value) {
        if (node == NULL)
            return _avl_createNode(key, value);
        if (key < node->key)
            node->left = _insert_AVL(node->left, key, value);
        else if (key > node->key)
            node->right = _insert_AVL(node->right, key, value);
        else
            return node;

        node->height = 1 + _max(_getHeight(node->left), _getHeight(node->right)); 

        int balanceFactor = _getBalanceFactor(node);

        if (balanceFactor > 1 && key < node->left->key)
            return _leftCaseRotate(node);
        if (balanceFactor > 1 && key > node->left->key)
            return _leftRightCaseRotate(node);
        if (balanceFactor < -1 && key > node->right->key)
            return _rightCaseRotate(node);
        if (balanceFactor < -1 && key < node->right->key)
            return _rightLeftCaseRotate(node);

        return node;
    }

    AVLNode* _findMinNode(AVLNode *node) {
        AVLNode *currNode = node;
        while (currNode && currNode->left != NULL)
            currNode = currNode->left;
        return currNode;
    }

    AVLNode* _remove_AVL(AVLNode* node, int key) {
        if (node == NULL)
            return node;
        if (key > node->key)
            node->right = _remove_AVL(node->right, key);
        else if (key < node->key)
            node->left = _remove_AVL(node->left, key);
        else {
            AVLNode *temp;
            if ((node->left == NULL) || (node->right == NULL)) {
                temp = node->left ? node->left : node->right;

                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                }
                else
                    *node = *temp;

                free(temp);
            }
            else {
                temp = _findMinNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = _remove_AVL(node->right, temp->key);
            }
        }

        if (node == NULL) return node;

        node->height = _max(_getHeight(node->left), _getHeight(node->right)) + 1;

        int balanceFactor = _getBalanceFactor(node);

        if (balanceFactor > 1 && _getBalanceFactor(node->left) >= 0)
            return _leftCaseRotate(node);

        if (balanceFactor > 1 && _getBalanceFactor(node->left) < 0)
            return _leftRightCaseRotate(node);

        if (balanceFactor < -1 && _getBalanceFactor(node->right) <= 0)
            return _rightCaseRotate(node);

        if (balanceFactor < -1 && _getBalanceFactor(node->right) > 0)
            return _rightLeftCaseRotate(node);

        return node;
    }

    void _inorder(AVLNode *node) {
        if (node) {
            _inorder(node->left);
            printf("Key: %d, Value: %d\n", node->key, node->value);
            _inorder(node->right);
        }
    }

public:
    void init() {
        _root = NULL;
        _size = 0U;
    }

    bool isEmpty() {
        return _root == NULL;
    }

    bool find(int key) {
        AVLNode *temp = _search(_root, key);
        if (temp == NULL)
            return false;

        if (temp->key == key) return true;
        else return false;
    }

    void insert(int key, int value) {
        if (!find(key)) {
            _root = _insert_AVL(_root, key, value);
            _size++;
        }
    }

    void remove(int key) {
        if (find(key)) {
            _root = _remove_AVL(_root, key);
            _size--;
        }
    }

    void inorder() {
        this->_inorder(_root);
    }

    AVLNode* getRoot() {
        return _root;
    }

    vector<int> getLevelSums() {
        vector<int> levelSums;

        queue<pair<AVLNode*, int>> q;
        q.push(make_pair(_root, 1)); // Push root with level 1

        while (!q.empty()) {
            AVLNode* curr = q.front().first; // Extract node
            int level = q.front().second; // Extract level
            q.pop();

            // If this is the first node of this level, push back a new sum
            if (levelSums.size() < level)
                levelSums.push_back(curr->value);
            else // Otherwise, add to the existing sum
                levelSums[level - 1] += curr->value;

            // Push children nodes with decremented level (from bottom to top)
            if (curr->right)
                q.push(make_pair(curr->right, level + 1));
            if (curr->left)
                q.push(make_pair(curr->left, level + 1));
        }
        // Reverse the levelSums vector
        reverse(levelSums.begin(), levelSums.end());

    return levelSums;
}

    string result(int trailblazerPower, const string& regionName){
        if (trailblazerPower % 2 == 0) {
            trailblazerPower += trailblazerPower * 8 / 100; // Bertambah 8%
        } else {
            trailblazerPower += trailblazerPower * 15 / 100; // Bertambah 15%
        }

        vector<int> levelSums = getLevelSums();
        int totalMonsterPower = accumulate(levelSums.begin(), levelSums.end(), 0);

        if (totalMonsterPower <= trailblazerPower) {
            return "menang melawan Final Boss dan memenangkan game di Honkai Star Rail Region " + regionName;
        } else {
            int stage = 0;
            int remainingPower = trailblazerPower;
            for (int power : levelSums) {
                stage++;

                if (remainingPower < 0) {
                    return "kalah dan mati di Region " + regionName + " pada Stage " + to_string(stage - 1);
                }
                remainingPower -= power;
            }
            return "kalah dan mati di Region " + regionName + " pada Final Stage";
        }
    }

};



int main(int argc, char const *argv[])
{
    AVL set;
    set.init();

    string trailblazerName, elementName, regionName;
    int n, power;

    cin >> trailblazerName >> n >> elementName >> power >> regionName;

    for(int i = 0; i < n; i++){
        int monsterCode, monsterPower;
        cin >> monsterCode >> monsterPower;
        set.insert(monsterCode, monsterPower);
    }

    cout << "*****************************************************************************" << endl;
    
    cout << "Honkai Star Rail Region " << regionName << endl << endl;
    cout << "Trailblazer : " << trailblazerName << endl;
    cout << "Element : " << elementName << " - " << power << endl;
    cout << "----------------------------------------------------------------------------" << endl;

    vector<queue<AVLNode*>> levels;
    queue<AVLNode*> q;
    q.push(set.getRoot());

    while (!q.empty()) {
        int size = q.size();
        queue<AVLNode*> level;
        for (int i = 0; i < size; i++) {
            AVLNode* curr = q.front();
            q.pop();
            level.push(curr);

            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
        levels.push_back(level);
    }

    

    for (int i = levels.size() - 1; i >= 0; i--) {
        int stage = levels.size() - 1 - i;
        if (stage == levels.size() - 1) {
            cout << "Final Stage:" << endl;
            while (!levels[i].empty()) {
                AVLNode* curr = levels[i].front();
                levels[i].pop();
                if (levels[i].empty()) {
                    cout << "Final Boss " << regionName << "_" << curr->key << ": " << curr->value << endl;
                } else {
                    cout << "Monster Code: " << curr->key << ", Power: " << curr->value << endl;
                }
            }
        } else {
            stage++;
            cout << "Stage " << stage << ":" << endl;
            char wuh = 'A';
            int flag = 1;
            while (!levels[i].empty()) {
                AVLNode* curr = levels[i].front();
                levels[i].pop();
                
                cout << "Monster " << wuh << curr->key << "_" << stage << "_" << flag << ": " << curr->value << endl;
                wuh++;
                flag++;
            }
            cout << endl;
        }
    }

    cout << endl;

    string gameResult = set.result(power, regionName);
    cout << "Result: \n" << trailblazerName << " " << gameResult << endl;
    //

    cout << "*****************************************************************************" << endl;

    return 0;
}
