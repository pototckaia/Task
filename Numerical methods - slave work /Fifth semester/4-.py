import sympy as sy
import numpy as np
import Plot as plt

# Для решения уравнения d2y = f(x, y, dy)
# Оно преобразуется в систему дифференциальных уравнений
# z = dy, dz = f(x, y, z)
def oneStepSolution(xSample, initCondition, f, correction):
	points = [initCondition[1], ]
	h = abs(xSample[0] - xSample[1])

	x_prev = initCondition[0]
	y_prev = initCondition[1]
	z_prev = initCondition[2]
	for x_i in xSample[1:]:
		yCorrection, zCorrection = correction(x_prev, y_prev, z_prev, h, f)
		y_prev = y_prev + yCorrection
		z_prev = z_prev + zCorrection
		x_prev = x_i
		points.append(y_prev)

	return np.array(points)

def rungeKuttCorrection(xi, yi, zi, step, f):
	di = f(xi, yi, zi)

	x0 = xi + (1/3) * step
	y0 = yi + (1/3) * step * zi
	z0 = zi + (1/3) * step * di
	diff_y = step * zi + (1/2) * step**2 * f(x0, y0, z0)

	x1 = xi + (2/3) * step
	y1 = yi + (2/3) * step * zi + (2/9) * step**2 * di
	z1 = zi + (2/3) * step * f(x0, y0, z0)
	diff_z = (1/4) * step * di + (3/4) * step * f(x1, y1, z1)

	return diff_y, diff_z

def shooting(xSample, xInit, yInit, f, z):
	t_prev = 0
	if 	not (xInit[0] - xInit[1] == 0):
		t_prev = (yInit[0] - yInit[0]) / (xInit[0] - xInit[1])
	eps = 0.00000001

	while True:
		initY = xInit[0], yInit[0], t_prev
		initZ = xInit[0], 0, 1

		y_ = oneStepSolution(xSample, initY, f, rungeKuttCorrection)
		z_ = oneStepSolution(xSample, initZ, z, rungeKuttCorrection)
		y_b = y_[-1]
		t_new = t_prev - (y_b - yInit[1]) / z_[-1]

		if (abs(t_new - t_prev) < eps):
			return y_

		t_prev = t_new

def approx(x, basis, C):
	n = len(basis)
	Ci = sy.symbols("Ci0:{0}".format(n-1))
	u = basis[0] + sum(Ci[k]*basis[k + 1] for k in range(n-1))
	for i in range(len(Ci)):
		u = u.subs(Ci[i], C[i])
	return sy.lambdify(x, u)

def checkBasis(u, l_a, l_b, c1, c2):
	if l_a(u[0]) != c1 or l_b(u[0]) != c2:
		raise ValueError("Basis function wrong")
	for ui in u[1:]:
		if l_a(ui) != sy.S(0) or l_b(ui) != sy.S(0):
			raise ValueError("Basis function wrong")

def Galerkina(basis, L, f, x, a, b):
	n = len(basis)
	Ly = [L(y) for y in basis]
	d = [sy.integrate(sy.expand(basis[j + 1] * (f - Ly[0])), (x, a, b)) for j in range(n - 1)]
	A = sy.Matrix(n - 1, n - 1, lambda i, j: sy.integrate(basis[i + 1] * Ly[j + 1], (x, a, b)))
	C = A.LUsolve(sy.Matrix(d))
	return approx(x, basis, C)


def Collocation(basis, L, f, x_c):
	n = len(basis)
	Ly = [L(y) for y in basis]
	d = [(f - Ly[0]).subs(x, xi) for xi in x_c]
	A = sy.Matrix(n - 1, n - 1, lambda i, j: Ly[j + 1].subs(x, x_c[i]))
	C = A.LUsolve(sy.Matrix(d))
	return approx(x, basis, C)

