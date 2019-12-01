'''

f_0 = 0.5 * x^T * A * x + b^T * x
f_x = c^T * x + d <= 0

d = const 
c, d - f(x) не выполнялось

y одномерно (число неравенств)

L(x, y) = f_0 + y *f =  0.5 * x^T * A * x + b^T * x + y * (c^T * x + d)

1. Ax + b + y * c = 0
2. y (c^T * x + d) = 0 

1. y = 0
x = -A^-1 * b

2. y > 0

x = -A^-1 (b + y * c)
y = (d - c^T * A^-1 * b) / (c^T * A^-1 * c)
'''

