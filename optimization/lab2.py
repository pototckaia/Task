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

y = (d - c^T * A^-1 * b) / (c^T * A^-1 * c)
x = -A^-1 (b + y * c)
'''


def isPD(B):
    try:
        _ = la.cholesky(B)
        return True
    except la.LinAlgError:
        return False


def rowToCol(v):
	if len(v.shape) == 2:
		return v.reshape((v.shape[1], 1))
	else:
		return v.reshape((v.shape[0], 1))


def colToRow(v):
	return v.reshape(v.shape[0])


# 1/2 * (x^T * A * x) + b^T * x
def f_0(A, b, x):
	x = rowToCol(x)
	return (0.5 * (x.transpose() @ A @ x)  + b.transpose() @ x)[0, 0]


# f_x = c^T * x + d <= 0
def f(c, d, x):
	return (c.transpose() @ x)[0, 0] + d 


import numpy as np
from numpy import linalg as la
from sklearn.datasets import make_spd_matrix
import argparse
import random


if __name__ == '__main__':

	argsParser = argparse.ArgumentParser()
	argsParser.add_argument('-n', '--n', type=int,
							default=6, help='dim')
	argsParser.add_argument('-a', '--alpha', type=float,
							default=-1, help='Size key')
	args = argsParser.parse_args()

	n = args.n
	print(n)

	A = make_spd_matrix(n)
	print('is positive-definite matrix:', isPD(A))
	print(A)
	b =  np.random.rand(1, n).transpose()
	print('b = ', b)
	if A.shape[0] != A.shape[1]:
		print('Матрица A должна быть квадратной')
		exit(0)
	if b.shape[0] != n or b.shape[1] != 1:
		print('Вектор-столбец b не правильно задан')
		exit(0)


	c = np.random.rand(1, n).transpose()
	print('c = ', c)
	d = random.uniform(1.0, 10.0)
	print('d = ', d)

	A_1 = la.inv(A)
	# min ans
	x_1 = -(A_1 @ b)
	print('arg min f_0 = ', x_1)
	if f(c, d, x_1) <= 0:
		print('also min with the condition f(x) <= 0')
	else:
		# y = (d - c^T * A^-1 * b) / (c^T * A^-1 * c)
		# x = -A^-1 (b + y * c)
		y = (d - (c.transpose() @ A_1 @ b)[0, 0]) / (c.transpose() @ A_1 @ c)[0, 0]
		x = -(A_1 @ (b + y * c))
		print('min with the condition f(x) <= 0')
		print(x)

