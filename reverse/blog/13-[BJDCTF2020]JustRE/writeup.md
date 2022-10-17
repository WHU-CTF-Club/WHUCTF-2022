## 0x00 - Extend Reading
[Windows与消息](https://learn.microsoft.com/en-us/windows/win32/winmsg/windowing)

## 0x01 - Disassemble
根据`MSDN`文档的描述容易知道`sub_4011C0`即为`MainWndProc`，处理主窗体的消息响应。
在里面发现函数`DialogFunc(0x401350)`，代码如下：
```cpp
INT_PTR __stdcall DialogFunc(HWND hWnd, UINT a2, WPARAM a3, LPARAM a4)
{
  CHAR String[100]; // [esp+0h] [ebp-64h] BYREF

  if ( a2 != 272 )
  {
    if ( a2 != 273 )
      return 0;
    if ( (_WORD)a3 != 1 && (_WORD)a3 != 2 )
    {
      sprintf(String, Format, ++dword_4099F0);
      if ( dword_4099F0 == 19999 )
      {
        sprintf(String, " BJD{%d%d2069a45792d233ac}", 19999, 0);
        SetWindowTextA(hWnd, String);
        return 0;
      }
      SetWindowTextA(hWnd, String);
      return 0;
    }
    EndDialog(hWnd, (unsigned __int16)a3);
  }
  return 1;
}
```

容易得到当点击了19999次后会显示`BJD{1999902069a45792d233ac}`

## 0x02 - Flag
`flag{1999902069a45792d233ac}`
