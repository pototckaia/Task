#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>


int main(){
	int n;
	scanf("%d\n", &n);
	int class_1[6] = {0, 0, 0, 0, 0, 0};
	int class_2[6] = {0, 0, 0, 0, 0, 0};
	
	int class;
	for (int i = 0; i < n; i++){
		scanf("%d", &class);
		class_1[class]++;
	}

	for (int i = 0; i < n; i++){
		scanf("%d", &class);
		class_2[class]++;
	}

	int c = 0, k = 0, ans, f;
	for (int i = 1; i < 6; i++){
		if (class_1[i] == class_2[i]) 
			continue;  
		f = class_1[i] - class_2[i];
		if (f % 2) {
			printf("%d\n", -1);
			return 0;
		}
		if (f > 0) {
			c += f / 2;
		} else  {
			k += -f / 2;
		}

	}

	if (c == k)
		printf("%d", c);
	else 
		printf("%d", -1);

}