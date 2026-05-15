#include <stdio.h>
#include <stdlib.h>

// DFS for an undirected graph using adjacency lists

typedef struct AdjNode {
	int dest;
	struct AdjNode *next;
} AdjNode;

typedef struct Graph {
	int V;
	AdjNode **array;
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
	graph->V = V;
	graph->array = (AdjNode**)malloc(V * sizeof(AdjNode*));
	for (int i = 0; i < V; i++) graph->array[i] = NULL;
	return graph;
}

void addEdge(Graph *graph, int src, int dest) {
	AdjNode *node = newAdjNode(dest);
	node->next = graph->array[src];
	graph->array[src] = node;

	node = newAdjNode(src);
	node->next = graph->array[dest];
	graph->array[dest] = node;
}

// Recursive DFS utility
void dfsRecursiveUtil(Graph *graph, int v, int *visited) {
	visited[v] = 1;
	printf("%d ", v);
	AdjNode *p = graph->array[v];
	while (p) {
		if (!visited[p->dest]) dfsRecursiveUtil(graph, p->dest, visited);
		p = p->next;
	}
}

void dfsRecursive(Graph *graph, int start) {
	int V = graph->V;
	int *visited = (int*)calloc(V, sizeof(int));
	printf("DFS (recursive) starting from %d: ", start);
	dfsRecursiveUtil(graph, start, visited);
	printf("\n");
	free(visited);
}

// Iterative DFS using explicit stack
void dfsIterative(Graph *graph, int start) {
	int V = graph->V;
	int *visited = (int*)calloc(V, sizeof(int));
	int *stack = (int*)malloc(V * sizeof(int));
	int top = -1;

	// push start
	stack[++top] = start;

	printf("DFS (iterative) starting from %d: ", start);
	while (top >= 0) {
		int v = stack[top--];
		if (!visited[v]) {
			visited[v] = 1;
			printf("%d ", v);
			// push neighbors
			AdjNode *p = graph->array[v];
			while (p) {
				if (!visited[p->dest]) stack[++top] = p->dest;
				p = p->next;
			}
		}
	}
	printf("\n");
	free(visited);
	free(stack);
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
	int V = 6;
	Graph *graph = createGraph(V);

	addEdge(graph, 0, 1);
	addEdge(graph, 0, 2);
	addEdge(graph, 1, 3);
	addEdge(graph, 1, 4);
	addEdge(graph, 2, 4);
	addEdge(graph, 3, 5);
	addEdge(graph, 4, 5);

	dfsRecursive(graph, 0);
	dfsIterative(graph, 0);

	dfsRecursive(graph, 2);
	dfsIterative(graph, 2);

	freeGraph(graph);
	return 0;
}
