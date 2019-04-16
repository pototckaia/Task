from libc.stdlib cimport  malloc, free
from math import fabs

cdef int *createSet(int size):
	disjointedSet = <int *>malloc(size * sizeof(int))
	cdef int i
	for i in range(size):
		disjointedSet[i] = i
	return disjointedSet

cdef int find(int *disjointedSet, int x):
	if x == disjointedSet[x]:
		return x
	else:
		disjointedSet[x] = find(disjointedSet, disjointedSet[x])
		return disjointedSet[x]

cdef int merge(int *disjointedSet, int rep_a, int rep_b):
	rep_a = find(disjointedSet,rep_a)
	rep_b = find(disjointedSet,rep_b)
	if rep_a == rep_b:
		return 0
	disjointedSet[rep_b] = rep_a
	return 1

cdef int i
cdef int m, prev_offset, cur_offset
cdef int rooms_count
cdef int create_count
cdef int merge_count
cdef int *disjointedSet


with open("input.txt", "r") as filein, open("output.txt", "w") as fout:
	line_p = filein.readline().rstrip('\n')
	m = len(line_p)
	disjointedSet = createSet(2 * m)

	for i in range(m):
		if line_p[i] != ' ': 
			continue
		if i == 0 or line_p[i - 1] != ' ':
			disjointedSet[i] = i
			create_count += 1
		else:
			disjointedSet[i] = disjointedSet[i - 1]	
	rooms_count = create_count
	
	cur_offset = m
	for line in filein:
		prev_offset = fabs(cur_offset - m)
		create_count = 0
		merge_count = 0
		for i in range(m):
			if line[i] != ' ': 
				continue
			if i == 0 or line[i - 1] != ' ':
				disjointedSet[cur_offset +  i] = cur_offset + i
				create_count += 1
			else:
				disjointedSet[cur_offset + i] = disjointedSet[cur_offset + i - 1]	
		for i in range(m):
			if line[i] == ' ' and line_p[i] == ' ':
				if merge(disjointedSet, cur_offset+i, prev_offset+i):
					merge_count += 1				

		line_p = line
		cur_offset = fabs(cur_offset - m)
		rooms_count += create_count - merge_count
	
	fout.write(str(rooms_count))

