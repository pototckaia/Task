import numpy as np
import Plot as p

a = 2

def f(x, t):
   return x + t

def ux0(t):
   return np.exp(-t)

def ut0(x):
   return np.cos(np.pi * x)

def accountScheme(x, t):
	h = abs(x[0]-x[1])
	r = abs(t[0]-t[1])

	res = np.zeros((len(t), len(x)))
	res_up = np.zeros((len(t), len(x)))
	for n in range(len(x)):
		res[0][n] = ut0(x[n]) # n -> x = i
		res_up[0][n] = ut0(x[n]) # n -> x = i
	for j in range(len(t)):
		res[j][0] = ux0(t[j]) # j -> t = j
		res_up[j][0] = ux0(t[j]) # j -> t = j

	t1 = (1 / 2 / r)
	t2 = (1 / h)
	for j in range(len(t)-1):
		for i in range(len(x)-2):
			fij = f(x[i], t[j])
			res_up[j+1][i] = res_up[j][i] - (r/h)*(res_up[j][i] - a * res_up[j][i-1]) + r * fij
			
			uij = f(x[i] + 0.5 * h, t[j] + 0.5 * r)
			uij = uij + (t2-t1)*res[j+1][i] + (t1 + t2)*res[j][i] + (t1 - t2)*res[j][i+1]
			uij = uij / (t1 + t2)
			res[j+1][i+1] = uij

	return res, res_up

def plt(u, x, t, title):
	plot = p.Plot()
	for j in range(0, len(t), int(len(t)/7)):
		plot.add(x, uApp[:][j], 't = {:^2.2}'.format(t[j]))
	plot.show(title)


x = np.linspace(0, 1, num=350)
t = np.linspace(0, 1, num=50)
uApp, uApp_up = accountScheme(x, t)
print(x)
print(uApp)
plt(uApp, x, t, 'Метод прямоугольника')
plt(uApp_up, x, t, 'Метод центральных разностей')
