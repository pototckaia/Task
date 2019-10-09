import rsa

#for i in range(10):
rsa_coder = rsa.Rsa()
length, encoded_string = rsa_coder.encode_string("Hello, world!")
#print([(encoded_string[i:i + length]) for i in range(0, len(encoded_string), length)])
decoded_string = rsa_coder.decode_string(encoded_string)
print(decoded_string)