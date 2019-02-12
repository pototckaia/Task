#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

int main(){
	int64_t n; 
	int64_t l, r;
	scanf("%I64d %I64d %I64d", &n, &l, &r);
	int64_t count = 0;

	l--;
	r--;
	int64_t count_i = pow(2, ceil(log(n+1)/log(2)) )-1;

	for (int i = l; i <= r; i++) {
		if (i % 2 == 0) {
			count++;
			continue;
		}
			int64_t first = 0;
			int64_t last = 	count_i;
			int64_t a = n;
			while (last - first > 1) {
				int64_t mid = (last + first) / 2;
				if (i < mid)
					last = mid;
				else 
					first = mid;
				if (mid == i) 
					break;
				a = a / 2;
			}
			//printf("%d %d\n", i, a);
			if (a % 2 == 1)
				count++;
	}
	printf("%I64d\n", count);
}