#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b) ((a) > (b) ? (b) : (a))
  
int **distance;
  
int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
      
    distance = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        distance[i] = (int *) calloc(n, sizeof(int ));
        for (int j = 0; j < n; j++) {
            if (i != j) {
                distance[i][j] = INT_MAX;
            }
 
        }
    }
     
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        scanf("%d%d%d", &from, &to, &weight);
        distance[from - 1][to - 1] = weight;
    }
      
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distance[i][k] < INT_MAX && distance[k][j] < INT_MAX)
                    distance[i][j] = MIN(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { // 
            if (distance[i][j] < INT_MAX && distance[j][i] < INT_MAX) {
                distance[i][j] = 0; 
                distance[j][i] = 0;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distance[i][k] < INT_MAX && distance[k][j] < INT_MAX)
                    distance[i][j] = MIN(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }

    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int s, f;
        scanf("%d%d", &s, &f);
        s--; f--;
        if (distance[s][f] == INT_MAX) 
                printf("-1\n");
            else
                printf("%d\n", distance[s][f]);

    }

}
