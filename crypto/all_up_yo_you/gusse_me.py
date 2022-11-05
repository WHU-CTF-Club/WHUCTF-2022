#!/usr/bin/env python3.9
# -*- coding: utf-8 -*-
import string
import random
import socketserver
import signal
from os import urandom
from hashlib import sha256
from flag import FLAG
from Crypto.Util.number import getPrime, getRandomNBitInteger, inverse
from fractions import Fraction
from gmpy2 import lcm
import re

N = 512
safe_expr = re.compile(r'^([-+*/0-9.~%^&()=|<>]|and|or|not|MSG)+$')


BANNER = rb"""
  __   __    __      _  _  ____    ____  __     _  _ 
 / _\ (  )  (  )    / )( \(  _ \  (_  _)/  \   / )( \
/    \/ (_/\/ (_/\  ) \/ ( ) __/    )( (  O )  ) \/ (
\_/\_/\____/\____/  \____/(__)     (__) \__/   \____/
"""


def encode(m, n, g):
    r = getRandomNBitInteger(N)
    c = pow(g, m, n*n) * pow(r, n, n*n) % (n*n)
    return c


def decode(c, n, l, u):
    return int(Fraction(pow(c, l, n * n) - 1, n) * u % n)


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

    def timeout_handler(self, signum, frame):
        raise TimeoutError

    def round(self, expr):
        p = getPrime(N)
        q = getPrime(N)

        n = p * q
        g = getRandomNBitInteger(N)
        self.send(f'n = {n}')
        self.send(f'g = {g}')

        a = getRandomNBitInteger(N)
        b = getRandomNBitInteger(N)

        aa = encode(a, n, g)
        bb = encode(b, n, g)

        self.send(f'a = {aa}')
        self.send(f'b = {bb}')

        msg = int(self.recv(prompt='msg = ').decode('l1'))

        l = int(lcm(p - 1, q - 1))
        u = inverse(Fraction(pow(g, l, n * n) - 1, n), n)

        decode_msg = decode(msg, n, l, u)
        eval_msg = eval(expr, None, {'MSG': decode(msg, n, l, u)})

        self.send(f'decode_msg = {decode_msg}')
        self.send(f'eval_msg = {eval_msg}')
        return (a > b) is bool(eval_msg)


    def handle(self):
        try:
            signal.alarm(600)
            self.send(BANNER)

            self.send(b'Greetings! This is a console game. Can you do it?'
                      b'You have to set some rules for yourself!')

            expr = self.recv(prompt=b'Please give me your expr: ').decode('l1')
            print(expr)
            expr = re.sub(r'\s', '', expr)
            

            if safe_expr.match(expr) is None:
                self.send(b'Hacker!!!')
                raise Exception('Hacker?')

            for i in range(100):
                self.send(f'Round: {i}')
                try:
                    assert self.round(expr)
                except:
                    self.send(b'You lost.')
                    break
            else:
                self.send(b'Well done! Flag is yours:')
                self.send(FLAG)

            self.send(b'Bye!')

        except TimeoutError:
            self.send(b'Timeout!')
        except:
            pass
        finally:
            self.request.close()


class ForkedServer(socketserver.ForkingMixIn, socketserver.TCPServer):
    pass


if __name__ == '__main__':
    HOST, PORT = '0.0.0.0', 9995
    print("HOST:POST " + HOST + ":" + str(PORT))
    server = ForkedServer((HOST, PORT), Task)
    #with socketserver.TCPServer((HOST, PORT), Task) as server:
        # Activate the server; this will keep running until you
        # interrupt the program with Ctrl-C
    #server = ForkedServer((HOST, PORT), Task)
    server.allow_reuse_address = True
    server.serve_forever()
