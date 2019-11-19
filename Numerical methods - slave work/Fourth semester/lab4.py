from math import log10


#  Вариант 8 
class Integral:
	def __init__(self, a, b, f, eps=0.000001):
		self.weight = [1/6, 4/6, 1/6]
		self.eps = eps
		self.f = f
		self.a = a
		self.b = b
		self.count = 2
		

	def itegrate(self):
		count_operation = 10
		segments = [[self.a, self.b]]
		I_n = self.integrating_newton_cotes(self.a, self.b)
		for i in range(count_operation):
			new_segments = []
			I_2n = 0
			for segment in segments:
				median = (segment[-1] + segment[0]) / 2
				I_2n += self.integrating_newton_cotes(segment[0], median)
				I_2n += self.integrating_newton_cotes(median, segment[-1])
				new_segments += [[segment[0], median], [median, segment[-1]]]

			if abs(I_n - I_2n) < self.eps:
				# print('Заданная точность достигнута ', I_2n)
				return I_2n

			segments = new_segments
			I_n = I_2n

		# print('Заданная точность не была достигнута ', I_n)
		return I_n

	def integrating_newton_cotes(self, a, b):
		res = 0
		step = (b - a) / self.count
		nodes = [a + i*step for i in range(self.count + 1)]
		for i in range(len(nodes)):
			res += self.weight[i] * self.f(nodes[i])
		return res * (nodes[-1] - nodes[0])


# print('Задание 4')
# a, b = 0.5, 1.0
# f = lambda x: x - log10(x + 2)
# eps = float(input('Введите точность '))
# print('Интеграл:', Integral(a, b, f, eps).itegrate())
# print('______________')