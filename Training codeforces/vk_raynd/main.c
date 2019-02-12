#include <stdio.h>
#include <stdlib.h>

int main(){

	int n, m, p;

	int** pos;

	int t_in, t;

	scanf("%d", &t_in);
	
	for (t = 0; t < t_in; t++){

		scanf("%d%d", &n, &m);

		pos = (int**) malloc(m * sizeof(int*));
		for (int i = 0; i < m; i++)
			pos[i] = (int*) malloc(n * sizeof(int));
		p = 1;

		int i = 0;
		while (p != n * m + 1){

			for (int j = 0; j < n; j++){
				if (i - j >= 0 && i - j < m){
					pos[i - j][j] = p;
					p++;
				}
			}
			i++;
		}

		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++)
				printf("%d ", pos[m-j][n-i]);
			printf("\n");
		}

		free(pos);

	}

}
