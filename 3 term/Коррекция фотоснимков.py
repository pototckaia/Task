
with open("input.txt", "r") as fin:
	n, m, k = map(int, fin.readline().split())
	matrix = []
	for i in range(n):
		matrix.append(map(float, fin.readline().split()))

with open("output.txt", "w") as fout:
	print(n, m, k)


for i in range(0, n):
c = matrix[i, i]
for j in range(0, n):
    matrix[i, j] = - matrix[i, j] / c
b[i] /= c
matrix[i, i] = 0.0

norm_matrix = 0
for j in range(0, n):
    norm_matrix = max(norm_matrix, nm.absolute(matrix[:, j]).sum())
if norm_matrix >= 1:
    raise Exception("Норма матрицы больше единицы. Метод Зейделя не сходиться")

e = 10**(-5)
x = [0.0 for i in range(0, n)]
k_max = 100
norm_sub = 1

for i in range(0, k_max):
    y = nm.array([0.0 for i in range(0, n)])
    for i in range(0, n):
        y[i] = b[i]
        for j in range(0, i):
            k = matrix[i, j] * y[j]
            y[i] += matrix[i, j] * y[j]
        for j in range(i, n):
            y[i] += matrix[i, j] * x[j]
    sub = nm.absolute(y - x)
    norm_sum = nm.max(sub)
    x = y.copy()
    if norm_sum <= e:
        break

