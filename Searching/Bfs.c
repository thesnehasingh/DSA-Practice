#include <stdio.h>
#include <stdlib.h>

// Simple BFS for an undirected graph using adjacency lists

typedef struct AdjNode {
	int dest;
	struct AdjNode *next;
} AdjNode;

typedef struct Graph {
	int V;
	AdjNode **array; // array of adjacency list heads
} Graph;

AdjNode* newAdjNode(int dest) {
	AdjNode *node = (AdjNode*)malloc(sizeof(AdjNode));
	if (!node) return NULL;
	node->dest = dest;
	node->next = NULL;
	return node;
}

Graph* createGraph(int V) {
	Graph *graph = (Graph*)malloc(sizeof(Graph));
	if (!graph) return NULL;
	graph->V = V;
	graph->array = (AdjNode**)malloc(V * sizeof(AdjNode*));
	for (int i = 0; i < V; i++) graph->array[i] = NULL;
	return graph;
}

void addEdge(Graph *graph, int src, int dest) {
	// add dest to src list
	AdjNode *node = newAdjNode(dest);
	node->next = graph->array[src];
	graph->array[src] = node;

	// since undirected, add src to dest list
	node = newAdjNode(src);
	node->next = graph->array[dest];
	graph->array[dest] = node;
}

// Simple queue for BFS
typedef struct Queue {
	int *data;
	int front, rear, capacity;
} Queue;

Queue* createQueue(int capacity) {
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->capacity = capacity;
	q->front = 0;
	q->rear = -1;
	q->data = (int*)malloc(capacity * sizeof(int));
	return q;
}

void enqueue(Queue *q, int val) {
	if (q->rear + 1 >= q->capacity) return;
	q->data[++q->rear] = val;
}

int dequeue(Queue *q) {
	if (q->front > q->rear) return -1;
	return q->data[q->front++];
}

int isEmptyQ(Queue *q) {
	return q->front > q->rear;
}

void freeQueue(Queue *q) {
	free(q->data);
	free(q);
}

// BFS starting from source
void BFS(Graph *graph, int start) {
	int V = graph->V;
	int *visited = (int*)calloc(V, sizeof(int));
	Queue *q = createQueue(V);

	visited[start] = 1;
	enqueue(q, start);

	printf("BFS traversal starting from %d: ", start);
	while (!isEmptyQ(q)) {
		int u = dequeue(q);
		printf("%d ", u);
		AdjNode *pCrawl = graph->array[u];
		while (pCrawl) {
			int v = pCrawl->dest;
			if (!visited[v]) {
				visited[v] = 1;
				enqueue(q, v);
			}
			pCrawl = pCrawl->next;
		}
	}
	printf("\n");

	free(visited);
	freeQueue(q);
}

void freeGraph(Graph *graph) {
	for (int i = 0; i < graph->V; i++) {
		AdjNode *p = graph->array[i];
		while (p) {
			AdjNode *t = p;
			p = p->next;
			free(t);
		}
	}
	free(graph->array);
	free(graph);
}

int main() {
	// Example graph
	int V = 6;
	Graph *graph = createGraph(V);
	addEdge(graph, 0, 1);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 3);
	addEdge(graph, 1, 4);
	addEdge(graph, 2, 4);
	addEdge(graph, 3, 5);
	addEdge(graph, 4, 5);

	BFS(graph, 0);
	BFS(graph, 2);

	freeGraph(graph);
	return 0;
}
