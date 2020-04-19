import numpy as np
import matplotlib.pyplot as plt
import math

def getIndex(s, s_i):
    for i in range(0, len(s_i) - 1):
        s1 = s_i[i]
        s2 = s_i[i + 1]
        if s1 <= s <= s2:
            return i
    assert False, "ERROR: 'i' not found!"

def d(i, x, y):
    return np.sqrt(pow(x[i+1] - x[i], 2) + pow(y[i+1] - y[i], 2))

def rationalSpline(f, s, p, q, s_i, d, m):
    i = getIndex(s, s_i)
    coeff = (2 + q[i]) * (2 + p[i]) - 1
    C_i = (-(3 + q[i])*(f[i+1] - f[i]) + d[i]*m[i] +\
          (2+q[i])*d[i]*m[i+1]) / coeff
    D_i = ((3+p[i])*(f[i+1]-f[i]) - d[i]*m[i+1] -\
          (2+p[i])*d[i]*m[i]) / coeff
    A_i = f[i+1] - C_i
    B_i = f[i] - D_i

    t = (s - s_i[i]) / d[i]
    
    term1 = A_i * t
    term2 = B_i * (1 - t)
    term3 = (C_i * np.power(t, 3)) / (1 + p[i] * (1 - t))
    term4 = (D_i * np.power(1 - t, 3)) / (1 + q[i] * t)
    return term1 + term2 + term3 + term4

def lam(i, d):
    return d[i] / (d[i-1] + d[i])

def mu(i, d):
    return 1 - lam(i, d)

def P_i(i, p, q):
    coeff = (2 + q[i]) * (2 + p[i]) - 1
    return (3 + 3 * p[i] + pow(p[i], 2)) / coeff

def Q_i(i, p, q):
    coeff = (2 + q[i]) * (2 + p[i]) - 1
    return (3 + 3 * q[i] + pow(q[i], 2)) / coeff

def c_i(i, p, q, f, d):
    term1 = lam(i,d) * P_i(i-1,p,q) * (3+q[i-1])
    term2 = (f[i] - f[i-1])/d[i-1]
    term3 = mu(i,d) * Q_i(i,p,q) * (3+p[i]) 
    term4 = (f[i+1]-f[i])/d[i]
    return term1 * term2 + term3 * term4

def getMCoeff(f, q, p, d):
    n = len(f) - 1
    m_a = np.zeros((n + 1, n + 1))
    m_b = np.zeros(n + 1)

    yy_0_2 = pow(d[0] / d[1], 2)
    yy_n_2 = pow(d[n-1] / d[n-2], 2)

    term1 = 2 * (f[1] - f[0]) / d[0]
    term2 = 2 * yy_0_2
    term3 = (f[2] - f[1]) / d[1]
    c_1__ =  term1 - term2 * term3
    
    term1 = 2*(f[n]-f[n-1])/d[n-1]
    term2 = 2*yy_n_2
    term3 = (f[n-1]-f[n-2])/d[n-2]
    c_n__ = term1 - term2 * term3

    m_a[0][0] = 1
    m_a[0][1] = -(yy_0_2 - 1)
    m_a[0][2] = -yy_0_2
    m_b[0] = c_1__


    m_a[1][1] = lam(1,d) * P_i(0,p,q) * (1 + q[0] + yy_0_2) +\
                mu(1,d) * Q_i(1,p,q) * (2 + p[1])
    m_a[1][2] = mu(1,d) * Q_i(1,p,q) + lam(1,d) * P_i(0,p,q) * yy_0_2
    m_b[1] = c_i(1,p,q,f,d) - lam(1,d) * P_i(0,p,q) * c_1__

    for i in range(2, n - 1):
        P_i_1 = P_i(i - 1,p,q)
        Q_i_ = Q_i(i,p,q)
        m_a[i][i - 1] = lam(i,d) * P_i_1
        m_a[i][i] = lam(i,d) * P_i_1 * (2 + q[i-1]) +\
                    mu(i,d) * Q_i_ * (2 + p[i])
        m_a[i][i + 1] = mu(i,d) * Q_i_

        m_b[i] = c_i(i,p,q,f,d)

    
    m_a[n-1][n-2] = lam(n-1,d) * P_i(n-2,p,q) +\
                    mu(n-1,d) * yy_n_2 * Q_i(n-1,p,q)
    m_a[n-1][n-1] = lam(n-1,d) * P_i(n-2,p,q) * (2 + q[n-2]) +\
                    mu(n-1,d) * Q_i(n-1,p,q) * (1 + p[n-1] + yy_n_2)
    m_b[n-1] = c_i(n-1,p,q,f,d) - mu(n-1,d) * Q_i(n-1,p,q) * c_n__ 

    m_a[n][n-2] = -yy_n_2
    m_a[n][n-1] = -(yy_n_2 - 1)
    m_a[n][n] = 1
    m_b[n] = c_n__

    return np.linalg.solve(m_a, m_b)


def cycloid(r, t):
    x = r * t - r * np.sin(t)
    y = r - r * np.cos(t)
    return x, y

def main():
    n = 10
    p = q = np.ones(n + 1) * 32
    t1, t2 = 0, 4*np.pi
    r = 1
    t = np.linspace(t1, t2, n+1)
    x, y = cycloid(r, t)
    
    d_ = np.zeros(n)
    for i in range(n):
        d_[i] = d(i, x, y)

    s_ = np.zeros(n + 1)
    for i in range(n + 1):
        s_[i] = sum([d_[j] for j in range(0, i - 1)])

    m_x = getMCoeff(x, q, p, d_)
    m_y = getMCoeff(y, q, p, d_)

    tt = np.linspace(0, s_[-1], 50)
    x_plot, y_plot = cycloid(r, np.linspace(t1, t2, len(tt)))
    x_s = np.array([rationalSpline(x, si, p, q, s_, d_, m_x) for si in tt])
    y_s = np.array([rationalSpline(y, si, p, q, s_, d_, m_y) for si in tt])

    fig, ax = plt.subplots()
    ax.grid()
    ax.plot(x_plot, y_plot, label="Function", lw=3)
    ax.plot(x_s, y_s, label="Spline")
    ax.legend()
    plt.show()

    k = np.linspace(-0.9, 1000, 100)
    err = []
    for k_ in k:
        p = [k_ for i in range(0, n)]
        q = [k_ for i in range(0, n)]
        
        n2 = 1000
        tt = np.linspace(0, s_[-1], n2)
        x_plot, y_plot = cycloid(r, np.linspace(t1, t2, len(tt)))
        x_s = np.array([rationalSpline(x, si, p, q, s_, d_, m_x) for si in tt])
        y_s = np.array([rationalSpline(y, si, p, q, s_, d_, m_y) for si in tt])

        e = 0
        for i in range(n2):
            e += math.sqrt(math.pow(x_plot[i] - x_s[i], 2) + math.pow(y_plot[i] - y_s[i], 2))
        e = e / n2
        err.append(e)
    fig, ax = plt.subplots()
    ax.grid()
    ax.plot(k, err, label="error")
    ax.legend()
    ax.set_xlabel('p, q')
    ax.set_ylabel('error')
    plt.show()

main()