#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Queue implemented using circular array
typedef struct Queue {
	int arr[MAX_SIZE];
	int front;    // index of front element
	int rear;     // index of last element
	int size;     // current number of elements
} Queue;

// Initialize queue (returns pointer allocated on heap)
Queue* initQueue() {
	Queue *q = (Queue*)malloc(sizeof(Queue));
	if (!q) {
		printf("Memory allocation failed!\n");
		return NULL;
	}
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	return q;
}

int isEmpty(Queue *q) {
	return q->size == 0;
}

int isFull(Queue *q) {
	return q->size == MAX_SIZE;
}

void enqueue(Queue *q, int value) {
	if (isFull(q)) {
		printf("Queue Overflow! Cannot enqueue %d\n", value);
		return;
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->arr[q->rear] = value;
	q->size++;
	printf("Enqueued %d\n", value);
}

int dequeue(Queue *q) {
	if (isEmpty(q)) {
		printf("Queue Underflow! Cannot dequeue from empty queue\n");
		return -1;
	}
	int val = q->arr[q->front];
	q->front = (q->front + 1) % MAX_SIZE;
	q->size--;
	printf("Dequeued %d\n", val);
	if (q->size == 0) { // reset indices for clarity
		q->front = 0;
		q->rear = -1;
	}
	return val;
}

int peek(Queue *q) {
	if (isEmpty(q)) {
		printf("Queue is empty! Nothing to peek\n");
		return -1;
	}
	return q->arr[q->front];
}

void displayQueue(Queue *q) {
	if (isEmpty(q)) {
		printf("Queue is empty!\n");
		return;
	}
	printf("Queue (front -> rear): ");
	int idx = q->front;
	for (int i = 0; i < q->size; i++) {
		printf("%d", q->arr[idx]);
		if (i < q->size - 1) printf(" -> ");
		idx = (idx + 1) % MAX_SIZE;
	}
	printf("\n");
}

void freeQueue(Queue *q) {
	free(q);
}

int main() {
	Queue *q = initQueue();
	if (!q) return 1;

	printf("=== Queue Implementation using Array (circular buffer) ===\n\n");

	enqueue(q, 10);
	enqueue(q, 20);
	enqueue(q, 30);
	enqueue(q, 40);
	enqueue(q, 50);
	displayQueue(q);

	printf("Peek: %d\n\n", peek(q));

	dequeue(q);
	dequeue(q);
	displayQueue(q);

	enqueue(q, 60);
	enqueue(q, 70);
	displayQueue(q);

	while (!isEmpty(q)) dequeue(q);
	displayQueue(q);

	freeQueue(q);
	return 0;
}
