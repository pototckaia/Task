#include <stdio.h>
#include <stdlib.h>

#define MIX(x, y) ( (x) > (y) ? (y) : (x))

int hod(int a, int b) {
	while (b) {
		a  = a % b;
		int t = a;
		a = b;
		b = t;
	}
	return a;
}

int main() {
	int t, a, b, c, d;
	scanf("%d", &t);
	for (int k = 0; k < t; k++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		int t1 , t2, res;
		if (b != d) {
			if (a != c) {
				t1 = (a / hod(a, c)) * c;
			}
			else {
				t1 = a;
			}	
			t2 = hod(b, d); 
		}
		else {
			t1 = (a / hod(a, c)) * c;
			t2 = b;
		}

		printf("%d %d\n", t1, t2);
	}
}