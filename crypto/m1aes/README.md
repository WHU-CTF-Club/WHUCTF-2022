# Description
LONG DESC

# Difficulty
⭐⭐⭐

# Flag
`FLAG`


# WriteUp
虽然似乎在模仿AES，但是实际上明文和密文是一一映射的，复杂度不是恶心的100^48 而只是100*48 ，穷举是很快的。一个小障碍是N1ES.py 第71行的L, R = R, L ，这导致了明文的[0:8] 、[8:16]、[16:24]、[24:32]、[32:40]、[40:48] 分别对应的是密文的[8:16]、[0:8] 、[24:32]、[16:24]、[40:48]、 [32:40] ，写穷举脚本时需要注意。
或者说稍微改一下加密就能解密了
```python
def decrypt(self, res):
        print '-' * 56
        print 'DECODE --------'
        res = base64.b64decode(res)
        print 'len:', len(res)
        print ap(res)
        flag = ''
        for i in range(len(res) / 16):
            block = res[i * 16:(i + 1) * 16]
            L = block[:8]
            R = block[8:]
            # L, R = R, L
            for round_cnt in reversed(range(32)):
                L, R = R, (unround_add(L, self.Kn[round_cnt]))
                print 'L:', ap(L), 'R:', ap(R), 'round_cnt:', round_cnt
            L, R = R, L
            flag += L + R
        print 'FLAG:', ap(flag)
        print 'FLAG:', flag


    def decrypt(self, res):
        print '-' * 56
        print 'DECODE --------'
        res = base64.b64decode(res)
        print 'len:', len(res)
        print ap(res)
        flag = ''
        for i in range(len(res) / 16):
            block = res[i * 16:(i + 1) * 16]
            L = block[:8]
            R = block[8:]
            # L, R = R, L
            for round_cnt in reversed(range(32)):
                L, R = R, (unround_add(L, self.Kn[round_cnt]))
                print 'L:', ap(L), 'R:', ap(R), 'round_cnt:', round_cnt
            L, R = R, L
            flag += L + R
        print 'FLAG:', ap(flag)
        print 'FLAG:', flag
```