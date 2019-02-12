import re
 
class Set:
    def __init__(self, parent, rank):
        self.parent = parent
        self.rank = rank # Р Р°Р·РјРµСЂ РґРµСЂРµРІР°
 
def find_set(set, a):
    if a == set[a].parent:
        return a
    set[a].parent = find_set(set, set[a].parent)
    return set[a].parent
 
def union_set(set, a, b):
    a = find_set(set, a)
    b = find_set(set, b)
    if a != b:
        if set[a].rank > set[b].rank:
            set[b].parent = a
            set[a].rank += set[b].rank
        else:
            set[a].parent = b
            set[b].rank += set[a].rank
 
with open("input.txt", "r") as fin:
    set = []
    k_p = 0
    line_p = ''
    for line in fin:
        k = 0
        j = 0
        for i in range(len(line)):
            if line_p and line_p[i] == ' ':
                j += 1
            if line[i] != ' ': continue
            set.append(Set(len(set), 0))
            l = len(set) - 1
            if i >= 1 and line[i - 1] == ' ':
                union_set(set, l, l - 1)
            if line_p and line_p[i] == ' ':
                b = l-k-k_p+j-1
                union_set(set, l, b)
            k += 1
        line_p = line
        k_p = k
 
    count = 0
    for i in range(len(set)):
        if find_set(set, i) == i:
            count+= 1
 
with open('output.txt', 'w') as fout:
    fout.write(str(count))
