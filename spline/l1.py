import numpy as np
import matplotlib.pyplot as plt
import random

def h(x, i):
    return x[i] - x[i - 1]


def s(x_, x, y, dy):
    for i in range(0, len(x)):
        if x[i] <= x_ <= x[i + 1]:
            a = 6 / h(x, i + 1) 
            a *= (y[i + 1] - y[i]) / h(x, i + 1) - (dy[i + 1] + 2 * dy[i]) / 3

            b = 12 / np.power(h(x, i + 1), 2)
            b *= (dy[i + 1] + dy[i]) / 2 - (y[i + 1] - y[i]) / h(x, i + 1)

            с = dy[i]
            
            result =  y[i] + с * (x_ - x[i]) 
            result += (a / 2) * np.power(x_ - x[i], 2)
            result += (b / 2) * np.power(x_ - x[i], 3)
            return result


def mu(x, i):
    return h(x, i + 1) / (h(x, i) + h(x, i + 1))


def lambda_(x, i):
    return h(x, i) / (h(x, i) + h(x, i + 1))


def getM(configuration):
    x = np.linspace(configuration["x_start"], 
                    configuration["x_end"], 
                    num=configuration["n"])
    y = configuration["y"]
    diff = configuration["diff"]

    n = len(x)
    m_a = np.zeros(n ** 2).reshape(n, n)
    m_a[0][0] = 1
    for i in range(1, n - 1):
        m_a[i][i - 1] = mu(x, i)
        m_a[i][i] = 2
        m_a[i][i + 1] = lambda_(x, i)
    m_a[-1][-2] = 1

    m_b = np.zeros(n)
    m_b[0] = diff[0] # (y[1] - y[0]) / h(x, 0)
    for i in range(1, n - 1):
        m_b[i] = lambda_(x, i) * (y[i + 1] - y[i]) / h(x, i + 1)
        m_b[i] += mu(x, i) * (y[i] - y[i - 1]) / h(x, i)
        m_b[i] *= 3
    m_b[-1] = diff[-1] # (y[-1] - y[-2]) / h(x, len(x) - 1) 

    return np.linalg.solve(m_a, m_b)


def setUp(conf):
    func = conf["func"] 
    fdiff = conf["diff"]
    tr = conf["tr_func"]
    conf["func"] = lambda x: func(conf["a"], x)
    conf["diff"] = lambda x: fdiff(conf["a"], x)
    conf["tr_func"] = lambda x: tr(conf["a"], x)

    conf["x"] = np.linspace(conf["x_start"], conf["x_end"], num=conf["n"] + 1)
    conf["y"] = np.array([func(conf["a"], x_) for x_ in conf["x"]])
    conf["diff"] = np.array([fdiff(conf["a"], x_) for x_ in conf["x"]])
    return getM(conf)


def plot(n, configuration):
    true_func = configuration["tr_func"]

    x_dots = np.linspace(configuration["x_start"], configuration["x_end"], num=n)
    y_dots = np.array([true_func(x_) for x_ in x_dots])
    s_dots = np.array([s(x_, x_dots, y_dots, configuration["m_res"]) for x_ in x_dots])
    
    plt.plot(x_dots, y_dots, label="func")
    plt.plot(x_dots, s_dots, label="spline")
    plt.legend()
    plt.show()

    d = max([abs(y_dots[i] - s_dots[i]) for i in range(0, len(y_dots))])
    print(d)
    return

def main(conf):
    conf["m_res"] = setUp(conf)
    plot(conf["n"], conf)

def func1(a, x):
    return np.sin(a * x)

def func1dx(a, x):
    return a * np.cos(a * x)

def func1app(a, x):
    offset = random.uniform(0.5, 1)
    return func1(a, x) + offset 

def func1dxapp(a, x):
    dx = 0.1
    return (func1(a, x) - func1(a, x - dx)) / (x - x + dx) 

def func1dxfalse(a, x):
    return a + x

configurations = [
    {"func": func1, "tr_func": func1, "diff": func1dx, "a": 5, "n": 50, "x_start": 0, "x_end": np.pi},
    {"func": func1app, "tr_func": func1, "diff": func1dxapp, "a": 5, "n": 50, "x_start": 0, "x_end": np.pi},
    {"func": func1app, "tr_func": func1, "diff": func1dxfalse, "a": 5, "n": 50, "x_start": 0, "x_end": np.pi}
]

if __name__ == "__main__":
    main(configurations[0])
    main(configurations[1])
    main(configurations[2])