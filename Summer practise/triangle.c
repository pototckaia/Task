#include <stdlib.h>
#include <stdio.h>

typedef struct{
	double x, y, z;
} Point;

Point computeVector(Point a, Point b){
	Point tmp;
	tmp.x = b.x - a.x;
	tmp.y = b.y - a.y;
	tmp.z = b.z - a.z;
	return tmp;
}

double det(Point a, Point b, Point c){
	return a.x * (b.y * c.z - b.z * c.y) + 
			a.y * (b.z * c.x - b.x * c.z) +
			a.z * (b.x * c.y - b.y *c.x);
}

int isIntersectTriangleLine(Point a, Point b, Point c, Point d, Point e){
	Point ab = computeVector(a, b);
	Point ac = computeVector(a, c);
	Point ed = computeVector(e, d);
	Point ad = computeVector(a, d);

	double delta = det(ab, ac, ed);
	if (!delta)
		return 0;

	double u = det(ad, ac, ed) / delta;
	double v = det(ab, ad, ed) / delta;
	double t = det(ab, ac, ad) / delta;
 	
	if (t > 1 || t < 0 || u < 0 || u > 1 || v < 0 || v > 1 || u + v > 1)
		return 0;

	return 1;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	Point ptr[6];
	for (int i = 0; i < 6; i++){
		scanf("%lf %lf %lf", &ptr[i].x, &ptr[i].y, &ptr[i].z);
	}

	int tri1 = (isIntersectTriangleLine(ptr[0], ptr[1], ptr[2], ptr[3], ptr[4]) ||
				isIntersectTriangleLine(ptr[0], ptr[1], ptr[2], ptr[3], ptr[5]) ||
				isIntersectTriangleLine(ptr[0], ptr[1], ptr[2], ptr[4], ptr[5]));

	int tri2 = (isIntersectTriangleLine(ptr[3], ptr[4], ptr[5], ptr[0], ptr[1]) ||
				isIntersectTriangleLine(ptr[3], ptr[4], ptr[5], ptr[0], ptr[2]) ||
				isIntersectTriangleLine(ptr[3], ptr[4], ptr[5], ptr[1], ptr[2]));

	if (!tri1 && !tri2)
		printf("0\n");		
	else if (tri1 && tri2)
		printf("3\n");
	else if (tri1)
		printf("2\n");
	else 
		printf("1\n");

	return 0;
}

