#!/usr/bin/env python3.9
# -*- coding: utf-8 -*-
import string
import random
import socketserver
import signal
from os import urandom
from hashlib import sha256
from Crypto.Util.number import getPrime, getRandomNBitInteger, inverse
from fractions import Fraction
from gmpy2 import lcm
import re
from flag import FLAG

N = 512
safe_expr = re.compile(r'^([-+*/0-9.~%^&()=|<>]|and|or|not|MSG)+$')
BANNER = rb"""
TBDTBDTBDTBD
"""

class GAME:
    def __init__(self):
        pass

    def encode(m, n, g):
        r = getRandomNBitInteger(N)
        c = pow(g, m, n*n) * pow(r, n, n*n) % (n*n)
        return c


    def decode(c, n, l, u):
        return int(Fraction(pow(c, l, n * n) - 1, n) * u % n)


    def round(expr):
        p = getPrime(N)
        q = getPrime(N)

        n = p * q
        g = getRandomNBitInteger(N)
        print('n =', n)
        print('g =', g)

        a = getRandomNBitInteger(N)
        b = getRandomNBitInteger(N)

        print('a =', encode(a, n, g))
        print('b =', encode(b, n, g))

        msg = int(input("msg = "))

        l = int(lcm(p - 1, q - 1))
        u = inverse(Fraction(pow(g, l, n * n) - 1, n), n)

        return (a > b) is bool(eval(expr, None, {'MSG': decode(msg, n, l, u)}))


class Task(socketserver.BaseRequestHandler):
    def _recv_all(self):
        BUFF_SIZE = 1024
        data = b''
        while True:
            part = self.request.recv(BUFF_SIZE)
            data += part
            if len(part) < BUFF_SIZE:
                break
        return data.strip()

    def send(self, msg, newline=True):
        if isinstance(msg, str):
            msg = msg.encode()
        if newline:
            msg += b'\n'
        self.request.sendall(msg)

    def recv(self, prompt='> '):
        self.send(prompt, newline=False)
        return self._recv_all()

    def proof_of_work(self):
        random.seed(urandom(32))
        alphabet = string.ascii_letters + string.digits
        proof = ''.join(random.choices(alphabet, k=32))
        hash_value = sha256(proof.encode()).hexdigest()
        self.send(f'sha256(XXXX+{proof[4:]}) == {hash_value}')
        nonce = self.recv(prompt='Give me XXXX > ')
        if len(nonce) != 4 or sha256(nonce + proof[4:].encode()).hexdigest() != hash_value:
            return False
        return True

    def timeout_handler(self, signum, frame):
        raise TimeoutError

    def handle(self):
        try:
            self.send(BANNER)
            
            #signal.signal(signal.SIGALRM, self.timeout_handler)
            #signal.alarm(240)
           
            if not self.proof_of_work():
                self.send('Wrong!')
                return
            

            game = GAME()
            coin = 1000
            count = 0

            self.send('Greetings! This is a console typing game(not). Can you do it?'
                      'One coin, one chance.')

            #signal.alarm(3600)

            while coin :
                coin -= 1
                c = "Mia is friendly. "+ game.deal()
                if count >= 666:
                    self.send(f'You need to type: ')
                else:
                    self.send(f'You need to type: {c}')
                r = self.recv(prompt='Yours > ').decode('l1')
                if r == c:
                    count += 1
                    self.send(f'Right! Your progress: {count}/999.')
                    if count >= 999:
                        self.send('You are a Incredible Typist! Flag is yours:')
                        self.send(FLAG)
                        break
                else:
                    self.send(f'Sorry! You need to type {c}.')


            if coin == 0:
                self.send('You have no coin! See you later.')

            self.send('Bye!')

        except TimeoutError:
            self.send('Timeout!')
        except:
            pass
        finally:
            self.request.close()


class ForkedServer(socketserver.ForkingMixIn, socketserver.TCPServer):
    pass


if __name__ == '__main__':
    HOST, PORT = '0.0.0.0', 11115
    print("HOST:POST " + HOST + ":" + str(PORT))
    server = ForkedServer((HOST, PORT), Task)
    #with socketserver.TCPServer((HOST, PORT), Task) as server:
        # Activate the server; this will keep running until you
        # interrupt the program with Ctrl-C
    #server = ForkedServer((HOST, PORT), Task)
    server.allow_reuse_address = True
    server.serve_forever()

def main():
    expr = input('Hello, Give me your expr: ')
    expr = re.sub(r'\s', '', expr)

    if safe_expr.match(expr) is None:
        raise Exception('Hacker?')

    for i in range(100):
        print('Round:', i)
        try:
            assert round(expr)
        except:
            print('You lost.')
            break
    else:
        print('Congratulations!')
        print(open('/flag').read())


if __name__ == '__main__':
    main()