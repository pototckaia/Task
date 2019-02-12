#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int *ans; 
int **p;
int *m;
int size = 0;



int main() {
	int n, w;
	FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
	fscanf(in, "%d%d", &n, &w);

	m = (int *) malloc(n * sizeof(int));
	ans = (int *) calloc(n, sizeof(int));
	
	for (int i = 0;i < n; i++){
		fscanf(in, "%d", &m[i]);
		
	}

	p = (int **) calloc(n + 1, sizeof(int *));
	for (int i = 0; i <= n; i++) {
		p[i] = (int *) calloc(w + 1, sizeof(int)); 
	}


	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= w; j++) {
			if (m[i - 1] <= j)
				p[i][j] = MAX(p[i - 1][j], p[i - 1][j - m[i - 1]] + m[i - 1]);
			else
				p[i][j] = p[i - 1][j];
		}
	}

	int *ans = (int *) calloc(n, sizeof(int));
	int i = n,  j = w;
	if (p[n][w] != w) {
		fprintf(out, "-1\n");
		return 0;
	}
	else {
		while (p[i][j] != 0) {
			if (p[i - 1][j] == p[i][j]){
				i--;
			}
			else {
				ans[i - 1] = 1;
				j = j - m[i - 1];
				i--;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		fprintf(out, "%d ", ans[i]);
	}
	 

	
}