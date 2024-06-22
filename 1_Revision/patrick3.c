#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 64

typedef struct chore Chore;
struct chore {
    int priority; //data
    char task[MAX_STRING_LENGTH];
    Chore *next;
};

// new chore node
Chore* newChore(int priority, char* task) {
    Chore* chore = (Chore*) malloc(sizeof(Chore));
    chore->priority = priority;
    strcpy(chore->task, task);
    chore->next = NULL;
    return chore;
}

Chore* enqueue(Chore* head, int priority, char* task) {
    Chore* chore = newChore(priority, task);
    if (head == NULL) {
        return chore;
    }
    if (chore->priority < head->priority) {
        chore->next = head;
        return chore;
    }
    Chore* curr = head;
    while (curr->next != NULL && chore->priority >= curr->next->priority) {
        curr = curr->next;
    }
    chore->next = curr->next;
    curr->next = chore;
    return head;
}

/*
Chore* dequeue(Chore* head, int* energy, int* available) {
    while (head != NULL && *energy >= head->priority) {
        printf("%s\n", head->task); //print the chores that can be done
        *energy -= head->priority;
        *available = 1;
        Chore* temp = head;
        head = head->next;
        free(temp);
    }
    if (*available) {
        return head;
    }
    return NULL;
}
*/


int main() {
    
    int n;
    scanf("%d", &n);
    Chore* head = NULL;
    for (int i = 0; i < n; i++) {
        int priority; //priority for doing chores
        char task[MAX_STRING_LENGTH]; //chores' name
        scanf("%d %s", &priority, task); //push the data into the queue
        head = enqueue(head, priority, task);
    }

    while(head != NULL){
        
    }

    

    

    return 0;
}