#include <stdio.h>
#include <math.h>
 
typedef struct {
    double x, y;
}  Point;
 
double z_cross(Point a, Point b, Point c) {
    double x1 = (b.x - a.x);
    double y1 = (b.y - a.y);
    double x2 = (c.x - a.x);
    double y2 = (c.y - a.y);
    return (x1*y2 - y1*x2);
}
 
int is_left_rotation(Point a, Point b, Point c) {
    return (z_cross(a, b, c) > 0);
}
 
double compute_coord(double V, double k) {
    int c = (int) floor(V / k);
    V = V - k * c;
    if (c & 1) {s
        V = k - V;
    }
    return V;
}
 
int main() {
    double a, t;
    Point P, V;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%lf %lf %lf %lf %lf %lf", &a, &P.x, &P.y, &V.x, &V.y, &t);
 
    Point S;
    S.x = P.x + V.x * t;
    S.y = P.y + V.y * t;
 
    S.x = compute_coord(S.x, a);
    S.y = compute_coord(S.y, a);
 
    Point c, b;
    c.x = a; c.y = 0;
    b.x = 0; b.y = a;
    if (!is_left_rotation(c, b, S)) {
        double t = S.x;
        S.x = a - S.y;
        S.y = a - t;
    }
 
    printf("%.3lf %.3lf", S.x, S.y);
 
}