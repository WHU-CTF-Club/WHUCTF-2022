import requests
import re

url = 'http://localhost:8088/index.php'

sess = requests.session()
def get_start():
    sess.get(url=url+'?start')

def run_typing():
    res = sess.get(url=url)
    inputWord = re.findall(r'<h1 class="typing">(.*?)</h1>', res.text)[0]
    for _ in range(6700):
        print(inputWord)
        res = sess.get(url=url+'?input='+inputWord)
        inputWord = re.findall(r'<h1 class="typing">(.*?)</h1>', res.text)[0]

def get_flag():
    res = sess.get(url=url)
    flag = re.findall(r'mayctf{(.*?)}', res.text)[0]
    print('mayctf{'+flag+'}')

def main():
    get_start()
    run_typing()
    get_flag()

if __name__ == '__main__':
    main()