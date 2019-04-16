import re
from collections import Counter

class Polynome:
	def __init__(self, str):
		self.terms = [{'cof': 1, 'str': str}, ]

	def __pos__(self):
		return self

	def __neg__(self):
		self.terms = [{'cof': -t['cof'], 'str': t['str']} for t in self.terms]
		return self

	def __add__(self, other):
		self.terms += other.terms
		return self

	def __sub__(self, other):
		self.terms += other.__neg__().terms
		return self

	def __mul__(self, other):
		terms = []
		for t in self.terms:
			for l in other.terms:
				terms.append({'cof': t['cof'] * l['cof'], 'str': t['str'] + l['str']})
		self.terms = terms
		return self

	def __str__(self):

		# Приведение подобных
		dic = {}
		for term in self.terms:
			s = ''.join(sorted(term['str']))
			if s in dic:
				dic[s] += term['cof']
			else:
				dic[s] = term['cof']
		terms = [[key, val] for key, val in dic.items()]
		terms.sort(key=lambda x: -x[1])

		res = ''
		for term in terms:
			if not term[1]: continue
			count = sorted(Counter(term[0]).items())

			node = '' if not res or term[1] < 0 else '+'
			node += str(term[1]) + '*'
			if term[1] == 1:
				node = '+'
			elif term[1] == -1:
				node = '-'

			node += '*'.join([c[0] if c[1] == 1 else c[0] + '^' + str(c[1]) for c in count])
			res += node
		res = res if res else '0'
		return res



with open('input.txt', 'r') as fin:
		text = re.sub(r"(\w)", "Polynome('" + r"\1" + r"')", fin.readline().rstrip("\n"))

pol = eval(text)

with open('output.txt', 'w') as fout:
	fout.write(str(pol))