#include <stdio.h>
#include <stdlib.h>
#include <limits.h>   
 
typedef struct {
    int weight;
    int count;
    int next_v;   
 } D;
 
void printfPath2(D **direction, int i, int j){
    int c = direction[i][j].next_v;
    if (c == -1){
        return ;
    }
    printfPath2(direction, i, c);
    printf(" %d ", c);
    printfPath2(direction, c, j);
}

int main() {
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    
    int n, m;
    scanf("%d%d", &n, &m);

    D **direction;
    direction = (D **) malloc(n * sizeof(D*));
    for (int i = 0; i < n; i++) {
        direction[i] = (D *) calloc(n, sizeof(D));
        for (int j = 0; j < n; j++) {
            direction[i][j].next_v = -1;
            direction[i][j].count = 0;
            direction[i][j].weight =  i!= j ? INT_MAX : 0;
        }
    }
    
    for (int i = 0; i < m; i++) {
        int from, to, weight;
        scanf("%d%d%d", &from, &to, &weight);
        direction[from][to].weight = weight;
        direction[from][to].count = 1;

        direction[to][from].weight = weight;
        direction[to][from].count = 1;
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (direction[i][k].weight == INT_MAX || direction[k][j].weight == INT_MAX)
                    continue;
                int new_weight = direction[i][k].weight + direction[k][j].weight;
                int new_count = direction[i][k].count + direction[k][j].count;
                if (direction[i][j].weight > new_weight || (direction[i][j].weight == new_weight && new_count > direction[i][j].count)){
                    direction[i][j].weight = new_weight;
                    direction[i][j].count = new_count;
                    direction[i][j].next_v = k;
                }
            }
        }
    }

    
    for (int i = 0; i < n; i++){
        for (int j=i+1; j < n; j++){
            printf(" %d ", i);
            printfPath2(direction, i, j);
            printf(" %d\n", j);
        }
    }

        
}