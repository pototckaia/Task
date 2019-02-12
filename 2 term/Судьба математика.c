#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left;
    char comp[2];
    int right;
} Conditions;

int telephone[6];
int answer = 0;
Conditions *condition;
int conditionSize = 0;

int check(void) {
    int res = 1;
    for (int i = 0; i < conditionSize; i++){
        int c = (int ) condition[i].comp[0] + (int ) condition[i].comp[1];
        switch (c) {
            case 60:
                res = res && telephone[condition[i].left] < telephone[condition[i].right];
                break;
            case 61:
                res = res && telephone[condition[i].left] == telephone[condition[i].right];
                break;
            case 62:
                res = res && telephone[condition[i].left] > telephone[condition[i].right];
                break;
            case 121:
                res = res && telephone[condition[i].left] <= telephone[condition[i].right];
                break;
            case 122:
                res = res && telephone[condition[i].left] != telephone[condition[i].right];
                break;
            case 123:
                res = res && telephone[condition[i].left] >= telephone[condition[i].right];
                break;
        }
        if (!res)
            return res;
    }
    return res;
}

void Search(int k) {
    if (k == 6) {
        if (check())
            answer++;
        return;
    }
    else {
        for (int i = 0; i < 10; i++) {
            telephone[k] = i;
            Search(k + 1);
        }
    }
}



int main() {
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");

    condition = (Conditions *) malloc(30 * sizeof(Conditions));

    char c;
    while ((c = fgetc(in)) != EOF) {
        if (c == '\n')
            continue;
        condition[conditionSize].left = c - 49;
        c = fgetc(in);
        condition[conditionSize].comp[0] = c;
        c = fgetc(in);
        if (c >= 60) {
            condition[conditionSize].comp[1] = c;
            c = fgetc(in);
            condition[conditionSize].right = c - 49;
        } else {
            condition[conditionSize].comp[1] = 0;
            condition[conditionSize].right = c - 49;
        }
        conditionSize++;
    }

    Search(0);
    fprintf(out, "%d\n", answer);
    fclose(in); fclose(out); free(condition);
}