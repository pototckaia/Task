import numpy as nm
from math import cos
import matplotlib.pyplot as plt

def l1(x):
	return -(x - 1.2) / 1.2 + cos(1.2) * (x / 1.2)

def l2(x):
	return cos(0.2) * (x - 0.6) * (x - 1) / 0.32 -\
		cos(0.6) * (x - 0.2) * (x - 1)  / 0.16 +\
		cos(1) * (x - 0.2) * (x - 0.6) / 0.32

a = 0
b = 1.2
count_plot_dot = 100

t = nm.linspace(a, b, count_plot_dot)

y = nm.cos(t)
L1 = l1(t)
L2 = l2(t)

plt.plot(t, y,  'g', label='cos(x)')
plt.plot(t, L1, 'b--', label='L1(x)')
plt.plot(t, L2, 'm--', label='L2(x)')


# plt.axis([a, b, -1, 1])  # задание [xmin, xmax, ymin, ymax]
plt.xlabel('x')    # обозначение оси абсцисс
plt.ylabel('y')    # обозначение оси ординат
plt.title('Интерполирование функции cos(x)')  # название графика
plt.legend()       # вставка легенды (текста в label)

plt.show()