def Moments(basis, L, f, w, x, a, b):
	n = len(basis)
	Ly = [L(y) for y in basis]
	d = [sy.integrate(sy.expand(wi * (f - Ly[0])), (x, a, b)) for wi in w]
	A = sy.Matrix(n - 1, n - 1, lambda i, j: sy.integrate(w[i] * Ly[j + 1], (x, a, b)))
	C = A.LUsolve(sy.Matrix(d))
	return approx(x, basis, C)

def LeastSquare(basis, L, f, x, a, b):
	n = len(basis)
	w = [L(y) for y in basis[1:]]
	return Moments(basis, L, f, w, x, a, b)

x = sy.Symbol('x', integer=True, positive=True)

L = lambda u: u.diff(x, 2) + u
f = -sy.S(1)
correctSolution = lambda i: - 1 + np.cos(i) + np.sin(i) * np.tan(1/2)

a, b = 0, 1
c1, c2 = sy.S(0), sy.S(0)  
l_a = lambda u: u.subs(x, a)
l_b = lambda u: u.subs(x, b)

X = np.linspace(a, b, num=50)

basis = []
basis.append(sy.S(0))
basis.append(x*(1-x))
basis.append(x*x*(1-x))
basis.append(x*x*x*(1-x))
x_c = [sy.S(1)/4, sy.S(1)/2, sy.S(3)/4]

w = []
w.append(x**4*(1-x))
w.append(x**5*(1-x))
w.append(x**6*(1-x))

c, d = 0, 0
approxSolution5 = shooting(X, (a, c), (c, d), lambda x, y, dy: - 1 - y, lambda x, y, dy: -y)

checkBasis(basis, l_a, l_b, c1, c2)

approxSolution1 = Galerkina(basis, L, f, x, a, b)
approxSolution2 = Collocation(basis, L, f, x_c)
approxSolution3 = LeastSquare(basis, L, f, x, a, b)
approxSolution4 = Moments(basis, L, f, w, x, a, b)

plot = plt.Plot()
plot.add(X, correctSolution(X), 'Точное решение')
plot.add(X, [approxSolution1(i) for i in X], 'Метод Галеркина')
plot.add(X, [approxSolution2(i) for i in X], 'Метод коллокации')
plot.add(X, [approxSolution3(i) for i in X], 'Метод наименьших квадратов')
plot.add(X, [approxSolution4(i) for i in X], 'Метод моментов')
plot.add(X, approxSolution5, 'Метод Cтрельбы')
plot.show('Сравнение методов')


plot.add(X, np.abs(correctSolution(X) - [approxSolution1(i) for i in X]), 'Метод Галеркина')
plot.add(X, np.abs(correctSolution(X) - [approxSolution2(i) for i in X]), 'Метод коллокации')
plot.add(X, np.abs(correctSolution(X) - [approxSolution3(i) for i in X]), 'Метод наименьших квадратов')
plot.add(X, np.abs(correctSolution(X) - [approxSolution4(i) for i in X]), 'Метод моментов')
plot.add(X, np.abs(correctSolution(X) - approxSolution5), 'Метод Cтрельбы')
plot.show('Сравнение методов погрешность')

print(X)

print("Ошибка Галеркина")
print(np.max(np.abs(correctSolution(X) - [approxSolution1(i) for i in X])))

print("Ошибка коллокации")
print(np.max(np.abs(correctSolution(X) - [approxSolution2(i) for i in X])))

print("Ошибка метода наименьших квадратов")
print(np.max(np.abs(correctSolution(X) - [approxSolution3(i) for i in X])))

print("Ошибка метода моментов")
print(np.max(np.abs(correctSolution(X) - [approxSolution4(i) for i in X])))

print(np.max(np.abs(correctSolution(X) - approxSolution5)))

# facor - собрать в скобки
#  expand расскрыть скобки 
# collect - собрать коэффициенты
# cancel - общий знаменатель
# apart - разложение дробей
# simplify -  упростьть 
