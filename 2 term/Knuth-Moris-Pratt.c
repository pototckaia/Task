#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_LENGTH 200001
 
int main() {
    char *text = (char *) malloc(MAX_LENGTH * sizeof(char));
    char *pattern = (char *) malloc(MAX_LENGTH * sizeof(char));
    FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
 
 
    fgets(text, MAX_LENGTH, in); fgets(pattern, MAX_LENGTH, in);
 
 
    int length_text = strlen(text);
    int length_pattern = strlen(pattern);
 
    if (text[length_text - 1] == '\n') {
        text[length_text - 1] = '\0';
        length_text--;
    }
    if (pattern[length_pattern - 1] == '\n') {
        pattern[length_pattern - 1] = '\0';
        length_pattern--;
    }
 
    int *pf = (int *) calloc(length_pattern, sizeof(int));
 
 
    for (int i = 1, j = 0; i < length_pattern; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pf[j - 1];
        }
        if (pattern[i] == pattern[j])
            j++;
        pf[i] = j;
    }
 
    int answer = -1;
    for (int i = 0, j = 0; i < length_text; i++) {
        while (j > 0 && pattern[j] != text[i]) {
            j = pf[j - 1];
        }
        if (pattern[j] == text[i])
            j++;
        if (j == length_pattern) {
            answer = i  - length_pattern + 2;
            break;
        }
 
    }
 
    fprintf(out, "%d", answer);
    free(text); free(pattern); free(pf);
    return 0;
}