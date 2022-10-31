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
 ___      ___       __        ______  ___________   __        __     
|"  \    /"  |     /""\      /    " \("     _   ") /""\      |" \    
 \   \  //   |    /    \    // ____  \)__/  \\__/ /    \     ||  |   
 /\\  \/.    |   /' /\  \  /  /    ) :)  \\_ /   /' /\  \    |:  |   
|: \.        |  //  __'  \(: (____/ //   |.  |  //  __'  \   |.  |   
|.  \    /:  | /   /  \\  \\        /    \:  | /   /  \\  \  /\  |\  
|___|\__/|___|(___/    \___)\"_____/      \__|(___/    \___)(__\_|_) 
"""


class GAME:
    def __init__(self):
        random.seed(urandom(32))
        self.boxs = []
        for t in ('Red_box', 'Blue_box', 'Yellow_box', 'Green_box'):
            for p in ('Candy', 'Chips', 'Pizza', 'Popcorn'):
                self.boxs.append(f'{p} in {t}')

    def deal(self):
        n = random.getrandbits(4)
        return self.boxs[n]


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
            signal.alarm(60)
            
            if not self.proof_of_work():
                self.send('Wrong!')
                return
            

            game = GAME()
            coin = 6000
            count = 0

            self.send('Greetings! I will hide something in boxes, if you can guess where i hide what 200 times in a row. '
                      'One coin, one chance.')

            signal.alarm(3600)

            while coin :
                coin -= 1
                c = game.deal()
                r = self.recv(prompt='Your guess > ').decode('l1')
                if r == c:
                    count += 1
                    self.send(f'Right! Your progress: {count}/200.')
                    if count >= 200:
                        self.send('You are a Incredible MIND READER! Flag is yours:')
                        self.send(FLAG)
                        break
                else:
                    count = 0
                    self.send(f'Sorry! Truth is {c}.')

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
    HOST, PORT = '0.0.0.0', 11113
    print("HOST:POST " + HOST + ":" + str(PORT))
    server = ForkedServer((HOST, PORT), Task)
    #with socketserver.TCPServer((HOST, PORT), Task) as server:
        # Activate the server; this will keep running until you
        # interrupt the program with Ctrl-C
    #server = ForkedServer((HOST, PORT), Task)
    server.allow_reuse_address = True
    server.serve_forever()
