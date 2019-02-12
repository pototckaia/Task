#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923

typedef struct{
	double leftAngle, rightAngle;
} Asteroid;

typedef struct{
	double x, y;
} Point;

int sizeAsteroid;

void pushAsteroid(Asteroid *arr, double l, double r){
	Asteroid t;
	t.leftAngle = l;
	t.rightAngle = r;
	arr[sizeAsteroid] = t;
	sizeAsteroid++;
}

void computeAngleInterval(Asteroid *ast, double x, double y, double R){
	double len = sqrt(x * x + y * y);
	double b = asin(R / len);

	double a = atan(y / x);
	if (x < 0) 
		a = M_PI + a;
	else if (x >= 0 && y < 0) 
		a = 2 * M_PI + a; 

	double l = a - b;
	double r = a + b;
	if (a > b){
		if (r > 2 * M_PI){
			pushAsteroid(ast, l, 2 * M_PI);
			pushAsteroid(ast, 0, r - 2 * M_PI);
		}
		else{
			pushAsteroid(ast, l, r);
		}
	}
	else{
		pushAsteroid(ast, l + 2 * M_PI, 2 * M_PI);
		pushAsteroid(ast, 0, r);
	}

}

int cmp(const void *t, const void *r){
	Asteroid *a = (Asteroid *)t;
	Asteroid *b = (Asteroid *)r;
	if (a->leftAngle > b->leftAngle){
		return 1;
	}
	else if (a->leftAngle < b->leftAngle){
		return -1;
	}
	else if (a->leftAngle == b->leftAngle){
		if (a->rightAngle > b->rightAngle){
			return 1;
		}
		else if (a->rightAngle < b->rightAngle){
			return -1;
	}
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	Point ship;
	int n;
	scanf("%lf %lf %d", &ship.x, &ship.y, &n);
	
	Asteroid *ast = (Asteroid *) malloc(2 * n * sizeof(Asteroid));

	for (int i = 0; i < n; i++){
		double x, y, r;
		scanf("%lf%lf%lf", &x, &y, &r);
		computeAngleInterval(ast, x - ship.x, y - ship.y, r);
	}
	qsort(ast, sizeAsteroid, sizeof(Asteroid), cmp);

	double t;
	if (ast[0].leftAngle > 0) {
		t = ast[0].leftAngle / 2;
	}
	else {
		double r = ast[0].rightAngle;
		int i;
		for (i = 0; i < sizeAsteroid - 1 && r >= ast[i + 1].leftAngle; i++){
			if (ast[i + 1].rightAngle > r) 
				r = ast[i + 1].rightAngle;
		}
		t = (r + ast[i + 1].leftAngle) / 2;
	}

	Point offset;
	if (t >= M_PI_2 && t <= 3 * M_PI_2){
		offset.x = -1;
	}
	else {
		offset.x = 1;
	}
	offset.y = offset.x * tan(t);
	printf("%.5lf %.5lf\n", ship.x + offset.x, ship.y + offset.y);

}