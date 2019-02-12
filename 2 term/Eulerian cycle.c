#include <stdlib.h>
#include <stdio.h>
  

FILE *out, *in; 
 

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
 
Node *find(Node *node, int value) {
    for (Node *inode = node; inode != NULL; inode = inode->next) {
        if (inode->value == value){
            return inode;
        }
    }
    return NULL;
} 

void findCycleEulerian(int v) {
    for (Node *node = graph[v].head; node != NULL; node = node->next) {
        if (node->isdelete == 1)
            continue;
        node->isdelete = 1;
        Node *tmp = find(graph[node->value].head, v);
        tmp->isdelete = 1;
        findCycleEulerian(node->value);
    }
    fprintf(out, "%d ", v + 1);
}
  
  
int main() {
    in = fopen("input.txt", "r"), out = fopen("output.txt", "w");
    int n, m;
    fscanf(in, "%d%d", &n, &m);
    graph = (List *) malloc(n * sizeof(List));
    for (int i = 0; i < n; i++) {
        graph[i].size = 0;
        graph[i].head = NULL;
    }
 
    for (int i = 0; i < m; i++) {
        int tn, tm;
        fscanf(in, "%d%d", &tn, &tm);
        pushBack(&graph[tn - 1], tm - 1);
        pushBack(&graph[tm - 1], tn - 1);
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d\t", i + 1);
        for (Node *node = graph[i].head; node != NULL; node = node->next)
            printf("%d ", node->value + 1);
        printf("\n");
    }

    int is_good = 1;
    for (int i = 0; i < n; i++) {
        int s = graph[i].size;
        if (s & 1) {
            is_good = 0;
            break;
        }
    }

    if (is_good) {
        findCycleEulerian(0);
    }
    else
        fprintf(out, "-1\n");

    fclose(in); fclose(out);
}