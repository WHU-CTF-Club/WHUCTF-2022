import hashlib

maze = ["*#########",
		"**########",
		"#*########",
		"***#######",
		"*#***##***",
		"**##****#*",
		"#**######*",
		"#*#*******",
		"**#*######",
		"###*******"]

vis = [ [ 0 for j in range(10) ] for i in range(10) ]

def check(x, y):
	if x >= 0 and y >= 0 and x < 10 and y < 10 and maze[x][y] == '*' and vis[x][y] == False:
		return True
	else:
		return False

path = ['0' for i in range(100)]

def extend(x, y, depth, dir):
	path[depth] = dir
	return solve(x, y, depth + 1)

def solve(x, y, depth):
	if x == 9 and y == 9:
		vis[x][y] = 1
		return True

	if check(x, y) == True:
		vis[x][y] = True
		if extend(x - 1, y, depth, 'W') == True:
			return True
		if extend(x, y - 1, depth, 'A') == True:
			return True
		if extend(x + 1, y, depth, 'S') == True:
			return True
		if extend(x, y + 1, depth, 'D') == True:
			return True

		vis[x][y] = False
		return False

def result():
	ans = ''
	for ch in path:
		if ch == '0':
			return ans
		else:
			ans = ans + ch

solve(0, 0, 0)
print('mayctf{' + hashlib.sha256(result().encode('utf-8')).hexdigest() + '}')
