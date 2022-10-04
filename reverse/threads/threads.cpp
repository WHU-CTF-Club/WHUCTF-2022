#include <Windows.h>

#include <iostream>

#include "sha256.h"

HANDLE hMutex;
HANDLE hThread1, hThread2;
std::string Input;
int DecodeCounter = 92;

// mayctf{It's_just@A_verrrrrrrry_s1mple_multiThr#ad_stuff_89EC1FBD-14ED-4DF3-93A3-91ED11A36956}
void Do_Input()
{
	std::cout << "Please input your flag:" << std::endl;
	std::cin >> Input;
}

void rot13(char& ch)
{
	if (ch >= 'a' && ch <= 'z')
		ch = (ch - 'a' + 13) % 26 + 'a';
	else if (ch >= 'A' && ch <= 'Z')
		ch = (ch - 'A' + 13) % 26 + 'A';
}

void xor_idx(char& ch)
{
	ch ^= DecodeCounter;
}

DWORD WINAPI Thread1Proc(LPVOID lpThreadParameter)
{
	while (true)
	{
		WaitForSingleObject(hMutex, -1);
		if (DecodeCounter > -1)
		{
			rot13(Input[DecodeCounter]);
			--DecodeCounter;
			Sleep(50);
		}
		ReleaseMutex(hMutex);
	}
}

DWORD WINAPI Thread2Proc(LPVOID lpThreadParameter)
{
	while (true)
	{
		WaitForSingleObject(hMutex, -1);
		if (DecodeCounter > -1)
		{
			xor_idx(Input[DecodeCounter]);
			--DecodeCounter;
			Sleep(50);
		}
		ReleaseMutex(::hMutex);
	}
}

std::string Get_SHA256(const std::string& str)
{
	SHA256 engine;
	engine.update(str);
	auto ptr = engine.digest();
	auto ret = engine.toString(ptr);
	delete[] ptr;
	return ret;
}

void Do_Validation()
{
	unsigned char answer_buffer[] =
	{
		0x7A, 0x60, 0x6C, 0x60, 0x67, 0x63, 0x7B, 0x4E,
		0x67, 0x2E, 0x66, 0x54, 0x77, 0x78, 0x66, 0x7B, 
		0x40, 0x50, 0x5F, 0x65, 0x72, 0x67, 0x65, 0x65, 
		0x65, 0x6B, 0x65, 0x69, 0x65, 0x64, 0x5F, 0x6C,
		0x31, 0x4C, 0x63, 0x4F, 0x72, 0x7A, 0x7A, 0x52, 
		0x79, 0x5D, 0x76, 0x7F, 0x75, 0x5F, 0x23, 0x4E,
		0x71, 0x6E, 0x66, 0x47, 0x68, 0x53, 0x73, 0x68,
		0x38, 0x00, 0x52, 0x78, 0x31, 0x7B, 0x4F, 0x7B, 
		0x2D, 0x70, 0x34, 0x06, 0x51, 0x68, 0x34, 0x03, 
		0x53, 0x7A, 0x2D, 0x72, 0x33, 0x0C, 0x33, 0x62,
		0x39, 0x60, 0x52, 0x17, 0x31, 0x64, 0x4E, 0x64, 
		0x36, 0x60, 0x35, 0x6D, 0x7D,
	};

	std::string s1;
	s1.resize(93);
	memcpy(&s1[0], answer_buffer, 93);

	if (Get_SHA256(s1) == Get_SHA256(Input))
		std::cout << "You really understand multi thread!" << std::endl;
	else
		std::cout << "Seems you cannot understand the multithread processing yet..." << std::endl;
}

int main()
{
	Do_Input();

	hMutex = CreateMutex(nullptr, NULL, TEXT("secsome's lovely mutex"));
	if (NULL == hMutex)
	{
		::std::cout << "Failed to set-up the mutex!" << std::endl;
		return 1;
	}

	hThread1 = CreateThread(nullptr, NULL, Thread1Proc, nullptr, NULL, NULL);
	if (NULL == hThread1)
	{
		std::cout << "Failed to start Thread1Proc!" << std::endl;
		return 1;
	}

	hThread2 = CreateThread(nullptr, NULL, Thread2Proc, nullptr, NULL, NULL);
	if (NULL == hThread2)
	{
		std::cout << "Failed to start Thread2Proc!" << std::endl;
		return 1;
	}

	CloseHandle(hThread1);
	CloseHandle(hThread2);

	while (DecodeCounter != -1)
		;

	CloseHandle(hMutex);

	Do_Validation();

	(void)getchar();

	return 0;
}
