#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct {
    int *ends;
    int logicalSize;
    int realSize;
} DinamicArray;
DinamicArray *graph;

void setSize(DinamicArray *array) {
    array->realSize = array->realSize * 2;
    array->ends = realloc(array->ends, array->realSize * sizeof(int));
}

void push(DinamicArray *array, int ends) {
    array->ends[array->logicalSize] = ends;
    array->logicalSize++;
    if (array->logicalSize == array->realSize) {
        setSize(array);
    }
}

void createGraph(int quanityVertex) {
    graph = (DinamicArray *) malloc(quanityVertex * sizeof(DinamicArray));
    for (int i = 0; i < quanityVertex; i++) {
        graph[i].logicalSize = 0;
        graph[i].realSize = 4;
        graph[i].ends = (int *) calloc(graph[i].realSize, sizeof(int));
    }
}

void createArray(DinamicArray *array, int n) {
    array->logicalSize = 0;
    array->realSize = 4;
    array->ends = (int *) calloc(n, sizeof(int));
}

long long int t1, t2;
int count_component;
long long int count_bridge;

int timer;
int *tin;
int *tup;

long long int *count_vertex;
DinamicArray bridge;


void dfs(int v, int p) {

    timer++;
    tin[v] = tup[v] = timer;
    count_vertex[v] = 1;
    if (count_component == 1)
        t1++;
    else if (count_component == 2)
        t2++;

    for (int i = 0; i < graph[v].logicalSize; i++) {
        int u = graph[v].ends[i];
        if (u == p)
            continue;
        if (count_vertex[u] != 0){
            tup[v] = MIN(tup[v], tin[u]);
        }
        else {
            dfs(u, v);
            tup[v] = MIN(tup[v], tup[u]);
            count_vertex[v] += count_vertex[u];
            if (tup[u] > tin[v]) {
                count_bridge++;
                push(&bridge, u);
            }
        }
    }

}

int main () {
    int n, m;
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    scanf("%d%d", &n, &m);

    createGraph(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        push(&graph[x - 1], y - 1);
        push(&graph[y - 1], x - 1);
    }
    /*
    for (int i = 0; i < n; i++) {
        int n = graph[i].logicalSize;
        printf("вершина %d ", i + 1);
        for (int j = 0; j < graph[i].logicalSize; j++) {
            int u = graph[i].ends[j];
            printf("%d ", u + 1) ;
        }
        printf("\n");
    }
*/
    createArray(&bridge, n);
    count_vertex = (long long int *) calloc(n, sizeof(long long int)); tin = (int *) calloc(n, sizeof(int)); tup = (int *) calloc(n, sizeof(int));

    for (int i = 0; i < n ; i++) {
        if (!count_vertex[i]) {
            count_component++;
            dfs(i, -1);
        }
    }

    if (count_component > 2) {
        printf("0\n");
        return 0;
    }

    long long int answer = 0;
    long long int edge_without_bridge = m - count_bridge;


    if (count_component == 2) {
        answer = t1 * t2 * edge_without_bridge;
        printf("%lli\n", answer);
    }
    else {

        if (count_component == 1) {

            for (int i = 0; i < bridge.logicalSize; i++) {
                long long int tt = count_vertex[bridge.ends[i]];
                long long int yy = (count_vertex[bridge.ends[i]] * (n - count_vertex[bridge.ends[i]]) - 1);
                answer += (count_vertex[bridge.ends[i]] * (n - count_vertex[bridge.ends[i]]) - 1);
            }

            long long int add = ((long long int) n ) * ((long long int)n - 1);
            add = add / 2 - m;
            answer += edge_without_bridge * add;
            printf("%lli\n", answer);
        }
    }
}