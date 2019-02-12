#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ( (a) > (b) ? (a) : (b));

int main(){
	int t, k, x, y;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		scanf("%d %d %d", &k, &x, &y);
		int count = 0;
		if (x > y) {
			if (x - y >= 2 && x >= k) {
				printf("%d\n", count);
			}else {
				while (x < k) {
					x++;
					count++;
				}
				while (x - y < 2) {
					x++;
					count++;
				}
				printf("%d\n", count);
			}
		} else {
			if (y - x >= 2 && y >= k) {
				printf("%d\n", count);
			}else {
				while (y < k) {
					y++;
					count++;
				}
				while (y - x < 2) {
					y++;
					count++;
				}
				printf("%d\n", count);
			}
		}
	}
}