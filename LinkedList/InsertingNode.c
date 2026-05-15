#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning
Node* insertAtBeginning(Node *head, int data) {
    Node *newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    newNode->next = head;
    head = newNode;
    return head;
}

// Function to insert a node at the end
Node* insertAtEnd(Node *head, int data) {
    Node *newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    
    if (head == NULL) {
        return newNode;
    }
    
    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Function to insert a node at any position (1-indexed)
Node* insertAtPosition(Node *head, int data, int position) {
    Node *newNode = createNode(data);
    if (newNode == NULL) {
        return head;
    }
    
    // Insert at beginning if position is 1
    if (position == 1) {
        newNode->next = head;
        return newNode;
    }
    
    Node *temp = head;
    int count = 1;
    
    // Traverse to the position before the insertion point
    while (temp != NULL && count < position - 1) {
        temp = temp->next;
        count++;
    }
    
    // If position is out of range
    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return head;
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

// Function to display the linked list
void displayList(Node *head) {
    Node *temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to free the linked list
void freeList(Node *head) {
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;

    printf("Inserting nodes at the beginning of the linked list:\n\n");

    // Insert nodes at the beginning
    head = insertAtBeginning(head, 10);
    displayList(head);

    head = insertAtBeginning(head, 20);
    displayList(head);

    head = insertAtBeginning(head, 30);
    displayList(head);

    printf("\nInserting nodes at the end of the linked list:\n\n");

    // Insert nodes at the end
    head = insertAtEnd(head, 100);
    displayList(head);

    head = insertAtEnd(head, 200);
    displayList(head);

    printf("\nInserting nodes at specific positions:\n\n");

    // Insert at position 2
    head = insertAtPosition(head, 25, 2);
    printf("After inserting 25 at position 2: ");
    displayList(head);

    // Insert at position 4
    head = insertAtPosition(head, 50, 4);
    printf("After inserting 50 at position 4: ");
    displayList(head);

    // Insert at position 1 (beginning)
    head = insertAtPosition(head, 5, 1);
    printf("After inserting 5 at position 1: ");
    displayList(head);

    // Insert at position 7
    head = insertAtPosition(head, 150, 7);
    printf("After inserting 150 at position 7: ");
    displayList(head);

    // Free the allocated memory
    freeList(head);

    return 0;
}
