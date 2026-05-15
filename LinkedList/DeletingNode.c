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

// Function to insert a node at the end (for building the list)
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

// Function to delete a node from the beginning
Node* deleteFromBeginning(Node *head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    
    Node *temp = head;
    head = head->next;
    printf("Deleted node with data: %d\n", temp->data);
    free(temp);
    return head;
}

// Function to delete a node from the end
Node* deleteFromEnd(Node *head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    
    // If only one node
    if (head->next == NULL) {
        printf("Deleted node with data: %d\n", head->data);
        free(head);
        return NULL;
    }
    
    Node *temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    
    printf("Deleted node with data: %d\n", temp->next->data);
    free(temp->next);
    temp->next = NULL;
    return head;
}

// Function to delete a node from any position (1-indexed)
Node* deleteFromPosition(Node *head, int position) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    
    // Delete from beginning
    if (position == 1) {
        Node *temp = head;
        head = head->next;
        printf("Deleted node with data: %d\n", temp->data);
        free(temp);
        return head;
    }
    
    Node *temp = head;
    int count = 1;
    
    // Traverse to the position before the node to be deleted
    while (temp != NULL && count < position - 1) {
        temp = temp->next;
        count++;
    }
    
    // If position is out of range
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of range!\n");
        return head;
    }
    
    Node *nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;
    printf("Deleted node with data: %d\n", nodeToDelete->data);
    free(nodeToDelete);
    return head;
}

// Function to delete a node by value
Node* deleteByValue(Node *head, int value) {
    if (head == NULL) {
        printf("List is empty!\n");
        return NULL;
    }
    
    // If the node to be deleted is the head
    if (head->data == value) {
        Node *temp = head;
        head = head->next;
        printf("Deleted node with data: %d\n", temp->data);
        free(temp);
        return head;
    }
    
    Node *temp = head;
    while (temp->next != NULL) {
        if (temp->next->data == value) {
            Node *nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            printf("Deleted node with data: %d\n", nodeToDelete->data);
            free(nodeToDelete);
            return head;
        }
        temp = temp->next;
    }
    
    printf("Node with value %d not found!\n", value);
    return head;
}

// Function to display the linked list
void displayList(Node *head) {
    if (head == NULL) {
        printf("Linked List: EMPTY\n");
        return;
    }
    
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

    // Build the initial list
    printf("Building initial linked list:\n\n");
    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);
    head = insertAtEnd(head, 50);
    displayList(head);

    printf("\n--- Deleting from Beginning ---\n");
    head = deleteFromBeginning(head);
    displayList(head);

    printf("\n--- Deleting from End ---\n");
    head = deleteFromEnd(head);
    displayList(head);

    printf("\n--- Deleting from Position 2 ---\n");
    head = deleteFromPosition(head, 2);
    displayList(head);

    printf("\n--- Deleting node with value 10 ---\n");
    head = deleteByValue(head, 10);
    displayList(head);

    printf("\n--- Deleting node with value 40 ---\n");
    head = deleteByValue(head, 40);
    displayList(head);

    printf("\n--- Deleting from Position 1 ---\n");
    head = deleteFromPosition(head, 1);
    displayList(head);

    // Free the allocated memory
    freeList(head);

    return 0;
}
