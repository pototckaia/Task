#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int i, j;
} Pair;
 
int n;
Pair pop(Pair *q, int *h) {
    Pair t = q[*h];
    *h = (*h + 1) % (n + 1000);
    return t;
}
 
void push(Pair *q, int *t, int i, int j) {
    q[*t].i = i;
    q[*t].j = j;
    *t = (*t + 1) % (n + 1000);
}
 
#define FREE  1501
#define WALL 1503
 
 
int main() {
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    fscanf(in, "%d", &n);
 
    int **labyrinth = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        labyrinth[i] = (int *) malloc(n * sizeof(int));
    }
 
    char c = '\0'; int i = 0, j = 0;
    while (c != EOF && i < n) {
        fscanf(in, "%c", &c);
        if (c == '.') {
            labyrinth[i][j] = FREE;
            i = (j == n - 1 ? i + 1 : i);
            j = (j + 1) % n;
        }
        else if (c == '#') {
            labyrinth[i][j] = WALL;
            i = (j == n - 1 ? i + 1 : i);
            j = (j + 1) % n;
        }
    }
 
    Pair * queue = (Pair *) malloc((n + 1000) * sizeof(Pair));
    int head = 0, tail = 0;
 
 
 
    Pair t;
    push(queue, &tail, 0, 0);
    labyrinth[0][0] = 0;
 
    while (tail != head) {
        t = pop(queue, &head);
        if ((t.i + 1) < n && labyrinth[t.i + 1][t.j] == FREE) {
            push(queue, &tail, t.i + 1, t.j);
            labyrinth[t.i + 1][t.j] = labyrinth[t.i][t.j] + 1;
        }
        if ((t.j + 1) < n && labyrinth[t.i][t.j + 1] == FREE) {
            push(queue, &tail, t.i, t.j + 1);
            labyrinth[t.i][t.j + 1] = labyrinth[t.i][t.j] + 1;
        }
        if ((t.i - 1) >= 0 && labyrinth[t.i - 1][t.j] == FREE) {
            push(queue, &tail, t.i - 1, t.j);
            labyrinth[t.i - 1][t.j] = labyrinth[t.i][t.j] + 1;
        }
        if ((t.j - 1) >= 0 && labyrinth[t.i][t.j - 1] == FREE) {
            push(queue, &tail, t.i, t.j - 1);
            labyrinth[t.i][t.j - 1] = labyrinth[t.i][t.j] + 1;
        }
        if (t.i == n - 1 && t.j == n - 1)
            break;
    }
 
    if (labyrinth[n - 1][n - 1] == FREE || labyrinth[n - 1][n - 1] == WALL)
        fprintf(out, "-1");
    else
        fprintf(out, "%d\n", labyrinth[n - 1][n - 1]);
 
 
    for (int k = 0; k < n; k++) {
        free(labyrinth[k]);
    }
    free(labyrinth); fclose(in); fclose(out);
    return 0;
}