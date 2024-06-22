/**
 * Implementasi ADT SInglyList (Singly Linked List)
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

/* Struktur Node */

typedef struct snode_t {
    int data;
    struct snode_t *next;
} SListNode;

/* Struktur ADT SinglyList */

typedef struct slist_t {
    unsigned _size;
    SListNode *_head;
} SinglyList;

/* DAFTAR FUNGSI YANG TERSEDIA */

void slist_init(SinglyList *list);
bool slist_isEmpty(SinglyList *list);
void slist_pushFront(SinglyList *list, int value);
void slist_popFront(SinglyList *list);
void slist_pushBack(SinglyList *list, int value);
void slist_popBack(SinglyList *list);
void slist_insertAt(SinglyList *list, int index, int value);
void slist_removeAt(SinglyList *list, int index);
void slist_remove(SinglyList *list, int value);
int  slist_front(SinglyList *list);
int  slist_back(SinglyList *list);
int  slist_getAt(SinglyList *list, int index);

/* Function definition below */

void slist_init(SinglyList *list) 
{
    list->_head = NULL;
    list->_size = 0;
}

bool slist_isEmpty(SinglyList *list) {
    return (list->_head == NULL);
}

void slist_pushFront(SinglyList *list, int value) 
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        list->_size++;
        newNode->data = value;

        if (slist_isEmpty(list)) newNode->next = NULL;
        else newNode->next = list->_head;
        list->_head = newNode;
    }
}

void slist_popFront(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        list->_head = list->_head->next;
        free(temp);
        list->_size--;
    }
}

void slist_pushBack(SinglyList *list, int value)
{
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
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

void slist_popBack(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *nextNode = list->_head->next;
        SListNode *currNode = list->_head;

        if (currNode->next == NULL) {
            free(currNode);
            list->_head = NULL;
            return;
        }

        while (nextNode->next != NULL) {
            currNode = nextNode;
            nextNode = nextNode->next;
        }
        currNode->next = NULL;
        free(nextNode);
        list->_size--;
    }
}

void slist_insertAt(SinglyList *list, int index, int value)
{
    /* Kasus apabila posisinya melebihi batas */
    if (slist_isEmpty(list) || index >= list->_size) {
        slist_pushBack(list, value);
        return;    
    }
    else if (index == 0 || index < 0) {
        slist_pushFront(list, value);
        return;
    }
    
    SListNode *newNode = (SListNode*) malloc(sizeof(SListNode));
    if (newNode) {
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index-1) {
            temp = temp->next;
            _i++;
        }
        newNode->data = value;
        newNode->next = temp->next;
        temp->next = newNode;
        list->_size++;
    }
}

void slist_removeAt(SinglyList *list, int index)
{
    if (!slist_isEmpty(list)) {
        
        /* Kasus apabila posisinya melebihi batas */
        if (index >= list->_size) {
            slist_popBack(list);
            return;    
        }
        else if (index == 0 || index < 0) {
            slist_popFront(list);
            return;
        }
        
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index-1) {
            temp = temp->next;
            _i++;
        }
        SListNode *nextTo = temp->next->next;
        free(temp->next);
        temp->next = nextTo;
        list->_size--;
    }
}

void slist_remove(SinglyList *list, int value)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp, *prev;
        temp = list->_head;

        if (temp->data == value) {
            slist_popFront(list);
            return;
        }
        while (temp != NULL && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) return;
        prev->next = temp->next;
        free(temp);
        list->_size--;
    }
}

int slist_front(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        return list->_head->data;
    }
    return 0;
}

int slist_back(SinglyList *list)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        while (temp->next != NULL) 
            temp = temp->next;
        return temp->data;
    }
    return 0;
}

int slist_getAt(SinglyList *list, int index)
{
    if (!slist_isEmpty(list)) {
        SListNode *temp = list->_head;
        int _i = 0;
        while (temp->next != NULL && _i < index) {
            temp = temp->next;
            _i++;
        }
        return temp->data;
    }
    return 0;
}

void slist_sortAscending(SinglyList *list)
{
    if (list->_size > 1) {
        bool swapped;
        do {
            swapped = false;
            SListNode *current = list->_head;
            while (current->next != NULL) {
                if (current->data > current->next->data) {
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
}

void slist_sortDescending(SinglyList *list)
{
    if (list->_size > 1) {
        bool swapped;
        do {
            swapped = false;
            SListNode *current = list->_head;
            while (current->next != NULL) {
                if (current->data < current->next->data) {
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
}

int main(int argc, char const *argv[])
{
    // Buat objek SinglyList
    SinglyList myList, myListAscending, myListDescending;

    // PENTING! Jangan lupa diinisialisasi
    slist_init(&myList);
    slist_init(&myListAscending);
    slist_init(&myListDescending);

    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        int val;
        scanf("%d", &val);
        slist_pushBack(&myListAscending, val);
        slist_pushBack(&myListDescending, val);
    }

    slist_sortAscending(&myListAscending);
    slist_sortDescending(&myListDescending);

    for(int i = 0; i < n; i++){
        if(i % 2 != 0){
            printf("%d ", slist_front(&myListDescending));
            slist_popFront(&myListDescending);
        } else {
            printf("%d ", slist_front(&myListAscending));
            slist_popFront(&myListAscending);
        }
    }


/*
    slist_sortAscending(&myList);
    while (!slist_isEmpty(&myList)) {
        slist_pushFront(&myListAscending, slist_front(&myList));
        slist_popFront(&myList);
    }

    slist_sortDescending(&myListAscending);
    while (!slist_isEmpty(&myListAscending)) {
        slist_pushFront(&myListDescending, slist_front(&myListAscending));
        slist_popFront(&myListAscending);
    }

    for(int i = 0; i < n; i++){
        if(i % 2 != 0){
            printf("%d ", slist_front(&myListAscending));
            slist_popFront(&myListAscending);
        } else {
            printf("%d ", slist_front(&myListDescending));
            slist_popFront(&myListDescending);
        }
    }

    printf("\n");
*/
    return 0;
}