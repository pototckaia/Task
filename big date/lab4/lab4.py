from collections import Counter

with open(sys.argv[1], "r") as file:
	countr = Counter()
	line = file.readline()
	while line:
		line = file.readline()
		countr[line] += 1

print(countr.most_common(15), "\n")
