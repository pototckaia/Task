# Simple Numerical Laplace Equation Solution using Finite Difference Method
import numpy as np
import matplotlib.pyplot as plt

# Set maximum iteration
maxIter = 1000

# Set Dimension and delta
lenX = lenY = 30 #we set it rectangular
delta = 1

# Boundary condition
Ttop = 100
Tbottom = 0
Tleft = 0
Tright = 0

# Initial guess of interior grid
Tguess = 0

# Set colour interpolation and colour map
colorinterpolation = 50
colourMap = plt.cm.jet #you can try: colourMap = plt.cm.coolwarm

# Set meshgrid
X, Y = np.meshgrid(np.arange(0, lenX), np.arange(0, lenY))

# Set array size and set the interior value with Tguess
T = np.empty((lenX, lenY))
T.fill(Tguess)

T2 = np.empty((lenX, lenY))
T2.fill(Tguess)


# Set Boundary condition
T[(lenY-1):, :] = Ttop
T[:1, :] = Tbottom
T[:, (lenX-1):] = Tright
T[:, :1] = Tleft

T2[(lenY-1):, :] = Ttop
T2[:1, :] = Tbottom
T2[:, (lenX-1):] = Tright
T2[:, :1] = Tleft


print("Please wait for a moment")
for iteration in range(0, maxIter):
    for i in range(1, lenX-1, delta):
        for j in range(1, lenY-1, delta):
            T[i, j] = 0.25 * (T[i+1][j] + T[i-1][j] + T[i][j+1] + T[i][j-1])
            T2[i, j] = 0.25 * (T[i-1][j-1] + T[i-1][j+1] + T[i+1][j-1] + T[i+1][j+1])

print("Iteration finished")


plt.title("Уравнение Пуассона - схемы «крест»")
plt.contourf(X, Y, T, colorinterpolation, cmap=colourMap)
plt.colorbar()
plt.show()

plt.title("Уравнение Пуассона схемы - «крест» на 45 градусов")
plt.contourf(X, Y, T2, colorinterpolation, cmap=colourMap)
plt.colorbar()
plt.show()

print("")