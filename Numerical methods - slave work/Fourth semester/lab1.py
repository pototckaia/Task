from math import log10, log, fabs
from scipy.optimize import minimize_scalar


a = 0.5
b = 1.0
dot = 0.72


def y(x):
	return x - log10(x + 2)


def diff2_y(x, sign=1.0):
	return sign/(log(10) * pow(x + 2, 2))


def diff3_y(x, sign=1.0):
	return (-1) * sign / (log(10) * pow(x + 2, 3))


count_knot = 11
step = (b - a) / (count_knot - 1)
knot = [a + i * step for i in range(count_knot)]
value_knot = [y(knot[i]) for i in range(count_knot)]

print("Шаг сетки", step)
print("Узлы сетки", knot)
print("Значения функции в узлах", value_knot)
print(" ")


def monomial2(x, y, z):
	return (x - y) / (z - y)


def remainder1(x, begin, end, sign=1.0):
	"""Возвращает остаточный член интерполяционной формулы Лагранжа первого порядка."""
	e = (begin + end) * 0.5
	return sign * 0.5 * diff2_y(e) * (x - begin) * (x - end)


epsilon1 = 10**(-4)
epsilon2 = 10**(-5)
print("Первый порядок")
for i in range(count_knot - 1):
	#По интерполяционной формуле Лагранжа первого порядка вычисляется значение y(dot) = y_dot
	if knot[i] > dot:
		break;
	n_i = i
	x_j = knot[i+1]
	n_j = i + 1
	while(x_j < dot):
		x_j  = knot[n_j]
		n_j += 1

	y_dot = value_knot[n_i] * monomial2(dot, knot[n_j], knot[n_i])
	y_dot += value_knot[n_j] * monomial2(dot, knot[n_i], knot[n_j])

	print("Используя две точки:", knot[n_i], knot[n_j], " L1(x*)=", y_dot)

	max_r = minimize_scalar(
		remainder1, bounds=(knot[n_i], knot[n_j]),
		method='bounded',
		args=(knot[n_i], knot[n_j], -1.0)
	)
	print("Максимум R(x) ", -1 * max_r.fun, "x= ", max_r.x)

	min_r = minimize_scalar(
		remainder1, bounds=(knot[n_i], knot[n_j]),
		method='bounded',
		args=(knot[n_i], knot[n_j])
	)
	print("Минимум R(x) ", min_r.fun, "x= ", min_r.x)

	r_dot = remainder1(dot, knot[n_i], knot[n_j])
	print("min R1 = " , min_r.fun, "R1(x*) = ", r_dot, "max R1 = ", -1 * max_r.fun)
	if min_r.fun < r_dot < (-1 * max_r.fun):
		print("Yes. minR1 < R1(x∗) < maxR1")
	else:
		print("Non")

	r_diff = fabs(y_dot - y(dot))
	print("|L1(x*) - f(x*)| = ", r_diff, "R1(x*) = ", r_dot, "Отличаюься на ", fabs(r_diff - r_dot))

	if epsilon1 > r_diff:
		print("Yes. Обеспечивается погрешность, не превосходящая 10−4")
	else:
		print("Non")

	print("")



def remainder2(x, x1, x2, x3, sign=1.0):
	"""Возвращает остаточный член интерполяционной формулы Лагранжа первого порядка."""
	e = (x1 + x2 + x3) / 3
	return sign * (1/6) * diff3_y(e) * (x - x1) * (x - x2) * (x - x3)


print("Второй порядок")
for i in range(count_knot - 2):
	# По интерполяционной формуле Лагранжа второго порядка вычисляется значение y(dot) = y_dot
	if knot[i] > dot:
		break;
	n_i = i
	x_j = knot[i+1]
	n_j = i + 1
	while(x_j < dot):
		x_j  = knot[n_j]
		n_j += 1
	if (n_j == count_knot - 2):
		break
	n_k = n_j + 1

	y_dot = value_knot[n_i] * monomial2(dot, knot[n_j], knot[n_i]) * monomial2(dot, knot[n_k], knot[n_i])
	y_dot += value_knot[n_j] * monomial2(dot, knot[n_i], knot[n_j]) * monomial2(dot, knot[n_k], knot[n_j])
	y_dot += value_knot[n_k] * monomial2(dot, knot[n_i], knot[n_k]) * monomial2(dot, knot[n_j], knot[n_k])

	print("Используя три точки:", knot[n_i], knot[n_j], knot[n_k], " L1(x*)=", y_dot)

	max_r = minimize_scalar(
		remainder2, bounds=(knot[n_i], knot[n_k]),
		method='bounded',
		args=(knot[n_i], knot[n_j], knot[n_k], -1.0)
	)
	print("Максимум R(x) ", -1 * max_r.fun, "x= ", max_r.x)

	min_r = minimize_scalar(
		remainder2, bounds=(knot[n_i], knot[n_k]),
		method='bounded',
		args=(knot[n_i], knot[n_j], knot[n_k])
	)
	print("Минимум R(x) на [a, b]", min_r.fun, "x= ", min_r.x)

	r_dot = remainder2(dot, knot[n_i], knot[n_j], knot[n_k])
	print("min R1 = ", min_r.fun, "R1(x*) = ", r_dot, "max R1 = ", -1 * max_r.fun)
	if min_r.fun < r_dot < (-1 * max_r.fun):
		print("Yes. minR1 < R1(x∗) < maxR1")
	else:
		print("Non")

	r_diff = fabs(y_dot - y(dot))
	print("|L1(x*) - f(x*)| = ", r_diff, "R1(x*) = ", r_dot, "Отличаюься н ", fabs(r_diff - r_dot))
	if epsilon2 > r_diff:
		print("Yes. Обеспечивается погрешность, не превосходящая 10−5")
	else:
		print("Non")
	print("")


