#include <stdio.h>
#include <stdlib.h>

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

void mergeRoutes(Node** head) {
    Node* current = *head;
    while (current != NULL && current->next != NULL) {
        if (current->route.end >= current->next->route.start) {
            if (current->route.end < current->next->route.end) {
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

void printList(Node* node) {
    while (node != NULL) {
        printf("%d %d\n", node->route.start, node->route.end);
        node = node->next;
    }
}

void freeList(Node* node) {
    while (node != NULL) {
        Node* temp = node;
        node = node->next;
        free(temp);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Node* head = NULL;

    for (int i = 0; i < n; i++) {
        Route route;
        scanf("%d %d", &route.start, &route.end);
        insertSorted(&head, route);
    }

    mergeRoutes(&head);
    printList(head);
    freeList(head);

    return 0;
}