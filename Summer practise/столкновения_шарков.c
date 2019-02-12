#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
int main() {
    double R;
    double x[2], y[2], dx[2], dy[2];
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    scanf("%lf", &R);
    for (int i  = 0; i < 2; i++) {
        scanf("%lf %lf %lf %lf", &x[i], &y[i], &dx[i], &dy[i]);
    }
 
    double a = pow(dx[1] - dx[0], 2) + pow(dy[1] - dy[0], 2);
    double b = (x[1] - x[0]) * (dx[1] - dx[0]) + (y[1] - y[0]) * (dy[1] - dy[0]);
    double c  = pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2) - 4 * R * R;
 
    double D = pow(b, 2) - a * c;
 
    double answer;
    if (D < 0 || a == 0) {
        answer  = -1;
    }
    else if (D == 0) {
        answer = -b / a;
        if (answer < 0) {
            answer = -1;
        }
 
    }
    else if (D > 0) {
        double k1 = (-b + sqrt(D)) / a;
        double k2 = (-b - sqrt(D)) / a;
        if (k1 < 0 && k2 < 0) {
            answer = -1;
        }
        else if (k1 < 0) {
            answer = k2;
        }
        else if (k2 < 0) {
            answer = k1;
        }
        else {
            answer = __min(k1, k2);
        }
    }
    printf("%.4lf", answer);
}