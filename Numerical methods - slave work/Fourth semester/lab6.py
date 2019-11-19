from math import log10, log
import numpy as np
import matplotlib.pyplot as plt
from scipy.misc import derivative

shap = (0.5, 1)
f = lambda x : x * x - np.log10(0.5 * x)
f_2 = lambda x : 2 + 1.0 / (x * x * np.log(10)) 

count_knot = 11
step = (shap[-1] - shap[0]) / (count_knot - 1)
knot = [shap[0] + i * step for i in range(count_knot)]
knot = np.array(knot)
value_knot = [f(knot[i]) for i in range(count_knot)]
print(knot)

def S(x, knot, value_knot, m, step):
	res = 0
	i = 0
	if x <= knot[0]:
		i = 0;
	elif x >= knot[-1]:
		i = len(knot) - 2
	else:
		left , right = 0, len(knot) - 1
		while left + 1 < right :
			med = left + (right - left) // 2
			if x <= knot[med]:
				right = med
			else:
				left = med
		i = left

	c = (value_knot[i + 1] - value_knot[i]) / step 
	c -= (step / 6) * (2*m[i] + m[i + 1])
	a = m[i]
	b = (m[i + 1] - m[i]) / step
	res = f(knot[i]) + c * (x - knot[i]) 
	res += a * (x - knot[i]) * (x - knot[i]) * 0.5
	res += b * (x - knot[i]) * (x - knot[i]) * (x - knot[i]) * (1/6)
	
	return res


def solve(mat, b):
	n = len(b)


	alpha[0] = 0
	beta[0] = 0
	for i in range(1, n-1):
		
		print('deg', z)
		alpha[i] = - mat[i - 1][i] / z
		beta[i] = (b[i - 1] - beta[i - 1] * mat[i - 1][i - 2]) / z
	
	x[-1] = (b[-1] - beta[-1] * mat[-1][-2]) / (mat[-1][-1] + alpha[-1] * mat[-1][-2])
	for i in range(n-2, 0, -1):
		x[i] = alpha[i + 1] * x[i + 1] + beta[i + 1]
	return x

r = (len(knot), len(knot))
mat = np.zeros(r)
b = np.zeros(len(knot))
m = np.zeros(len(knot))

for i in range(0, count_knot-1):
	b[i] = 3 * (value_knot[i + 1] - 2*value_knot[i] + value_knot[i - 1]) / step / step
b[-1] = 3 * (value_knot[-1] - 2*value_knot[-2] + value_knot[-3]) / step / step

alpha = np.zeros(len(knot))
beta = np.zeros(len(knot))
A, B, C = 0, 0, 3
for i in range(1, count_knot-1):
	A = 0.5
	B = 2
	C = 0.5
	F = b[i]
	z = alpha[i - 1] * A + B
	alpha[i] = -C / z
	beta[i] = (F - beta[i - 1] * A) / z
A, B = 0, 3
m[-1] = (b[-1] - beta[-1] * A) / (B + alpha[-1] * A)
for i in range(len(knot)-2, 0, -1):
	m[i] = alpha[i + 1] * m[i + 1] + beta[i + 1]

# for i in range(0, count_knot-1):
# 	b[i] = 3 * (value_knot[i + 1] - 2*value_knot[i] + value_knot[i - 1]) / step / step
# b[-1] = 3 * (value_knot[-1] - 2*value_knot[-2] + value_knot[-3]) / step / step

# mat[0][1] = 3.0
# for i in range(1, count_knot-1):
# 	mat[i][i - 1] = 0.5
# 	mat[i][i] = 2
# 	mat[i][i + 1] = 0.5	
# mat[-1][-2] = 3.0

print(mat)
print(b)
""" Вычисление вторых производных"""
# m = np.linalg.solve(mat, b)
# m = solve(mat, b)
m_true = f_2(knot)
print('Значение производных', m)
print('Значение производных истинное', m_true)


count_plot_dot = 100
t = np.linspace(shap[0], shap[-1], count_plot_dot)
y =  f(t)
l = [S(x, knot, value_knot, m, step) for x in t]

plt.plot(t, y,  'g', label='x^2 - lg(0.5*x)')
plt.plot(t, l, 'b--', label='L1(x)')
plt.xlabel('x')    # обозначение оси абсцисс
plt.ylabel('y')    # обозначение оси ординат
plt.title('Интерполирование функции ')  # название графика
plt.legend()       # вставка легенды (текста в label)
plt.show()