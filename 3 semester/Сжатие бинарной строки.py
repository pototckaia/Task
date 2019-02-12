import math

with open("input.txt", "r") as fin:
	n, m = map(int, fin.readline().split())
	bin_str = fin.readline()


summa = 0
combination = 1;


c = n + m - 1;
j = 0
i = 0

while m != j:
	if (bin_str[c] == '0'):
		i += 1
	elif (bin_str[c] == '1'):
		j += 1
		
	if (bin_str[c] == '1'):
		if (j <= i + j - 1):
			summa += combination * (i) // (j)
		if (j <= i + j):
			combination = combination * (j + i) // (j)
	else:
		if (j <= i + j):
			combination = combination * (i + j) // (i)

	c -= 1

ans = ""
if summa == 0:
    ans = "0"
while summa > 0:
    t = str(summa % 2)
    ans = t + ans
    summa = summa // 2 

with open("output.txt", "w") as fout:
	fout.write(ans)
