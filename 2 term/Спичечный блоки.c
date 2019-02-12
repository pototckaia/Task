#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct {
    int A, B;
} Block;

typedef struct {
    Block *blocks;
    int count;
} Combinations;

Combinations com;
int numberMatches;
FILE *in, *out;

int computeMatch(int a, int b) {
    return (a * (b + 1) + b * (a + 1));
}

int count = 0;

void search(int a, int b, int n) {
    if (n < 4) {
        if (n == 0) {
            fprintf(out, "%d ", com.count);
            for (int i = 0; i < com.count; i++)
                fprintf(out, "%d %d ", com.blocks[i].A, com.blocks[i].B);
            fprintf(out, "\n");
        }
        count++;
        return;
    }
    else {
        int j;
        for (int i = a;  computeMatch(i, i) - n <= 0; i++) {
            if (i == a)
                j = MAX(i, b);
            else
                j = i;
            while (computeMatch(i, j) - n <= 0 ) {

                n -= computeMatch(i, j);
                com.blocks[com.count].A = i;
                com.blocks[com.count].B = j;
                com.count++;

                search(i, j, n);

                n += computeMatch(i, j);
                com.count--;
                j++;
            }
        }
    }
}

int main() {
    in = fopen("input.txt", "r");
    out = fopen("output.txt", "w");

    fscanf(in, "%d", &numberMatches);

    com.blocks = (Block *) calloc(numberMatches, sizeof(Block));
    com.count = 0;
    search(1, 1, numberMatches);

    fprintf(out, " ");
    fprintf(out, "\n%d\n", count);

    fclose(in); fclose(out); free(com.blocks);
}