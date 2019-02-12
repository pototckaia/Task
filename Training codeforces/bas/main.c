#include <stdio.h>
#include <stdlib.h>

int main(){
	int n, a;
	scanf("%d%d", &n, &a);
	int j = 1, i;
	int time = a % 2;
	if (a % 2){ // нечетное
		j = (a-1)/2+1;
	} else {
		j = (n-a)/2+1;	
	} 
	printf("%d", j);

}