#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	scanf("%d", &n);
	int *hard = calloc(n+2, sizeof(int));
	for (int i = 2; i*i <= n+1; i++){
		if (!hard[i]) 
			for (int j = i+i; j <= n+1; j+=i)
				hard[j] = 1;
	}
	printf("%d\n", (n > 2) ? 2 : 1);

	for (int i = 2; i < n+2; i++){
		printf("%d ",hard[i] ? 2 : 1);
	}
}