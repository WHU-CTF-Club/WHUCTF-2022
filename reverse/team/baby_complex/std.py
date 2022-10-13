import base64
from Crypto.Cipher import AES
from Crypto.Cipher import ARC4

def read_whole_file(path : str):
	file = open(path, 'rb')
	file.seek(0, 2)
	size = file.tell()
	file.seek(0, 0)
	ret = file.read(size)
	file.close()
	return ret

def buffer_pe_steg(buf : bytes):
	length = buf[2]
	return buf[3 : 3 + length]

def file_pe_steg(path : str):
	return buffer_pe_steg(read_whole_file(path))

rc4key = base64.decodebytes(file_pe_steg('baby_complex_net.exe'))
aesdata = AES.new(b'S1mpleFirstRound', AES.MODE_ECB).decrypt(read_whole_file('complex_message'))
flag = ARC4.new(rc4key).decrypt(buffer_pe_steg(aesdata))

print(flag)
