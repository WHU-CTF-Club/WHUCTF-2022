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
   _____       .___.________   _________                       .___
  /     \    __| _/|   ____/  /   _____/_  _  _____________  __| _/
 /  \ /  \  / __ | |____  \   \_____  \\ \/ \/ /  _ \_  __ \/ __ | 
/    Y    \/ /_/ | /       \  /        \\     (  <_> )  | \/ /_/ | 
\____|__  /\____ |/______  / /_______  / \/\_/ \____/|__|  \____ | 
        \/      \/       \/          \/                         \/
'''

guard_menu = br'''
1.Tell the guard my name
2.Go away
'''

sword_menu = br'''1.calculate md5
2.current blood volume
3.say Goodbye
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
        self.blood = 999999999
        self.send(b"You are a dragon slayer")
        self.send(b"You shall not pass, unless you kill the dragon.")
        self.send(b"You have two choices now. Tell me who you are or leave now!")
        self.send(guard_menu, newline=False)
        option = self.recv()
        if option == b'1':
            try:
                self.name = self.register()
                self.send(b"Hello " + self.name)
                self.send(b"Nice to meet you. But I can't let you pass. I can give you a md5 sword. You can use it to kill the dragon.")
                while True:
                    self.send(b"Calculate Md5 and you can play your ace")
                    self.send(sword_menu, newline=False)
                    op = self.recv()
                    if op == b'1':
                        self.magic = os.urandom(64)
                        ans = hashlib.md5(self.magic).hexdigest().encode()
                        self.send(b"calculate Md5 of it: ") 
                        self.send(self.magic)
                        self.send(b"your answer is: ")
                        #self.send(ans)
                        tmp = self.register()
                        if tmp == ans:
                        #if tmp == b'1': 
                            self.send(b"KANG!!!QIANG!!!")
                            self.blood -= random.randint(1,999999)
                        else :
                            self.send(b"WRONG!!!")
                    elif op == b'2':
                        self.send(b"Now the dragon's blood volume is: ")
                        self.send(str(self.blood).encode())
                        self.send(b"Hooo~ Hooo~")
                    elif op == b'3':
                        self.send(b"I'm leaving. Bye~")
                        break
                self.send(b"Oh, you're here again. Let me check your achievement.")
                if self.blood > 0:
                    self.send(b"You are a coward, I am so disappointed.")
                    return
                else:
                    self.send(b"Unbelievable! How did you get it!")
                    self.send(b"The prince asked me to tell you this:")
                    #f = open('flag.txt', 'rb')
                    f = open('L:\\ctf\\crypto\\easy_md5\\flag.txt', 'rb')
                    flag = f.read()
                    f.close()
                    self.send(flag)

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