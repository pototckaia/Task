'''
f_0 = 0.5 * x^T * A * x + b^T * x
f = ||x - x_0 || - z <= 0, z - радиус, x_0 - центр
f^2 =  ||x - x_0 ||^2 - z^2 <= 0

L(x, y) = 0.5 * x^T * A * x + b^T * x + y * (||x - x_0 ||^2 - z^2 )

1. y > 0

Ax + b + 2y(x - x_0) = 0
||x - x_0||^2 = r^2

'''