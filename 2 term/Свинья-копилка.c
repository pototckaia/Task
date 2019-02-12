#include <stdio.h>
#include <stdlib.h>


#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
 
int **dp;
int *c; // достоинство
int *w; //вес

// минимальная сумма содержащаяся в копилки

int main() {
	int n, e, f;
	FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
	fscanf(in, "%d%d%d", &e, &f, &n);

	w = (int *) malloc(n * sizeof(int));
	c = (int *) malloc(n * sizeof(int));
	
	for (int i = 0; i < n; i++){
		fscanf(in, "%d%d", c + i, w + i);		
	}

	int s = f - e;
	dp = (int **) calloc(n + 1, sizeof(int *));
	for (int i = 0; i <= n; i++) {
		dp[i] = (int *) calloc(f - e + 1, sizeof(int)); 
	}

	dp[0][0] = 0;
	for (int i = 1; i <= s; i++) {
		dp[0][i] = 10000000;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= s; j++) {
			dp[i][j] = dp[i - 1][j];
			for (int l = j / w[i - 1]; l > 0; l--) {
				if (l * w[i - 1] <= j)
					dp[i][j] = MIN(dp[i][j], dp[i - 1][j - l * w[i - 1]] + l * c[i - 1]);
			}
		}
	}

	if (dp[n][s] == 10000000)
		fprintf(out, "-1\n");
	else
		fprintf(out, "%d\n", dp[n][s]);	
}