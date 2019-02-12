#include <stdio.h>
#include <stdlib.h>

#define max(a, b)  ((a) > (b) ? (a) : (b))

int hapen = 0;
int t, n, m, k;
int **massiv;

int main(){
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		
		scanf("%d %d %d", &n, &m, &k);
		massiv = (int **) malloc(n * sizeof(int *));

		int con = 0;
		int max_w = 0;
		for (int j = 0; j < n; j++) {
			massiv[j] = (int *) malloc(m * sizeof(int));
			con = 0;
			for (int k = 0; k < m; k++) {
				scanf("%d", &massiv[j][k]);
				
				if (massiv[j][k] == 0) {
					max_w = max(max_w, con);
					con = 0;
				} 
				else {
					con++;
				}
				
				max_w = max(max_w, con);
			}	
		}
		con = 0;
		int max_h = 0;
		for (int j = 0; j < m; j++) {
			con = 0;
			for (int k = 0; k < n; k++) {

				if (massiv[k][j] == 0) {
					max_h = max(max_h, con);
					con = 0;
				}
				else {
					con++;
				}
				
				max_h = max(max_h, con);
			}
		}

		int l = max(max_h, max_w);
		if (l > k) {
			printf("NO\n");
		} 
		else {
			printf("YES\n");
			for (int j = 0;j < n; j++){ 
				for (int k = 0; k < m; k++) {
					if (massiv[j][k] != 0) 
						massiv[j][k] = (j + k) % l + 1;
					printf("%d ", massiv[j][k]);
				}
				printf("\n");
			}
		}


	}
}
