#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Define the stack structure
typedef struct Stack {
    Node *top;
} Stack;

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

// Function to initialize the stack
Stack* initStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

// Function to check if stack is empty
int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

// Function to push element onto the stack
void push(Stack *stack, int value) {
    Node *newNode = createNode(value);
    if (newNode == NULL) {
        return;
    }
    
    newNode->next = stack->top;
    stack->top = newNode;
    printf("Pushed %d onto the stack\n", value);
}

// Function to pop element from the stack
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow! Cannot pop from empty stack\n");
        return -1;
    }
    
    Node *temp = stack->top;
    int value = temp->data;
    stack->top = stack->top->next;
    printf("Popped %d from the stack\n", value);
    free(temp);
    return value;
}

// Function to peek the top element
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty! Nothing to peek\n");
        return -1;
    }
    return stack->top->data;
}

// Function to display all elements in the stack
void displayStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    
    printf("Stack (top to bottom): ");
    Node *temp = stack->top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to get the size of the stack
int getSize(Stack *stack) {
    int count = 0;
    Node *temp = stack->top;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Function to free the stack
void freeStack(Stack *stack) {
    Node *temp;
    while (stack->top != NULL) {
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    free(stack);
}

int main() {
    Stack *stack = initStack();

    if (stack == NULL) {
        return 1;
    }

    printf("=== Stack Implementation using Linked List ===\n\n");

    printf("--- Pushing elements onto the stack ---\n");
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    push(stack, 40);
    push(stack, 50);
    printf("\n");

    printf("--- Displaying the stack ---\n");
    displayStack(stack);
    printf("Stack size: %d\n\n", getSize(stack));

    printf("--- Peeking the top element ---\n");
    printf("Top element: %d\n\n", peek(stack));

    printf("--- Popping elements from the stack ---\n");
    pop(stack);
    pop(stack);
    printf("\n");

    printf("--- Displaying the stack after popping ---\n");
    displayStack(stack);
    printf("Stack size: %d\n\n", getSize(stack));

    printf("--- Pushing more elements ---\n");
    push(stack, 60);
    push(stack, 70);
    push(stack, 80);
    printf("\n");

    printf("--- Final stack display ---\n");
    displayStack(stack);
    printf("Stack size: %d\n\n", getSize(stack));

    printf("--- Popping all remaining elements ---\n");
    while (!isEmpty(stack)) {
        pop(stack);
    }
    printf("\n");

    printf("--- Stack after popping all elements ---\n");
    displayStack(stack);

    // Free the allocated memory
    freeStack(stack);

    return 0;
}
