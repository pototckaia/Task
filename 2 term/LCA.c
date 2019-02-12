#include <stdlib.h>
#include <stdio.h>

#define INF 100001

typedef struct {
    int *value;
    int logicalSize;
    int realSize;
} DinamicArray;
DinamicArray *graph;

int *used;
DinamicArray order;
int *positionOrder;
int *height;

void setSize(DinamicArray *array) {
    array->realSize = array->realSize * 2;
    array->value = realloc(array->value, array->realSize * sizeof(int));
}

void push(DinamicArray *array, int value) {
    array->value[array->logicalSize] = value;
    array->logicalSize = array->logicalSize + 1;
    if (array->logicalSize == array->realSize) {
        setSize(array);
    }
}

void createGraph(int quanityVertex) {
    graph = (DinamicArray *) malloc(quanityVertex * sizeof(DinamicArray));
    for (int i = 0; i < quanityVertex; i++) {
        graph[i].logicalSize = 0;
        graph[i].realSize = 4;
        graph[i].value = (int *) calloc(graph[i].realSize, sizeof(int));
    }
}

void createArray(DinamicArray *array) {
    array->logicalSize = 0;
    array->realSize = 4;
    array->value = (int *) calloc(array->realSize, sizeof(int));
}

typedef struct {
    int *value;
    int size;
    int offset;
} Tree;
Tree tree;

int nearestPower(int n) {
    int degree2 = 1;
    while(degree2 < n)
        degree2 = degree2 << 1;
    return degree2;
}

void buildTree(Tree *tree, int size, int inf) {
    tree->offset = nearestPower(size);
    tree->size = 2 * tree->offset;
    tree->value = (int *) malloc(tree->size * sizeof(int));
    for (int i = 0; i < tree->size; i++) {
        tree->value[i] = inf;
    }

    for (int i = 0; i < size; i++) {
        tree->value[tree->offset - 1 + i] = order.value[i];
    }
    for (int i = tree->offset - 2; i >= 0; i--) {
        if (height[tree->value[2 * i + 1]] < height[tree->value[2 * i + 2]])
            tree->value[i] = tree->value[2 * i + 1];
        else
            tree->value[i] = tree->value[2 * i + 2];
    }

}

int queryTree(Tree *tree, int l, int r, int v) {
    if (l > r)
        return 0;
    l += tree->offset - 1;
    r += tree->offset - 1;
    int ans = v;
    while (l < r) {
        if (!(l & 1))
            ans = (height[ans] < height[tree->value[l]] ? ans : tree->value[l]);
        if (r & 1)
            ans = (height[tree->value[r]] < height[ans] ? tree->value[r] : ans);
        l = l / 2;
        r = (r - 2) / 2;
    }
    if (l == r)
        ans = (height[ans] < height[tree->value[l]] ? ans : tree->value[l]);
    return  ans;
}

void dfs(int v, int h) {
    used[v] = 1;
    height[v] = h;
    push(&order, v);
    for (int i = 0; i < graph[v].logicalSize; i++) {
        if (!used[graph[v].value[i]]) {
            dfs(graph[v].value[i], h + 1);
            push(&order, v);
        }
    }

}



int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    createGraph(n);

    for (int i = 0; i < n - 1; i++) {
        int t1, t2;
        scanf("%d%d", &t1, &t2);
        push(graph + t1 - 1, t2 - 1);
        push(graph + t2 - 1, t1 - 1);
    }

    used = (int *) calloc(n, sizeof(int)); positionOrder = (int *) malloc(n * sizeof(int)); height = (int *) malloc(n * sizeof(int ));
    createArray(&order);

    dfs(0, 0);
    int maxh = 0, maxV = 0;
    for (int i = 0; i < n; i++) {
        if (height[i] > maxh) {
            maxh = height[i];
            maxV = i;
        }
    }

    buildTree(&tree, order.logicalSize, maxV);
    for (int i = 0; i < n; i++)
        positionOrder[i] = -1;

    for (int i = 0; i < order.logicalSize; i++) {
        if (positionOrder[order.value[i]] == -1) {
            positionOrder[order.value[i]] = i;
        }
    }


    int a = -1, b = -1;
    while (!feof(stdin)) {
        a = -1; b = -1;
        scanf("%d%d", &a, &b);
        if (a == -1 || b == -1)
            break;
        int l = positionOrder[a - 1], r = positionOrder[b - 1];
        if (l > r) {
            int t = l;
            l = r;
            r = t;
        }
        printf("%d\n", queryTree(&tree, l, r, a - 1) + 1);
    }

    free(used); free(positionOrder); free(height); free(order.value);
    for (int i = 0; i < n; i++) {
        free(graph[i].value);
    }
    free(graph); free(tree.value);
}