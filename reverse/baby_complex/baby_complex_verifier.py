from Crypto.Cipher import AES
from numpy import uint32

def __build_uint32(s):
	if len(s) == 4:
		return uint32(s[0] & 0xFF | ((s[1] & 0xFF) << 8) | ((s[2] & 0xFF) << 16) | ((s[3] & 0xFF) << 24))
	else:
		return uint32(0)

# 'S1mpleFirstRound'
def __verify(s):
	x = uint32(0)
	if len(s) == 16:
		for i in range(13):
			t = __build_uint32(s[i : i + 4])
			x ^= t
		if x == 0x61683711:
			return True
	return False

def __read_whole_file(path):
	file = open(path, 'rb')
	file.seek(0, 2)
	size = file.tell()
	file.seek(0, 0)
	ret = file.read(size)
	file.close()
	return ret

def decode(s):
	if __verify(s) == True:
		return AES.new(s, AES.MODE_ECB).decrypt(__read_whole_file('complex_message'))
	else:
		return bytes(0)
