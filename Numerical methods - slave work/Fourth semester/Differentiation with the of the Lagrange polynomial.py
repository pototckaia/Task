from math import log, log10, factorial, floor, fabs
from itertools import product
from functools import reduce
from scipy.optimize import minimize_scalar
import numpy as nm
import matplotlib.pyplot as plt

a = 0.5
b = 0.7
dot = 0.5


count_knot = 5
step = (b - a) / (count_knot - 1)
# 		0		1	2	3		4
knot = [0.5, 0.55, 0.6, 0.65, 0.7]
knot = [a + i * step for i in range(count_knot)]

def y(x):
	"""Заданная функция."""

	return x - log10(x + 2)

def diff2_y(x):
	"""Производная втрого порядка от заданной функции."""

	return 1 / log(10) / ((x + 2) ** (2))

def diffn_y(x, n):
	"""Производная третьего порядка и выше"""

	return (-1)**(n) * factorial(n - 1) / (x + 2)**(n) / log(10)


def comb(n, k):
    """Генерация сочетаний из `n` по `k` без повторений."""

    d = list(range(0, k))
    yield d

    while True:
        i = k - 1
        while i >= 0 and d[i] + k - i + 1 > n:
            i -= 1
        if i < 0:
            return

        d[i] += 1
        for j in range(i + 1, k):
            d[j] = d[j - 1] + 1

        yield d

def comb_sets(sets, m):
    """Генерация сочетаний из элементов множеств `sets` по `m` элементов."""

    for ci in comb(len(sets), m):
        yield list(map(lambda x: sets[x], ci))



def p_diff2(x, i):
	""" `i` полином для производной 2 порядка интерполяцонной формулы Лагранжа четвертого порядка"""   

	count = floor(factorial(count_knot - 1) / 2 / factorial(count_knot - 3))
	comb_set_ = [knot[j] for j in range(count_knot) if i != j]
	
	res = 0
	for x_i, x_j in comb_sets(comb_set_, 2):
		res += 2 * (x - x_i) * (x - x_j)

	return res

def diff2_L(x):
	""" Производная второго порядка для интерполяционной формулы Лагранжа четвертого порядка"""

	coeff = [24.0, -6.0, 4.0, -6.0, 24.0]
	step_pow = step ** (count_knot - 1)

	derivative = 0
	for i in range(count_knot):
		const = coeff[i] * step_pow
		derivative += (y(knot[i]) * p_diff2(x, i)) / const 

	return derivative


def w(x, set):
	return reduce(lambda x, y: x * y, map(lambda k: x - k, set))

def diff_w(x, set):
	res = sum(w(x, ci) for ci in comb_sets(set, count_knot - 1))
	return res

def diff2_w(x, set):
	res = sum(2 * w(x, ci) for ci in comb_sets(set, count_knot - 2))
	return res

def R(x):
	"""Остаточный член R_{4, 2} для производной второго порядка формулы Лагранжа четвертого порядка"""

	w_ = w(x, knot)
	e = (a + b) / 2
	res = w_ * diffn_y(e, count_knot + 2) / factorial(count_knot + 2)

	res += (diff_w(x, knot) * diffn_y(e, count_knot + 1)) / factorial(count_knot + 1)
	res += (diff2_w(x, knot) * diffn_y(e, count_knot)) / factorial(count_knot)
	return res

def plot_(y, a, b):
	t = nm.linspace(a, b, 1000)
	y = list(map(lambda x: y(x), t))
	plt.plot(t, y,  'g', label='y(x)')

	# plt.axis([a, b, -1, 1])  # задание [xmin, xmax, ymin, ymax]
	plt.xlabel('x')    # обозначение оси абсцисс
	plt.ylabel('y')    # обозначение оси ординат
	plt.title('Остаточный член R(x)')  # название графика
	plt.legend()       # вставка легенды (текста в label)

	plt.show()

def appraisal(y):
	"""Оценка минимального и максимально значения функции `y`."""
	t = nm.linspace(a, b, 100)
	y_ = list(map(lambda x: y(x), t))

	# min_r = minimize_scalar(y, bounds=(a, b), method='bounded')
	# max_r = minimize_scalar(lambda x: -y(x), bounds=(a, b),method='bounded')
	
	print("Минимальное значение функции",  min(y_))
	print("Максимальное значение функции", max(y_))
	
	# return min_r.fun, -max_r.fun
	return min(y_), max(y_)

y_dot = diff2_y(dot)
L_dot = diff2_L(dot) 

print("Точное значение", y_dot)
print("Вычисленное значение", L_dot) 
print("Ошибка вычисления", fabs(y_dot - L_dot))

min_r, max_r = appraisal(R)
r = L_dot - y_dot 
# plot_(R, a, b)
print("Условие min(R_{n,k})<R_{n,k}(x)< max(R_{n,k})", min_r < r < max_r)
