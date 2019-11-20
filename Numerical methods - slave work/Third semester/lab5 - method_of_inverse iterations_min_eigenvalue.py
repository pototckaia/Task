matrix = [
[2, 1, 1],
[1, 2.5, 1],
[1, 1, 3]]

n = 3
epsilon = 0.001
eigen_vector = [1 for x in range(n)]
eigen_values = 1 / max(eigen_vector, key=abs) 
maxIter = 40

lu = [[0] * (n) for i in range(0, n)]
for i in range(0, n): 
	for j in range(i, n):
		summ = 0
		for k in range(0, i):
			summ += lu[i][k] * lu[k][j]
		lu[i][j] = matrix[i][j] - summ
		if j == i:
			continue
		summ = 0
		for k in range(0, i):
			summ += lu[j][k] * lu[k][i]
		lu[j][i] = (matrix[j][i] - summ) / lu[i][i]


def methodLU(eigen_vector):
	b = [x * eigen_values for x in eigen_vector]
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

	eigen_vector.clear()
	for i in range(n):
		eigen_vector.append(x[i])

for i in range(maxIter):
	methodLU(eigen_vector)

	old_eigen_value =  eigen_values
	eigen_values = 1 / max(eigen_vector, key=abs)

	if abs(old_eigen_value -  eigen_values) < epsilon:
		break 

s = 'Собственное значение матрицы {0: .4f}'.format(eigen_values)
print(s)
s = 'Собственный вектор матрицы x=('
for x in eigen_vector:
	s+= '{0: .7f}, '.format(x)

s +=')'
print(s)