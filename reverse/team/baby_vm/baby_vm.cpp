#include "vm.hpp"

#include <iostream>
#include <memory>

#include <cstring>

template<typename T>
constexpr UInt32 To_Inst(T&& x)
{
	return UInt32(x);
}

const char* key1 = "It's 07:55 a.m.!\n";
const char* key2 = "Almost 23:55 now\n";

const char* welcome_msg = "Welcome to secsome's super computer!\n";

char data1[25] = {0};
char data2[25] = {0};

UInt32 VMCodeDatas[] =
{
	VM_NOP,
	
	// showstr(welcome_msg)
	VM_SETREG, REG_EAX, To_Inst(welcome_msg),
	VM_SHOWSTR, REG_EAX,

	// mov edi, key1
	// push key2
	VM_SETREG, REG_EAX, To_Inst(key1),
	VM_SETREG, REG_EBX, To_Inst(key2),
	VM_PUSH, REG_EAX,
	VM_PUSH, REG_EBX,
	VM_POP, REG_ESI,
	VM_POP, REG_EDI,
	VM_PUSH, REG_ESI,
	
	// mov ecx, data1
	// mov edx, data2
	// push data2
	VM_SETREG, REG_ECX, To_Inst(data1),
	VM_SETREG, REG_EDX, To_Inst(data2),
	VM_PUSH, REG_EDX,

	// showstr(key1)
	VM_SHOWSTR, REG_EDI,

	// readstr(data1, 24)
	VM_SETREG, REG_EAX, 24,
	VM_READSTR, REG_ECX, REG_EAX,

	// tea_encrypt(data1, key1)
	// tea_encrypt(data1 + 8, key1)
	// tea_encrypt(data1 + 16, key1)
	VM_TEA, VM_TEA_ENCRYPT, REG_ECX, REG_EDI,
	VM_SETREG, REG_ESI, 8,
	VM_ADD, REG_ECX, REG_ESI,
	VM_TEA, VM_TEA_ENCRYPT, REG_ECX, REG_EDI,
	VM_ADD, REG_ECX, REG_ESI,
	VM_TEA, VM_TEA_ENCRYPT, REG_ECX, REG_EDI,

	// eax : data2
	// ebx : key2
	VM_POP, REG_EAX,
	VM_POP, REG_EBX,

	// showstr(key2)
	VM_SHOWSTR, REG_EBX,

	// readstr(data2, 24)
	VM_SETREG, REG_EDX, 24,
	VM_READSTR, REG_EAX, REG_EDX,

	// tea_decrypt(data2, key2)
	// tea_decrypt(data2 + 8, key2)
	// tea_decrypt(data2 + 16, key2)
	VM_TEA, VM_TEA_DECRYPT, REG_EAX, REG_EBX,  
	VM_SETREG, REG_ECX, 8,
	VM_ADD, REG_EAX, REG_ECX,
	VM_TEA, VM_TEA_DECRYPT, REG_EAX, REG_EBX,
	VM_ADD, REG_EAX, REG_ECX,
	VM_TEA, VM_TEA_DECRYPT, REG_EAX, REG_EBX,
	
	// return 0
	VM_SETREG, REG_EAX, 0,
	VM_EXIT,
};

int main()
{
	std::unique_ptr<VirtualMachine> machine = std::make_unique<VirtualMachine>(VMCodeDatas, 0);

	int result = machine->run();

	if (result) {
		std::cout << "Do not modify my super computer!" << std::endl;
		return 0;
	}

	// mayctf{I_@m_Sleeeeeepy!I_aM_Always_V3ry_Sl33py!}
	// first 24 bytes decoded by "It's 07:55 a.m.!"
	// later 24 bytes encoded by "Almost 23:55 now"

	unsigned char ans1[] = 
	{
		0xd1, 0x77, 0xdc, 0xfb, 0xe9, 0xd5, 0xce, 0xfd,
		0x02, 0x1a, 0xbc, 0xc7, 0x86, 0x00, 0x01, 0x6b,
		0x5d, 0xad, 0xc0, 0x4a, 0x57, 0xa8, 0xf2, 0x2e,
	};

	unsigned char ans2[] = 
	{
		0xd4, 0xef, 0xa1, 0xa1, 0x45, 0x1f, 0x6e, 0xa0,
		0xe5, 0xf5, 0xc6, 0xe7, 0x89, 0x66, 0x8c, 0xdd,
		0xaf, 0xf2, 0x73, 0x59, 0x3f, 0x79, 0x8c, 0x82,
	};

	if (!memcmp(ans1, data1, sizeof(ans1)) && !memcmp(ans2, data2, sizeof(ans2)))
		std::cout << "Congratulations!" << std::endl;
	else
		std::cout << "It's not too simple... Be patient!" << std::endl;

	return 0;
}