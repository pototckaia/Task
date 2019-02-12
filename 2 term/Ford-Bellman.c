#include <stdio.h>

#include <stdlib.h>
 

#define INF 1000001

#define MIN(a, b) ((a) > (b) ? (b) : (a))


typedef struct {
    
int to, from , weight;    
} 
Edge;


int main() {
    
freopen("input.txt", "r", stdin); 
freopen("output.txt", "w", stdout);
    
int n, m, s;
    
scanf("%d%d%d", &n, &m, &s);
    
s--;
    
    
Edge *edges = malloc(m * sizeof(Edge));
    
    
for (int i = 0; i < m; i++) {
        
scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].weight);
        
edges[i].from--; 
        edges[i].to--;
    }
    
    
int *distance = (int *) malloc(n * sizeof(int));
    
for (int i = 0; i < n; i++) {
        distance[i] = INF;
    }
    
distance[s] = 0;

    for (int i = 0; i < n - 1; i++) {
        
for (int j = 0; j < m; j++) {
            
if (distance[edges[j].from] != INF) {
                distance[edges[j].to] = MIN(distance[edges[j].from] + edges[j].weight, distance[edges[j].to]);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (distance[i] !=  INF)
            printf("%d ", distance[i]);
        else 
            printf(" " );
    }
}