#include <bits/stdc++.h>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void swap(Node*& head, int k) {
    if (head == nullptr) return;

    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }

    if (k < 1 || k > count) {
        return;
    }

    Node* firstKthNode = head;
    for (int i = 1; i < k; ++i) {
        firstKthNode = firstKthNode->next;
    }

    Node* secondKthNode = head;
    for (int i = 1; i <= count - k; ++i) {
        secondKthNode = secondKthNode->next;
    }

    int tempData = firstKthNode->data;
    firstKthNode->data = secondKthNode->data;
    secondKthNode->data = tempData;
}

void printList(Node* node) {
    while (node != nullptr) {
        cout << node->data;
        if (node->next != nullptr)
            cout << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    vector<int> values;
    int val;
    while (cin >> val && val != -1) {
        values.push_back(val);
    }

    int k;
    cin >> k;

    Node* head = nullptr;
    Node* tail = nullptr;
    for (int value : values) {
        if (head == nullptr) {
            head = new Node(value);
            tail = head;
        } else {
            tail->next = new Node(value);
            tail = tail->next;
        }
    }

    swap(head, k);

    printList(head);

    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
