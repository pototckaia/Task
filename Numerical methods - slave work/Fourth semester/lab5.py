from math import log10
import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate

class FourierSeries:
	def __init__(self, f, a, b):
		self.f = f
		self.a = a
		self.b = b
		self.period = (b - a)

	def getRes(self, x, n):
		
		cos = lambda x, n: np.cos( 2 * np.pi * n * x / self.period)
		sin = lambda x, n: np.sin(2 * np.pi * n * x / self.period) 

		a_n = lambda x, n: integrate.quad(lambda x: self.f(x) * cos(x, n), self.a, self.a + self.period)[0] * (2  / self.period)  
		b_n = lambda x, n: integrate.quad(lambda x: self.f(x) * sin(x, n), self.a, self.a + self.period)[0] * (2 / self.period)
		
		y = np.array([cos(x, i) * a_n(x, i) + sin(x, i) * b_n(x, i) for i in range(1, n + 1)])

		a_0 = integrate.quad(self.f, self.a, self.a + self.period)[0] * (2 / self.period)

		return a_0 / 2 + y.sum()


a, b = 0, 1
period = (b - a)
f = lambda x: x - np.log10(x + 2)
time = np.linspace(a, b, num=50)
y = f(time)

n = int(input('Колличество шагов'))
f_s = FourierSeries(f, a, b)
y3 = np.array([f_s.getRes(t, n) for t in time])

plt.plot(time, y, label='y = x - log(x+2)')
plt.plot(time, y3, label='ряд Фурье')
plt.title('Разложение функции y в ряд Фурье')
plt.legend();
plt.show()



