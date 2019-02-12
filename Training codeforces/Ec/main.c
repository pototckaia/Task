#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int n, l, r;
	scanf("%d%d%d", &n, &r, &l);
	char *massiv = (char *) malloc(n * sizeof(char));
	
	int x = n, size  = -1;
	while (x > 1){
		size++;
		massiv[size] = x % 2;
		x /= 2;
	}
	
	char *massiv_2 = (char *) malloc ( ((n+1) << (n+1)) * sizeof(char)); 
	massiv_2 = "1";

	for (int i = size; i >= 0; i--){
		strcpy(ma)
	}
	for (int i = 0; i < size; i++){
		printf("%d ", massiv_2[i]);
	}
	free(massiv_2);
	free(massiv);

}