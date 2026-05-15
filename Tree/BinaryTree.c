#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;

Node* createNode(int data) {
	Node *n = (Node*)malloc(sizeof(Node));
	if (!n) {
		printf("Memory allocation failed!\n");
		return NULL;
	}
	n->data = data;
	n->left = n->right = NULL;
	return n;
}

// Insert into Binary Search Tree
Node* insertNode(Node *root, int data) {
	if (root == NULL) return createNode(data);
	if (data < root->data) root->left = insertNode(root->left, data);
	else root->right = insertNode(root->right, data);
	return root;
}

// Inorder traversal (L Root R)
void inorder(Node *root) {
	if (!root) return;
	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

// Preorder (Root L R)
void preorder(Node *root) {
	if (!root) return;
	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);
}

// Postorder (L R Root)
void postorder(Node *root) {
	if (!root) return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->data);
}

// Search in BST
Node* search(Node *root, int key) {
	if (!root) return NULL;
	if (root->data == key) return root;
	if (key < root->data) return search(root->left, key);
	return search(root->right, key);
}

// Find minimum node in tree
Node* findMin(Node *root) {
	if (!root) return NULL;
	while (root->left) root = root->left;
	return root;
}

// Delete a node from BST
Node* deleteNode(Node *root, int key) {
	if (!root) return NULL;
	if (key < root->data) root->left = deleteNode(root->left, key);
	else if (key > root->data) root->right = deleteNode(root->right, key);
	else {
		// node found
		if (!root->left) {
			Node *tmp = root->right;
			free(root);
			return tmp;
		} else if (!root->right) {
			Node *tmp = root->left;
			free(root);
			return tmp;
		}
		// two children: replace with inorder successor
		Node *succ = findMin(root->right);
		root->data = succ->data;
		root->right = deleteNode(root->right, succ->data);
	}
	return root;
}

// Height of tree
int height(Node *root) {
	if (!root) return 0;
	int lh = height(root->left);
	int rh = height(root->right);
	return (lh > rh ? lh : rh) + 1;
}

// Free whole tree
void freeTree(Node *root) {
	if (!root) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

int main() {
	Node *root = NULL;

	int values[] = {50, 30, 20, 40, 70, 60, 80};
	int n = sizeof(values)/sizeof(values[0]);
	for (int i = 0; i < n; i++) root = insertNode(root, values[i]);

	printf("Inorder traversal: "); inorder(root); printf("\n");
	printf("Preorder traversal: "); preorder(root); printf("\n");
	printf("Postorder traversal: "); postorder(root); printf("\n");

	int key = 40;
	printf("\nSearching for %d: %s\n", key, search(root, key) ? "Found" : "Not Found");
	key = 100;
	printf("Searching for %d: %s\n", key, search(root, key) ? "Found" : "Not Found");

	printf("\nTree height: %d\n", height(root));

	printf("\nDeleting 20 (leaf)\n"); root = deleteNode(root, 20);
	printf("Inorder: "); inorder(root); printf("\n");

	printf("\nDeleting 30 (node with one child)\n"); root = deleteNode(root, 30);
	printf("Inorder: "); inorder(root); printf("\n");

	printf("\nDeleting 50 (node with two children - root)\n"); root = deleteNode(root, 50);
	printf("Inorder: "); inorder(root); printf("\n");

	freeTree(root);
	return 0;
}
