#include <stdio.h>
#include <stdlib.h>
 
#define INF 100000001

typedef struct {
    int first;
    int second;
} Pair;
 
typedef struct {
    int to, from , weight, number;    
} Edge;

Pair * disjointedSet;
void createSet(int size) {
    disjointedSet = (Pair *) malloc(size * sizeof(Pair));
    for (int i = 0; i < size; i++) {
        disjointedSet[i].first = i;
        disjointedSet[i].second = 0;
    }
}

int find(int x) {
    return (x == disjointedSet[x].first ? x : (disjointedSet[x].first = find(disjointedSet[x].first)));
}

void merge(int rep_a, int rep_b) {
    //int rep_a = find(a), rep_b = find(b);
    if (disjointedSet[rep_a].second > disjointedSet[rep_b].second) {
        disjointedSet[rep_b].first = rep_a;
    }
    else {
        disjointedSet[rep_a].first = rep_b;
        if (disjointedSet[rep_a].second == disjointedSet[rep_b].second) {
            disjointedSet[rep_b].second++;
        }
    }

}

int compare_edge (const void * a, const void * b) {
    if (((Edge *)a)->weight == ((Edge *)b)->weight)
        return 0;
    if ( ((Edge *)a)->weight > ((Edge *)b)->weight )
        return 1;
    else
        return -1;
}

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    
    Edge *edges = malloc(m * sizeof(Edge));   

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].weight);        
        edges[i].number = i;
    }
    
    qsort(edges, m, sizeof(Edge), compare_edge);
    createSet(n);
    int answer = 0;
    int quantity_vertices = 1;

    for (int i = 0; i < m; i++) {
        int re_from = find(edges[i].from);
        int re_to = find(edges[i].to);
        if (re_from != re_to) {
            answer += edges[i].weight;
            quantity_vertices++;
            merge(re_from, re_to);
            printf("%d\n", edges[i].number);
        }
    }
}