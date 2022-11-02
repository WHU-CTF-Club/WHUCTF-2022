import gmpy2
from Crypto.Util.number import *
from flag import FLAG

flag1 = FLAG.encode()
assert(len(FLAG) == 35)

E = 11
for i in range(50):
    P = getPrime(512)
    Q = getPrime(512)
    N = P * Q
    phi = (P-1) * (Q-1)
    try :
        d = gmpy2.invert(E,phi)
        m = bytes_to_long(flag1)

        c = pow(m, E, N)
        print('N=' + str(N) )
        print('c=' + str(c) )
        print('E=' + str(E) )
        print('------------------------------------------------------')
    except:
        continue;