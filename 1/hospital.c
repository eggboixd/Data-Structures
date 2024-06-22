#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//Fadhil Revinno Hairman
//5025231002


typedef struct dnode_t {
    int data;
    struct dnode_t *next, *prev;
} DListNode;

typedef struct deque_t {
    DListNode *_head, *_tail;
    unsigned _size;
} Deque;

DListNode* __dlist_createNode(int value) {
    DListNode *newNode = (DListNode*) malloc(sizeof(DListNode));
    if (!newNode) return NULL;
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void deq_init(Deque *deque) {
    deque->_head = deque->_tail = NULL;
    deque->_size = 0;
}

bool deq_isEmpty(Deque *deque) {
    return (deque->_head == NULL && deque->_tail == NULL);
}

void deq_pushFront(Deque *deque, int value) {
    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        deque->_size++;
        if (deq_isEmpty(deque)) {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }
        newNode->next = deque->_head;
        deque->_head->prev = newNode;
        deque->_head = newNode;
    }
}

void deq_pushBack(Deque *deque, int value) {
    DListNode *newNode = __dlist_createNode(value);
    if (newNode) {
        deque->_size++;
        if (deq_isEmpty(deque)) {
            deque->_head = newNode;
            deque->_tail = newNode;
            return;
        }
        deque->_tail->next = newNode;
        newNode->prev = deque->_tail;
        deque->_tail = newNode;
    }
}

int deq_front(Deque *deque) {
    if (!deq_isEmpty(deque)) {
        return (deque->_head->data);
    }
    return 0;
}

int deq_back(Deque *deque) {
    if (!deq_isEmpty(deque)) {
        return (deque->_tail->data);
    }
    return 0;
}

void deq_popFront(Deque *deque) {
    if (!deq_isEmpty(deque)) {
        DListNode *temp = deque->_head;
        if (deque->_head == deque->_tail) {
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        } else {
            deque->_head = deque->_head->next;
            deque->_head->prev = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

void deq_popBack(Deque *deque) {
    if (!deq_isEmpty(deque)) {
        DListNode *temp;
        if (deque->_head == deque->_tail) {
            temp = deque->_head;
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        } else {
            temp = deque->_tail;
            deque->_tail = deque->_tail->prev;
            deque->_tail->next = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

int main() {
    Deque mydeq;
    deq_init(&mydeq);

    int n, capacity, resource;
    scanf("%d %d %d", &n, &capacity, &resource);

    int treated = 0;
    int transferred = 0;

    int severity;
    for (int i = 0; i < n; i++) {
        scanf("%d", &severity);
        deq_pushFront(&mydeq, severity);
    }

    while (!deq_isEmpty(&mydeq)) {
        int current_patient = deq_front(&mydeq);
        if (capacity > 0 && resource >= current_patient) {
            treated++;
            capacity--;
            resource -= current_patient;
        } else {
            transferred++;
        }
        deq_popFront(&mydeq);
    }

    printf("Patients treated: %d\n", treated);
    printf("Patients transferred: %d\n", transferred);

    return 0;
}
