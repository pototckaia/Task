#include <stdio.h>
#include <stdlib.h>
#include <math.h> 


void search_1(int n, int *del) {
	int ans = 2, count = 0;
	int k = n;
	while (n > 1) {
		if (n % ans == 0 ) {
			if (ans != k){
				del[count] = ans; 
				count++;
			}
			n = (int ) floor(n / ans);
		}
		else 
			ans++;
	}
}

int search(int n) {
	int ans = 2, count = 0;
	while (ans * ans <= n ) {
		if (n % ans == 0 ) {
			return 0;
		}
		else 
			ans++;
	}
	return 1;
}

int main() {
	int n;
	scanf("%d", &n);
	int p = 0;
	int size = 0;
	for (int i = 2; i < n+1; i++){
		if (search(i)){
			for (int j = i + 1; j < n + 1; j++){

			}
		}
				
	}
}