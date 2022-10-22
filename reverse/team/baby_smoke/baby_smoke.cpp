#include <Windows.h>
#include <bcrypt.h>
#include <iostream>

// https://learn.microsoft.com/zh-cn/windows/win32/seccng/creating-a-hash-with-cng
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define NT_FAILED(Status) (!NT_SUCCESS(Status))
#define STATUS_UNSUCCESSFUL ((NTSTATUS)0xC0000001L)
#pragma comment(lib, "Bcrypt.lib")

std::string CalculateHash(const std::string& src, LPCWSTR mode)
{
	BCRYPT_ALG_HANDLE       hAlg            = NULL;
    BCRYPT_HASH_HANDLE      hHash           = NULL;
    NTSTATUS                status          = STATUS_UNSUCCESSFUL;
    DWORD                   cbData          = 0,
                            cbHash          = 0,
                            cbHashObject    = 0;
    PBYTE                   pbHashObject    = NULL;
    PBYTE                   pbHash          = NULL;

	//open an algorithm handle
    status = BCryptOpenAlgorithmProvider(&hAlg, mode, NULL, NULL);
	if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
        goto Cleanup;
    }

    //calculate the size of the buffer to hold the hash object
	status = BCryptGetProperty(hAlg, BCRYPT_OBJECT_LENGTH, (PBYTE)&cbHashObject, sizeof(DWORD), &cbData, NULL);
    if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
        goto Cleanup;
    }

    //allocate the hash object on the heap
    pbHashObject = (PBYTE)HeapAlloc(GetProcessHeap(), NULL, cbHashObject);
    if (NULL == pbHashObject)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;
    }

    //calculate the length of the hash
    status = BCryptGetProperty(hAlg, BCRYPT_HASH_LENGTH, (PBYTE)&cbHash, sizeof(DWORD), &cbData, 0);
	if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
        goto Cleanup;
    }

    //allocate the hash buffer on the heap
    pbHash = (PBYTE)HeapAlloc(GetProcessHeap(), NULL, cbHash);
    if (NULL == pbHash)
    {
        wprintf(L"**** memory allocation failed\n");
        goto Cleanup;
    }

    //create a hash
	status = BCryptCreateHash(hAlg, &hHash, pbHashObject, cbHashObject, NULL, NULL, NULL);
    if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptCreateHash\n", status);
        goto Cleanup;
    }

    //hash some data
	status = BCryptHashData(hHash, (PBYTE)src.c_str(), src.length(), NULL);
    if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptHashData\n", status);
        goto Cleanup;
    }
    
    //close the hash
	status = BCryptFinishHash(hHash, pbHash, cbHash, NULL);
    if (NT_FAILED(status))
    {
        wprintf(L"**** Error 0x%x returned by BCryptFinishHash\n", status);
        goto Cleanup;
    }

Cleanup:
	std::string result;
	if (pbHash)
	{
		result.resize(cbHash * 2);
		for (size_t i = 0; i < cbHash; ++i)
			sprintf(&result[i * 2], "%02x", pbHash[i]);
		HeapFree(GetProcessHeap(), 0, pbHash);
	}
    if (hAlg)
        BCryptCloseAlgorithmProvider(hAlg, 0);
    if (hHash)    
        BCryptDestroyHash(hHash);
    if (pbHashObject)
        HeapFree(GetProcessHeap(), 0, pbHashObject);

	return result;
}

std::string DecodeData(LPVOID lpData, DWORD dwSize, const std::string& key)
{
	std::string result;
	result.resize(dwSize);
	auto pData = reinterpret_cast<char*>(lpData);	
	
	for (DWORD i = 0; i < dwSize; ++i)
		result[i] = pData[i] ^ key[i % key.length()];
	
	return result;
}

bool GenerateRTFFile(const std::string& key)
{
	HRSRC hResInfo = FindResourceA(NULL, MAKEINTRESOURCEA(1919), MAKEINTRESOURCEA(810));
	if (NULL == hResInfo)
		return false;

	DWORD dwSize = SizeofResource(NULL, hResInfo);
	if (NULL == dwSize)
		return false;

	HGLOBAL hResData = LoadResource(NULL, hResInfo);
	if (NULL == hResData)
		return false;

	LPVOID lpData = LockResource(hResData);
	if (nullptr == lpData)
		return false;

	const auto data = DecodeData(lpData, dwSize, key);

	DeleteFileA("litang.rtf");
	HANDLE hFile = CreateFileA("litang.rtf", GENERIC_ALL, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return false;

	if (FALSE == WriteFile(hFile, data.c_str(), dwSize, nullptr, nullptr))
		return false;

	CloseHandle(hFile);
	return true;
}

int main()
{
	std::string passwd1, passwd2;

	std::cout << "Please input password 1:" << std::endl;
	std::cin >> passwd1;
	if (passwd1.length() != 6)
	{
		std::cout << "Must be 6 characters!" << std::endl;
		return 0;
	}
	for (const auto& ch : passwd1)
	{
		if (ch >= 'a' && ch <= 'z')
			continue;
		std::cout << "Wrong!" << std::endl;
		return 0;
	}

	if (CalculateHash(passwd1 + "@LiTang-DingZhen", BCRYPT_SHA256_ALGORITHM) != "b9abee92a7fbd5e305615890183e90b9126be0040065f96dc2daa1b579f4c278")
		return 0;

	std::cout << "Please input password 2:" << std::endl;
	std::cin >> passwd2;
	if (passwd2.length() != 6)
	{
		std::cout << "Must be 6 characters!" << std::endl;
		return 0;
	}

	if (CalculateHash(passwd2 + passwd1 + "@LiTang-DingZhen", BCRYPT_MD5_ALGORITHM) != "fa81569f626defaa5fe6ab52e8fa2361")
		return 0;

	std::cout << passwd2 + passwd1 + "@LiTang-DingZhen" << std::endl;
	if (GenerateRTFFile(passwd2 + passwd1 + "@LiTang-DingZhen"))
		std::cout << "Done!" << std::endl;
	else
		std::cout << "Something is wrong!" << std::endl;

	return 0;
}
