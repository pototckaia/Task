with open("input.txt", "r") as filein:
	number, power = [int(i) for i in filein.read().split()]
ans = number ** power
with open("output.txt", "w") as fileout:
	fileout.write(str(ans))

