from matplotlib import pyplot as plt

class Plot:  
  def __init__(self):
    fig = plt.figure(facecolor='white')

  def add(self, dots, solution, title):
    plt.plot(dots, solution, linewidth=1, label=title)

  def show(self, title):
    plt.legend(loc=3)
    plt.title(title)
    plt.ylabel('y')
    plt.xlabel('x')
    plt.grid(True)
    plt.grid(True)
    plt.show()