#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

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
}

int main(int argc, char const *argv[]) {
    // Buat objek Stack
    Stack myStack;

    // PENTING! Jangan lupa diinisialisasi
    stack_init(&myStack);

    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        int size;
        scanf("%d", &size);
        char wordNums[size];
        scanf("%s", wordNums);
        
        // Push each character onto the stack
        for(int j = 0; j < size; j++) {
            stack_push(&myStack, wordNums[j]);
        }
    }

    return 0;
}
