#include <stdlib.h>

#include <stdio.h>

#include <math.h>


#define INF 1000000007


int delta_x, delta_y, delta_z;

int **combination;


int multiplication(int a, int b, int m) {
    if (!a || !b)
        return 0;
    if (a & 1)
        return (b + multiplication(a - 1, b, m) % m) % m;
    else 
        return ((multiplication(a / 2, b, m) % m) * 2) % m;
}


int main() {
    
int  xb, yb, zb, xm, ym, zm;
    
    
FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
    
fscanf(in, "%d%d%d%d%d%d",&xb, &yb, &zb, &xm, &ym, &zm);
    
delta_x = abs(xm - xb);
    delta_y = abs(ym - yb);
    
delta_z = abs(zm - zb);

    
int n = delta_x + delta_y + delta_z + 1;

    
int **combination = (int **) calloc(n, sizeof(int *));
    
for (int i = 0; i < n; i++) {
        combination[i] = (int *) calloc(n, sizeof(int));
    }

    
combination[0][0] = 1;
    
for (int i = 1; i < n; i++) {
        combination[i][0] = 1;
        combination[i][i] = 1;
        
for (int j = 1; j < i; j++) {
            combination[i][j] = (combination[i - 1][j - 1] + combination[i - 1][j]) % INF;
        }
    }
    

    
int result = multiplication(combination[delta_x + delta_y][delta_x], combination[delta_x + delta_y + delta_z][delta_x + delta_y], INF);
    
fprintf(out, "%d\n", result);

    for (int i = 0; i < n; i++)
        free(combination[i]);
    free(combination); fclose(in); fclose(out);
}