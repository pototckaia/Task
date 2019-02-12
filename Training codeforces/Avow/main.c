#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

int main(){
	int n, d;
	scanf("%d", &n);
	int *steward = (int *) malloc(n * sizeof(int));
	int maxV = -1, minV = 1000000001;

	for (int i = 0; i < n; i++){
		scanf("%d", &steward[i]);
		maxV = MAX(maxV, steward[i]);
		minV = MIN(minV, steward[i]);
	}

	int size = 0;
	for (int i = 0; i < n; i++) {
		if (steward[i] < maxV && steward[i] > minV)
			size++;
	}
	printf("%d\n", size);
	free(steward);
}