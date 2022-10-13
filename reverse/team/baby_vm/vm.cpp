#include "vm.hpp"

#include <iostream>
#include <string>
#include <cstring>

VirtualMachine::VirtualMachine(UInt32* codedata, UInt32 eip) noexcept
	: StackBuffer{ 0 }
{
	CodeDatas = codedata;
	RegisterDatas.Single.ESP = RegisterDatas.Single.EBP = StackBufferSize / 2;
	RegisterDatas.Single.EAX = RegisterDatas.Single.EBX =
	RegisterDatas.Single.ECX = RegisterDatas.Single.EDX =
	RegisterDatas.Single.ESI = RegisterDatas.Single.EDI = 0;
	RegisterDatas.Single.EIP = eip;
}

VirtualMachine::~VirtualMachine()
{	
}

RegisterID VirtualMachine::next_register_id()
{
	return next_data<RegisterID>();
}

Register32& VirtualMachine::next_register()
{
	return RegisterDatas.Array[next_register_id()];
}

void VirtualMachine::push(UInt32 x)
{
	*reinterpret_cast<UInt32*>(StackBuffer + RegisterDatas.Single.ESP) = x;
	RegisterDatas.Single.ESP += sizeof(UInt32);
}

UInt32 VirtualMachine::pop()
{
	RegisterDatas.Single.ESP -= sizeof(UInt32);
	return *reinterpret_cast<UInt32*>(StackBuffer + RegisterDatas.Single.ESP);
}

void VirtualMachine::throw_exception(const std::string_view sv)
{
	std::cout << sv;
}

int VirtualMachine::run()
{
	do 
	{
		switch(next_data())
		{
			case VM_EXIT:
			{
				return RegisterDatas.Single.EAX;
			}
			case VM_NOP:
			{
				continue;
			}
			case VM_SETREG:
			{
				auto& reg = next_register();
				reg = next_data();
				continue;
			}
			case VM_MOVREG:
			{
				auto& dst = next_register();
				auto& src = next_register();
				dst = src;
				continue;
			}
			case VM_SHOWSTR:
			{
				std::cout << reinterpret_cast<char*>(next_register());
				continue;
			}
			case VM_TEA:
			{
				bool is_decrypt = next_data<bool>();
				UInt32* v = reinterpret_cast<UInt32*>(next_register());
				UInt32* k = reinterpret_cast<UInt32*>(next_register());

				auto encrypt = [](UInt32* v, UInt32* k) {
    				UInt32 v0=v[0], v1=v[1], sum=0, i;           /* set up */
    				UInt32 delta=0x9e3779b9;                     /* a key schedule constant */
    				UInt32 k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    				for (i=0; i < 32; i++) {                       /* basic cycle start */
    				    sum += delta;
    				    v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
    				    v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);  
    				}                                              /* end cycle */
    				v[0]=v0; v[1]=v1;
				};

				auto decrypt = [](UInt32* v, UInt32* k) {
				    UInt32 v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
				    UInt32 delta=0x9e3779b9;                     /* a key schedule constant */
				    UInt32 k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
				    for (i=0; i<32; i++) {                         /* basic cycle start */
				        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
				        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
				        sum -= delta;                                   
				    }                                              /* end cycle */
				    v[0]=v0; v[1]=v1;
				};

				if (is_decrypt) 
					decrypt(v, k);
				else
					encrypt(v, k);

				continue;
			}
			case VM_PUSH:
			{
				push(next_register());
				continue;
			}
			case VM_POP:
			{
				next_register() = pop();
				continue;
			}
			case VM_ADD:
			{
				auto& dst = next_register();
				auto& delta = next_register();
				dst += delta;
				continue;
			}
			case VM_READSTR:
			{
				char* buffer = reinterpret_cast<char*>(next_register());
				std::string tmp; 
				std::cin >> tmp; 
				tmp.resize(next_register());
				memcpy(buffer, tmp.c_str(), tmp.size());
				continue;
			}

			default:
			{
				throw_exception("secsome's super PC cannot recognize this byte code!\n");
				return 1;
			}
		}
	} while(true);
}

