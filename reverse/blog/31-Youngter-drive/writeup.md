## 0x01 - Disassemble
`UPX`脱壳后用`IDA`打开程序：
```cpp
int __cdecl main_0(int argc, const char **argv, const char **envp)
{
  HANDLE hthread2; // [esp+D0h] [ebp-14h]
  HANDLE hthread1; // [esp+DCh] [ebp-8h]

  input();
  hObject = CreateMutexW(0, 0, 0);
  j_strcpy(user_input, input_buffer);
  hthread1 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread1, 0, 0, 0);
  hthread2 = CreateThread(0, 0, thread2, 0, 0, 0);
  CloseHandle(hthread1);
  CloseHandle(hthread2);
  while ( mutex != -1 )
    ;
  j_put_answer();
  CloseHandle(hObject);
  return 0;
}

void __stdcall Thread1Proc(int a1)
{
  while ( 1 )
  {
    WaitForSingleObject(hMutex, 0xFFFFFFFF);
    if ( Current_Index > -1 )
    {
      Thread1Impl(input_buffer, Current_Index);
      --Current_Index;
      Sleep(0x64u);
    }
    ReleaseMutex(hMutex);
  }
}

void __cdecl Thread1Impl(char *buffer, int mutex)
{
  char chr; // [esp+D3h] [ebp-5h]

  chr = buffer[mutex];
  if ( (chr < 'a' || chr > 'z') && (chr < 'A' || chr > 'Z') )
    exit(0);
  if ( chr < 'a' || chr > 'z' )
    buffer[mutex] = table[buffer[mutex] - 38];
  else
    buffer[mutex] = table[buffer[mutex] - 96];
}

void __stdcall Thread2Proc(LPVOID lpParam)
{
  while ( 1 )
  {
    WaitForSingleObject(hMutex, 0xFFFFFFFF);
    if ( Current_Index > -1 )
    {
      Sleep(0x64u);
      --Current_Index;
    }
    ReleaseMutex(hMutex);
  }
}
```

## 0x02 - Analyse
程序使用两个线程轮流对同一个buffer进行操作，逆向处理即可。
验证中少了一位，事实上还有一位`E`在结尾

```python
import string

#  abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ
# QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm

ans = 'TOiZiZtOrYaToUwPnToBsOaOapsyS'
t = str.maketrans('QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm_', '_' + string.ascii_lowercase + string.ascii_uppercase)

flag = ''
for i in range(len(ans)):
	if i % 2 == 1:
		flag += ans[i].translate(t)
	else:
		flag += ans[i]

print('flag{' + flag + 'E}')
```

## 0x03 - Flag
`flag{ThisisthreadofwindowshahaIsESE}`
