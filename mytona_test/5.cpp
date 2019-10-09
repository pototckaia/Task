#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

//Программа ожидает ввода трёх пар целочисленных значений, представляющих собой точки в двумерном пространстве
//Вывести на экран координаты точек кривой Безье для всех целочисленных x построенных через заданные точки.

struct Point {
    Point(): x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    double x, y;
};

bool inRange(double low, double h, double value) {
    return value >= low && value <= h;
}

//B(t) = (1 - t)^2*p0 + 2t*(1-t)*p1 + t^2*p2
// 0 <= t <= 1
double curveBezier(double t, double p0, double p1, double p2) {
    double tt = (1 - t);
    return tt * tt * p0 + 2 * t * tt * p1 + t * t * p2;
}

//1. p0 - 2p1 + p2 != 0
//t^2 * (p0 - 2p1 + p2) + 2t * (p1 - p0) + (po - B) = 0
//t_1,2 = (po - p1 +- sqrt(p1^2 - p1*p0 + (p0 - 2p1 + p2)B)) / (p0 - 2p1 + p2)

//2. p0 - 2p1 + p2 == 0, p1 != p0
// 2t * (p1 - p0) + (p0 - B) = 0
// t = (B - p0) / (p1 - p0)

// 3. p1 == p0 != p2
// t^2 (p2 - p0) + (p0 - B) = 0
// t = sqrt((B - p0) / (p2 - p0))
std::vector<Point> curveBezierIntX(Point &p0, Point &p1, Point &p2) {
    std::vector<Point> res;

    const double eps = 0.0001;
    double p0_2p1_p2 = p0.x - 2 * p1.x + p2.x;
    bool first = std::abs(p0_2p1_p2) >= eps;

    double p1_p0 = p1.x - p0.x;
    bool second = !first && std::abs(p1_p0) >= eps;

    double p2_p0 = p2.x - p0.x;
    bool third = std::abs(p1_p0) < eps && std::abs(p2_p0) >= eps;

    if (!first && !second && !third) {
        return res;
    }

    auto addIfInRange = [&res, &p0, &p1, &p2](double x, double t) {
        if (!inRange(0, 1, t)) {
            return;
        }
        res.emplace_back(x, curveBezier(t, p0.y, p1.y, p2.y));
    };


    long endX = (long) std::floor(p2.x);
    for (long x = (long) std::ceil(p0.x); x <= endX; ++x) {
        if (first) {
            double D = p1.x * p1.x - p2.x * p0.x + p0_2p1_p2 * x;
            if (D < 0) { continue; }
            D = std::sqrt(D);
            double t1 = (p0.x - p1.x + D) / p0_2p1_p2;
            double t2 = (p0.x - p1.x - D) / p0_2p1_p2;

            addIfInRange(x, t1);
            addIfInRange(x, t2);
        } else if (second) {
            double t = (x - p0.x) / p1_p0;
            addIfInRange(x, t);
        } else if (third) {
            double t = (x - p0.x) / p2_p0;
            if (t < 0) { continue; }
            t = std::sqrt(t);
            addIfInRange(x, t);
        }
    }
    return res;
}

void printCurveBezier(Point &p0, Point &p1, Point &p2) {
    for (double t = 0; t <= 1; t += 0.002) {
        std::cout
                << "x: " << curveBezier(t, p0.x, p1.x, p2.x)
                << " y: " << curveBezier(t, p0.y, p1.y, p2.y)
                << std::endl;
    }
}


int main(int argc, char **argv) {
    std::vector<Point> p(3);
    std::cin
            >> p[0].x >> p[0].y
            >> p[1].x >> p[1].y
            >> p[2].x >> p[2].y;
    std::sort(p.begin(), p.end(), [](const Point &a, const Point &b) { return a.x < b.x; });
    auto r = curveBezierIntX(p[0], p[1], p[2]);


    for (auto& e : r) {
        std::cout << "x : " << e.x << " y: " << e.y << std::endl;
    }
//    std::cout << "Test" << std::endl;
//    printCurveBezier(p[0], p[1], p[2]);
}