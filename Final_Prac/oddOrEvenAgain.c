#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Struktur Node
typedef struct snode_t {
    int data;
    struct snode_t *next;
} SListNode;

// Struktur ADT SinglyList
typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

// Function prototypes
void slist_init(SinglyList *list);
bool slist_isEmpty(SinglyList *list);
void slist_pushFront(SinglyList *list, int value);
void slist_pushBack(SinglyList *list, int value);
void slist_popBack(SinglyList *list);
int slist_back(SinglyList *list);

int main() {
    // Initialize lists for even and odd numbers
    SinglyList myList, myListGenap, myListGanjil;
    slist_init(&myList);
    slist_init(&myListGenap);
    slist_init(&myListGanjil);

    int n;
    scanf("%d", &n);

    // Input numbers into the main list
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        slist_pushBack(&myList, val);
    }

    // Separate even and odd numbers into their respective lists
    while (!slist_isEmpty(&myList)) {
        int num = slist_back(&myList);
        slist_popBack(&myList);
        if (num % 2 == 0) {
            // Sort even numbers ascendingly
            if (slist_isEmpty(&myListGenap) || num >= slist_back(&myListGenap)) {
                slist_pushBack(&myListGenap, num);
            } else {
                while (!slist_isEmpty(&myListGenap) && num < slist_back(&myListGenap)) {
                    slist_pushBack(&myList, slist_back(&myListGenap));
                    slist_popBack(&myListGenap);
                }
                slist_pushBack(&myListGenap, num);
            }
        } else {
            // Sort odd numbers descendingly
            if (slist_isEmpty(&myListGanjil) || num <= slist_back(&myListGanjil)) {
                slist_pushBack(&myListGanjil, num);
            } else {
                while (!slist_isEmpty(&myListGanjil) && num > slist_back(&myListGanjil)) {
                    slist_pushBack(&myList, slist_back(&myListGanjil));
                    slist_popBack(&myListGanjil);
                }
                slist_pushBack(&myListGanjil, num);
            }
        }
    }

    // Output numbers based on index
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            // Output even index from myListGenap
            printf("%d ", slist_back(&myListGenap));
            slist_popBack(&myListGenap);
        } else {
            // Output odd index from myListGanjil
            printf("%d ", slist_back(&myListGanjil));
            slist_popBack(&myListGanjil);
        }
    }

    return 0;
}

// Initialize list
void slist_init(SinglyList *list) {
    list->_head = NULL;
    list->_size = 0;
}

// Check if list is empty
bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

// Insert value at the front of the list
void slist_pushFront(SinglyList *list, int value) {
    SListNode *newNode = (SListNode *)malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;

        if (slist_isEmpty(list))
            newNode->next = NULL;
        else
            newNode->next = list->_head;
        list->_head = newNode;
    }
}

// Insert value at the back of the list
void slist_pushBack(SinglyList *list, int value) {
    SListNode *newNode = (SListNode *)malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;
        newNode->next = NULL;

        if (slist_isEmpty(list))
            list->_head = newNode;
        else {
            SListNode *temp = list->_head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }
}

// Remove the last element from the list
void slist_popBack(SinglyList *list) {
    if (!slist_isEmpty(list)) {
        if (list->_size == 1) {
            free(list->_head);
            list->_head = NULL;
        } else {
            SListNode *prev = NULL;
            SListNode *curr = list->_head;
            while (curr->next != NULL) {
                prev = curr;
                curr = curr->next;
            }
            free(curr);
            prev->next = NULL;
        }
        list->_size--;
    }
}

// Get the value of the last element in the list
int slist_back(SinglyList *list) {
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        while (temp->next != NULL)
            temp = temp->next;
        return temp->data;
    }
    return 0;
}
