#include <stdlib.h>
#include <stdio.h>

typedef struct Node_{
	int value;
	struct Node_ *next;	
} Node;

typedef struct {
	Node *head;
	int size;	
} List;
List *graph;

int *used;
int *answer;
int sizeAnswer = 0;

void pushBack(List *list, int value) {
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = list->head;
	list->head = newNode;
	list->size++;
}

int dfs(int v) {
	used[v] = 1;
	for (Node *node = graph[v].head; node != NULL; node = node->next) {
		if (used[node->value] == 0) {
			if (!dfs(node->value))
				return 0;
		}
		else if (used[node->value] == 1)
			return 0;
	}
	used[v] = 2;
	answer[sizeAnswer] = v + 1;
	sizeAnswer++;
	return 1;
}

int main() {
	FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
	int n, m;
	fscanf(in, "%d%d", &n, &m);

	int hasCycle = 0;
	used = (int *) calloc(n, sizeof(int));
	graph = (List *) malloc(n * sizeof(List));
	answer = (int *) malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		graph[i].size = 0;
		graph[i].head = NULL;
	}

	for (int i = 0; i < m; i++) {
		int tn, tm;
		fscanf(in, "%d%d", &tn, &tm);
		pushBack(&graph[tn - 1], tm - 1);
	}

	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			if (!dfs(i)) {
				hasCycle = 1;
				break;
			}
		}
	}

	if (hasCycle) {
		fprintf(out, "-1");
	}
	else {
		for (int i = sizeAnswer - 1; i >= 0; i--) {
			fprintf(out, "%d ", answer[i]);
		}
	}

	for (int i = 0; i < n; i++) {
		Node *tmp = graph[i].head;
		while (tmp != NULL) {
			Node *next = tmp->next;
			free(tmp);
			tmp = next;
		}

	}
	free(graph); free(used); free(answer); fclose(in); fclose(out);
}