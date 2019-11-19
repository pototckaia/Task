n = 7
a = [
[5, 4, 7, 5, 6, 7, 5],
[4, 12, 8, 7, 8, 8, 6],
[7, 8, 10, 9, 8, 7, 7],
[5, 7, 9, 11, 9, 7, 5],
[6, 8, 8, 9, 10, 8, 9],
[7, 8, 7, 7, 8, 10, 10],
[5, 6, 7, 5, 9, 10, 10],
]

b = [1, 1, 1, 1, 1, 1, 1]
lu = [[0] * (n) for i in range(0, n)]



for i in range(0, n): 
	for j in range(i, n):
		summ = 0
		for k in range(0, i):
			summ += lu[i][k] * lu[k][j]
		lu[i][j] = a[i][j] - summ
		if j == i:
			continue
		summ = 0
		for k in range(0, i):
			summ += lu[j][k] * lu[k][i]
		lu[j][i] = (a[j][i] - summ) / lu[i][i]

l = ''
u = ''
for i in range(0, n):
	for j in range(0, n):
		l += str(lu[i][j] if i > j else 1 if (i == j) else 0) + '\t'
		u += str(0 if i > j else lu[i][j]) + '\t'
	l += '\n'
	u += '\n'

print(l)
print(u)

y = [0 for i in range(0, n)]

for i in range(0, n):
	matsum = 0
	for k in range(0, i):
		matsum += lu[i][k] * y[k]
	y[i] = (b[i] - matsum)

x = [0 for i in range(0, n)]
for i in range(n - 1, -1, -1):
	right = y[i]
	for j in range(i + 1, n):
		right -= x[j] * lu[i][j]
	x[i] = right / lu[i][i]

print(x)




