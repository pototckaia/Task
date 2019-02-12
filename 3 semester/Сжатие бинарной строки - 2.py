with open("input.txt", "r") as filein:
	c = [int(i) for i in filein.read().split()]

p, n = c[:2]
del c[:2]

ans = [0 for i in range(n+1)]
ans[0] = c[0]

for i in range(1, n + 1):	
	ans[i] = ans[i - 1]
	for k in range(i - 1, 0, -1):
		ans[k] = (ans[k - 1] - (c[i] * ans[k]) % p) % p
	ans[0] = (-1) * c[i] * ans[0] % p

	

ans = [str(i) for i in ans]

with open("output.txt", "w") as fileout:
	for i in ans:
		fileout.write(i + '\n')

