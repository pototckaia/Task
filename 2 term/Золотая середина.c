#include <stdio.h>
#include <stdlib.h>

#define left(a) (2 * (a) + 1)
#define right(a) (2 * (a) + 2)
#define parent(a) (((a) - 1) / 2)

int cmpMaxHeap(int a, int b) {
	return (a > b ? 1 : 0);
}

int cmpMinHeap(int a, int b) {
	return (a < b ? 1 : 0);
}

typedef struct {
    int *value;
    int size;
} MinMaxHeap;

typedef struct {
	MinMaxHeap *maxHeap;
	MinMaxHeap *minHeap;	
} Heap;

void siftDown(MinMaxHeap *heap, int i, int (* cmp)(int, int)) {
    int l = left(i);
    int r = right(i);
    while (l < heap->size) {		        
        int j = l;
        if (r < heap->size && cmp(heap->value[r], heap->value[l])/* <*/)
            j = r;
        if (!cmp(heap->value[j], heap->value[i])/*<=*/)
            break;
		int tt = heap->value[j];
        heap->value[j] = heap->value[i];
        heap->value[i] = tt;
        i = j;
        l = left(i);
        r = right(i);
    }
}

void siftUp(MinMaxHeap *heap, int i, int (*cmp)(int, int)) {
    int p = parent(i);
    while (i > 0 && cmp(heap->value[i], heap->value[p]) /*<*/) {
        int tt = heap->value[p];
        heap->value[p] = heap->value[i];
        heap->value[i] = tt;
        i = p;
        p = parent(i);
    }
}

void insertMinMax(MinMaxHeap *heap, int value, int (*cmp)(int, int)) {
	heap->size++;
    heap->value[heap->size - 1] = value;
    siftUp(heap, heap->size - 1, cmp);
}

void deleteFirst(MinMaxHeap *heap, int (*cmp)(int, int)) {
	if (heap->size <= 0)
		return;
	int tmp = heap->value[0];
	heap->value[0] = heap->value[heap->size - 1];
	heap->value[heap->size - 1] = tmp;
	heap->size--;
	siftDown(heap, 0, cmp);
}

int median(Heap *heap) {
	if (heap->minHeap->size <= 0 && heap->maxHeap->size <= 0)
		return 1000000011;
	if (heap->minHeap->size > heap->maxHeap->size)
		return heap->minHeap->value[0];
	if (heap->maxHeap->size > heap->minHeap->size)
		return heap->maxHeap->value[0];
	if (heap->maxHeap->size == heap->minHeap->size)
		return heap->maxHeap->value[0]; 
}

void insert(Heap *heap, int value) {
	if (value > median(heap))
		insertMinMax(heap->minHeap, value, cmpMinHeap);
	else
		insertMinMax(heap->maxHeap, value, cmpMaxHeap);
	
	if (heap->maxHeap->size - heap->minHeap->size > 1) {
		insertMinMax(heap->minHeap, heap->maxHeap->value[0], cmpMinHeap);
		deleteFirst(heap->maxHeap, cmpMaxHeap);
	}
	else if (heap->minHeap->size - heap->maxHeap->size > 1) {
		insertMinMax(heap->maxHeap, heap->minHeap->value[0], cmpMaxHeap);
		deleteFirst(heap->minHeap, cmpMinHeap);
	}

} 

int main() {
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);

    Heap heap;
    heap.maxHeap = (MinMaxHeap *) malloc(sizeof(MinMaxHeap));
    heap.maxHeap->value = (int *) malloc(n * sizeof(int));
    heap.maxHeap->size = 0;
    heap.minHeap = (MinMaxHeap *) malloc(sizeof(MinMaxHeap));
    heap.minHeap->value = (int *) malloc(n * sizeof(int));
    heap.minHeap->size = 0;
    
    int k;
   
    for (int i  = 0;  i < n; i++) {
        fscanf(in, "%d", &k);
    	insert(&heap, k);
 		fprintf(out, "%d ", median(&heap));
    }


    free(heap.maxHeap->value); free(heap.minHeap->value);
    free(heap.maxHeap); free(heap.minHeap);
    fclose(in); fclose(out);
}

