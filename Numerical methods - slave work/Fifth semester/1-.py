import numpy as np
import Plot as plt

def accuracy(exactSolution, approxSolution):
  return np.abs(exactSolution - approxSolution)

def printAccuracy(fout, x, L):
  for xi, Li in zip(x, L):
    fout.write('{:^10.4} {:^10.4E}\n'.format(xi, Li))
  fout.write('---------')

# Одношаговый метод
def oneStep(step, dots, yStart, derivative, iteration):
  points = [yStart, ]
  xPrev = dots[0]
  yPrev = yStart
  for xi in dots[1::]:
    yPrev = iteration(step, xPrev, yPrev, derivative)
    xPrev = xi
    points.append(yPrev)

  return points

#для метода Эйлера
def eulerIteration(step, xi, yi, derivative):
  return yi + step * derivative(xi, yi)

# для yлучшенного метода Эйлера
def improvedEulerIteration(step, xi, yi, derivative):
  k1 = derivative(xi, yi)
  k2 = derivative(xi + 0.5 * step, yi + 0.5 * step * k1)
  return yi + step * k2

# для метода Ранге-Кутты 4-го порядка
def rungeKuttIteration(step, xi, yi, derivative):
  k1 = derivative(xi, yi)
  k2 = derivative(xi + 0.25 * step, yi + 0.25 * step * k1)
  k3 = derivative(xi + 0.5 * step, yi + 0.5 * step * k2)
  k4 = derivative(xi + step, yi + step * (k1 - 2 * k2 + 2 * k3))
  return yi + (1/6) * step * (k1 + 4 * k3 + k4)

# Явный метод Адамса-Бешфорта 3-го порядка
def obviousAdam(step, dots, yStart, derivative):
  sol = [yStart, ]
  for i in range(0, 2):
    sol.append(eulerIteration(step, dots[i], sol[i], derivative))

  for i in range(3, len(dots)):
    I = step * ((23)/12 * derivative(dots[i - 1], sol[i - 1]) - 
                (4/3) * derivative(dots[i - 2], sol[i - 2]) + 
                (5/12) * derivative(dots[i - 3], sol[i - 3]))
    sol.append(sol[i - 1] + I)
  return sol

# Неявный метод Адамса-Моултона -го порядка
def implicitAdam(step, dots, yStart, derivative):
  sol = [yStart, eulerIteration(step, dots[0], yStart, derivative), ]

  for i in range(1, len(dots) - 1):
    d = 1 - (5/12) * step * (2 - dots[i + 1])
    yi = sol[i] + (1/12) * step * (8 * derivative(dots[i], sol[i]) - 
                                   derivative(dots[i - 1], sol[i - 1]))
    sol.append(yi / d)
  return sol

# Метод прогноза-коррекции Адамса 4-го порядка
class Correction: 
  
  def obviousAdamIteration(self, i, step, dots, nodes, derivative):
    t = 55 * derivative(dots[i], nodes[i]) - 59 * derivative(dots[i - 1], nodes[i - 1])
    t += 37 * derivative(dots[i - 2], nodes[i - 2]) - 9 * derivative(dots[i - 3], nodes[i - 3])
    return nodes[i] + (step / 24) * t

  def implicitAdamIteration(self, iPrev, step, dots, nodes, derivative):
    t = 9 * derivative(dots[iPrev + 1], nodes[iPrev + 1]) + 19 * derivative(dots[iPrev], nodes[iPrev])
    t += (-5) * derivative(dots[iPrev - 1], nodes[iPrev - 1]) + derivative(dots[iPrev - 2], nodes[iPrev - 2])
    return nodes[iPrev] + (step / 24) * t

  def done(self, step, dots, yStart, derivative, eps):
    approx = np.zeros(len(dots))

    approx[0] = yStart
    for i in range(1, 4):
       approx[i] = rungeKuttIteration(step, dots[i - 1], approx[i - 1], derivative)

    iStart = 4
    for i in range(iStart, len(dots)):
       approx[i] = self.obviousAdamIteration(i, step, dots, approx, derivative)
       checkEps = False
       while not checkEps:
          newApprox = self.implicitAdamIteration(i - 1, step, dots, approx, derivative)
          e = abs(newApprox - approx[i])
          checkEps = e <= eps
          approx[i] = newApprox
    return approx


if __name__ == "__main__":

  derivative = lambda x_, y_: 2*y_ - x_*y_
  solution = lambda x_: 2 * np.exp(-x_ * (x-4) * 0.5)

  x0, xn = 0, 5
  y0 = 2
  count = 30

  x = np.linspace(x0, xn, num=count)
  exact = solution(x)
  h = abs(x[0] - x[1])
  eps = h**6

  methodCorrection = Correction()
  plot = plt.Plot()

  with open('correction.table', 'w') as fout:
    y1 = oneStep(h, x, y0, derivative, eulerIteration)
    y2 = oneStep(h, x, y0, derivative, improvedEulerIteration)
    y3 = oneStep(h, x, y0, derivative, rungeKuttIteration)
    y4 = obviousAdam(h, x, y0, derivative)
    y5 = implicitAdam(h, x, y0, derivative)
    y6 = methodCorrection.done(h, x, y0, derivative, eps)


    printAccuracy(fout, x, accuracy(exact, y1))
    printAccuracy(fout, x, accuracy(exact, y2))
    printAccuracy(fout, x, accuracy(exact, y3))
    printAccuracy(fout, x, accuracy(exact, y4))
    printAccuracy(fout, x, accuracy(exact, y5))
    printAccuracy(fout, x, accuracy(exact, y6))

    plot.add(x, accuracy(exact, y1), 'Метод Эйлера')
    plot.add(x, accuracy(exact, y2), 'Усовершенствованный метод Эйлера')
    plot.add(x, accuracy(exact, y3), 'Классический метод Рунге-Кутта 4-го порядка')
    plot.add(x, accuracy(exact, y4),'Явный метод Адамса-Бешфорта 3-го порядка')
    plot.add(x, accuracy(exact, y5), 'Неявный метод Адамса-Моултона -го порядка')
    plot.add(x, accuracy(exact, y6), 'Метод прогноза-коррекции Адамса 4-го порядка')
    plot.show('Сравнение методов погрешность')

    plot.add(x, exact, 'Точное решение')
    plot.add(x, y1, 'Метод Эйлера')
    plot.add(x, y2, 'Усовершенствованный метод Эйлера')
    plot.add(x, y3, 'Классический метод Рунге-Кутта 4-го порядка')
    plot.add(x, y4,'Явный метод Адамса-Бешфорта 3-го порядка')
    plot.add(x, y5, 'Неявный метод Адамса-Моултона -го порядка')
    plot.add(x, y6, 'Метод прогноза-коррекции Адамса 4-го порядка')
    plot.show('Сравнение методов')




