#include <stdio.h>
#include <stdlib.h>

void myqsort(int *m, int l, int r) {
    int  x = m[(l + r) / 2];
    int i = l;
    int j = r;
    while (i < j) {
        while (m[i] < x)
            i++;
        while (m[j] > x)
            j--;
        if (i <= j) {
            int t = m[j];
            m[j] = m[i];
            m[i] = t;

            i++;
            j--;
        }
    }
    //if (l < j)  myqsort(m, l, j);
    //if (i < r)  myqsort(m, i, r);
}



int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int size;
    fscanf(in, "%d", &size);
    int *m = (int *) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        fscanf(in, "%d", &m[i]);
    }

    myqsort(m, 0, size-1);

    for (int i = 0; i < size; i++) {
        fprintf(out, "%d ", m[i]);
    }

    fclose(in);
    fclose(out);
    free(m);

}