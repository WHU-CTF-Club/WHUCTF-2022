#!/usr/bin/env python3.9
# -*- coding: utf-8 -*-
import string
import random
import socketserver
import signal
from os import urandom
from hashlib import sha256
from flag import FLAG

BANNER = rb"""
  ____  _  _  ____  ____  _  _  ___     ___    __    __  __  ____ 
(_  _)( \/ )(  _ \(_  _)( \( )/ __)   / __)  /__\  (  \/  )( ___)
  )(   \  /  )___/ _)(_  )  (( (_-.  ( (_-. /(__)\  )    (  )__) 
 (__)  (__) (__)  (____)(_)\_)\___/   \___/(__)(__)(_/\/\_)(____)
"""


class GAME:
    def __init__(self):
        random.seed(urandom(32))

    def deal(self):
        n = random.getrandbits(32)
        return str(n)


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
            
            signal.signal(signal.SIGALRM, self.timeout_handler)
            signal.alarm(240)
            
            if not self.proof_of_work():
                self.send('Wrong!')
                return
            

            game = GAME()
            coin = 1000
            count = 0

            self.send('Greetings! This is a console typing game. Can you do it?'
                      'One coin, one chance.')

            signal.alarm(3600)

            while coin :
                coin -= 1
                c = "Mia is friendly. "+ game.deal()
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
    HOST, PORT = '0.0.0.0', 11114
    print("HOST:POST " + HOST + ":" + str(PORT))
    server = ForkedServer((HOST, PORT), Task)
    #with socketserver.TCPServer((HOST, PORT), Task) as server:
        # Activate the server; this will keep running until you
        # interrupt the program with Ctrl-C
    #server = ForkedServer((HOST, PORT), Task)
    server.allow_reuse_address = True
    server.serve_forever()
