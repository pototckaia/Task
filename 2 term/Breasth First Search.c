#include <stdio.h>
#include <stdlib.h>

typedef struct Node_{
    int value;
    int isdelete;
    struct Node_ *next; 
} Node;
  
typedef struct {
    Node *head;
    int size;   
} List;
List *graph;

void pushBack(List *list, int value) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = list->head;
    newNode->isdelete = 0;
    list->head = newNode;
    list->size++;
}

int *used;
int *queue;

int main() {
	FILE *in = fopen("input.txt", "r");
	FILE *out = fopen("output.txt", "w");
	int n, m, s;
	fscanf(in, "%d %d %d", &n, &m, &s);

	used = (int *) calloc(n, sizeof(int));
	queue = (int *) calloc(n + 1, sizeof(int));
	
	graph = (List *) malloc(n * sizeof(List));
	for (int i = 0; i < n; i++) {
        graph[i].size = 0;
        graph[i].head = NULL;
    }

	for (int i = 0; i < m; i++) {
		int t1, t2;
		fscanf(in, "%d%d", &t1, &t2);
		pushBack(&graph[t1 - 1], t2 - 1);
        pushBack(&graph[t2 - 1], t1 - 1);
	}

	int head = 0, count = n - 1, tail = 0;


	used[s - 1] = 1;
	queue[tail] = s - 1;
	tail++;
	while (count >= 0 && tail > head) {
		int t = queue[head];
		++head;
		for (Node *node = graph[t].head; node != NULL; node = node->next) {
			if (used[node->value] == 0) {
				count--;
				queue[tail] = node->value;
				tail++;
				used[node->value] = 1;
			}
		}
	}

	if (count != 0) {
		fprintf(out, "-1\n");
	}
	else {
		for (int i = 0; i < n; i++) {
			fprintf(out, "%d ", queue[i] + 1);
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
	free(used); free(graph); fclose(in); fclose(out); free(queue);
}