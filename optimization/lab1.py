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


def rowToCol(v):
	if len(v.shape) == 2:
		return v.reshape((v.shape[1], 1))
	else:
		return v.reshape((v.shape[0], 1))


def colToRow(v):
	return v.reshape(v.shape[0])


r'''
	backtracking line search
	- fix beta \in (0, 1) - B&T recommend (0.1, 0.8)
	- at each iteration, start with t = 1 and while 
		f(x - t * df(x)) > f(x) - t/2 * ||df(x)||^2_2 - Armijo-Goldstein condition
		update t = beta * t
'''
def backtrackingLineSerarch(f, df, x, p, min_t, c1, c2):
	f_0 = f(x)
	grad_f_0 = df(x) @ p.transpose()
	t = 1
	while t >= min_t:
		f_t = f(x - t * p)
		if f_t <= f_0 - t * c1 * grad_f_0:
			return t
		t *= c2
	return min_t


r'''
	min f(x)
	x^(k + 1) = x^k - t_k * df(x^k)
	- backtracking line search
	- exact line search
		t = argmin(f(x - s * df(x)))
'''
def gradientDescent(f, df, x0, precision, lr = None, max_iter=100):
	cur_x = x0
	learning_rate = 1
	dot = [x0]
	res = {}
	for _ in range(1, max_iter):
		if lr is not None:
			learning_rate = lr
		else:
			learning_rate = backtrackingLineSerarch(f, df, cur_x, df(cur_x), 0.001, 0.5, 0.1)
		next_x = cur_x - learning_rate * df(cur_x)
		if (la.norm(df(next_x), 2) <= precision): # || df(x^(k+1)) || = 0
			cur_x = next_x
			res['success'] = True
			break
		res['success'] = False
		dot.append(cur_x)
		cur_x = next_x

	res['x'] = cur_x
	res['fun'] = f(cur_x)
	res['jac'] = df(cur_x)
	res['iteration'] = len(dot)
	return res


def newtonMethod(f, df, d2f, x0, precision, max_iter=1000):
	cur_x = x0
	dot = [x0]
	res = {}
	for _ in range(1, max_iter):
		next_x = cur_x - df(cur_x) @ la.inv(d2f(cur_x))
		if (la.norm(df(next_x), 2) <= precision): 
			cur_x = next_x
			res['success'] = True
			break
		res['success'] = False
		dot.append(cur_x)
		cur_x = next_x
	
	res['x'] = cur_x
	res['fun'] = f(cur_x)
	res['jac'] = df(cur_x)
	res['iteration'] = len(dot)
	return res

n = 6
A = make_spd_matrix(n)
A = np.array([[ 3.54575775,  1.40632856,  2.36437092, -1.01604035, -0.42511447, -0.25484018],
 [ 1.40632856,  0.71820751,  1.1093031,  -0.35012359, -0.24096428, -0.10150292],
 [ 2.36437092,  1.1093031,   2.24586614, -0.84271466, -0.22288024, -0.17881253],
 [-1.01604035, -0.35012359, -0.84271466,  0.82865489,  0.15732203,  0.18745785],
 [-0.42511447, -0.24096428, -0.22288024,  0.15732203,  0.39335921,  0.24514533],
 [-0.25484018, -0.10150292, -0.17881253,  0.18745785,  0.24514533,  0.44956944]])
print('is positive-definite matrix:', isPD(A))
print(A)
b = np.matrix('1; 2; 3; 4; 5; 6')
print(b)
if A.shape[0] != A.shape[1]:
	print('Матрица A должна быть квадратной')
	exit(0)
if b.shape[0] != n or b.shape[1] != 1:
	print('Вектор-столбец b не правильно задан')
	exit(0)

# 1/2 * (x^T * A * x) + b^T * x
def f(x):
	x = rowToCol(x)
	return (0.5 * (x.transpose() @ A @ x)  + b.transpose() @ x)[0, 0]


# 1/2 * (A + A^T) * x + b
def df(x):
	x = rowToCol(x)
	aa = (A + A.transpose())
	res = 0.5 * aa @ x + 0.5 * b
	return colToRow(res)


# 1/2 * (A + A^T)
def d2f(x):
	return 0.5 * (A + A.transpose())


x0 = np.zeros(n)
print('xo', x0)

res = minimize(f, x0=x0, method='Newton-CG', 
				jac=lambda x: np.ravel(df(x)), hess=d2f,
				options={'xtol': 1e-5})
print('Результат scipy.optimize.minimize')
print('\t message: {}'.format(res['message']))
print('\t success: {}'.format(res['success']))
print('\t fun: {}'.format(res['fun']))
print('\t x: {}'.format(res['x']))
print('\t jac: {}'.format(res['jac']))
print()

ans = gradientDescent(f, df, x0, 1e-6) # 0.3
print('Результат gradientDescent')
for key in ans:
	print('\t {}: {}'.format(key, ans[key]))
print()

ans = newtonMethod(f, df, d2f, x0, 1e-6)
print("Результат newtonMethod")
for key in ans:
	print('\t {}: {}'.format(key, ans[key]))
print()
