import hashlib
import collections
from typing import List, Tuple
import random

EllipticCurve = collections.namedtuple('EllipticCurve', 'name p a b g n h')

curve = EllipticCurve(
    'secp256k1',
    # Field characteristic.
    p=0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f,
    # Curve coefficients.
    a=0,
    b=7,
    # Base point.
    g=(0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798,
       0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8),
    # Subgroup order.
    n=0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141,
    # Subgroup cofactor.
    h=1,
)

r"""
a mod b = a - b * floor(a / b)
lcm(a, b) = (a * b) / gcd(a, b), least common multiplier
a * x + b *y = gcd(a, b)"""
def advanced_gcd(a: int, b: int) -> Tuple[int, int, int]:
    xx, yy = 0, 1
    x, y = 1, 0
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx*q
        y, yy = yy, y - yy*q 
    return a, x, y


'''
a * b = 1 (mod m)  -> a^-1 - взаимно простое с m
a * x + m * y = 1
a * x = 1 (mod m)
'''
def reverse_by_mod(k : int, p: int) -> int:
    if k < 0:
        # k ** -1 = p - (-k) ** -1  (mod p)
        return p - reverse_by_mod(-k, p)

    gcd, x, y = advanced_gcd(k, p)

    assert gcd == 1
    assert (k * x) % p == 1

    return x % p


def is_on_curve(point):
    """Returns True if the given point lies on the elliptic curve."""
    if point is None:
        # None represents the point at infinity.
        return True

    x, y = point

    # y^2 = x^3 + ax + b mod point
    return (y*y - x*x*x - curve.a * x - curve.b) % curve.p == 0


def point_neg(point):
    assert is_on_curve(point)

    if point is None:
        return None

    x, y = point
    result = (x, -y % curve.p)
    assert is_on_curve(result)
    return result


def point_add(point1, point2):
    assert is_on_curve(point1)
    assert is_on_curve(point2)

    if point1 is None:
        # 0 + point2 = point2
        return point2

    if point2 is None:
        # point1 + 0 = point1
        return point1

    x1, y1 = point1
    x2, y2 = point2

    if x1 == x2 and y1 != y2:
        # point1 + (-point1) = 0
        return None

    if x1 == x2:
        # This is the case point1 == point2.
        m = (3 * x1 * x1 + curve.a) * reverse_by_mod(2 * y1, curve.p)
    else:
        # This is the case point1 != point2.
        m = (y1 - y2) * reverse_by_mod(x1 - x2, curve.p)

    x3 = m * m - x1 - x2
    y3 = y1 + m * (x3 - x1)
    result = (x3 % curve.p, -y3 % curve.p)
    assert is_on_curve(result)
    return result


"""
Генерирует двоичные разряды n, начиная
с наименее значимого бита.
"""
def bits(n):
    while n:
        yield n & 1
        n >>= 1


def scalar_mult(k, point):

    if k % curve.n == 0 or point is None:
        return None

    if k < 0:
        # k * point = -k * (-point)
        return scalar_mult(-k, point_neg(point))

    result = None
    addend = point

    for bit in bits(k):
        if bit == 1:
            # Add.
            result = point_add(result, addend)
        # Double.
        addend = point_add(addend, addend)
    return result


def make_keypair():
    private_key = random.randrange(1, curve.n)
    public_key = scalar_mult(private_key, curve.g)

    return private_key, public_key


def clip_hash(message_hash):
    z = message_hash >> (message_hash.bit_length() - curve.n.bit_length())

    assert z.bit_length() <= curve.n.bit_length()
    return z


def sign_message(private_key, hash_):
    z = clip_hash(hash_)
    r, s = 0, 0

    while not r or not s:
        k = random.randrange(1, curve.n)
        x, y = scalar_mult(k, curve.g)

        r = x % curve.n
        s = ((z + r * private_key) * reverse_by_mod(k, curve.n)) % curve.n
    return (r, s)


def verify_signature(public_key, hash_, signature):
    z = clip_hash(hash_)

    r, s = signature

    w = reverse_by_mod(s, curve.n)
    u1 = (z * w) % curve.n
    u2 = (r * w) % curve.n

    x, y = point_add(scalar_mult(u1, curve.g),
                     scalar_mult(u2, public_key))

    if (r % curve.n) == (x % curve.n):
        return 'signature matches'
    else:
        return 'invalid signature'