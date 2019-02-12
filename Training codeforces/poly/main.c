#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compar(const void *a, const void *b){ 
	return (strcmp( *((char **)a), *((char **)b)));
}

int find(char **m, char * word, int n){
	int l = 0, r = n;
	int mid;
	while(r-l>1){
		mid = (r+l)/2;
		if (strcmp(m[mid], word) > 0)
			r = mid; 
		else 
			l = mid;
	}
	return l;
}

int main(){
	int n;
	scanf("%d", &n);
	
	char **adress = (char **) malloc(sizeof(char *)*n);
	char **sort = (char **) malloc(sizeof(char *)*n);
	int *used = (int *) calloc(n, sizeof(int));

	for (int i = 0; i < n; i++){
		adress[i] = (char *) malloc(11 * sizeof(char));
		sort[i] = (char *) malloc(11 * sizeof(char));
		scanf("%s", adress[i]);
		strcpy(sort[i], adress[i]);
	}

	
	qsort(sort, n, sizeof(char *), compar);

	int j;
	for (int i = n-1; i >= 0; i--){
		//printf("ddd %s\n", sort[i]);
		j = find(sort, adress[i], n);
		if (!used[j]){
			printf("%s\n", adress[i]);
			used[j] = 1;
		} 
	}
}

