#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void push(Node** head, int value) {
    if (*head == NULL) {
        *head = createNode(value);
        printf("push value: %d.\n", value);
    }

    Node* tmp = *head;

    // Search for the node with the given value
    while (tmp != NULL && tmp->data != value) {
        tmp = tmp->next;
    }

    if (tmp != NULL) {
        // If node is found, move it to the top
        if (tmp == *head) {
            printf("Node with value %d is already at the top.\n", value);
            return;
        }

        // Detach the node from current pos
        // e.g. 1<=>2<=>3, now push 2
        if (tmp->prev != NULL) { // 1<-2<=>3
            tmp->prev->next = tmp->next; // 1e: 1->3
        }
        if (tmp->next != NULL) { // 1<=>2->3
            tmp->next->prev = tmp->prev; // 2e: 1<-3
        }

        // Move the node to the top
        tmp->prev = NULL; // 3e: head as top
        tmp->next = *head; // 4e: 2->top
        (*head)->prev = tmp; // 5e: 2<-top, i.e. 2<=>top
        *head = tmp; // 6e
        // Total: 6 ptr op
        printf("Node with value %d moved to the top.\n", value);
    } else {
        // If node is not found, create a new node and push
        Node* newNode = createNode(value);
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;

        printf("Node with value %d pushed.\n", value);
    }
}

void disp(Node* head) {
    Node* tmp = head;
    printf("Doubly Linked List: ");
    while (tmp != NULL) {
        if(tmp->next == NULL)
            printf("%d ", tmp->data);
        else
            printf("%d -> ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;

    push(&head, 10);
    disp(head);

    push(&head, 20);
    disp(head);

    push(&head, 30);
    disp(head);

    push(&head, 10);
    disp(head);

    push(&head, 40);
    push(&head, 50);
    push(&head, 60);
    push(&head, 20);
    disp(head);

    return 0;
}
