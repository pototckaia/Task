import numpy as np
from numpy import linalg as la
from scipy.optimize import minimize
from sklearn.datasets import make_spd_matrix

def isPD(B):
    try:
        _ = la.cholesky(B)
        return True
    except la.LinAlgError:
        return False


r'''
	backtracking line search
	- fix beta \in (0, 1) - B&T recommend (0.1, 0.8)
	- at each iteration, start with t = 1 and while 
		f(x - t * df(x)) > f(x) - t/2 * ||df(x)||^2_2 - Armijo-Goldstein condition
		update t = beta * t
'''
def backtrackingLineSerarch(init_t, beta, x, f, df, max_iter=10):
	cur_t = init_t
	c = 1/2
	for _ in range(1, max_iter):
		a = f(x - cur_t * df(x))
		b = f(x) - c * cur_t * la.norm(df(x), 2)**2
		if a > b:
			break
		cur_t *= beta
	return cur_t


r'''
	min f(x)
	x^(k + 1) = x^k - t_k * df(x^k)
	- backtracking line search
	- exact line search
		t = argmin(f(x - s * df(x)))
'''
def gradientDescent(f, df, x0, precision, lr = None, max_iter=30):
	cur_x = x0
	learning_rate = 1
	dot = [x0]
	res = {}
	for _ in range(1, max_iter):
		if lr is not None:
			learning_rate = 1
		else:
			learning_rate = backtrackingLineSerarch(learning_rate, 0.7, cur_x, f, df)
		next_x = cur_x - learning_rate * df(cur_x)
		if (la.norm(df(next_x), 2) <= precision): # || df(x^(k+1)) || = 0
			cur_x = next_x
			res['success'] = True
			break
		res['success'] = False
		dot.append(cur_x)
		cur_x = next_x

	res['x'] = cur_x.transpose()
	res['fun'] = f(cur_x)
	res['dx'] = df(cur_x).transpose()
	res['iteration'] = len(dot)
	return res


def newtonMethod(f, df, d2f, x0, precision, max_iter=1000):
	cur_x = x0
	dot = [x0]
	res = {}
	for _ in range(1, max_iter):
		next_x = cur_x - la.inv(d2f(cur_x)) @ df(cur_x)
		if (la.norm(df(next_x), 2) <= precision):
			cur_x = next_x
			res['success'] = True
			break
		res['success'] = False
		dot.append(cur_x)
		cur_x = next_x
	
	res['x'] = cur_x.transpose()
	res['fun'] = f(cur_x)
	res['dx'] = df(cur_x).transpose()
	res['iteration'] = len(dot)
	return res

n = 6
A = make_spd_matrix(n)
A = np.array([[ 0.41288544,  0.14402624,  0.08398111,  0.14910279,  0.19943268, -0.1850263 ],
 [ 0.14402624,  0.519214,    0.49199552,  0.67888757, -0.02225559, -0.20041139],
 [ 0.08398111,  0.49199552,  1.67634324,  2.25012679,  0.34441188, -1.10743227],
 [ 0.14910279,  0.67888757,  2.25012679,  3.85956323,  0.12809546, -1.90510422],
 [ 0.19943268, -0.02225559,  0.34441188,  0.12809546,  0.53617464, -0.10144008],
 [-0.1850263,  -0.20041139, -1.10743227, -1.90510422, -0.10144008,  1.44175826]])
# print('is positive-definite matrix:', isPD(A))
# print(A)
b = np.matrix('1; 2; 3; 4; 5; 6')
# print(b)
if A.shape[0] != A.shape[1]:
	print('Матрица A должна быть квадратной')
	exit(0)
if b.shape[0] != n or b.shape[1] != 1:
	print('Вектор-столбца b не правильно задан')
	exit(0)

# 1/2 * (x^T * A * x) + b^T * x
def f(x):
	return (0.5 * (x.transpose() @ A @ x)  + b.transpose() @ x)[0, 0]

# 1/2 * (A + A^T) * x + b
def df(x):
	aa = (A + A.transpose())
	return 0.5 * aa @ x + 0.5 * b

# 1/2 * (A + A^T)
def d2f(x):
	return 0.5 * (A + A.transpose())

x0 = np.zeros((n, 1))

from scipy.misc import derivative
def partial_derivative(func, var=0, point=[]):
    args = point[:]
    def wraps(x):
        args[var] = x
        return func(args)
    return derivative(wraps, point[var], dx = 1e-10)
def der(f, x):
	res = []
	for i in range(x.shape[0]):
		res.append(partial_derivative(f, i, b))
	return res

print(df(b))
for i in range(n):
	print(partial_derivative(f, i, b))

res = minimize(f, x0=x0)
print('Результат scipy.optimize.minimize')
print('\t message: {}'.format(res['message']))
print('\t success: {}'.format(res['success']))
print('\t fun: {}'.format(res['fun']))
print('\t x: {}'.format(res['x']))
print()

ans = gradientDescent(f, df, x0, 0.005, 30)
print('Результат gradientDescent')
for key in ans:
	print('\t {}: {}'.format(key, ans[key]))
print()

ans = newtonMethod(f, df, d2f, x0, 0.005)
print("Результат newtonMethod")
for key in ans:
	print('\t {}: {}'.format(key, ans[key]))
print()
