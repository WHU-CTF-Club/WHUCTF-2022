## 0x00 - Install JEB
[下载](https://bbs.pediy.com/thread-268316.htm)
[激活](https://www.52pojie.cn/thread-1598242-1-1.html)
之后我们的讲解中对安卓java层的逆向全部将使用`JEB`进行讲解

## 0x01 - Decompile
使用`JEB`打开apk文件，得到：
```java
package com.example.findit;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.MenuItem;
import android.view.View.OnClickListener;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends ActionBarActivity {
    @Override  // android.support.v7.app.ActionBarActivity
    protected void onCreate(Bundle arg8) {
        super.onCreate(arg8);
        this.setContentView(0x7F030018);  // layout:activity_main
        Button btn = (Button)this.findViewById(0x7F05003D);  // id:widget3
        EditText edit = (EditText)this.findViewById(0x7F05003E);  // id:widget2
        TextView text = (TextView)this.findViewById(0x7F05003F);  // id:widget1
        btn.setOnClickListener(new View.OnClickListener() {
            @Override  // android.view.View$OnClickListener
            public void onClick(View arg13) {
                char[] x = new char[17];
                char[] y = new char[38];
                int i;
                for(i = 0; i < 17; ++i) {
                    if(new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] < 73 && new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] >= 65 || new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] < 105 && new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] >= 97) {
                        x[i] = (char)(new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] + 18);
                    }
                    else if(new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] >= 65 && new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] <= 90 || new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] >= 97 && new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] <= 0x7A) {
                        x[i] = (char)(new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i] - 8);
                    }
                    else {
                        x[i] = new char[]{'T', 'h', 'i', 's', 'I', 's', 'T', 'h', 'e', 'F', 'l', 'a', 'g', 'H', 'o', 'm', 'e'}[i];
                    }
                }

                if(String.valueOf(x).equals(edit.getText().toString())) {
                    int v0_1;
                    for(v0_1 = 0; v0_1 < 38; ++v0_1) {
                        if(new char[]{'p', 'v', 'k', 'q', '{', 'm', '1', '6', '4', '6', '7', '5', '2', '6', '2', '0', '3', '3', 'l', '4', 'm', '4', '9', 'l', 'n', 'p', '7', 'p', '9', 'm', 'n', 'k', '2', '8', 'k', '7', '5', '}'}[v0_1] >= 65 && new char[]{'p', 'v', 'k', 'q', '{', 'm', '1', '6', '4', '6', '7', '5', '2', '6', '2', '0', '3', '3', 'l', '4', 'm', '4', '9', 'l', 'n', 'p', '7', 'p', '9', 'm', 'n', 'k', '2', '8', 'k', '7', '5', '}'}[v0_1] <= 90 || new char[]{'p', 'v', 'k', 'q', '{', 'm', '1', '6', '4', '6', '7', '5', '2', '6', '2', '0', '3', '3', 'l', '4', 'm', '4', '9', 'l', 'n', 'p', '7', 'p', '9', 'm', 'n', 'k', '2', '8', 'k', '7', '5', '}'}[v0_1] >= 97 && new char[]{'p', 'v', 'k', 'q', '{', 'm', '1', '6', '4', '6', '7', '5', '2', '6', '2', '0', '3', '3', 'l', '4', 'm', '4', '9', 'l', 'n', 'p', '7', 'p', '9', 'm', 'n', 'k', '2', '8', 'k', '7', '5', '}'}[v0_1] <= 0x7A) {
                            y[v0_1] = (char)(new char[]{'p', 'v', 'k', 'q', '{', 'm', '1', '6', '4', '6', '7', '5', '2', '6', '2', '0', '3', '3', 'l', '4', 'm', '4', '9', 'l', 'n', 'p', '7', 'p', '9', 'm', 'n', 'k', '2', '8', 'k', '7', '5', '}'}[v0_1] + 16);
                            if(y[v0_1] > 90 && y[v0_1] < 97 || y[v0_1] >= 0x7A) {
                                y[v0_1] = (char)(y[v0_1] - 26);
                            }
                        }
                        else {
                            y[v0_1] = new char[]{'p', 'v', 'k', 'q', '{', 'm', '1', '6', '4', '6', '7', '5', '2', '6', '2', '0', '3', '3', 'l', '4', 'm', '4', '9', 'l', 'n', 'p', '7', 'p', '9', 'm', 'n', 'k', '2', '8', 'k', '7', '5', '}'}[v0_1];
                        }
                    }

                    text.setText(String.valueOf(y));
                    return;
                }

                text.setText("答案错了肿么办。。。不给你又不好意思。。。哎呀好纠结啊~~~");
            }
        });
    }

    @Override  // android.app.Activity
    public boolean onOptionsItemSelected(MenuItem arg3) {
        return arg3.getItemId() == 0x7F050040 ? true : super.onOptionsItemSelected(arg3);  // id:action_settings
    }
}


```
`JEB`的反编译是比较清楚的，直接参照写出解密脚本即可。

## 0x02 - Analyse
```python
ans = [
	0x70, 0x76, 0x6b, 0x71, 0x7b, 0x6d, 0x31, 0x36, 0x34, 0x36, 0x37, 0x35, 0x32, 0x36, 0x32, 0x30, 0x33, 0x33, 0x6c,
	0x34, 0x6d, 0x34, 0x39, 0x6c, 0x6e, 0x70, 0x37, 0x70, 0x39, 0x6d, 0x6e, 0x6b, 0x32, 0x38, 0x6b, 0x37, 0x35, 0x7d
]

flag = ''
for i in ans:
	if (i >= ord('a') and i <= ord('z')):
		i += 16
		if (i >= ord("z")):
			flag += chr(i - 26)
	else:
		flag += chr(i)

print(flag)
```

## 0x03 - Flag
`flag{c164675262033b4c49bdf7f9cda28a75}`
