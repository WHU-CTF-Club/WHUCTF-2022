#ifndef _MAYCTF_BABYVM_VM_HPP
#define _MAYCTF_BABYVM_VM_HPP

#include <string_view>

using UInt32 = unsigned int;
using Register32 = UInt32;
using Address = UInt32;

enum VMOpcode : UInt32
{
	VM_EXIT,
	VM_NOP,
	VM_SETREG,
	VM_MOVREG,
	VM_SHOWSTR,
	VM_TEA,
	VM_TEA_ENCRYPT = 0,
	VM_TEA_DECRYPT = 1,
	VM_PUSH = VM_TEA + 1,
	VM_POP,
	VM_ADD,
	VM_READSTR,
	VM_INSTCOUNT
};

enum RegisterID : UInt32
{
	REG_EAX = 0,
	REG_EBX,
	REG_ECX,
	REG_EDX,
	REG_ESI,
	REG_EDI,
	REG_EBP,
	REG_ESP,
	REG_EIP,
	REG_COUNT
};

struct Registers
{
	Register32 EAX;
	Register32 EBX;
	Register32 ECX;
	Register32 EDX;
	Register32 ESI;
	Register32 EDI;
	Register32 EBP;
	Register32 ESP;
	Register32 EIP;
};

class VirtualMachine final
{
public:
	explicit VirtualMachine(UInt32* codedata, UInt32 eip) noexcept;
	virtual ~VirtualMachine();

	int run();

private:
	template<typename T = UInt32>
	T next_data()
	{
		return static_cast<T>(CodeDatas[RegisterDatas.Single.EIP++]);
	}

	RegisterID next_register_id();
	Register32& next_register();

	void push(UInt32 x);
	UInt32 pop();
	
	void throw_exception(const std::string_view sv);

	static constexpr UInt32 StackBufferSize = 0x20000;
	unsigned char StackBuffer[StackBufferSize];

	union
	{
		Registers Single;
		Register32 Array[REG_COUNT];
	} RegisterDatas;

	UInt32* CodeDatas;
};

static_assert(sizeof(UInt32) == 4, "sizeof UInt32 must to be 4!");
static_assert(sizeof(size_t) == 4, "This program need to be compiled under x86 mode!");

#endif // _MAYCTF_BABYVM_VM_HPP