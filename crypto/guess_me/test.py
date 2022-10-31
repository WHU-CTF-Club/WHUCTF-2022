import random
import time
import copy
# Quick hack
import sys
sys.path.append('./source')
# Import symbolic execution
from MT19937 import MT19937, MT19937_symbolic
# Import XorSolver
from XorSolver import XorSolver
import string
from pwn import *
import randcrack
from tqdm import tqdm
from hashlib import *
from itertools import product
from Crypto.Util.number import *
r = remote('127.0.0.1', 11111,ssl=False)
# context(log_level='debug')
ALPHABET = string.ascii_letters + string.digits
r.recvuntil(b'sha256')
rec = r.recvline().decode().replace(' ', '')
print(rec)
rec = rec[rec.find('+')+1::]
suffix = rec[rec.find('+')+1:rec.find(')')]
digest = rec[rec.find('==')+2:-1]
print(f"suffix: {suffix} \ndigest: {digest}")
for i in product(ALPHABET, repeat=4):
 prefix = ''.join(i)
 guess = prefix + suffix
 if sha256(guess.encode()).hexdigest() == digest:
 log.info(f"Find XXXX: {prefix}")
 break
r.sendline(prefix.encode())
# r.interactive()
rc = randcrack.RandCrack()
cards = []
for t in ('Hearts', 'Spades', 'Diamonds', 'Clubs'):
 for p in ('J', 'Q', 'K', 'A'):
 cards.append(f'{p} {t}')
n_test = []
for i in tqdm(range(4992)):
 r.sendlineafter(b'Your guess > ', b'lyutoon')
 r.recvuntil(b'Sorry! My card is ')
 real = r.recvline().decode().strip()[:-1]
 num = cards.index(real)
 n_test.append(num)
t = time.time()
rng_clone = MT19937(state_from_data = (n_test, 4))
print("Time taken: {}s".format(time.time() - t))
for n in n_test:
 assert n == rng_clone() >> (32-4), "Clone failed!"
print("[*] Cloning successful!")
cnt = 0
for i in range(5200 - 4992):
 num = rng_clone() >> (32-4)
 r.sendlineafter(b'Your guess > ', cards[num].encode())
 res = r.recvline().decode()
 print(res)
 if 'Correct' in res:
 cnt += 1
 if cnt >= 200:
 r.interactive()
# # Collecting data
# n_test = []
# for _ in range(624*32//nbits):
# # Get random number from rng and save for later testing
# n_test.append(n)
# t = time.time()
# # Cloning MT19937 from data
# rng_clone = MT19937(state_from_data = (n_test, nbits))
# print("Time taken: {}s".format(time.time() - t))
# # Test if cloning has been successful
# for n in n_test:
# assert n == rng_clone() >> (32-nbits), "Clone failed!"
# print("[*] Cloning successful!")
# print(rng_clone() >> (32-nbits))
# print(rng()