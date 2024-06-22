/**
 * Implementasi ADT Stack (Stack menggunakan Linked List)
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

/* Struktur Node */

typedef struct stackNode_t {
    int data;
    struct stackNode_t *next;
} StackNode;

/* Struktur ADT Stack */

typedef struct stack_t {
    StackNode *_top;
    unsigned _size;
} Stack;

/* Function prototype */

void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value);
void stack_pop(Stack *stack);
int stack_top(Stack *stack);
unsigned stack_size(Stack *stack);

/* Function definition below */

void stack_init(Stack *stack) 
{
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, int value) 
{
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) 
{
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

int stack_top(Stack *stack) 
{
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

int main(int argc, char const *argv[])
{
    // Buat objek Stack
    Stack myStack;

    // PENTING! Jangan lupa diinisialisasi
    stack_init(&myStack);
    /*
    // Operasi pada stack
    stack_push(&myStack, 1);
    stack_push(&myStack, 2);
    stack_push(&myStack, 3);

    // cetak isi stack
    while (!stack_isEmpty(&myStack)) {
        printf("%d ", stack_top(&myStack));
        stack_pop(&myStack);
    }
    puts("");

    */

    int n;
    scanf("%d", &n);

    char cmd[20];
    int val;
    for(int i = 0; i < n; i++){
        scanf("%s", cmd);
        if(strcmp(cmd, "add") == 0){
            scanf("%d", &val);
            stack_push(&myStack, val);
        } else if(strcmp(cmd, "dbl") == 0){
            int newtop = stack_top(&myStack) * 2;
            stack_push(&myStack, newtop);
        } else if(strcmp(cmd, "six") == 0){
            int newTop = stack_top(&myStack) + 6;
            stack_push(&myStack, newTop); 
        } else if(strcmp(cmd, "total") == 0){
            
        }
    }
    return 0;
}


//Fadhil Revinno Hairiman
//5025231002