import rsa
import rdprime

#for i in range(10):
rsa_coder = rsa.Rsa(rdprime.randprime, 1024)
length, encoded_string = rsa_coder.encode_string("Hello, world!")
print(length)
print(encoded_string)
decoded_string = rsa_coder.decode_string(encoded_string)
print(decoded_string)