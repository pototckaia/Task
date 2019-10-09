from math import log10, log, fabs, factorial
from scipy.optimize import minimize_scalar
import numpy as np
from scipy.misc import derivative

a = 0.5
b = 1.0
dot_1 = 0.52
dot_2 = 0.97
dot_3 = 0.73


def y(x):
	return x - log10(x + 2)


def diff11_y(x, sign=1.0):
	return (-1) * sign * (factorial(10) / (log(10) * pow(x + 2, 11)))


def w(x):
	res = 1
	for i in range(len(knot)):
		res *= (x - knot[i])
	return res


def remainder_11(x, sign=1.0):
	e = 0.5 * (knot[10] - knot[0]) 
	const = -1 / 11 / log(10) / pow(e + 2, 11)
	return sign * const * w(x)


def evaluation(func):
	def wrapper(*args, **kwargs):
		y_dot = func(*args, **kwargs)
		dot = kwargs["dot"] 
		knot = kwargs["knot"]
		
		print("")
		print("Точка", dot)
		print("Вычисленное значение ", y_dot)
		print("Нужное значение", y(dot))

		# min_f = minimize_scalar(
		# 	diff11_y, bounds=(knot[0], knot[10]),
		# 	method='bounded'
		# )

		# max_f = minimize_scalar(
		# 	diff11_y, bounds=(knot[0], knot[10]),
		# 	method='bounded',
		# 	args=(-1.0)
		# )
		# print("Максимальное и минимальное значение производной 11 порядка", -max_f.fun, min_f.fun)

		array = [remainder_11(i) for i in np.arange(0.5, 1, 0.00001)]
		min_r = min(array)
		max_r = max(array)

		r = y_dot - y(dot)
		
		print("Максимальное и минимальное значение остаточного члена", max_r, min_r)
		print("Остаточный член", r)
		print("Неравенство min(R_n)< R_n(z)< max(R_n)")

		if (min_r < r < max_r):
			print("Выполняется")
		else:
			print("Не выполняется")				
		print("")

		return y_dot
	return wrapper


@evaluation
def forward_Newton_polynomial(dot, knot, step, value_knot, finite_diff):
	t = (dot - knot[0]) / step
	if t > 1 or t < 0:
		raise Exception("Invalid date")
	
	y_dot = value_knot[0]
	
	buf_fac = 1
	buf_mul = 1
	for i in range(len(knot) - 1):
		buf_fac *= (i + 1)
		buf_mul *= (t - i)
		y_dot += (buf_mul / buf_fac) * finite_diff[i][0]
	return y_dot


@evaluation
def backward_Newton_polynomial(dot, knot, step, value_knot, finite_diff):
	t = (dot - knot[10]) / step
	if t < -1 or t > 0:
		raise Exception("Invalid date")
	
	y_dot = value_knot[10]
	
	buf_fac = 1
	buf_mul = 1
	for i in range(len(knot) - 1):
		buf_fac *= (i + 1)
		buf_mul *= (t + i)
		y_dot += (buf_mul / buf_fac) * finite_diff[i][-1]
	return y_dot


@evaluation
def backward_Gauss_polynomial(dot, knot, step, value_knot, finite_diff):
	list_of_difs = [abs(dot - x) for x in knot]
	r_index = list_of_difs.index(min(list_of_difs))

	t = (dot - knot[r_index]) / step
	
	if t < -0.5 or t > 0:
		raise Exception("Invalid date")
	
	diff = []

	l = len(knot) - 1
	r = r_index - 1
	for i in range(0, l, 2):
		diff.append(finite_diff[i][r])
		diff.append(finite_diff[i + 1][r])
		r -= 1

	buf_fac = 1
	buf_mul = 1
	m = 1
	y_dot = value_knot[r_index]
	
	for i in range(1, l+1):
		buf_fac *= i
		buf_mul *= t + (-1)**(i) * (i // 2)		
		y_dot += (buf_mul / buf_fac) * diff[i-1]

	return y_dot





count_knot = 11
step = (b - a) / (count_knot - 1)
knot = [a + i * step for i in range(count_knot)]
value_knot = [y(knot[i]) for i in range(count_knot)]

print("Шаг сетки", step)
print("Узлы сетки", knot)
print("Значения функции в узлах", value_knot)
print(" ")


finite_diff = [[] for i in range(count_knot)]
for i in range(1, count_knot):
	finite_diff[0].append(value_knot[i] - value_knot[i - 1])
print("Конечная разность первого порядка", finite_diff[0])

for i in range(1, count_knot - 1):
	for j in range(1, len(finite_diff[i - 1])):
		finite_diff[i].append(finite_diff[i - 1][j] - finite_diff[i - 1][j - 1])
	print("Конечная разность", i + 1, "n-го порядка", finite_diff[i])


print(forward_Newton_polynomial(dot=dot_1, knot=knot, step=step, value_knot=value_knot, finite_diff=finite_diff))
print(backward_Newton_polynomial(dot=dot_2, knot=knot, step=step, value_knot=value_knot, finite_diff=finite_diff))
print(backward_Gauss_polynomial(dot=dot_3, knot=knot, step=step, value_knot=value_knot, finite_diff=finite_diff))
