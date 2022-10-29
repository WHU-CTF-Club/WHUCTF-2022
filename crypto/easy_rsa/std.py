import gmpy2
from Crypto.Util.number import *
import flag

flag1 = flag.encode()
assert(len(flag) == 40)

P = getPrime(1038)
Q = getPrime(512)
N = P * Q
phi = ((P-1) * (Q-1)) // gmpy2.gcd(P-1 , Q-1)

d = getPrime(128)
E = gmpy2.invert(d,phi)
assert(pow(3*d,4) < N)
assert(E < phi)

m = bytes_to_long(flag1)


c = pow(m, E, N)

print('N=' + str(N) )
print('c=' + str(c) )
print('E=' + str(E) )