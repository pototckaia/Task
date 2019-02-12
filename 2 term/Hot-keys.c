#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
int n, maxQuantityPosit, quantityPosit, minSumPosit, sumPosit;
int *keyPosit; 
int *keyPositBest;
char **captions;
bool charactersUsed[25];
 
 
void HotKeys(int numStr) {
    if (numStr >= n) {
        if (quantityPosit > maxQuantityPosit ||  (sumPosit < minSumPosit && quantityPosit == maxQuantityPosit)) {
            maxQuantityPosit = quantityPosit;
            minSumPosit = sumPosit;
            for (int i = 0; i < n; i++) {
                keyPositBest[i] = keyPosit[i];
            }
        }
        return;
    }
    
    for (int j = 0; captions[numStr][j] != '\0'; j++) {
        if (maxQuantityPosit == n - 1 && sumPosit + j >= minSumPosit)
          break;
        if (charactersUsed[captions[numStr][j] - 'a'] == false) {
            charactersUsed[captions[numStr][j] - 'a'] = true;
            keyPosit[numStr] = j;
            quantityPosit++;
            sumPosit = sumPosit + j;
            
            if (quantityPosit + n - numStr - 1 >= maxQuantityPosit)
                HotKeys(numStr + 1);
 
            charactersUsed[captions[numStr][j] - 'a'] = false;
            keyPosit[numStr] = -1;
            quantityPosit--;
            sumPosit = sumPosit - j;
        }
    }
    if (maxQuantityPosit != n - 1)
        HotKeys(numStr + 1);
}
 
int main() {
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    fscanf(in, "%d", &n);
 
    captions = (char **) malloc(n * sizeof(char *));
 
    keyPositBest = (int *) malloc(n * sizeof(int));
    keyPosit = (int *) malloc(n * sizeof(int));
 
    for (int i = 0; i < n; i++) {
        captions[i] = (char *) malloc(15 * sizeof(char));
        fscanf(in, "%s", captions[i]);
        keyPosit[i] = -1;
        keyPositBest[i] = -1;
    }
 
    for (int i = 0; i < 25; i++) {
        charactersUsed[i] = false;
    }
 
    maxQuantityPosit = -1;
    quantityPosit = -1;
    minSumPosit = 1000000;
    sumPosit = 0;
 
    HotKeys(0);
 
    for (int i = 0; i < n; i++) {
        if (keyPositBest[i] == -1) {
            fprintf(out, "%s\n", captions[i]);
        }
        else {
            for (int j = 0; j < keyPositBest[i]; j++) {
                fprintf(out, "%c", captions[i][j]);
            }
            fprintf(out, "&");
            for (int j = keyPositBest[i]; captions[i][j] != '\0'; j++) {
                fprintf(out, "%c", captions[i][j]);
            }
            fprintf(out, "\n");
        }
    }
 
    free(keyPosit);
    free(keyPositBest);
    for (int i = 0; i < n; i++) {
        free(captions[i]);
    }
    free(captions);
    fclose(in); fclose(out);
}