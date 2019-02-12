#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *data;
	int head, tail;	
} Queue;

typedef struct {
	Queue q;
	int time;
} Server

int empty(Queue *q){
	return (q->head == q->tail)
}

int push(Queue *q, int x, int n){
	if (size(&q) != n){
		s->data[tail] = x;
		tail = (tail + 1) % n;
		return 0;
	} else 
		return -1;
}

int pop(Queue *q){
	if (empty(&q))
}

int main(){
	int n, b;
	scanf("%d%d", &n, &b);
	Server s;

	s.size = 0;
	s.time = 0;
	s.q = (int *) malloc(n * sizeof(int));

	int t, d;
	for (int i; i < n; i++)
		scanf("%d%d", &t, &d);

}