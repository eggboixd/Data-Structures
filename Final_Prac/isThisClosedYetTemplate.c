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

/* Struktur Node */
typedef struct stackNode_t {
    char data;
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
void stack_push(Stack *stack, char value);
void stack_pop(Stack *stack);
char stack_top(Stack *stack);
unsigned stack_size(Stack *stack);

/* Function definition below */

void stack_init(Stack *stack) {
    stack->_size = 0;
    stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, char value) {
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        
        if (stack_isEmpty(stack)) newNode->next = NULL;
        else newNode->next = stack->_top;

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        free(temp);
        stack->_size--;
    }
}

char stack_top(Stack *stack) {
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return '\0'; // Returning '\0' if stack is empty; could also be an error code.
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

int main(int argc, char const *argv[]) {
    // Buat objek Stack
    Stack myStack;

    // PENTING! Jangan lupa diinisialisasi
    stack_init(&myStack);

    char brackets[1000000];
    scanf("%s", brackets);
    
    for(int i = 0; brackets[i] != '\0'; i++) {
        if(brackets[i] == '(' || brackets[i] == '[' || brackets[i] == '{') {
            stack_push(&myStack, brackets[i]);
        }
        else if(brackets[i] == ')' || brackets[i] == ']' || brackets[i] == '}') {
            if(stack_isEmpty(&myStack) ||
               (brackets[i] == ')' && stack_top(&myStack) != '(') ||
               (brackets[i] == ']' && stack_top(&myStack) != '[') ||
               (brackets[i] == '}' && stack_top(&myStack) != '{')) {
                printf("Belum ditutup\n");
                return 0;
            }
            stack_pop(&myStack);
        }
    }

    if(stack_isEmpty(&myStack)) {
        printf("Sudah ditutup\n");
    }
    else {
        printf("Belum ditutup\n");
    }
/*
    // Operasi pada stack
    stack_push(&myStack, 'A');
    stack_push(&myStack, 'B');
    stack_push(&myStack, 'C');

    // cetak isi stack
    while (!stack_isEmpty(&myStack)) {
        printf("%c ", stack_top(&myStack));
        stack_pop(&myStack);
    }
    puts("");
*/
    return 0;
}
