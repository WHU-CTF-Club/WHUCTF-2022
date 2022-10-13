from Crypto.Cipher import AES

def read_whole_file(path : str):
	file = open(path, 'rb')
	file.seek(0, 2)
	size = file.tell()
	file.seek(0, 0)
	ret = file.read(size)
	file.close()
	return ret

# Step-1: steg b64 encoded rc4 key in .NET
# rc4key = 'B64EncodedMeHere'
# QjY0RW5jb2RlZE1lSGVyZQ==\n
# len = 25
netdata = read_whole_file('baby_complex_net.exe')
netfile = open('baby_complex_net.exe', 'wb')
netcode = b'\x19QjY0RW5jb2RlZE1lSGVyZQ==\n'
netfile.write(netdata[0 : 2] + netcode + bytes(57 - len(netcode)) + netdata[59 : len(netdata)])
netfile.close()

# Step-2: steg rc4 encoded flag in native
# flag = mayctf{secsome_d0oest_like_c0mpl3x_prOblem!}
# b'\x97\xed&\x87\xcd\xf2\x90\x85\x16s\xab\xe6\xf4{\xcf^[\xedr\x04\x85\xfe\r\x0c\xba\\q\x1e<8\x91$\x06~<\xa2\xddPG\xfe)XP\x84'  
# len = 44
nativedata = read_whole_file('baby_complex_native.exe')
nativefile = open('complex_message', 'wb')
nativecode = b'\x2c\x97\xed&\x87\xcd\xf2\x90\x85\x16s\xab\xe6\xf4{\xcf^[\xedr\x04\x85\xfe\r\x0c\xba\\q\x1e<8\x91$\x06~<\xa2\xddPG\xfe)XP\x84'
aesdata = AES.new(b'S1mpleFirstRound', AES.MODE_ECB).encrypt(nativedata[0 : 2] + nativecode + bytes(57 - len(nativecode)) + nativedata[59 : len(nativedata)])
nativefile.write(aesdata)
nativefile.close()
