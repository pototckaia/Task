'''
c * x -> max
Ax <= b
x >= 0



A неотрицательная 8x6
b неотрицательны

 Ищется оптимальноерешение  (симплекс-метод), 
 В двойственнойзадаче  ищется допустимое  и оптимальное рещения.


table 
базис  | B   | x_1 ...  x_k ... x_j ... x_n 
 ...
  x_t  | b_t |          a_tk   a_tj
  ...
  x_r  | b_r |          a_rk   a_rj
  ...  | b_m |
  ___  | ____|__________________________________
  f(x) |  0  | -c_1 ...        -c_j


1.Проверка базисного плана на оптимальность по условия
если при каком-либо ДБР(допустимое базисное решение)
в симплекс-таблице все коэфф. стоки f(x) не отрицательные
то ДБР оптимально. В противном 2
2. Переходи на новый базис
Из числа небазисных переменных с отрицательным значениями 
в последней строке выбирается перменная, вводимая в базис
 - x_k, это переменная соответсвует наибольшая
 по модулю отрицательная оценка
 |c_k| = max |c_j|, c_j < 0
столбец отвечающий переменной x_k называется главным 
3. r - находим через
b_r / a_rk = min_i (a_i/a_ik), a_ik >= 0
сторока таблице ведущая 
4.
 1.
  b_k = b_r / a_rk
  a_kj = a_rj / a_rk
 2.
  a`_ij = a_ij - (a_rj * a_ik) / a_rk
  b`_i = b_i - (b_r * a_ik) / a_rk
  f`(x) = f(x) - (b_r * c_k) / a_rk
  c`_j = c_j - (a_rj * c_k) / a_rk  

'''




import numpy as np
import math


def simplex(source, result):
	m, n = source.shape
	table = np.eye(m, n + m - 1)
	basis = []

	for i in range(0, table.shape[0]):
		for j in range(0, table.shape[1]):
			if j < n:
				table[i, j] = source[i, j]
			else:
				table[i, j] = 0
		if n + i < table.shape[1]:
			table[i, n + i] = 1
			basis.append(n + i)
	n = table.shape[1]

	mainCol, mainRow = 0, 0
	while min(table[m - 1, 1:n]) < 0:
		mainCol = 1 + np.argmin(table[m - 1, 1:n])
		mainRow = findMainRow(m, m, table, mainCol)
		if mainRow is None:
			return None
		basis[mainRow] = mainCol

		new_table = np.eye(m, n)
		for j in range(0, n):
			new_table[mainRow, j] = table[mainRow, j] / table[mainRow, mainCol]
		
		for i in range(0, m):
			if i == mainRow:
				continue		
			for j in range(0, n):
				new_table[i, j] = table[i, j] - table[i, mainCol] * new_table[mainRow, j]
		table = new_table

	for i in range(0, len(result)):
		if (basis.count(i + 1) > 0):
			k = basis.index(i + 1)
			result[i] = table[k, 0]
		else:
			result[i] = 0
	return table


def findMainRow(m, n, table, mainCol):
	cand = np.empty(shape=[0, 2])
	for i in range(0, m - 1):
		if (table[i, mainCol] != 0 and table[i, 0] / table[i, mainCol] > 0):
			v = table[i, 0] / table[i, mainCol]
			cand = np.append(cand, [[v, i]], axis=0)
	if cand.shape[0] == 0:
		return None
	return int(cand[np.argmin(cand[:, 0]), 1])


'''
f(x_1, x_2) = 6 * x_1 + 5 * x_2 -> max
-3 * x_1 + 5 * x_2 <= 25
-2 * x_1 + 5 * x_2 <= 30
x_1 <= 10
3 * x_1 - 8 * x_2 <= 6
x_1, x_2 >= 0
'''
A = np.array([[-3.0, 5],
	[-2.0, 5.0],
	[1.0, 0.0],
	[3.0, -8.0]])
B = np.array([25.0, 30.0, 10.0, 6.0])
C = np.array([-6.0, -5.0])

s = np.eye(A.shape[0] + 1, A.shape[1] + 1)

s[0:B.shape[0], 0] = B
s[0][s.shape[1] - 1] = 0
s[s.shape[0] - 1, 1:s.shape[1]] = C
s[0:s.shape[0] - 1, 1:s.shape[1] + 1] = A

result = np.zeros(2)

table = simplex(s, result)
print(table)
print(result)

s = np.array([[240.0, 2.0, 3.0, -6.0],
 [200.0, 4.0, 2.0, -4.0],
 [160.0, 4.0, 6.0, -8.0],
 [0.0, -4.0, -5.0, -4.0]])
result = np.zeros(3)

table = simplex(s, result)
print(table)
print(result)
