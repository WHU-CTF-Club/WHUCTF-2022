def read_whole_file(path):
	file = open(path, 'rb')
	file.seek(0, 2)
	size = file.tell()
	file.seek(0, 0)
	ret = file.read(size)
	file.close()
	return ret

def write_whole_bytes(path, data):
	file = open(path, 'wb')
	file.write(data)
	file.close()

buffer = read_whole_file('flag.rtf')
writebuffer = []
key = bytes(b'An1M@lcheese@LiTang-DingZhen')

for i in range(len(buffer)):
	writebuffer.append(buffer[i] ^ key[i % len(key)])

write_whole_bytes('flag.rtf.enc', bytes(writebuffer))
