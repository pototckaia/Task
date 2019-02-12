#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ( (a) > (b) ? (a) : (b) ) 

typedef struct {
	int size;
	int *maximum; 	
} stack;

typedef struct {
 	stack right, left;
 	int count_push;
 } queue;

void push(queue *a , int value);
int maxim(queue *a);
void pop(queue *a, int *n);

int main(){
	FILE *input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w");
	
	int n;
	fscanf(input, "%d", &n);
	int *digit = (int *) malloc(n * sizeof(int)); 

	queue q; 
	q.right.maximum = (int *) malloc(n * sizeof(int));
	q.left.maximum = (int *) malloc(n * sizeof(int));
	q.right.size = -1; 
	q.left.size = -1;
	q.count_push = -1;

	for (int i = 0; i < n; i++){
		fscanf(input, "%d", &digit[i]);
	}
	
	int m;
	fscanf(input, "%d\n", &m);
	char  *point = (char *) malloc(m * sizeof(char));
	for (int i = 0; i < m; i++){
		fscanf(input, "%c" , &point[i]);
	}


	push(&q, digit[0]);
	int j = 1;
	for (int i = 0; i < m; i++){
		if (point[i] == 'R'){
			push(&q, digit[j]);
			j++;
		} else if (point[i] == 'L')
			pop(&q, digit);	
		fprintf(output, "%d ", maxim(&q));
	}

	free(digit); free(point); 
	free(q.right.maximum); free(q.left.maximum); 
	fclose(input); fclose(output);
}



void push(queue *a , int value){
	int m = (a->right.size == -1 ? value : max(value, a->right.maximum[a->right.size]));
	a->right.size++;
	a->count_push++;
	a->right.maximum[a->right.size] = m;
}

void pop(queue *a, int * n){
	int p = a->count_push;
	if ( a->left.size == -1){
		while (a->right.size != -1){
			int e = n[p--];
			a->right.size--;
			int m = (a->left.size == -1 ? e : max(e, a->left.maximum[a->left.size]));
			a->left.size++;
			a->left.maximum[a->left.size] = m; 
		}
	}
	a->left.size--;
}

int maxim(queue *a){
	if ( a->right.size == -1 || a->left.size == -1)
		return (a->right.size == -1 ? a->left.maximum[a->left.size] : a->right.maximum[a->right.size]); 
	else 
		return max( a->right.maximum[a->right.size], a->left.maximum[a->left.size]);
}
