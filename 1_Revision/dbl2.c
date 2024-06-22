#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
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
    int _min;
    int _max;
    int _sum;
} Stack;

/* Function prototype */

void stack_init(Stack *stack);
bool stack_isEmpty(Stack *stack);
void stack_push(Stack *stack, int value);
void stack_pop(Stack *stack);
int stack_top(Stack *stack);
unsigned stack_size(Stack *stack);
int stack_min(Stack *stack);
int stack_max(Stack *stack);
int stack_sum(Stack *stack);

/* Function definition below */

void stack_init(Stack *stack) {
    stack->_size = 0;
    stack->_top = NULL;
    stack->_min = INT_MAX;
    stack->_max = INT_MIN;
    stack->_sum = 0;
}

bool stack_isEmpty(Stack *stack) {
    return (stack->_top == NULL);
}

void stack_push(Stack *stack, int value) {
    StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
    if (newNode) {
        stack->_size++;
        newNode->data = value;
        
        if (stack_isEmpty(stack)) {
            newNode->next = NULL;
            stack->_min = value;
            stack->_max = value;
            stack->_sum = value;
        }
        else {
            newNode->next = stack->_top;
            stack->_min = (value < stack->_min) ? value : stack->_min;
            stack->_max = (value > stack->_max) ? value : stack->_max;
            stack->_sum += value;
        }

        stack->_top = newNode;
    }
}

void stack_pop(Stack *stack) {
    if (!stack_isEmpty(stack)) {
        StackNode *temp = stack->_top;
        stack->_top = stack->_top->next;
        stack->_size--;
        
        if (stack_isEmpty(stack)) {
            stack->_min = INT_MAX;
            stack->_max = INT_MIN;
            stack->_sum = 0;
        }
        else {
            int removedData = temp->data;
            if (removedData == stack->_min || removedData == stack->_max) {
                StackNode *current = stack->_top;
                stack->_min = INT_MAX;
                stack->_max = INT_MIN;
                stack->_sum = 0;
                while (current != NULL) {
                    int currentData = current->data;
                    stack->_min = (currentData < stack->_min) ? currentData : stack->_min;
                    stack->_max = (currentData > stack->_max) ? currentData : stack->_max;
                    stack->_sum += currentData;
                    current = current->next;
                }
            }
        }
        
        free(temp);
    }
}

int stack_top(Stack *stack) {
    if (!stack_isEmpty(stack)) 
        return stack->_top->data;
    return 0;
}

unsigned stack_size(Stack *stack) {
    return stack->_size;
}

int stack_min(Stack *stack) {
    return stack->_min;
}

int stack_max(Stack *stack) {
    return stack->_max;
}

int stack_sum(Stack *stack) {
    return stack->_sum;
    stack->_sum = 0;
}

int main(int argc, char const *argv[]) {
    // Buat objek Stack
    Stack myStack;

    // PENTING! Jangan lupa diinisialisasi
    stack_init(&myStack);

    /*
    // Operasi pada stack
    stack_push(&myStack, 1);
    stack_push(&myStack, 2);
    stack_push(&myStack, 3);

    // Cetak isi stack
    printf("Stack elements: ");
    while (!stack_isEmpty(&myStack)) {
        printf("%d ", stack_top(&myStack));
        stack_pop(&myStack);
    }
    puts("");

    // Operasi pada stack
    stack_push(&myStack, 5);
    stack_push(&myStack, 8);
    stack_push(&myStack, 2);

    printf("Minimum value in the stack: %d\n", stack_min(&myStack));
    printf("Maximum value in the stack: %d\n", stack_max(&myStack));
    printf("Total sum of values in the stack: %d\n", stack_sum(&myStack));
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
            printf("%d\n", stack_sum(&myStack));
        } else if(strcmp(cmd, "del") == 0){
            stack_pop(&myStack);
        }
    }

    return 0;
}
