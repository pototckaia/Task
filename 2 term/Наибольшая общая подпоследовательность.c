#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
	FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
	char *a = (char *) malloc(1001 * sizeof(char));
	char *b = (char *) malloc(1001 * sizeof(char));
	fscanf(in, "%s%s", a, b);

	int stra = strlen(a), strb = strlen(b);
	int **dp = (int **) calloc((stra + 1), sizeof(int *));
	for (int i = 0; i <= stra; i++) {
		dp[i] = (int *) calloc((strb + 1), sizeof(int));
		dp[i][0] = 0;
	}

	for (int i = 0; i < strb; i++)
		dp[0][i] = 0;

	for (int i = 0; i < stra; i++) {
		for (int j = 0; j < strb; j++) {
			if (a[i] == b[j])
				dp[i + 1][j + 1] = MAX(dp[i][j] + 1, dp[i + 1][j + 1]);
			dp[i + 1][j + 1] = MAX(dp[i + 1][j], dp[i + 1][j + 1]);
            dp[i + 1][j + 1] = MAX(dp[i][j + 1], dp[i + 1][j + 1]);
		}
	}

	char *res = (char *) calloc(1001, sizeof(char));
	int kk = 0;
	int len = dp[stra][strb];
    int i = stra - 1, j = strb - 1;

	while (len != 0 && i >= 0 && j >= 0) {
		if (a[i] == b[j]) {
			res[kk] = a[i];
			kk++; j--; i--; len--;
		}
		else {
			if (dp[i + 1][j + 1] == dp[i][j + 1])
				i--;
			else if (dp[i + 1][j + 1] == dp[i + 1][j])
				j--;
		}
	}

	for (int i = kk - 1; i >= 0; i--) {
		fprintf(out, "%c", res[i]);
	}

}