import rsa
import rdprime

rsa_coder = rsa.Rsa(rdprime.td_randprime, 512)
encoded_string = rsa_coder.encode_string("Hello, world!")
print(encoded_string)
decoded_string = rsa_coder.decode_string(encoded_string)
print(decoded_string)
print(rsa_coder.e)
print(rsa_coder.d)
print(rsa_coder.n)