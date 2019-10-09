from math import fabs 


with open("input.txt", "r") as fin:
	n = int(fin.readline())
	A = [[0] * (n + 1) for i in range(0, n)]

	for i in range(0, n):
		line = fin.readline().split(' ')
		A[i] = [float(line[j]) for j in range(0, n + 1)]

answer = [i for i in range(0, n)]

for k in range(0, n):
	
	for p in range(k, n + 1):
		summ = 0
		for r in range(0, k):
			summ += A[r][p] * A[k][r]
		A[k][p] = A[k][p] - summ

	b_i = k
	for i in range(k + 1, n):
		b_i = (i if fabs(A[k][i]) > fabs(A[k][b_i]) else b_i)
	answer[b_i], answer[k] = answer[k], answer[b_i]
	for i in range(0, n):
		A[i][k], A[i][b_i] = A[i][b_i], A[i][k]

	m = A[k][k]
	for p in range(k , n + 1):
		A[k][p] = A[k][p] / m

	for i in range(0, k):
		b = A[i][k]
		for p in range(k, n + 1):
			A[i][p] = A[i][p] - A[k][p] * b
			
	
for i in range(0, n):
	print('x', answer[i],'=',  A[i][n])


