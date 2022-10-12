# CTF - Crypto和Blockchain入门简介
> maybemia
## Crypto入门
Crypto方向为密码学原理及应用。掌握古典密码学和现代密码学，分析密码算法和协议，计算密钥和进行加解密操作。
### 古典密码学
其中，古典密码学，作为一种实用性艺术存在，其编码和破译通常依赖于设计者和敌手的创造力与技巧，并没有对密码学原件进行清晰的定义。古典密码学主要包含以下几个方面：

- 单表替换加密（Monoalphabetic Cipher）
- 多表替换加密（Polyalphabetic Cipher）
- 奇奇怪怪的加密方式
大多可使用在线工具解密，较为简单，多为flag最后一层的加密手段。

### 现代密码学
现代密码学起源于 20 世纪中后期出现的大量相关理论，1949 年香农（C. E. Shannon）发表的题为《保密系统的通信理论》的经典论文标志着现代密码学的开始。现代密码学主要包含以下几个方面：

- 对称加密（Symmetric Cryptography），以 DES，AES，RC4 为代表。
- 非对称加密（Asymmetric Cryptography），以 RSA，ElGamal，椭圆曲线加密为代表。
- 哈希函数（Hash Function），以 MD5，SHA-1，SHA-512 等为代表。
- 数字签名（Digital Signature），以 RSA 签名，ElGamal 签名，DSA 签名为代表。
其中，对称加密体制主要分为两种方式：

- 分组密码（Block Cipher），又称为块密码。
- 序列密码（Stream Cipher），又称为流密码。

现代密码学对于数学要求较高（信安数基），尤其是数论。题目通常要求在十数行加密代码中找到加密方法的漏洞，从而利用给出的密文和部分加密参数写出脚本解密。

在做密码学题目时，不要害怕，首先积极使用搜索引擎，查看该加密方法是否已经有破解方式，不限于博客、论文和github；若无法找到，则需考验你数学分析的能力了。

常用python库：
- gmpy2
- pycryptodome(Crypto)
- libnum
- hashlab 
- z3
- openssl


常用工具
- yafu 大整数分解
- hashcat
- RsaCtfTool
- [rsatool](https://github.com/ius/rsatool)
- openssl
- http://factordb.com/

## Blockchain 入门
区块链安全主要分为 公链安全 和 智能合约 安全，常见为智能合约安全。

### 智能合约安全
Ethereum 是区块链 2.0 的代表产物，因其底层使用区块链技术，所以继承区块链的各种特性，其中有一项便是 代码一旦上链，便难以篡改或更改，所以我们需要额外关注它的安全。

智能合约 (Smart Contract) 是 Ethereum 中最为重要的一个概念，允许在没有第三方的情况下进行可信交易，这些交易可追踪且不可逆转。

CTF 中有关于 Ethereum Security 主要涉及到的是 Solidity Security。 
下面介绍一下需要具备的基本能力。
- 对区块链基本知识以及交易本质有所了解
- 熟悉并掌握 Solidity 编程语言及以太坊虚拟机 EVM 运行机制
- 熟悉各种测试链，包括私链
- 熟悉 Remix、MetaMask、web3.js、web3.py 等工具或库的使用
- 了解并掌握以太坊智能合约各种漏洞及其攻击原理
- 对底层 opcodes 理解透彻
- 较强的程序理解和逆向分析能力

本次mayctf中区块链题目并不难，对上述要求不高，大家可以大胆尝试。

常用工具
- docker 
- MetaMask
- [Remix](http://remix.ethereum.org/)
- web3
- [solidity智能合约逆向](https://ethervm.io/decompile)
