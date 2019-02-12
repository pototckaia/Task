#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *input = fopen("input.txt", "r"), *output = fopen("output.txt", "w");
	int n;
	fscanf(input, "%d/n", &n);
	int *digit = (int*) malloc(n * sizeof(int));
	int *index = (int*) malloc(n * sizeof(int));

	for (int i= 0; i < n; i++)
		fscanf(input, "%d", &digit[i]); 

	int i, j;
	index[n-1] = n-1;

	for (i = n-2; i >= 0; i--){
		index[i] = i;
		j = i + 1;
		while (digit[i] >= digit[j] && j != index[j]){ 
			j = index[j];
		}
		if (digit[i] >= digit[j])
			index[i] = i;
		else
			index[i] = j;
	}

	for (i = 0; i < n; i++)
		fprintf(output, "%d ", digit[index[i]]);

	free(digit); free(index);
	fclose(input);  fclose(output);
}