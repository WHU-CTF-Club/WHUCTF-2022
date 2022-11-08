import copy
# Quick hack
import sys
sys.path.append('./source')
# Import symbolic execution
# Import XorSolver
from tqdm import tqdm
from hashlib import *
from Crypto.Util.number import *
r = remote('127.0.0.1', 11111,ssl=False)
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