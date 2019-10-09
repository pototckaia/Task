import sympy as sy
import numpy as np
from matplotlib import pyplot as plt

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

def plot(dots, exactSolution, approxSolution, title):
	plt.plot(dots, exactSolution, 'g-', label='Точное решение')
	plt.plot(dots, approxSolution, 'b-', label='Численное решения')
	plt.legend(loc=9)
	plt.title(title)
	plt.grid(True)
	plt.show()

x = sy.Symbol('x', integer=True, positive=True)

L = lambda u: u.diff(x, 2) + (sy.S(3)/2 * u.diff(x)) / (x + 1) - (x + 1) * u
f = -2*sy.sqrt(x+1) + x + 1
correctSolution = lambda i: 2 / np.sqrt(i + 1) - 1

a, b = 0, 1
c1, c2 = sy.S(2), -2**(sy.S(-3)/2)  
l_a = lambda u: u.subs(x, a) - u.diff(x).subs(x, a)
l_b = lambda u: u.diff(x).subs(x, b)

X = np.linspace(a, b, num=100)

c2_s = 2**(sy.S(-3)/2)
basis = []
basis.append(-c2_s * x + 2 - c2_s)
basis.append(-x*x + 2 * x + 2)
basis.append(-x*x*x + x*x + x + 1)
basis.append(-(sy.S(1)/4)*x**4 + x**3 - x**2)
x_c = [sy.S(1)/4, sy.S(1)/2, sy.S(3)/4]

checkBasis(basis, l_a, l_b, c1, c2)

approxSolution1 = Galerkina(basis, L, f, x, a, b)
approxSolution2 = Collocation(basis, L, f, x_c)

plot(X, correctSolution(X), [approxSolution1(i) for i in X], 'Метод Галеркина')
plot(X, correctSolution(X), [approxSolution2(i) for i in X], 'Метод коллокации')

print("Ошибка Галеркина")
print(np.max(np.abs(correctSolution(X) - [approxSolution1(i) for i in X])))

print("Ошибка коллокации")
print(np.max(np.abs(correctSolution(X) - [approxSolution2(i) for i in X])))

# facor - собрать в скобки
#  expand расскрыть скобки 
# collect - собрать коэффициенты
# cancel - общий знаменатель
# apart - разложение дробей
# simplify -  упростьть 
