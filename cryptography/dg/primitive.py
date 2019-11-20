
'''
primitive root modulo n
если g является первообразным корнем по модулю n, 
то для любого целого a такого, что gcd(a,n)=1, 
найдётся такое целое k, что g^k = a mod{n}.
'''

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

def generator (p: int) -> int:
	phi = p-1
	fact = trial_division(phi)

	for res in range(2, p + 1):
		ok = True;
		for i in range(0, len(fact))
			ok &= pow(res, phi / fact[i], p) != 1
			if not ok:
				break
		if ok:  
			return res;
	return -1;
