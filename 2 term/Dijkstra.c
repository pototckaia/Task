#include <stdio.h>
#include <stdlib.h>

#define INF 100000001
#define parent(a) (((a) - 1) / 2)
#define right(a) (2 * (a) + 2)
#define left(a) (2 * (a) + 1)
#define cmpMinHeap(a , b) ((a) < (b) ? 1 : 0)

typedef struct {
	int first;
	int second;
} Pair;

typedef struct {
    Pair *edges;
    int logicalSize;
    int realSize;
} DinamicArray;
DinamicArray *graph;
int n, m, s;
int *distance;
int *used;
  
void setSize(DinamicArray *array) {
    array->realSize = array->realSize * 2;
    array->edges = realloc(array->edges, array->realSize * sizeof(Pair));
}
 
void push(DinamicArray *array, int first, int second) {
    array->edges[array->logicalSize].first = first;
    array->edges[array->logicalSize].second = second;
    array->logicalSize++;
    if (array->logicalSize == array->realSize) {
        setSize(array);
    }
}
 
void createGraph(int quanityVertex) {
    graph = (DinamicArray *) malloc(quanityVertex * sizeof(DinamicArray));
    for (int i = 0; i < quanityVertex; i++) {
        graph[i].logicalSize = 0;
        graph[i].realSize = 4;
        graph[i].edges = (Pair *) calloc(graph[i].realSize, sizeof(Pair));
    }
}

typedef struct {
    int *value;
    int size;
} Heap;
Heap queue;

void createHeap(int n) {
	queue.size = 0;
	queue.value = (int *) malloc(n * sizeof(int));	
}

void siftDown(Heap *heap, int i) {
    int l = left(i);
    int r = right(i);
    while (l < heap->size) {		        
        int j = l;
        if (r < heap->size && cmpMinHeap(distance[heap->value[r]],distance[heap->value[l]]))
            j = r;
        if (!cmpMinHeap(distance[heap->value[j]],distance[heap->value[i]]))
            break;
		int tt = heap->value[j];
        heap->value[j] = heap->value[i];
        heap->value[i] = tt;
        i = j;
        l = left(i);
        r = right(i);
    }
}

void siftUp(Heap *heap, int i) {
    int p = parent(i);
    while (i > 0 && cmpMinHeap(distance[heap->value[i]],distance[heap->value[p]])) {
        int tt = heap->value[p];
        heap->value[p] = heap->value[i];
        heap->value[i] = tt;
        i = p;
        p = parent(i);
    }
}

int isEmpty(Heap *heap) {
	return (heap->size == 0);
}

void insert(Heap *heap, int value) {
	heap->size++;
    heap->value[heap->size - 1] = value;
    siftUp(heap, heap->size - 1);
}

int deleteFirst(Heap *heap) {
	int tmp = heap->value[0];
	heap->value[0] = heap->value[heap->size - 1];
	heap->value[heap->size - 1] = tmp;
	heap->size--;
	siftDown(heap, 0);
	return tmp;
}


void dijkstra(int s) {
	distance[s] = 0;
	insert(&queue, s);
	while (!isEmpty(&queue)) {
		int v = deleteFirst(&queue);
		for (int j = 0; j < graph[v].logicalSize; j++) {
			int end = graph[v].edges[j].first;
			int len = graph[v].edges[j].second;
			if (distance[v] + len < distance[end]) {
				distance[end] = distance[v] + len;
				insert(&queue, end);
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	scanf("%d%d%d", &n, &m, &s);
	s--;
	createGraph(n);
	createHeap(5 * n);
	for (int i = 0; i < m; i++) {
		int start, end, weight;
		scanf("%d%d%d", &start, &end, &weight);
		start--; end--;
		push(graph + start, end, weight);
	}
	distance = (int *) malloc(n * sizeof(int)); used = (int *) calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		distance[i] = INF;
	}
	
	dijkstra(s);

	for (int i = 0; i < n; i++) {
		if (distance[i] == INF)
			distance[i] = -1;
		printf("%d ", distance[i]);
	}
}