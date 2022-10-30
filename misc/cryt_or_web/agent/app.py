from Crypto import Random
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_v1_5 as Cipher_pkcs1_v1_5
import base64
from flask import Flask
from flask import render_template, redirect, url_for
from flask import request, session

app = Flask(__name__)

@app.before_request
def before_action():
    # 伪随机数生成器
    random_generator = Random.new().read
    # rsa算法生成实例
    rsa = RSA.generate(1024, random_generator)
    # 私钥的生成
    private_pem = rsa.exportKey()
    with open("private.pem", "wb") as f:
        f.write(private_pem)
    # 公钥的生成
    public_pem = rsa.publickey().exportKey()
    with open("public.pem", "wb") as f:
        f.write(public_pem)


@app.route('/encrypt', methods=['GET'])
def encrypt():
    if request.method == 'GET':
        message = "FAKE_HINT"
        rsakey = RSA.importKey(open("public.pem").read())
        cipher = Cipher_pkcs1_v1_5.new(rsakey)  # 创建用于执行pkcs1_v1_5加密或解密的密码
        cipher_text = base64.b64encode(cipher.encrypt(message.encode('utf-8')))
        return render_template('encrypt.html', a=cipher_text.decode('utf-8'))

@app.route('/decrypt', methods=['GET'])
def decrypt():
    if request.method == 'GET':
        cipher_text = "JdUt22KMYhlapZosoogmXdrWR4LQGUB80PsUPiuTMXh3KCu8AqOVK79b7qO5+nJ9vROzPPbvHuI7eYlhTj4LabNotVCIMejeUSTlCGoXAaK11BcnofjobV9fpXsfG/sPE+b+sys31/+yG9SImPDXqL5WVVYADvIoGDOH4TWc7C4="
        encrypt_text = cipher_text.encode('utf-8')
        rsakey = RSA.importKey(open("private.pem").read())
        cipher = Cipher_pkcs1_v1_5.new(rsakey)  # 创建用于执行pkcs1_v1_5加密或解密的密码
        text = cipher.decrypt(base64.b64decode(encrypt_text),"error")
        return render_template('decrypt.html', a=text.decode('utf-8'))


if __name__ == '__main__':
    app.run('0.0.0.0', 80)