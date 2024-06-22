#include <stdio.h>
#include <stdlib.h>

//Fadhil Revinno Hairiman
//5025231002

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}


int getTotalSum(struct Node* queues[], int n, int k) {
    int totalSum = 0;
    int busesTaken = 0;
    

    while (busesTaken < k) {
        int maxCapacity = -1;
        int maxQueueIndex = -1;
        

        for (int i = 0; i < n; i++) {
            if (queues[i] != NULL && queues[i]->data > maxCapacity) {
                maxCapacity = queues[i]->data;
                maxQueueIndex = i;
            }
        }
        

        if (maxQueueIndex != -1) {
            struct Node* maxNode = queues[maxQueueIndex];
            queues[maxQueueIndex] = maxNode->next;
            totalSum += maxNode->data;
            free(maxNode);
            busesTaken++;
        } else {
            break;
        }
    }
    
    return totalSum;
}

int main() {
    int n;
    scanf("%d", &n);
    
    struct Node* queues[n];
    

    for (int i = 0; i < n; i++) {
        int m; 
        scanf("%d", &m);
        queues[i] = NULL;
        for (int j = 0; j < m; j++) {
            int capacity;
            scanf("%d", &capacity);
            insertAtEnd(&queues[i], capacity);
        }
    }
    
    int k; 
    scanf("%d", &k);
    
   
    int totalSum = getTotalSum(queues, n, k);
    printf("%d\n", totalSum);
   
    for (int i = 0; i < n; i++) {
        struct Node* current = queues[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    
    return 0;
}
