#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
typedef struct {
    double x, y, r;
} Circle;
 
double one(Circle x, double angle) {
    return (pow(x.r, 2) * (angle - sin(angle)) * 0.5);
}
 
double two(Circle x, double angle) {
    return (pow(x.r, 2) * (sin(2 * M_PI - angle) + angle) * 0.5);
}
 
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    Circle a, b;
    scanf("%lf%lf%lf %lf%lf%lf", &a.x, &a.y, &a.r, &b.x, &b.y, &b.r);
 
 
    double d = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    double answer = 0;
 
    if (d < a.r + b.r) {
        if (d <= fabs(a.r - b.r)) {
            answer = M_PI * pow(__min(a.r, b.r), 2);
        }
        else {
            double angle1 = 2 * acos((pow(a.r, 2) + pow(d, 2) - pow(b.r, 2)) / (2 * a.r * d));
            double angle2 = 2 * acos((pow(b.r, 2) + pow(d, 2) - pow(a.r, 2)) / (2 * b.r * d));
 
            if (angle1 < M_PI  && angle2 < M_PI) {
                answer = one(a, angle1) + one(b, angle2);
            }
            else if (angle1 >= M_PI) {
                answer = two(a, angle1) + one(b, angle2);
            }
            else {
                answer = one(a, angle1) + two(b, angle2);
            }
 
        }
    }
 
    printf("%.2lf", answer);
    return 0;
}