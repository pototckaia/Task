#include <stdio.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int main(){
	int k, a, b;
	scanf("%d %d %d", &k, &a, &b);
	int res = a / k + b / k;
	if ((b / k == 0 && a % k > 0) || (a / k == 0 && b % k > 0))
		res = 0;
	printf("%d", (res != 0) ? res : -1);

}