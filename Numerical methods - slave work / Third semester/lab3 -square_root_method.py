# import math as m

# with open("input.txt", "r") as fin:
# 	n = int(fin.readline())

# 	A = [[0] * (n) for i in range(0, n)]
# 	G = [[0] * (n) for i in range(0, n)]
# 	b = [0 for i in range(0, n)]

# 	for i in range(0, n):
# 		line = fin.readline().split(' ')
# 		for j in range(0, n):
# 			A[i][j] = float(line[j])

# 	line = fin.readline().split(' ')
# 	for j in range(0, n):
# 		b[j] = float(line[j])	


n = 4
A = [[2.12, 0.42, 1.34, 0.88],
[0.42, 3.95, 1.87, 0.43],
[1.34, 1.87, 2.98, 0.46],
[0.88, 0.43, 0.46, 4.44]]

b = [11.172, 0.115, 9.009, 9.349]
G = [[0] * (n) for i in range(0, n)];


summ = 0
no_solution = 0


for i in range(0, n):
	for j in range	(i, n):
		summ = 0
		for k in range(0, i):
			summ += G[k][j] * G[k][i]
		if (i != j): 
			G[i][j] = (A[i][j] - summ) / G[i][i]
		else:
			G[i][i] = (A[i][i] - summ)**(1/2)
	if G[i][i] == 0 :
		no_solution = 1
		break  

if no_solution:
	print("Решение не существует")
else:

	for i in range(0, n):
		summ = 0
		for k in range(0, i):
			summ += G[k][i] * b[k]
		b[i] = (b[i] - summ) / G[i][i] 

	x = [0 for i in range(0, n)]
	for i in range(n - 1, -1, -1):
		summ = 0
		for k in range(i + 1, n):
			summ  += G[i][k] * x[k]
		x[i] = (b[i] - summ) / (G[i][i])

	for i in x:
		print(i.real)

