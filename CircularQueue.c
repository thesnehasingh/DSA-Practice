
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Circular queue using fixed-size array
typedef struct CircularQueue {
	int arr[MAX_SIZE];
	int front; // index of front element
	int rear;  // index of rear element
	int count; // number of elements
} CircularQueue;

CircularQueue* initQueue() {
	CircularQueue *q = (CircularQueue*)malloc(sizeof(CircularQueue));
	if (!q) return NULL;
	q->front = 0;
	q->rear = -1;
	q->count = 0;
	return q;
}

int isEmpty(CircularQueue *q) {
	return q->count == 0;
}

int isFull(CircularQueue *q) {
	return q->count == MAX_SIZE;
}

void enqueue(CircularQueue *q, int value) {
	if (isFull(q)) {
		printf("Queue Overflow! Cannot enqueue %d\n", value);
		return;
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->arr[q->rear] = value;
	q->count++;
	printf("Enqueued %d\n", value);
}

int dequeue(CircularQueue *q) {
	if (isEmpty(q)) {
		printf("Queue Underflow! Cannot dequeue from empty queue\n");
		return -1;
	}
	int val = q->arr[q->front];
	q->front = (q->front + 1) % MAX_SIZE;
	q->count--;
	printf("Dequeued %d\n", val);
	if (q->count == 0) { // reset indices
		q->front = 0;
		q->rear = -1;
	}
	return val;
}

int peek(CircularQueue *q) {
	if (isEmpty(q)) {
		printf("Queue is empty! Nothing to peek\n");
		return -1;
	}
	return q->arr[q->front];
}

void displayQueue(CircularQueue *q) {
	if (isEmpty(q)) {
		printf("Queue is empty!\n");
		return;
	}
	printf("Queue (front -> rear): ");
	int idx = q->front;
	for (int i = 0; i < q->count; i++) {
		printf("%d", q->arr[idx]);
		if (i < q->count - 1) printf(" -> ");
		idx = (idx + 1) % MAX_SIZE;
	}
	printf("\n");
}

void freeQueue(CircularQueue *q) {
	free(q);
}

int main() {
	CircularQueue *q = initQueue();
	if (!q) {
		printf("Failed to allocate queue\n");
		return 1;
	}

	printf("=== Circular Queue Demo (size = %d) ===\n\n", MAX_SIZE);

	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);
	enqueue(q, 4);
	enqueue(q, 5);
	displayQueue(q);

	// Try overflow
	enqueue(q, 6);

	dequeue(q);
	dequeue(q);
	displayQueue(q);

	enqueue(q, 6);
	enqueue(q, 7);
	displayQueue(q);

	printf("Peek: %d\n\n", peek(q));

	while (!isEmpty(q)) dequeue(q);
	displayQueue(q);

	freeQueue(q);
	return 0;
}

