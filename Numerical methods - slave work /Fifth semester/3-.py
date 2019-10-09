import numpy as np

from scipy.integrate import odeint
import matplotlib.pyplot as plt

der_y = lambda x, y: x * x - 2 * y
f_y_true = lambda x: 0.75 * np.exp(-2 * x) + 0.5 * x * x - 0.5 * x + 0.25 

x_0 = 0
y_0 = 1.0
h = 0.1
x_n = 1.0
x = np.arange(x_0, x_n + h, h)

# Одношаговый метод
def one_step(step, dots, yStart, derivative, iteration):
  points = [yStart, ]
  xPrev = dots[0]
  yPrev = yStart
  for xi in dots[1::]:
    yPrev = iteration(step, xPrev, yPrev, derivative)
    xPrev = xi
    points.append(yPrev)

  return points

#для метода Эйлера
def eulerIteration(step, xi, yi, derivative):
  return yi + step * derivative(xi, yi)

# для усовершеннствованного метода Эйлера
def improvedEulerIteration(step, xi, yi, derivative):
  k1 = derivative(xi, yi)
  k2 = derivative(xi + 0.5 * step, yi + 0.5 * step * k1)
  return yi + step * k2

# для метода Ранге-Кутты 4-го порядка
def rungeKuttIteration(step, xi, yi, derivative):
  k1 = derivative(xi, yi)
  k2 = derivative(xi + 0.25 * step, yi + 0.25 * step * k1)
  k3 = derivative(xi + 0.5 * step, yi + 0.5 * step * k2)
  k4 = derivative(xi + step, yi + step * (k1 - 2 * k2 + 2 * k3))
  return yi + (1/6) * step * (k1 + 4 * k3 + k4)

def plot_(x_interval, y_true, y_1, y_2, y_4):
	fig = plt.figure(facecolor='white')
	plt.plot(x_interval, y_true, '-o', linewidth=1, label='Tочное решение')
	plt.plot(x_interval, y_1, '-o', linewidth=1, label='Метод Эйлера')
	plt.plot(x_interval, y_2, '-o', linewidth=1, label='Усовершенствованный метод Эйлера')
	plt.plot(x_interval, y_4, '-o', linewidth=1, label='Классический метод Рунге-Кутта 4-го порядка')
	plt.legend(loc='upper right')
	plt.ylabel('y')
	plt.xlabel('x')
	plt.grid(True)
	plt.show() # display	

# локальная ошибка дискретизации
def L(h, x, y, f, l):
	return abs((y(x + h) - y(x)) / h - l(h, x, y(x), f))


y_1 = one_step(h, x, y_0, der_y, eulerIteration)
y_2 = one_step(h, x, y_0, der_y, improvedEulerIteration)
y_4 = one_step(h, x, y_0, der_y, rungeKuttIteration)


# y_true = odeint(der_y, y_0, x_interval)
# y_true = nm.array(y_true).flatten()
y_true = f_y_true(x)

plot_(x, y_true, y_1, y_2, y_4)

# print('_____________________________________________________________________________________________')
# print('|  x_i   |     y*    |    y_1   |    e_1    |    y_2    |    e_2    |    y_4    |    e_4    |')

# E_1 = 0 
# E_2 = 0
# E_4 = 0
# for x_i, y_1, y_2, y_4, y_true in zip(x_interval, y_1, y_2, y_4, y_true):
# 	print('|{0:^8f}|{1:^11f}|{2:^10f}|{3:^11f}|{4:^11f}|{5:^11f}|{6:^11f}|{7:^11f}|'
