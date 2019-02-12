#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	scanf("%d", &n);
	char **gen = (char **) malloc(n * sizeof(char *));
	int **alph = (int **) calloc(n, sizeof(int *));
	int j;
	for (int i = 0; i < n; i++){
		gen[i] = (char *) malloc(30 * sizeof(char));
		alph[i] = (char *) malloc(30 * sizeof(char));
		scanf("%s", gen[i]);
		j = 0; 
		while (gen[i][j] != '\0'){
			alph[gen[i][j]-97]++;
			j++;
		}
	}
	for (int i = 0; i < 26; i++)
		printf("%d %c\n", alph[i], i+97);

}