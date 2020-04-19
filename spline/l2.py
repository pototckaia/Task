import numpy as np
import matplotlib.pyplot as plt
import random

def h(x, i):
    return x[i + 1] - x[i]

def getInte(configuration):    
    x = np.linspace(configuration["x_start"], 
                configuration["x_end"], 
                num=configuration["n"] +1)
    y = configuration["y"]
    diff = configuration["diff"]

    a, b = 0, 0
    print(len(x), len(y))
    for i in range(len(y) - 1):
        a += h(x, i) * (y[i] + y[i + 1])
        b += pow(h(x, i), 2) * (diff[i] - diff[i + 1])
    return 0.5 * a + (1/12) * b


def main(conf):
    func = conf["func"] 
    fdiff = conf["diff"]

    conf["x"] = np.linspace(conf["x_start"], conf["x_end"], num=conf["n"] + 1)
    conf["y"] = np.array([func(conf["a"], x_) for x_ in conf["x"]])
    conf["diff"] = np.array([fdiff(conf["a"], x_) for x_ in conf["x"]])
    res =  getInte(conf)
    true_res = conf["funcint"](conf["a"], conf["x_end"]) - conf["funcint"](conf["a"], conf["x_start"])
    print(res)
    print(true_res)
    print(abs(true_res - res))

def func1(a, x):
    return np.sin(a * x)

def func1app(a, x):
    return func1(a, x) + random.uniform(-0.1, 0.1)

def func1dx(a, x):
    return a * np.cos(a * x)

def func1dxapp(a, x):
    dx = 0.1
    return (func1(a, x + dx) - func1(a, x)) / dx

def func1int(a, x):
    return -(1/a) * np.cos(a*x)


def func2(a, x):
    return a / (1 + 9 * np.power(x, 2))

def func2app(a, x):
    return func2(a, x) + random.uniform(-0.1, 0.1)

def func2dx(a, x):
    return -18 * a * x / np.power(9 * np.power(x, 2) + 1, 2)

def func2dxapp(a, x):
    dx = 0.1
    return (func2(a, x + dx) - func2(a, x)) / dx

def func2int(a, x):
    return np.arctan(3*x) * (a/3)

configurations = [
    {"a": 8, "n": 50, "x_start": -1, "x_end": 1, "funcint": func2int, "func": func2, "diff": func2dx},
    {"a": 8, "n": 50, "x_start": -1, "x_end": 1, "funcint": func2int, "func": func2app, "diff": func2dx},
    {"a": 8, "n": 50, "x_start": -1, "x_end": 1, "funcint": func2int, "func": func2, "diff": func2dxapp},
    {"a": 8, "n": 50, "x_start": -1, "x_end": 1, "funcint": func2int, "func": func2app, "diff": func2dxapp},

    {"a": 8, "n": 100, "x_start": -1, "x_end": 1, "funcint": func2int, "func": func2, "diff": func2dx},
    {"a": 8, "n": 100, "x_start": -1, "x_end": 1, "funcint": func2int, "func": func2app, "diff": func2dx},
    {"a": 8, "n": 100, "x_start": -1, "x_end": 1, "funcint": func2int, "func": func2, "diff": func2dxapp},
    {"a": 8, "n": 100, "x_start": -1, "x_end": 1, "funcint": func2int, "func": func2app, "diff": func2dxapp},
]

if __name__ == "__main__":
    for conf in configurations:
        main(conf)
