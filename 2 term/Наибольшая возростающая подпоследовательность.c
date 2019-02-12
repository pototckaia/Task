#include <stdio.h>
#include <stdlib.h>
 
#define MAX(a, b) ((a) > (b) ? (a) : (b))
 
typedef struct Node_{
    int key;
    int pos;
    struct Node_ *prev;
    struct Node_ *prevLIS;
} Node;
 
typedef struct {
    Node *peak;
} List;
 
int main() {
    int n;
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    fscanf(in, "%d", &n);
    int *sequence = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &sequence[i]);
    }
 
    List *table = (List *) malloc(n * sizeof(List));
    for (int i = 0; i < n; i++)
        table[i].peak = NULL;
    int lengthTable = 0;
 
 
    for (int i = 0; i < n; i++) {
 
        int l = -1, r = lengthTable - 1;
        while (r - l > 1) {
            int mid = (r + l) / 2;
            if (table[mid].peak->key < sequence[i])
                l = mid;
            else
                r = mid;
        }
 
 
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode->key = sequence[i];
        newNode->pos = i + 1;
        newNode->prev = table[r].peak;
 
        r = MAX(r, 0);
        if (r < 0 || table[r].peak == NULL) {
            table[r].peak = newNode;
            lengthTable++;
        }
        else if (table[r].peak->key >= sequence[i]){
            table[r].peak = newNode;
        }
        else if (table[r].peak->key < sequence[i]) {
            r = lengthTable;
            table[lengthTable].peak = newNode;
            lengthTable++;
        }
 
        newNode->prevLIS = NULL;
        if (r > 0)
            newNode->prevLIS = table[r - 1].peak;
 
    }
 
    fprintf(out, "%d\n", lengthTable);
    Node *t = table[lengthTable - 1].peak;
    int *answer = (int *) malloc(lengthTable * sizeof(int));
    int j = 0;
    while (t) {
        answer[j] = t->pos;
        j++;
        t = t->prevLIS;
    }
    for (int i = lengthTable - 1; i >= 0; i--)
        fprintf(out, "%d ", answer[i]);
}
