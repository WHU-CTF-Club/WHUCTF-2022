from Crypto.Cipher import AES
import os
from hashlib import sha256
import socketserver
import signal
import string
import random
import hashlib
 
table = string.ascii_letters + string.digits
BANNER = br'''
 __      __.__                                      
/  \    /  \__| ____    ____   _____ _____    ____  
\   \/\/   /  |/    \  / ___\ /     \\__  \  /    \ 
 \        /|  |   |  \/ /_/  >  Y Y  \/ __ \|   |  \
  \__/\  / |__|___|  /\___  /|__|_|  (____  /___|  /
       \/          \//_____/       \/     \/     \/ 
'''

guard_menu = br'''
1.Tell me her position
2.Go away
'''

def Pad(msg):
    return msg + os.urandom((16 - len(msg) % 16) % 16)


class Task(socketserver.BaseRequestHandler):
    def _recvall(self):
        BUFF_SIZE = 2048
        data = b''
        while True:
            part = self.request.recv(BUFF_SIZE)
            data += part
            if len(part) < BUFF_SIZE:
                break
        return data.strip()

    def send(self, msg, newline=True):
        try:
            if newline:
                msg += b'\n'
            self.request.sendall(msg)
        except:
            pass

    def recv(self, prompt=b'[-] '):
        self.send(prompt, newline=False)
        return self._recvall()

    def proof_of_work(self):
        proof = (''.join([random.choice(table) for _ in range(12)])).encode()
        sha = sha256(proof).hexdigest().encode()
        self.send(b"[+] sha256(XXXX+" + proof[4:] + b") == " + sha)
        XXXX = self.recv(prompt=b'[+] Give Me XXXX :')
        if len(XXXX) != 4 or sha256(XXXX + proof[4:]).hexdigest().encode() != sha:
            return False
        return True

    def register(self):
        self.send(b'')
        username = self.recv()
        return username

    def handle(self):
        #signal.alarm(50)
        #if not self.proof_of_work():
        #   return
        self.send(BANNER, newline=False)
        self.east_longitude = 1354545625
        self.north_latitude = 348045625
        self.send(b"You are my wingman.")
        self.send(b"You are the only one who can help me")
        self.send(b"You have two choices now. Tell me where she is or leave now!")
        self.send(guard_menu, newline=False)
        option = self.recv()
        if option == b'1':
            try:
                self.send(b"east_longitude * 10000000:(+-1000000) ") 
                ee = int(self.register())
                self.send(b"north_latitude * 10000000:(+-1000000) ")
                nn = int(self.register())
                
                if ee <= self.east_longitude+1000000 and ee >= self.east_longitude-1000000:
                    if nn <= self.north_latitude+1000000 and ee >= self.east_longitude-1000000:
                        self.send(b"Unbelievable! How did you get it!")
                        self.send(b"This is my award:")
                        #f = open('flag.txt', 'rb')
                        f = open('L:\\ctf\\misc\\wingman\\flag.txt', 'rb')
                        flag = f.read()
                        f.close()
                        self.send(flag)
                else:
                    self.send(b"You are a bad wingman.")
            except:
                self.request.close()
        if option == b'2':
            self.send(b"Stay away from here!")
        self.request.close()
'''
class ThreadedServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

class ForkedServer(socketserver.ForkingMixIn, socketserver.TCPServer):
    pass
'''

if __name__ == "__main__":
    HOST, PORT = '0.0.0.0', 11111
    print("HOST:POST " + HOST + ":" + str(PORT))
    #server = ForkedServer((HOST, PORT), Task)
    with socketserver.TCPServer((HOST, PORT), Task) as server:
        # Activate the server; this will keep running until you
        # interrupt the program with Ctrl-C
    #server = ForkedServer((HOST, PORT), Task)
        server.allow_reuse_address = True
        server.serve_forever()