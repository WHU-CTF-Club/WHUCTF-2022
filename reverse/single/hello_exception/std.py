secrets = list(b'L1jf[VpbnnUYg}=lw prK[wyau|i=<?')

for i in range(len(secrets)):
	secrets[i] ^= i

def rot13(ch):
	if ch >= ord('A') and ch <= ord('Z'):
		return (ch - ord('A') + 13) % 26 + ord('A')
	elif ch >= ord('a') and ch <= ord('z'):
		return (ch - ord('a') + 13) % 26 + ord('a')
	else:
		return ch

ans = ''
for ch in secrets:
	ans += chr(rot13(ch))

print('mayctf{' + ans + '}')
