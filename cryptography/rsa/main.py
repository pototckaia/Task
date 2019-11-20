import rsa
import rdprime
import argparse
import time

if __name__ == '__main__':

	argsParser = argparse.ArgumentParser()
	argsParser.add_argument('-tdt', '--tdt', action='store_true',
							help='Trial division primality test')
	argsParser.add_argument('-sst', '--sst', action='store_true',
							help='Solovay–Strassen primality test')
	argsParser.add_argument('-mrt', '--mrt',action='store_true',
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

	start_time = time.time()
	rsa_coder = rsa.Rsa(prime, args.key)
	end_time = time.time()
	generate_rsa_key = end_time - start_time
	print('generate rsa key, {} seconds'.format(generate_rsa_key))

	start_time = time.time()
	with open(args.filename.name, 'r') as f_in, \
		open('{}_encoded_{}'.format(prefix, args.filename.name), 'w') as f_en:

		for chunk in iter(lambda: f_in.read(chunk_size), ''):
			encoded_string = rsa_coder.encode_string(chunk)
			f_en.write(encoded_string)
	end_time = time.time()
	encode_time = end_time - start_time
	print('encode file, {} seconds'.format(encode_time))

	start_time = time.time()
	with open('{}_encoded_{}'.format(prefix, args.filename.name), 'r') as f_en, \
		open('{}_decoded_{}'.format(prefix, args.filename.name), 'w') as f_de:

		for chunk in iter(lambda: f_en.read(chunk_size), ''):
			decoded_string = rsa_coder.decode_string(chunk)
			f_de.write(decoded_string)
	end_time = time.time()
	decode_time = end_time - start_time
	print('decode file, {} seconds'.format(decode_time))

	with open('{}_info_{}'.format(prefix, args.filename.name), 'w') as f_i:
		f_i.writelines(['key: {}\n'.format(rsa_coder.max_length),
						'time generate rsa key: {} seconds\n'.format(generate_rsa_key),
						'encode time: {} seconds\n'.format(encode_time),
						'decode time: {} seconds\n'.format(decode_time),
						'opened key: {}\n'.format(rsa_coder.e),
						'closed key: {}\n'.format(rsa_coder.d),
						'module: {}\n'.format(rsa_coder.n)])