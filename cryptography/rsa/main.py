import rsa
import rdprime
import argparse
import time

if __name__ == '__main__':

	argsParser = argparse.ArgumentParser()
	argsParser.add_argument('-tdt', '--tdt',
							help='Trial division primality test')
	argsParser.add_argument('-sst', '--sst', 
							help='Solovay–Strassen primality test')
	argsParser.add_argument('-mrt', '--mrt',
							help='Miller–Rabin primality test')
	argsParser.add_argument('-f', '--filename', type=argparse.FileType('r'),
							required=True, help='Encoded file')
	argsParser.add_argument('-k', '--key', type=int,
							default=512, help='Size key')
	args = argsParser.parse_args()

	prefix = 'mrt'
	prime = rdprime.mr_randprime
	if args.tdt:
		prefix = 'tdt'
		prime = rdprime.td_randprime
	if args.sst:
		prefix = 'sst'
		prime = rdprime.ss_randprime
	if args.mrt:
		prefix = 'mrt'
		prime = rdprime.mr_randprime
	print(prefix)
	print(args.key)
	print(args.filename.name)
	chunk_size = 4096

	rsa_coder = rsa.Rsa(prime, args.key)

	start_time = time.time()
	with open(args.filename.name, 'r') as f_in, \
		open('{}_encoded_{}'.format(prefix, args.filename.name), 'w') as f_en, \
		open('{}_decoded_{}'.format(prefix, args.filename.name), 'w') as f_de:

		for chunk in iter(lambda: f_in.read(chunk_size), ''):
			encoded_string = rsa_coder.encode_string(chunk)
			f_en.write(encoded_string)

			decoded_string = rsa_coder.decode_string(encoded_string)
			f_de.write(decoded_string)
	end_time = time.time()

	with open('{}_info_{}'.format(prefix, args.filename.name), 'w') as f_i:
		f_i.writelines(['time {} seconds\n'.format(end_time - start_time),
						'opened key: {}\n'.format(rsa_coder.e),
						'closed key: {}\n'.format(rsa_coder.d),
						'module: {}\n'.format(rsa_coder.n)])