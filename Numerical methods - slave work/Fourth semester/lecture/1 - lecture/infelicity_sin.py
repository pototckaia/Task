from math import fabs


x = 25.66
eps = 10**(-8)

a = x
res = a

k = 0
x_ = x
fac = 1

while (fabs(a) >= eps):
	k += 1
	x_ = x_ * x * x
	fac = fac * (2 * k) * (2 * k + 1)
	sign = -1 if k % 2 == 1 else 1 
	
	a = sign * (x_ / fac)
	res = res + a

print(res)