from libc.stdlib cimport  malloc, qsort, free
from libc.string cimport memcpy
from libc.math cimport fabs
 
cdef int n, m, k
cdef double **matrix
cdef double **new_matrix
cdef double **old_matrix
cdef int i, j, l, h
 
 
with open("input.txt", "r") as fin:
    n, m, k = map(int, fin.readline().split())
   
    matrix = <double**> malloc(n*sizeof(double *)) 
    new_matrix = <double**> malloc(n*sizeof(double *))     
    old_matrix = <double**> malloc(n*sizeof(double *)) 
    for i in range(n):
        matrix[i] = <double *> malloc(m * sizeof(double))
        new_matrix[i] = <double *> malloc(m * sizeof(double))
        old_matrix[i] = <double *> malloc(m * sizeof(double))
        for j, fff in enumerate(fin.readline().split()):   
            matrix[i][j] = float(fff)
            new_matrix[i][j] = 0
            old_matrix[i][j] = 0
 
cdef double *cofficients = <double*> malloc(k*sizeof(double))
cdef int power = 1
cdef int side = 1
cdef int N
for l in range(k):
    N = side * 4 + 4
    power *= 2
    side += 2
    cofficients[l] = 1.0/power/N
 
cdef double eps = 0.00000001
cdef int step_max = 100
cdef double norm_sum = 0
cdef double amount
cdef int x1, x2, y1, y2, x, y
 
for l in range(step_max):
    for i in range(n):
        for j in range(m):
            new_matrix[i][j] = matrix[i][j]
            for h in range(k):
                amount = 0
 
                x1 = i - h - 1
                x2 = i + h + 1
                for y in range(j - h - 1, j + h + 2):
                    if 0 <= x1 < n and 0 <= y < m:
                        amount += new_matrix[x1][y]
                    if 0 <= x2 < n and 0 <= y < m:
                        amount += new_matrix[x2][y]
 
                y1 = j - h - 1
                y2 = j + h + 1
                for x in range(i - h, i + h + 1):
                    if 0 <= y1 < m and 0 <= x < n:
                        amount += new_matrix[x][y1]
                    if 0 <= y2 < m and 0 <= x < n:
                        amount += new_matrix[x][y2]
 
                new_matrix[i][j] -= cofficients[h] * amount
            sub = fabs(new_matrix[i][j] - old_matrix[i][j])
            norm_sum = max(sub, norm_sum)
    if norm_sum <= eps:
        break
    for i in range(n):
        for j in range(m):
            old_matrix[i][j] = new_matrix[i][j]

with open("output.txt", "w") as fout:
    for i in range(n):
        for j in range(m):
            fout.write(" %.5f " % new_matrix[i][j])
        fout.write("\n") 

free(cofficients)
free(matrix)
free(old_matrix)
free(new_matrix)