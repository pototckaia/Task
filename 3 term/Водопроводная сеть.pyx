from libc.stdlib cimport  malloc, qsort, free

ctypedef struct Pair:
	int first
	int second

ctypedef struct Edge:
	int v_to
	int v_from
	int weight
	int number

	
cdef Pair *createSet(int size):
	cdef Pair *disjointedSet = <Pair *>malloc(size * sizeof(Pair))
	cdef int i
	for i in range(size):
		disjointedSet[i].first = i
		disjointedSet[i].second = 0
	return disjointedSet
	
cdef int find(Pair *disjointedSet, int x):
	if x == disjointedSet[x].first:
		return x
	else:
		disjointedSet[x].first = find(disjointedSet, disjointedSet[x].first)
		return disjointedSet[x].first

cdef void merge(Pair *disjointedSet,int rep_a, int rep_b):
	if disjointedSet[rep_a].second > disjointedSet[rep_b].second:
		disjointedSet[rep_b].first = rep_a
	else:
		disjointedSet[rep_a].first = rep_b
		if disjointedSet[rep_a].second == disjointedSet[rep_b].second:
			disjointedSet[rep_b].second += 1

cdef int compare_edge (const void * a, const void * b) nogil:
	cdef Edge *aa = <Edge*> (a)
	cdef Edge *bb =  <Edge*> (b)
	cdef int w_a = aa.weight
	cdef int w_b = bb.weight 
	if w_a == w_b:
		return 0
	if w_a > w_b:
		return 1
	else:
		return -1


cdef int n, m
cdef Edge *edges 
cdef Pair *disjointedSet

cdef int i
cdef int re_from
cdef int re_to 	


with open("input.txt", "r") as filein, open("output.txt", "w") as fout:
	n = int(filein.readline())
	m = int(filein.readline())
	edges = <Edge *>malloc((m) * sizeof(Edge))
	if not edges:
		raise MemoryError()
	
	for i in range(m):
		data = filein.readline().split()
		edges[i].v_from = int(data[0])
		edges[i].v_to = int(data[1]) 
		edges[i].weight = int(data[2])
		edges[i].number = i
	
	qsort(edges, m, sizeof(Edge), compare_edge)
	disjointedSet = createSet(n)

	try:
		for i in range(m):
			re_from = find(disjointedSet, edges[i].v_from)
			re_to = find(disjointedSet, edges[i].v_to)
			if re_from != re_to:
				merge(disjointedSet,re_from, re_to)
				fout.write(str(edges[i].number) + "\n")
	finally:
		free(disjointedSet)
		free(edges)