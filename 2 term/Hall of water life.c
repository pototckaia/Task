#include <stdlib.h>
#include <stdio.h>

#define INF 1000000000
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))


int main(){
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int n, m;
    int *distance;
    int **maxDistance;
    scanf("%d%d", &n, &m);

    distance = (int *) calloc(n, sizeof(int));

    maxDistance = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        maxDistance[i] = (int *) calloc((m + 1), sizeof(int));
        for (int j = 0; j <= m; j++) {
            maxDistance[i][j] = INF;
        }
    }

    int prev = 0;
    scanf("%d", &prev);
    for (int i = 1; i < n; i++) {
        int t;
        scanf("%d", &t);
        distance[i] = t - prev;
        prev = t;
    }

    maxDistance[0][0] = 0;
    for (int i = 1; i < n; i++) {
        maxDistance[i][0] = MAX(maxDistance[i - 1][0], distance[i]);
    }


    for (int i = 1; i < n; i++) {
        for (int j = 1; i > j && j <= m; j++) {
            maxDistance[i][j] = maxDistance[i - 1][j];

            int currentDistance = distance[i];

            for (int k = 1; k <= MIN(i, j); k++) {

                currentDistance += distance[i - k];

                maxDistance[i][j] = MIN(maxDistance[i][j], MAX(maxDistance[i - k - 1][j - k], currentDistance));
                maxDistance[i][j] = MAX(maxDistance[i][j], maxDistance[i][0]);
            }

        }
    }
 }
    printf("%d", maxDistance[n - 1][m]);
    free(distance);
}