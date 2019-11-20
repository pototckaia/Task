from typing import Tuple, List
from math import sqrt
import random as rn

r"""
a^n = a^(n/2) * a^(n/2) or a^(n-1) * a"""
def modular_pow(a: int, b: int, n: int) -> int:
    return pow(a, b, n)
    # res = 1
    # while b:
    #     if (b & 1): # is odd
    #         res = (res * a) % n
    #     a = (a * a) % n
    #     b >>= 1
    # return res


r"""
a mod b = a - b * floor(a / b)
lcm(a, b) = (a * b) / gcd(a, b), least common multiplier
a * x + b *y = gcd(a, b)"""
def advanced_gcd(a: int, b: int) -> Tuple[int, int, int]:
    xx, yy = 0, 1
    x, y = 1, 0
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx*q
        y, yy = yy, y - yy*q 
    return a, x, y


def lcp(a: int, b: int) -> int:
    return abs(a * b) // advanced_gcd(a, b)[0]

r"""
Returns the Jacobi symbol `(m / n)`.

For any integer ``m`` and any positive odd integer ``n`` the Jacobi symbol
is defined as the product of the Legendre symbols corresponding to the
prime factors of ``n``"""
def Jacobi(m: int, n: int) -> int:
    if n < 0 or not n % 2:
        raise ValueError("n should be an odd positive integer")
    if m < 0 or m > n:
        m = m % n
    if not m: # m == 0
        return int(n == 1)
    if n == 1 or m == 1:
        return 1
    if advanced_gcd(m, n)[0] != 1: # gcd(m, n) == 1
        return 0

    j = 1
    if m < 0:
        m = -m
        if n % 4 == 3:
            j = -j
    while m != 0:
        while m % 2 == 0 and m > 0:
            m >>= 1
            if n % 8 in [3, 5]:
                j = -j
        m, n = n, m
        if m % 4 == 3 and n % 4 == 3:
            j = -j
        m %= n
    if n != 1:
        j = 0
    return j


def sieve_of_eratosthenes(n: int) -> List[int]:
    isPrime = [True for i in range(n + 1)]
    isPrime[0] = isPrime[1] = False
    sqrtn = int(sqrt(n + 1))
    for i in range(2, sqrtn):
        if isPrime[i]:
            if (i * i <= n):
                for j in range(i*i, n + 1, i):
                    isPrime[j] = False

    prime = []
    for i, x in enumerate(isPrime):
        if x:
            prime.append(i)
    return prime


def trial_division(n: int) -> List[int]:
    factors = []
    while not (n & 1): # not odd
        n >>= 1 # n / 2
        factors.append(2)

    sqrtn = int(sqrt(n + 1))
    for i in range(3, sqrtn, 2):
        while not (n % i): # division i
            n //= i
            factors.append(i)
    if n != 1:
        factors.append(n)
    return factors


def is_prime_td(n: int) -> bool:
    sqrtn = int(sqrt(n))
    if n % 2 == 0:
        return False

    for i in range(3, sqrtn + 1, 2):
        if n % i == 0:
            return False
    return True


def fermat_test(n: int, t: int) -> bool:
    for i in range(1, t + 1):
        a = rn.randint(2, n - 2) # [2, n - 2]
        r = modular_pow(a, n - 1, n)
        if r != 1: 
            return False
    return True


def solovay_strassen(n: int, t: int) -> bool:
    for i in range(1, t + 1):
        a = rn.randint(2, n - 2)
        r = modular_pow(a, (n-1) // 2, n)
        if r != 1 and r != n - 1:
            return False
        s = Jacobi(a, n)
        if r != s % n:
            return False
    return True


def miller_rabin_test(n: int, t: int) -> bool:
    s, r = 0, n - 1 # n - 1 = 2^s * r
    while not (r & 1): # not odd
        s += 1
        r >>= 1
    for i in range(1, t + 1):
        a = rn.randint(2, n - 2)
        y = modular_pow(a, r, n)
        if y == 1 or y == n - 1:
            continue
        for j in range(1, s):
            y = modular_pow(y, 2, n)
            if y == 1:
                return False
            if y == n - 1:
                continue
        return False
    return True
