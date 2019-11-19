def matrix_to_vector(matrix, vector):
	m = len(matrix)
	n = len(vector)
	result = [0 for i in range(0, m)]
	for i in range(0, m):
		for j in range(0, n):
			result[i] += matrix[i][j] * vector[j]
	return result

def scal(vector1, vector2):
	result = 0
	n = len(vector1)
	for i in range(0, n):
		result += vector1[i] * vector2[i]
	return result

def add_vector(vector1, vector2):
	n = len(vector1)
	result = [0  for x in range(0, n)]
	for i in range(0, n):
		result[i] = vector1[i] + vector2[i]
	return result

def sub_vector(vector1, vector2):
	n = len(vector1)
	result = [0  for x in range(0, n)]
	for i in range(0, n):
		result[i] = vector1[i] - vector2[i]
	return result

def mult_vector(vector, scal):
	n = len(vector)
	result = [0  for x in range(0, n)]
	for i in range(0, n):
		result[i] = scal * vector[i]
	return result

def norm(vector):
	return max(vector, key=abs)


matrix = [
[5.0, 2.0, 3.0],
[2.0, 6.0, 1.0],
[3.0, 1.0, 7.0]]

b = [10.0, 20.0, 30.0]

epsilon = 0.0001
maxIteration = len(matrix)
approximation = b[:]
discrepancy =  sub_vector(b, matrix_to_vector(matrix, approximation))
descent = discrepancy[:]

k = 1
while k <= maxIteration:
	alpha = scal(discrepancy, discrepancy) / scal(matrix_to_vector(matrix, descent), descent)
	approximation = add_vector(approximation, mult_vector(descent, alpha))
	
	new_discrepancy = sub_vector(discrepancy, mult_vector(matrix_to_vector(matrix, descent), alpha))
	beta = scal(new_discrepancy, new_discrepancy) / scal(discrepancy, discrepancy)
	descent = add_vector(new_discrepancy, mult_vector(descent, beta)) 
	discrepancy = new_discrepancy[:]
	if norm(discrepancy) / norm(b) < epsilon:
		break

print(approximation)



