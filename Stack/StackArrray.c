
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Define the stack structure
typedef struct Stack {
    int arr[MAX_SIZE];
    int top;
} Stack;

// Function to initialize the stack
Stack* initStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    stack->top = -1;
    return stack;
}

// Function to check if stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to check if stack is full
int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Function to push element onto the stack
void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow! Cannot push %d\n", value);
        return;
    }
    stack->arr[++stack->top] = value;
    printf("Pushed %d onto the stack\n", value);
}

// Function to pop element from the stack
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow! Cannot pop from empty stack\n");
        return -1;
    }
    int value = stack->arr[stack->top--];
    printf("Popped %d from the stack\n", value);
    return value;
}

// Function to peek the top element
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty! Nothing to peek\n");
        return -1;
    }
    return stack->arr[stack->top];
}

// Function to display all elements in the stack
void displayStack(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    
    printf("Stack (top to bottom): ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

// Function to get the size of the stack
int getSize(Stack *stack) {
    return stack->top + 1;
}

// Function to free the stack
void freeStack(Stack *stack) {
    free(stack);
}

int main() {
    Stack *stack = initStack();

    if (stack == NULL) {
        return 1;
    }

    printf("=== Stack Implementation using Array ===\n\n");

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
