'''
протокол диффи-хеллмана
1.  p является случайным простым числом
	g является первообразным корнем по модулю p - примитивный элемент группы Z_p
2. расспространяем p, q
3. A: 1 < a < p, x =  g^a mod p
   B: 1 < b < p, y = g^b mod p
4. x swap y
5. k = y ^ a mod p= x ^ b mod p 


Протокол можно изменить таким образом, чтобы вместо мультипликативной группы простого умножения 
использовать аддитивную группу сложения точек эллиптической кривой. 
1. Стороны договорились о группе точек эллиптической кривой E, 
её циклической подгруппе G мощности n и генераторе g группы G (или хотя бы достаточно большой подгруппы группы G).
2. Алиса выбирает случайное a
3. Боб выбирает случайное  b
4. Алиса вычисляет точку K = a x b
В качестве нового сессионного ключа стороны могут выбрать, например, первую координату найденной точки K.

Протокол Эль-Гамаля

- Генерируется случайное простое число p.
- Выбирается целое число g — первообразный корень p.
- Выбирается случайное целое число x такое, что 1 < x < p − 1.
- Вычисляется y=g^x mod p.
- Открытым ключом является y, закрытым ключом — число x.
(p, g, y)

Сообщение M должно быть меньше числа p
- Выбирается сессионный ключ — случайное целое число k такое, что 1 < k < p − 1.
- Вычисляются числа a = g^k mod p и b = y^k M mod p.
- Пара чисел ( a , b ) является шифротекстом.

Зная закрытый ключ x, исходное сообщение можно вычислить из шифротекста ( a , b ) :
	M = b (( a^x )^(− 1)) mod p 

Подпись
предполагается наличие фиксированной хеш-функции h(⋅), значения которой лежат в интервале (1, p−1). 

Подпись сообщений
Для подписи сообщения M
- m = h (M)
- Выбирается случайное число 1 < k < p − 1 взаимно простое с p − 1 
	и вычисляется r = g ^k mod p
- Вычисляется число s ≡ (m − x*r)k^(− 1) ( mod p − 1 ) 
	где k^(-1) - мультипликативное обратное.
- Подписью сообщения M  является пара (r, s)

Проверка подписи
Открытый ключ (p, g, y), подпись (r, s) сообщения M
- проверяется выполнимость 0 < r < p, 0 < s < p - 1
- если хоты бы одно из них не выполняется, то подпись не верная
- m = h(M)
- верна если y^r r^s = g^m (mod p)

Число k  должно быть случайным и не должно дублироваться для различных подписей, полученных при одинаковом значении секретного ключа.



'''

import hashlib
import argparse
from random import randint
from sympy import randprime
from primitive import get_prime_and_generator, randcoprime, reverse_by_mod

if __name__ == '__main__':

	argsParser = argparse.ArgumentParser()
	argsParser.add_argument('-f', '--filename', type=argparse.FileType('r'),
							required=True, help='Encoded file')
	argsParser.add_argument('-g', '--create',
							action='store_true', help='Create key and generate dg')
	argsParser.add_argument('-c', '--check', 
							action='store_true', help='Check dg')

	args = argsParser.parse_args()
	chunk_size = 4096
	file_name = args.filename.name

	file_hash = hashlib.sha256()
	print('read file')
	with open(file_name, 'r') as f_in:
		for chunk in iter(lambda: f_in.read(chunk_size), ''):
			file_hash.update(chunk.encode('utf-8'))

	m = int(file_hash.hexdigest(), 16)
	print('hash {}'.format(m))

	if args.create:
		# - Генерируется случайное простое число p.
		# - Выбирается целое число g — первообразный корень p.
		# - Выбирается случайное целое число x такое, что 1 < x < p − 1.
		# - Вычисляется y=g^x mod p.
		# - Открытым ключом является y, закрытым ключом — число x.
		# (p, g, y)
		p, g = get_prime_and_generator(256)
		x = randint(2, p - 2)
		y = pow(g, x, p)

		# Для подписи сообщения M
		# - m = h (M)
		# - Выбирается случайное число 1 < k < p − 1 взаимно простое с p − 1 
		# 	и вычисляется r = g ^k mod p
		# - Вычисляется число s ≡ (m − x*r)k^(− 1) ( mod p − 1 ) 
		# 	где k^(-1) - мультипликативное обратное.
		# - Подписью сообщения M  является пара (r, s)
		k = randcoprime(p - 1)
		r = pow(g, k, p)
		s = ((m - x*r) * reverse_by_mod(k, p - 1)) % (p - 1)
		print('dg ', r, s)

		with open('{}_pub'.format(file_name), 'w') as fin:
			fin.write('{}\n {}\n {} \n'.format(g, p, y))
			fin.write('{} \n {}'.format(r, s))
	elif args.check:
			
		g, p, y, r, s = 0, 0, 0, 0, 0
		with open('{}_pub'.format(file_name), 'r') as fin:
			lines_list = fin.readlines	()
			vals = [int(val) for line in lines_list for val in line.split()]
			g, p, y, r, s = vals[0], vals[1], vals[2], vals[3], vals[4]
		# Открытый ключ (p, g, y), подпись (r, s) сообщения M
		# - проверяется выполнимость 0 < r < p, 0 < s < p - 1
		# - если хоты бы одно из них не выполняется, то подпись не верная
		# - m = h(M)
		# - верна если y^r r^s = g^m (mod p)
		isOwner = 0 < r < p and 0 < s < p - 1 and \
				(pow(y, r, p) * pow(r, s, p)) % p == pow(g, m, p)
		print(isOwner)