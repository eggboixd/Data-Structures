/**
 * Implementasi ADT PriorityQueue menggunakan Linked List
 * [default: minimum priority]
 * 
 * Dibuat dan ditulis oleh Bayu Laksana
 * -- tanggal 22 Januari 2019
 * Struktur Data 2020
 * Implementasi untuk bahasa C
 * 
 * !!NOTE!!
 * cara menggunakan lihat pada fungsi main()
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 64
/* Struktur Node */

typedef struct pqueueNode_t {
    int data;
    char task[MAX_STRING_LENGTH];
    struct pqueueNode_t *next;
} PQueueNode;

/* Struktur ADT PriorityQueue menggunakan Linked List */

// Prioritas default: nilai minimum
typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

/* Function prototype */

void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int priority, char* task);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_topData(PriorityQueue *pqueue);
char  pqueue_topStr(PriorityQueue *pqueue);
/* Function definition below */

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int priority, char* task)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));
    newNode->data = priority;
    strcpy(newNode->task, task);
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (priority > pqueue->_top->data) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while (temp->next != NULL && temp->next->data > priority)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}


void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

int pqueue_topData(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->data; 
        /*return pqueue->_top->task;*/
    else return 0;
}

char pqueue_topStr(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        printf("%s\n", pqueue->_top->task);
        /*return pqueue->_top->task;*/
    else return 0;
}

int main(int argc, char const *argv[])
{
    // Buat objek PriorityQueue
    PriorityQueue myPque;

    // PENTING! Jangan lupa diinisialisasi
    pqueue_init(&myPque);

    /*
    // Operasi pada priority queue
    pqueue_push(&myPque, 12);
    pqueue_push(&myPque, 3);
    pqueue_push(&myPque, 1);

    // cetak isi pque
    while (!pqueue_isEmpty(&myPque)) {
        printf("%d ", pqueue_top(&myPque));
        pqueue_pop(&myPque);
    }
    puts("");
    */

    int n;
    scanf("%d", &n);

    int priority;
    char task[MAX_STRING_LENGTH];
    for(int i = 0; i < n; i++){
        scanf("%d %s", &priority, task);
        pqueue_push(&myPque, priority, task);
    }

    while (!pqueue_isEmpty(&myPque)) {
        pqueue_topStr(&myPque);
        pqueue_pop(&myPque);
    }
    return 0;
}


//Fadhil Revinno Hairiman
//5025231002