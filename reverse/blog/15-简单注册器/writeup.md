## 0x01 - Decompile
还是用dex2jar转换文件后用`Java Decompiler`打开，在`com.example.flag/MainActivity`中：
```java
package com.example.flag;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v7.app.ActionBarActivity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends ActionBarActivity {
  protected void onCreate(Bundle paramBundle) {
    super.onCreate(paramBundle);
    setContentView(2130903063);
    if (paramBundle == null)
      getSupportFragmentManager().beginTransaction().add(2131034172, new PlaceholderFragment()).commit(); 
    Button button = (Button)findViewById(2131034175);
    final TextView textview = (TextView)findViewById(2131034174);
    button.setOnClickListener(new View.OnClickListener() {
          public void onClick(View param1View) {
            byte b = 1;
            String str = editview.getText().toString();
            if (str.length() != 32 || str.charAt(31) != 'a' || str.charAt(1) != 'b' || str.charAt(0) + str.charAt(2) - 48 != 56)
              b = 0; 
            if (b == 1) {
              char[] arrayOfChar = "dd2940c04462b4dd7c450528835cca15".toCharArray();
              arrayOfChar[2] = (char)(char)(arrayOfChar[2] + arrayOfChar[3] - 50);
              arrayOfChar[4] = (char)(char)(arrayOfChar[2] + arrayOfChar[5] - 48);
              arrayOfChar[30] = (char)(char)(arrayOfChar[31] + arrayOfChar[9] - 48);
              arrayOfChar[14] = (char)(char)(arrayOfChar[27] + arrayOfChar[28] - 97);
              for (b = 0;; b++) {
                String str1;
                if (b >= 16) {
                  str1 = String.valueOf(arrayOfChar);
                  textview.setText("flag{" + str1 + "}");
                  return;
                } 
                String str2 = str1[31 - b];
                str1[31 - b] = str1[b];
                str1[b] = str2;
              } 
            } 
            textview.setText("");
          }
        });
  }
  
  public boolean onCreateOptionsMenu(Menu paramMenu) {
    getMenuInflater().inflate(2131492864, paramMenu);
    return true;
  }
  
  public boolean onOptionsItemSelected(MenuItem paramMenuItem) {
    return (paramMenuItem.getItemId() == 2131034176) ? true : super.onOptionsItemSelected(paramMenuItem);
  }
  
  public static class PlaceholderFragment extends Fragment {
    public View onCreateView(LayoutInflater param1LayoutInflater, ViewGroup param1ViewGroup, Bundle param1Bundle) {
      return param1LayoutInflater.inflate(2130903064, param1ViewGroup, false);
    }
  }
}

```

## 0x02 - Analyse
```python
data = list('dd2940c04462b4dd7c450528835cca15')
data[2] = chr(ord(data[2]) + ord(data[3]) - 50)
data[4] = chr(ord(data[2]) + ord(data[5]) - 48)
data[30] = chr(ord(data[31]) + ord(data[9]) - 48)
data[14] = chr(ord(data[27]) + ord(data[28]) - 97)

for i in range(16):
	t = data[i]
	data[i] = data[31 - i]
	data[31 - i] = t

ans = ''
for ch in data:
	ans += ch

print('flag{' + ans + '}')
```

## 0x03 - Flag
`flag{59acc538825054c7de4b26440c0999dd}`
