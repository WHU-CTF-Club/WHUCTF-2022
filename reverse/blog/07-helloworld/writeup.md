## 00 - Preprocess
将`classes.dex`文件提取出来，使用`dex2jar`转换为jar文件

## 01 - Disassemble
使用`Java Decompiler`打开，在`com.example.helloworld/MainActivity.class`中得到：
```java
package com.example.helloword;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends ActionBarActivity {
  protected void onCreate(Bundle paramBundle) {
    super.onCreate(paramBundle);
    setContentView(2130903064);
    "flag{7631a988259a00816deda84afb29430a}".compareTo("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  }
  
  public boolean onCreateOptionsMenu(Menu paramMenu) {
    getMenuInflater().inflate(2131492864, paramMenu);
    return true;
  }
  
  public boolean onOptionsItemSelected(MenuItem paramMenuItem) {
    return (paramMenuItem.getItemId() == 2131034172) ? true : super.onOptionsItemSelected(paramMenuItem);
  }
}

```

## 02 - Flag
故`flag{7631a988259a00816deda84afb29430a}`
