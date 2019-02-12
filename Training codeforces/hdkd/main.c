#include <stdio.h>
#include <stdlib.h>


int main(){
	int n;
	scanf("%d", &n);
	
	int photo;
	int *like = (int *) calloc(1000001, sizeof(int));
	int *last = (int *) calloc(1000001, sizeof(int));


	for(int i = 0; i < n; i++){
		scanf("%d", &photo);
		like[photo]++;
		last[photo] = i;
	} 
	int m = -1, k = 0;;
	for (int i = 1; i < 1000001; i++){
		if (like[i] > like[k] || like[i] == like[k] && last[i] < last[k]){
			k = i;
		}
	}
	printf("%d\n", k);
}
