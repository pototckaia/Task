import rsa
import rdprime

rsa_coder = rsa.Rsa(rdprime.randprime, 1024)
length, encoded_string = rsa_coder.encode_string("Hello, world!")
print(length)
print(encoded_string)
decoded_string = rsa_coder.decode_string(encoded_string)
print(decoded_string)
print(rsa_coder.e)
print(rsa_coder.d)
print(rsa_coder.n)