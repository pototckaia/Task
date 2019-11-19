from math import log10, log
import numpy as np
import matplotlib.pyplot as plt
from scipy.misc import derivative
import sympy as sympy

def chord(a, b, f, d2f, eps) :
	x_i, x_0, dx = 0, 0, 1

	# определяем с какого конца начать поиск
	if f(a) * d2f(a) < 0:
		x_i = a
	elif f(b) * d2f(b) < 0:
		x_i = b

	if f(a) * d2f(a) > 0:
		x_0 = a
	elif f(b) * d2f(b) > 0:
		x_0 = b

	step = 0
	while abs(dx) > eps:
		dx = f(x_i)*(x_i - x_0) / (f(x_i) - f(x_0))
		x_0 = x_i
		x_i -= dx
		step += 1
	print("Количество итераций", step)

	return x_i

def tanget(a, b, f, df, d2f, eps):
	x, dx = 0, 1

	if f(a) * d2f(a) > 0:
		x = a
	elif f(b) * d2f(b) > 0:
		x = b

	step = 0
	while abs(dx) > eps:
		dx = f(x) / df(x)
		x -= dx
		step += 1
	print("Количество итераций", step)
		
	return x 

a = -1
b = 1
eps = 0.00000000001

f = lambda x: 2 * x * x - np.cos(2 * x)
df = lambda x: 2 * x + 2 * np.sin(2 * x)
d2f = lambda x: 2  + 4 * np.cos(2 * x)

a_0, b_0 = -1.0, 0.0
a_1, b_1 = 0.0, 1.0

x_1 = chord(a_0, b_0, f, d2f, eps)
x_2 = chord(a_1, b_1, f, d2f, eps)


print(x_1, f(x_1))
print(x_2, f(x_2))

x_1 = tanget(a_0, b_0, f, df, d2f, eps)
x_2 = tanget(a_1, b_1, f, df, d2f, eps)


print(x_1, f(x_1))
print(x_2, f(x_2))
# print(sympy.solve('x**2-cos(2*x)'))
# 
# t = np.linspace(-0.515, -0.510, 100)
# plt.plot(t, f(t),  'g', color='red')
# plt.xlabel('x')    # обозначение оси абсцисс
# plt.ylabel('y')    # обозначение оси ординат
# plt.grid(True)
# plt.show()
