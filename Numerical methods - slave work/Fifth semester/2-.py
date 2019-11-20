import numpy as np
from matplotlib import pyplot as plt


def rungeKuttIteration(step, xi, yi, derivative):
	k1 = derivative(xi, yi)
	k2 = derivative(xi + 0.25 * step, yi + 0.25 * step * k1)
	k3 = derivative(xi + 0.5 * step, yi + 0.5 * step * k2)
	k4 = derivative(xi + step, yi + step * (k1 - 2 * k2 + 2 * k3))
	return yi + (1/6) * step * (k1 + 4 * k3 + k4)

def accuracy(x, sol, approxi):
	E = 0
	L = []
	for i in range(len(approxi)):
		L.append(abs(solution(x[i]) - approxi[i]))
		E = max(E, L[i])

	return L, E

class Adam:
	def obviousAdam(self, x, y_0, f, h):
		sol = [y_0, ]
		for i in range(0, 2):
			sol.append(sol[i] + h * f(x[i], sol[i]))

		for i in range(3, len(x)):
			I = h / 12 * (23 * f(x[i - 1], sol[i - 1]) - 16 * f(x[i - 2], sol[i - 2]) + 5 * f(x[i - 3], sol[i - 3]))
			sol.append(sol[i - 1] + I)
		return sol


	def implicitAdam(self, x, y_0, f, h):
		sol = [y_0, y_0 + h * f(x[0], y_0), ]

		for i in range(1, len(x) - 1):
			d = 1 + (5/12) * (h/x[i + 1])
			y_i = sol[i] + (1/12) * h * (10 * np.exp(x[i + 1]**2) + 8 * f(x[i], sol[i]) - f(x[i - 1], sol[i - 1]))
			sol.append(y_i / d)
		return sol

if __name__ == "__main__":

	f = lambda x_, y_: 2 * np.exp(x_ * x_) - y_ / x_
	solution = lambda x_: np.exp(x_ * x_) / x_

	x_0, x_n = 1, 2
	h = 0.1

	x = [i for i in np.arange(x_0, x_n + h, h)]
	y_0 = np.exp(1)

	methAdam = Adam()

	with open('obviousAdam.table', 'w') as fout_o, open('implicitAdam.table', 'w') as fout_i:
		approxi_o = methAdam.obviousAdam(x, y_0, f, h)
		L_o, E_o = accuracy(x, solution, approxi_o)
		approxi_i = methAdam.implicitAdam(x, y_0, f, h)
		L_i, E_i = accuracy(x, solution, approxi_i)

		for i in range(len(x)):
			fout_o.write('{:^10.4} {:^10.6} {:^10.6} {:^10.6}\n'.format(x[i], approxi_o[i], solution(x[i]), L_o[i]))
			fout_i.write('{:^10.4} {:^10.6} {:^10.6} {:^10.6}\n'.format(x[i], approxi_i[i], solution(x[i]), L_i[i]))

		fout_o.write('{:10.6}'.format(E_o))
		fout_i.write('{:10.6}'.format(E_i))

		Y = []
		for i in x:
			Y.append(solution(i))

		plt.plot(x, Y, 'g-', label='Точное решение')
		plt.plot(x, approxi_o, 'b-', label='явный метод Адамса-Бешфорта')
		plt.plot(x, approxi_i, 'r-', label=' неявный метод Адамса-Моултона')
		plt.legend(loc=9)
		plt.title('методы Адамса')
		plt.grid(True)
		plt.show()

		plt.plot(x, L_o, 'g-', label='явный метод Адамса-Бешфорта')
		plt.plot(x, L_i, 'b-', label=' неявный метод Адамса-Моултона')
		plt.legend(loc=9)
		plt.title('Локальная погрешность')
		plt.grid(True)
		plt.show()

