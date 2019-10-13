import sympy as sp
import util
import random as rn

def randprime(min: int, max: int) -> int:
    return sp.randprime(min, max)

def oddRand(min: int, max: int) -> int:
	r = rn.randrange(min, max + 1)
	return r + ~(r & 1)

def rand_search(min: int, max: int, maxInter: int, check) -> int:
	r = oddRand(min, max) # odd
	for i in range(1, maxInter):
		if check(r):
			break
		r = oddRand(min, max)
	return r

def incremental_search(min: int, max: int, maxInter: int, check) -> int:
	r = oddRand(min, max) # odd
	for i in range(1, maxInter):
		if check(r):
			break
		r += 2
	return r

def td_randprime(min: int, max: int):
	return incremental_search(min, max, 1000, util.is_prime_td)

def ss_randprime(min: int, max: int) -> int:
	return rand_search(min, max, 1000, 
		lambda x: util.solovay_strassen(x, 3))

def mr_randprime(min: int, max: int) -> int:
	return rand_search(min, max, 1000, 
		lambda x: util.miller_rabin_test(x, 3))