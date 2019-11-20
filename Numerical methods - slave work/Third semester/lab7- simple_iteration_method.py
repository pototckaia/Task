from math import fabs

a = [
[10.9, 1.2, 2.1, 0.9, -7],
[1.2, 11.2, 1.5, 2.5, 5.3],
[2.1, 1.5, 9.8, 1.3, 10.3],
[0.9, 2.5, 1.3, 12.1, 24.6]]

n = 4
for i in range(0, n):
	c = a[i][i]
	for j in range(0, n):
		a[i][j] = - a[i][j] / c
	a[i][n] /= c
	a[i][i] = 0.0

e = 10**(-5)
x = [row[n] for row in a]
norm = 1
print(a) 

while norm > e:
	y = x[:]
	for i in range(0, n):
		summ = a[i][n]
		for j in range(0, n):
			summ += a[i][j] * x[j]
		y[i] = summ

	sub = []
	for i in range(0, n):
		sub.append(fabs(y[i] - x[i])) 

	norm = sum(sub)
	x = y[:]
	print(x)

for i, coord in enumerate(x):
	print('x{0}  = {1: .7f}'.format(i, coord))