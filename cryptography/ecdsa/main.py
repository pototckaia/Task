import hashlib
import argparse
import elliptic as el

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

		private, public = el.make_keypair()
		print("Private key:", private)
		print("Public key:", public)

		signature = el.sign_message(private, m)
		print(signature)

		with open('{}_pub'.format(file_name), 'w') as fin:
			fin.write('{}\n {}\n'.format(public[0], public[1]))
			fin.write('{} \n {}'.format(signature[0], signature[1]))
	elif args.check:
			
		public, signature = (0, 0), (0, 0)
		with open('{}_pub'.format(file_name), 'r') as fin:
			lines_list = fin.readlines	()
			vals = [int(val) for line in lines_list for val in line.split()]
			public, signature = (vals[0], vals[1]), (vals[2], vals[3])
		
		print(el.verify_signature(public, m, signature))