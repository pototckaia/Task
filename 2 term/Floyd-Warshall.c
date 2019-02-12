#include <stdio.h>
#include <stdlib.h>
  
#define INF 1000001
#define MIN(a, b) ((a) > (b) ? (b) : (a))
 
int **direction;
 
int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
     
    direction = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        direction[i] = (int *) calloc(n, sizeof(int ));
        for (int j = 0; j < n; j++) {
            if (i != j) {
                direction[i][j] = INF;
            }

        }
    }
    
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        scanf("%d%d%d", &from, &to, &weight);
        direction[from - 1][to - 1] = weight;
    }
     
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (direction[i][k] < INF && direction[k][j] < INF)
                    direction[i][j] = MIN(direction[i][j], direction[i][k] + direction[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (direction[i][j] == INF) 
                printf("  ");
            else 
                printf("%d ", direction[i][j]);
            
        }
        printf("\n");
    }
}