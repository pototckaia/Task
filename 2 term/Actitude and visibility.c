#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) > (b) ? (b) : (a))

int main(){
	FILE *input = fopen("input.txt", "r"), *output = fopen("output.txt", "w");
	int n;
	fscanf(input, "%d/n", &n);
	
	int *height = (int *) malloc(n * sizeof (int));
	int *right = (int *) malloc(n * sizeof (int));
	int *left = (int *) malloc(n * sizeof(int));
	int *radius = (int *) malloc(n * sizeof(int));

	int i, j;
	for (i = 0; i < n; i++)
		fscanf(input, "%d", &height[i]);

	right[n-1] = n-1;
	left[0] = 0;

	for (i = n-2; i >= 0; i--){
        right[i] = i;
        j = i + 1;
        while (height[i] >= height[j] && j != right[j]){ 
            j = right[j];
        }
        if (height[i] >= height[j])
            right[i] = i;
        else
            right[i] = j;
    }
 
	for (i = 1; i < n; i++){
		left[i] = i;
		j = i - 1;
		while (height[i] >= height[j] && j != left[j]){
			j = left[j];
		}
		if (height[i] >= height[j])
			left[i] = i;
		else 
			left[i] = j;
	}

	int d, a, b;
	for (i = 0; i < n; i++){ 
		//fprintf(output, "%d %d %d %d ",i, height[i],left[i], right[i] );
		if (left[i] == right[i]) 
			d = 0;
		else if (left[i] == i || i == 0)
			d = right[i] - i;
		else if (right[i] == i || i == n-1)
			d = i - left[i];
		else {
			a = right[i] - i;
			b = i - left[i];
			d = min(a, b);
		}
		fprintf(output, "%d ", d);
	}

	free(height); free(right); free(left); free(radius);
	fclose(input); fclose(output);
}

