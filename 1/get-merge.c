#include <stdio.h>
#include <stdlib.h>

//Fadhil Revinno Hairiman
//5025231002

typedef struct Route {
    int start;
    int end;
} Route;

typedef struct Node {
    Route route;
    struct Node* next;
} Node;

void insertSorted(Node** head, Route newRoute) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->route = newRoute;
    newNode->next = NULL;

    if (*head == NULL || (*head)->route.start >= newRoute.start) {
        newNode->next = *head;
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->route.start < newRoute.start) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void merge(Node ** head){
    Node* current = *head;
    while(current != NULL && current->next != NULL){
        if(current->route.end >= current->next->route.start){
            if(current->route.end < current->next->route.end){
                current->route.end = current->next->route.end;
            }

            Node* temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
        current = current->next;
    }
 }
}

int main(){
    int n;
    scanf("%d", &n);

    Node* head = NULL;

    for (int i = 0; i < n; i++) {
        Route route;
        scanf("%d %d", &route.start, &route.end);
        insertSorted(&head, route);
    }

    merge(&head);

    while (head != NULL){
        printf("%d %d\n", head->route.start, head->route.end);
        head = head->next;
    }

    return 0;
}