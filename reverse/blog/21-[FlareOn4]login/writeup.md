## 0x01 - Analyse
```html
<!DOCTYPE Html />
<html>
    <head>
        <title>FLARE On 2017</title>
    </head>
    <body>
        <input type="text" name="flag" id="flag" value="Enter the flag" />
        <input type="button" id="prompt" value="Click to check the flag" />
        <script type="text/javascript">
            document.getElementById("prompt").onclick = function () {
                var flag = document.getElementById("flag").value;
                var rotFlag = flag.replace(/[a-zA-Z]/g, function(c){return String.fromCharCode((c <= "Z" ? 90 : 122) >= (c = c.charCodeAt(0) + 13) ? c : c - 26);});
                if ("PyvragFvqrYbtvafNerRnfl@syner-ba.pbz" == rotFlag) {
                    alert("Correct flag!");
                } else {
                    alert("Incorrect flag, rot again");
                }
            }
        </script>
    </body>
</html>
```

一眼`rot13`，直接解密即可。

```python
code = 'PyvragFvqrYbtvafNerRnfl@syner-ba.pbz'
ans = ''

for t in code:
  ch = ord(t)
  if ch >= ord('a') and ch <= ord('z'):
    ans += chr((ch - ord('a') + 13) % 26 + ord('a'))
  elif ch >= ord('A') and ch <= ord('Z'):
    ans += chr((ch - ord('A') + 13) % 26 + ord('A'))
  else:
    ans += chr(ch)

print('flag{' + ans + '}')
```

## 0x02 - Flag
`flag{ClientSideLoginsAreEasy@flare-on.com}`
