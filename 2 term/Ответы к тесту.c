#include <stdlib.h>
#include <stdio.h>

void increment(int *f, int c) {
    static int size = 0;
    int pos = -1;
    for (int i = 0; i < size; i++) {
    	if (f[i] == 0) {
    		pos = i;
    		break;
    	} 
    	else {
    		f[i] = 0;
    	}
    }
    if (pos != -1) {
    	f[pos] = 1;
    } 
    else {
    	f[size] = 1;
    	size++;
    }
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int p, q;
    fscanf(in, "%d%d\n", &p, &q);

    int *variant = (int *) calloc(q, sizeof(int));
    int **tests = (int **) malloc(p * sizeof(int *));
    int *mark = (int *) malloc(p * sizeof(int));


    char c;
    for (int i = 0; i < p; i++) {
        tests[i] = (int *) malloc(q * sizeof(int));
        for (int j = 0; j < q; j++) {
            fscanf(in, "%c", &c);
            tests[i][j] = (c == '+' ? 1 : 0);
        }
        fscanf(in, "%d\n", &mark[i]);
    }

    int count = 1;
    for (int i = 0; i < q; i++)
        count = count << 1;

    int tmpcount, isresult;
    for (int k = 0; k < count; k++){
        isresult = 1;
        tmpcount = 0;
        
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < q; j++) {
                if (tests[i][j] == variant[j])
                    tmpcount++;
            }
            if (tmpcount != mark[i]) {
                isresult = 0;
                break;
            }
            tmpcount = 0;
        }
        if (isresult) {
            for (int i = 0; i < q; i++)
                fprintf(out, "%c", (variant[i] ? '+' : '-'));
            break;
        }
        increment(variant, q);
    }
}