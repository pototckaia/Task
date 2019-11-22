from typing import List, Tuple
from sympy import randprime
from math import sqrt
from random import randint

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


def randcoprime(u: int) -> int:
    # gcd(u, e) = 1 and e simple number, example Fermat number
    # having a short bit-length and small Hamming weight 
    for _ in range(1, 30):
        e = randprime(2, u - 1)
        print('coprime {}'.format(e))
        if advanced_gcd(u, e)[0] == 1:
            return e
    return 65537


'''
a * b = 1 (mod m)  -> a^-1 - взаимно простое с m
a * x + m * y = 1
a * x = 1 (mod m)
'''
def reverse_by_mod(x : int, m: int) -> int:
	a, x, y = advanced_gcd(x, m)
	# a != 1
	return (x % m + m) % m


'''
primitive root modulo n
если g является первообразным корнем по модулю n, 
то для любого целого a такого, что gcd(a,n)=1, 
найдётся такое целое k, что g^k = a mod{n}.
O( \sqrt{ \phi(n) } )).

o test that a is a primitive root of p you need to do the following. 
First, let s=ϕ(p) where ϕ() is the Euler's totient function. 
If p is prime, then s=p−1. Then you need to determine all the prime 
factors of s: p1,…,pk. Finally, calculate as/pimodp for 
all i=1…k, and if you find 1 among residuals then it is 
NOT a primitive root, otherwise it is.
'''
def generator (p: int) -> int:
	phi = p-1
	fact = trial_division(phi)

	for res in range(2, p + 1):
		ok = True;
		for i in range(0, len(fact)):
			ok = ok and pow(res, phi // fact[i], p) != 1
			if not ok:
				break
		if ok:  
			return res;
	return -1;


def miller_rabin_test(n: int, t: int) -> bool:
    s, r = 0, n - 1 # n - 1 = 2^s * r
    while not (r & 1): # not odd
        s += 1
        r >>= 1
    for i in range(1, t + 1):
        a = randint(2, n - 2)
        y = pow(a, r, n)
        if y == 1 or y == n - 1:
            continue
        for j in range(1, s):
            y = pow(y, 2, n)
            if y == 1:
                return False
            if y == n - 1:
                continue
        return False
    return True



# generate a safe prime p and primitive root modulo p
def safe_prime(k: int) -> Tuple[int, int]:
	while True:
		q = randprime(2**(k//4), 2**(k - 1))
		p = 2 * q + 1
		if miller_rabin_test(p, 100):
			return p, q


def get_prime_and_generator(k: int) -> Tuple[int, int]:
	p, q = safe_prime(k)
	# Note that the order of the group is n=p-1=2q, where q is prime
	while True:
		g = randprime(3, p - 2)
		if (pow(g, 2, p) !=1 and pow(g, q, p) !=1):
			return p, g
