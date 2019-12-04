'''
f_0 = 0.5 * x^T * A * x + b^T * x
f = ||x - x_0 || - z <= 0, z - радиус, x_0 - центр
f^2 =  ||x - x_0 ||^2 - z^2 <= 0

L(x, y) = 0.5 * x^T * A * x + b^T * x + y * (||x - x_0 ||^2 - z^2 )

1. y > 0

Ax + b + 2y(x - x_0) = 0
||x - x_0||^2 = r^2

x = (A + 2Iy)^(-1)(2yx_0 - b)
||x - x_0||^2 = r^2
'''


import numpy as np
from numpy import linalg as la
from scipy.optimize import root
from sklearn.datasets import make_spd_matrix
import argparse
import random

def isPD(B):
    try:
        _ = la.cholesky(B)
        return True
    except la.LinAlgError:
        return False

def f_0(A, b, x):
	return (x @ A @ x.transpose() + b @ x.transpose())[0, 0]


def f(x_0, z, x):
	return la.norm(x - x_0, 2) - z 


def x_(A, b, x_0, n, y):
	return (2 * y * x_0 - b) @ la.inv(A + 2 * y * np.eye(n))


if __name__ == '__main__':

	argsParser = argparse.ArgumentParser()
	argsParser.add_argument('-n', '--n', type=int,
							default=6, help='dim')
	args = argsParser.parse_args()

	n = args.n
	print(n)

	A = make_spd_matrix(n)
	A = np.array([[ 4.86716558, -0.23636781, -0.61816128, -0.15304448,  2.54504109, -0.67458228],
 [-0.23636781,  0.84502051,  0.1635084,   0.07969577, -0.07063309, -0.0613299],
 [-0.61816128,  0.1635084,   0.80722873,  0.17313754, -0.51640825,  0.30509174],
 [-0.15304448,  0.07969577,  0.17313754,  0.34512097,  0.14426913, -0.01583605],
 [ 2.54504109, -0.07063309, -0.51640825,  0.14426913,  2.26861519, -0.47524533],
 [-0.67458228, -0.0613299,   0.30509174, -0.01583605, -0.47524533,  0.80191505]])
	print('is positive-definite matrix:', isPD(A))
	print(A)
	if A.shape[0] != A.shape[1]:
		print('Матрица A должна быть квадратной')
		exit(0)

	b =  np.random.rand(1, n)
	b =  np.array([[0.90175436, 0.51041034, 0.67882025, 0.49486765, 0.6410782,  0.48502675]])
	print('b = ', b)
	if b.shape[1] != n or b.shape[0] != 1:
		print('Вектор-строка b не правильно задан')
		exit(0)

	x_0 = np.random.rand(1, n)
	x_0 = np.array([[10.01182076, 10.50170593, 10.60628952, 10.38716832, 10.52470984, 10.40231676]])
	print('x_0 = ', x_0)
	
	z = 0.2# random.uniform(0.2, 10.0)
	print('z = ', z)

	A_1 = la.inv(A)
	# min ans
	x_1 = -(b @ A_1)
	print('arg min f_0 = ', x_1)
	print('min f = ', f_0(A, b, x_1))
	if f(x_0, z, x_1) <= 0:
		print('also min with the condition f(x) <= 0')
		exit(0)

	x = lambda y: x_(A, b, x_0, n, y)
	F = lambda y: pow(la.norm(x(y) - x_0, 2), 2) - z * z
	
	sol = root(F, 0)
	print(sol.message)
	print(sol.x)
	y = sol.x[0]
	x_ans = x(sol.x)
	if f(x_0, z, x_1) <= 0 or y <= 0:
		print('condition don\'t resolve')
		exit(0)
	
	print('min with the condition f(x) <= 0')
	print(x_ans)
	print('f = ', f_0(A, b, x_ans))