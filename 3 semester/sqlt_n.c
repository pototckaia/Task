#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double _pow(double a, int n){
	double res = 1;
	while(n != 0){
		if (n & 1){
			res = res * a;
		}
		a = a * a;
		n >>= 1;

	}
	return res;
} 

int main(){
	double a;
	long int n;
	double eps = 0.000001;

	scanf("%lf %ld", &a, &n);

	double l = -a - 1;
	double r = a + 1;

	while (r - l > eps){
		double m = (l + r) / 2;		
		double p = _pow(m, n);
		if (p > a)
			r = m;
		else
			l = m;
	}

	printf("%lf", l);

}