#include <stdio.h>
#include <math.h>
 
int main() {
    double a, b, c;
   freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    scanf("%lf%lf", &a, &b);
 
    if(!((b > a && a <= 180 && b <= 180) || (a > b && b > 180 && a > 180))) {
        printf("0 0");
        return 0;
    }
 
 
    c = (b - a) * M_PI / 180;
    a = a * M_PI / 180;
    b = (180 - b) * M_PI / 180;
 
    double t = (100) / sin(c);
    double AB = t * sin(b);
    double x = AB * cos(a);
    double y = AB * sin(a);
 
    printf("%.4lf %.4lf", x, y);
    return 0;
}