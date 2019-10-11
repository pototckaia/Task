import sympy as sp
from typing import Tuple, List
from math import sqrt

# a^n = a^(n/2) * a^(n/2) or a^(n-1) * a
def modular_pow(a: int, b: int, n: int) -> int:
    return pow(a, b, n)
    # res = 1
    # while b:
    #     if (b & 1): # is odd
    #         res = (res * a) % n
    #     a = (a * a) % n
    #     b >>= 1
    # return res


# a mod b = a - b * floor(a / b)
# lcm(a, b) = (a * b) / gcd(a, b), least common multiplier
# a * x + b *y = gcd(a, b)
def advanced_gcd(a: int, b: int) -> Tuple[int, int, int]:
    xx, yy = 0, 1
    x, y = 1, 0
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx*q
        y, yy = yy, y - yy*q 
    return a, x, y


def randprime(min: int, max: int) -> int:
    return sp.randprime(min, max)


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