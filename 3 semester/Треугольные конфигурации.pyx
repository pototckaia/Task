from fractions import Fraction
from libc.stdlib cimport  malloc, qsort, free
from libc.math cimport fabs



cdef struct Line:
	long double A
	long double B
	long double C

cdef struct Point:
	long double x
	long double y
	int index1
	int index2

cdef int n
cdef int count = 0
cdef int len_vertex = 0
cdef int i, j, l, h 
cdef Line *lines
cdef Point *vertex
cdef long double x1, x2, y1, y2
cdef long double eps = 0.0000000001

with open("input.txt", "r") as fin:
	n = int(fin.readline().rstrip('\n'))
	lines = <Line *> malloc(n * sizeof(Line))
	for i in range(n):
		x1, y1, x2, y2 = [float(jjj) for jjj in fin.readline().split()]
		lines[i].A = y1 - y2 # A
		lines[i].B = x2 - x1 # B
		lines[i].C = x1 * y2 - x2 * y1 # C

vertex = <Point *> malloc(n * n * sizeof(Point))
cdef long double t
for i in range(n):
	for j in range(i+1, n):
		t = lines[i].A * lines[j].B - lines[j].A * lines[i].B
		if abs(t) <= eps:
			continue
		vertex[count].x = -(lines[i].C * lines[j].B - lines[j].C * lines[i].B) / t
		vertex[count].y = -(lines[i].A * lines[j].C - lines[j].A * lines[i].C) / t
		vertex[count].index1 = i
		vertex[count].index2 = j
		count += 1
free(lines)

cdef int compare (const void * a, const void * b) nogil:
	cdef Point *aa = <Point*> (a)
	cdef Point *bb =  <Point*> (b)
	cdef long double e = eps * max(1.0, fabs(aa.x), fabs(bb.x))
	if fabs(aa.x -bb.x) <= e:
		if aa.y > bb.y:
			return 1
		else:
			return -1
	if aa.x > bb.x:
		return 1
	else:
		return -1

qsort(vertex, count, sizeof(Point), compare);

cdef int count1 = -1
cdef int **m_tmp = <int **> malloc(n * sizeof(int *)) 
for i in range(n):
	m_tmp[i] = <int *> malloc((n+1) * sizeof(int))
	m_tmp[i][0] = 1

cdef int buf_len
cdef int buf_index
cdef int ttt
cdef int eq_1 = 0
cdef int eq_2 = 0
cdef long double e

for i in range(count):
	if i != 0:
		e = eps * max(1.0, fabs(vertex[i - 1].x), fabs(vertex[i].x))
		eq_1 = fabs(vertex[i - 1].x - vertex[i].x) <= e

		e = eps * max(1.0, fabs(vertex[i - 1].y), fabs(vertex[i].y))
		eq_2 = fabs(vertex[i - 1].y - vertex[i].y) <= e        
	
	if i == 0 or not eq_1  or not eq_2:
		count1 += 1

	buf_index = vertex[i].index1  
	buf_len = m_tmp[buf_index][0]
	m_tmp[buf_index][buf_len] = count1
	m_tmp[buf_index][0] += 1

	buf_index = vertex[i].index2  
	buf_len = m_tmp[buf_index][0]
	m_tmp[buf_index][buf_len] = count1
	m_tmp[buf_index][0] += 1


free(vertex)

count1 += 1
matrix = [[] for i in range(count1)]

cdef int len_
for i in range(n):
	len_ = m_tmp[i][0]
	for j in range(2, len_):
		if m_tmp[i][j - 1] == m_tmp[i][j]:
			continue
		matrix[m_tmp[i][j - 1]].append(m_tmp[i][j])
		matrix[m_tmp[i][j]].append(m_tmp[i][j - 1])

cdef find = 0
cdef int count_c = 0
for i in range(count1):
	for j in matrix[i]:
		if j <= i:
			continue
		find = 0
		for l in matrix[j]:
			if l > j:
				for h in matrix[l]:
					if h == i:
						count_c += 1
						find = 0
						break 
					if find:
						break	


with open('output.txt', 'w') as fout:
	fout.write(str(count_c))

for j in range(n):
	free(m_tmp[j])
free(m_tmp) 
