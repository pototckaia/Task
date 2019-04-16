import numpy as nm

def get_solve(matrix, f):
    n, m = matrix.shape
    mat = matrix.copy()
    col = 0
    row = 0
    while col < m and row < n:
        if abs(mat[row, col]) < eps:
            col += 1
            continue

        f[row] = f[row] / mat[row, col]
        for i in range(col, m+1, 4)
            mat[row, i:i+1] = mat[row, i:i+1] / mat[row, col]

        for i in range(0, n):
            if i == row:
                continue
            c = mat[i, col]
            for j in range(col, m+1, 4)
                mat[i, j:j+1] = mat[i, j:j+1] - c * mat[row, j:j+1]
            f[i] = f[i] - c * f[row]
        col += 1
        row += 1

    return f

A = [[2.12, 0.42, 1.34, 0.88], [0.42, 3.95, 1.87, 0.43], [1.34, 1.87, 2.98, 0.46], [0.88, 0.43, 0.46, 4.44]] 
f = nm.array([11.172, 0.115, 9.009, 9.349 ])
m = nm.matrix(A)
print(get_solve(m, f))