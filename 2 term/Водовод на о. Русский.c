#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define FREE  1501
#define WALL 1503
#define BUSY 1504

typedef struct {
    int i, j;
} Pair;

typedef struct {
    Pair *value;
    int logicalSize;
    int realSize;
} DinamicArray;

void setSize(DinamicArray *array) {
    array->realSize = array->realSize * 2;
    array->value = realloc(array->value, array->realSize * sizeof(Pair));
}

void pushArray(DinamicArray *array, int first, int second) {
    array->value[array->logicalSize].i = first;
    array->value[array->logicalSize].j = second;
    array->logicalSize++;
    if (array->logicalSize == array->realSize) {
        setSize(array);
    }
}

void popArray(DinamicArray *array ) {
    if (array->logicalSize == 0) {
        return;
    }
    array->logicalSize--;
}

DinamicArray *createArray() {
    DinamicArray *array =  (DinamicArray *) malloc(sizeof(DinamicArray));
    array->value = malloc(sizeof(Pair));
    array->logicalSize = 0;
    array->realSize = 1;
    return array;
}

int h, w;
int **map;
DinamicArray *way;
DinamicArray *answer[2];
int sizeAnswer;
int isWayFound;
int second;

int cmp() {
    for (int i = 0; i < way->logicalSize; i++) {
        if (way->value[i].i != answer[0]->value[i].i || way->value[i].j != answer[0]->value[i].j) {
            return 1;
        }
    }
    return 0;
}

void dfs(int i, int j) {
    if (sizeAnswer >= 2 || i < 0 || i >= h || j < 0 || j >= w || map[i][j] != FREE)
        return;

    map[i][j] = BUSY;
    pushArray(way, i, j);

    if (j == w - 1) {
        int l = way->logicalSize;
        int k = answer[0]->logicalSize;

        int h = memcmp(way->value, answer[0]->value, way->logicalSize * sizeof(Pair));

        if (sizeAnswer == 0 || way->logicalSize != answer[0]->logicalSize ||
                memcmp(way->value, answer[0]->value, way->logicalSize * sizeof(Pair)) != 0 ) {
            isWayFound = 1;
            for (int k = 0; k < way->logicalSize; k++) {
                pushArray(answer[sizeAnswer], way->value[k].i, way->value[k].j);
            }
            sizeAnswer++;
        }
    }

    if (!second) {
        dfs(i + 1, j);
        dfs(i, j + 1);
        dfs(i - 1, j);
        dfs(i, j - 1);
    }
    else {
        dfs(i, j - 1);
        dfs(i - 1, j);
        dfs(i, j + 1);
        dfs(i + 1, j);
    }
    popArray(way);
}

void clearMap() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (map[i][j] == BUSY)
                map[i][j] = FREE;
        }
    }
}

int main() {
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    fscanf(in, "%d%d", &h, &w);

    map = (int **) malloc(h * sizeof(int *));
    for (int i = 0; i < h; i++) {
        map[i] = (int *) malloc(w * sizeof(int));
    }

    char c = '\0';
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fscanf(in, "%c", &c);
            if (c == '\n') {
                fscanf(in, "%c", &c);
            }
            if (c == '.') {
                map[i][j] = WALL;
            }
            else if (c == '#') {
                map[i][j] = FREE;
            }
        }
    }


    answer[0] = createArray(); answer[1] = createArray();
    way = createArray();

    for (int i = 0; i < h; i++) {
        if (map[i][0] == FREE) {
            second = 0;
            dfs(i, 0);

            second = 1;
            clearMap();
            way->logicalSize = 0;
            dfs(i, 0);
        }
        clearMap();
        way->logicalSize = 0;
    }

    if (isWayFound) {
        if (sizeAnswer == 1) {
            fprintf(out, "YES\n");
        }
        else if (sizeAnswer == 2){
            fprintf(out, "MULTIPLE\n");
        }
        for (int i = 0; i < 2 && answer[i]->logicalSize != 0; i++){
            fprintf(out, "%d  ", answer[i]->logicalSize);
            for (int j = 0; j < answer[i]->logicalSize; j++) {
                fprintf(out, "%d %d  ", answer[i]->value[j].i + 1, answer[i]->value[j].j + 1);
            }
            fprintf(out, "\n");
        }
    }
    else {
        fprintf(out, "NO");
    }

    fclose(in); fclose(out);
    return 0;
}