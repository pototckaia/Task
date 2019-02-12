#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
  
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))
  
typedef struct {
    double x, y;
} Point;
  
typedef struct {
    int *val;
    int size;
} Stack;
  
void push(Stack *stack, int val){
    stack->val[stack->size] = val;
    stack->size++;
}
  
void pop(Stack *stack) {
    stack->size--;
}
  
Stack *createStack(int size) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->val = (int *) malloc(size * sizeof(int));
    stack->size = 0;
    return stack;
}
  
void clearStack(Stack *stack) {
    stack->size = 0;
}
  
Stack *pos_convex_hull;
Point val_startV;
  
double z_cross(Point a, Point b, Point c) {
    double x1 = (b.x - a.x);
    double y1 = (b.y - a.y);
    double x2 = (c.x - a.x);
    double y2 = (c.y - a.y);
    return (x1*y2 - y1*x2);
}
  
int is_left_rotation(Point a, Point b, Point c) {
    return (z_cross(a, b, c) >= 0);
}
  
double angle(Point a, Point b, Point c) {
    Point ab, bc;
    ab.x = a.x - b.x; ab.y = a.y - b.y;
    bc.x = c.x - b.x; bc.y = c.y - b.y;
    double dot  = ab.x * bc.x + ab.y * bc.y;
    double len_ab = sqrt(pow(ab.x, 2) + pow(ab.y, 2));
    double len_bc = sqrt(pow(bc.x, 2) + pow(bc.y, 2));
    double angle =  acos(dot / (len_ab * len_bc));
   return angle;
}
  
void swap(Point *x, Point *y) {
    Point t = *x;
    *x = *y;
    *y = t;
  
}
  
void copy(Point *b, Point *a, int size) {
    for (int i = 0; i < size; i++) {
        b[i].x = a[i].x;
        b[i].y = a[i].y;
    }
}
  
  
void merge(Point *a, int left, int mid, int right) {
    int it1 = 0, it2 = 0;
    Point *res = (Point *) malloc((right - left) * sizeof(Point));
  
    while(left + it1 < mid && mid + it2 < right) {
        if (is_left_rotation(a[0], a[left + it1], a[mid + it2])) {
            res[it1 + it2] = a[left + it1];
            it1++;
        }
        else {
            res[it1 + it2] = a[mid + it2];
            it2++;
        }
    }
    while(left + it1 < mid) {
        res[it1 + it2] = a[left + it1];
        it1++;
    }
  
    while (mid + it2 < right) {
        res[it1 + it2] = a[mid + it2];
        it2++;
    }
  
    for (int i = 0; i < (it1 + it2); i++) {
        a[left + i] = res[i];
    }
    free(res);
}
  
void merge_sort(Point *a,int left, int right) {
    if (left + 1 >= right) {
        return;
    }
    int mid = (left + right) / 2;
    merge_sort(a, left, mid);
    merge_sort(a, mid, right);
    merge(a, left, mid, right);
}
  
void build_MCH(Point *points, int size_points) {
    int pos_startV = 0;
    val_startV.x = LONG_MAX; val_startV.y = LONG_MAX;
  
    for (int i = 0; i < size_points; i++) {
        if (points[i].x < val_startV.x || (points[i].x == val_startV.x &&
                                           points[i].y < val_startV.y)) {
            pos_startV = i;
            val_startV = points[i];
        }
    }
  
    swap(&points[0], &points[pos_startV]);
    merge_sort(points, 1, size_points);
  
    push(pos_convex_hull, 0);
    push(pos_convex_hull, 1);
    for (int i = 2; i < size_points; i++) {
        while (pos_convex_hull->size >= 2 &&
               !is_left_rotation(points[pos_convex_hull->val[pos_convex_hull->size - 2]],
                                 points[pos_convex_hull->val[pos_convex_hull->size - 1]],
                                 points[i])) {
            pop(pos_convex_hull);
        }
        push(pos_convex_hull, i);
    }
 
    push(pos_convex_hull, 0);
    push(pos_convex_hull, 1);
}
  
double find_sharpest_angle(Point *points, int size_points) {
    double sharpest_angle = LONG_MAX;
    for (int i = 0; i < pos_convex_hull->size - 2; i++) {
        sharpest_angle = MIN(sharpest_angle,
                               angle(points[pos_convex_hull->val[i]],
                                         points[pos_convex_hull->val[i + 1]],
                                         points[pos_convex_hull->val[i + 2]]));
  
    }
    return sharpest_angle;
}
  
  
int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
  
    int n;
    scanf("%d", &n);
  
    Point *points = (Point *) malloc(n * sizeof(Point));
    Point *buf = (Point *) malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
        buf[i].x = points[i].x;
        buf[i].y = points[i].y;
    }
  
  
  
    pos_convex_hull = createStack(n + 10);
    build_MCH(buf, n);
    double answer = find_sharpest_angle(buf, n);
  
  
    for (int i = 0; i < n; i++) {
        copy(buf, points, n);
        swap(&buf[i], &buf[n - 1]);
        clearStack(pos_convex_hull);
        build_MCH(buf, n - 1);
        double angle =  find_sharpest_angle(buf, n - 1);
        answer = __max(answer, angle);
    }
  
  
    printf("%.3lf", answer);
    return 0;
}