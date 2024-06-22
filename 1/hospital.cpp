/**
 * Implementasi ADT Deque (Double-ended Queue)
 * 
 * Dibuat dan ditulis oleh Bayu Laksana
 * -- tanggal 22 Januari 2019
 * Struktur Data 2020
 * Implementasi untuk bahasa C
 * 
 * !!NOTE!!
 * cara menggunakan lihat pada fungsi main()
 */

/*
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
*/

#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;


/* Struktur Node */

typedef struct dnode_t {
    int data;
    struct dnode_t      \
        *next,
        *prev;
} DListNode;

/* Struktur ADT Deque */
/* Implementasi didasarkan pada Doubly-Linked List */

typedef struct deque_t {
    DListNode           \
        *_head, 
        *_tail;
    unsigned _size;
} Deque;

/* DAFTAR FUNGSI YANG TERSEDIA */

DListNode* __dlist_createNode(int value);
void deq_init(Deque *deque);
bool deq_isEmpty(Deque *deque);
void deq_pushFront(Deque *deque, int value);
void deq_pushBack(Deque *deque, int value);
int  deq_front(Deque *deque);
int  deq_back(Deque *deque);
void deq_popFront(Deque *deque);
void deq_popBack(Deque *deque);

/* Definisi Fungsi */

DListNode* __dlist_createNode(int value)
{
    DListNode *newNode = \
        (DListNode*) malloc (sizeof(DListNode));
    
    if (!newNode) return NULL;
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return (DListNode*) newNode;
}

void deq_init(Deque *deque)
{
    deque->_head = deque->_tail = NULL;
    deque->_size = (unsigned) 0;
}

bool deq_isEmpty(Deque *deque) {
    return (deque->_head == NULL && \
            deque->_tail == NULL);
}

void deq_pushFront(Deque *deque, int value)
{
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

void deq_pushBack(Deque *deque, int value)
{
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

void deq_popFront(Deque *deque)
{
    if (!deq_isEmpty(deque)) {
        DListNode *temp = deque->_head;
        if (deque->_head == deque->_tail) {
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        }
        else {
            deque->_head = deque->_head->next;
            deque->_head->prev = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

void deq_popBack(Deque *deque)
{
    if (!deq_isEmpty(deque)) {
        DListNode *temp;
        if (deque->_head == deque->_tail) {
            temp = deque->_head;
            deque->_head = NULL;
            deque->_tail = NULL;
            free(temp);
        }
        else {
            temp = deque->_tail;
            deque->_tail = deque->_tail->prev;
            deque->_tail->next = NULL;
            free(temp);
        }
        deque->_size--;
    }
}

int main(int argc, char const *argv[])
{
    Deque mydeq;
    deq_init(&mydeq);

    /*
    deq_pushBack(&mydeq, 1);
    deq_pushBack(&mydeq, 12);
    deq_pushBack(&mydeq, 6);
    deq_pushBack(&mydeq, 7);
    deq_pushBack(&mydeq, 2);

    deq_pushFront(&mydeq, 11);
    deq_pushFront(&mydeq, 8);
    deq_pushFront(&mydeq, 0);

    deq_popBack(&mydeq);
    deq_popFront(&mydeq);

    while (!deq_isEmpty(&mydeq)) {
        printf("%d ", deq_front(&mydeq));
        deq_popFront(&mydeq);
    }
    puts("");*/

    int n, capacity, resource;
    cin >> n >> capacity >> resource;

    int treated = 0;
    int transfered = 0;

    int severity;
    for(int i = 0; i < n; i++){
        cin >> severity;
        deq_pushFront(&mydeq, severity);
    }

    while (!deq_isEmpty(&mydeq)) {
        int current_patient = deq_front(&mydeq);
        if(capacity > 0 && resource >= current_patient){
            treated++;
            capacity--;
            resource -= current_patient;
        } else {
            transfered++;
        }
        deq_popFront(&mydeq);
    }

    /*
    if (treated == 0 && transfered == 0){
        printf("All %d patients are transferred\n", n);
    } else {
        printf("Patients treated: %d\n", treated);
        printf("Patients transferred: %d\n", transfered);
    }*/


    if(treated != 0 && transfered != 0){
        /*printf("Patients treated: %d\n", treated);*/
        cout << "Patients treated: " << treated << "\n";

        /*printf("Patients transferred: %d\n", transfered);*/
        cout << "Patients transferred: " << transfered << "\n";
        
    } else {
        /*printf("All %d patients are transferred\n", n);*/
        cout << "All " << n << " patients are transferred\n";
    }

    return 0;
}