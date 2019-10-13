from typing import Tuple
import util

class Rsa:
    def __init__(self, randprime, max_len = 512):
        self.max_length = max(512, max_len)
        self.__maxBorder = 2 ** self.max_length
        self.__minBorder = 2 ** 256
        p = randprime(self.__minBorder, self.__maxBorder)
        q = randprime(self.__minBorder, self.__maxBorder)
        # module
        self.n = p * q
        # Euler's function of n
        u = (p - 1) * (q - 1)
        # opened key
        self.e = self.__calculate_open_key(u)
        # closed key
        self.d = self.__calculate_private_key(self.e, u)

    # u: euler function of module
    @staticmethod
    def __calculate_open_key(u: int) -> int:
        # gcd(u, e) = 1 and e simple number, example Fermat number
        return 65537

    @staticmethod
    def __calculate_private_key(e: int, u: int) -> int:
        # d * e = 1 mod u
        d, x, y = util.advanced_gcd(e, u)
        return x if x > 0 else x + u

    # code: character code to encode,
    # code ^ (open_key) mod n
    def __encode_char(self, code: int) -> int:
        return util.modular_pow(code, self.e, self.n)

    # string: string to encode
    def encode_string(self, string: str) -> Tuple[int, str]:
        result = []

        for char in string:
            result.append(str(self.__encode_char(ord(char))))

        for i, code in enumerate(result):
            if self.max_length > len(code):
                result[i] = ("0" * (self.max_length - len(code))) + code

        return self.max_length, ''.join(result)

    # code: encrypted character code to decode
    # code ^ private_key mod n
    def __decode_char(self, code: int) -> int:
        return pow(code, self.d, self.n)

    # string: string of encrypted characters to decode
    def decode_string(self, string: str) -> Tuple[int, str]:
        codes = [(string[i:i + self.max_length]) for i in range(0, len(string), self.max_length)]
        result = ""
        for code in codes:
            if len(code) < self.max_length:
                return -1, ""
            result += chr(self.__decode_char(int(code)))

        return self.max_length, result