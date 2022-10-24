#include <iostream>
#include <string>
#include <cstring>

void encrypt(void* V, const void* K) 
{
	auto v = reinterpret_cast<uint32_t*>(V);
	auto k = reinterpret_cast<const uint32_t*>(K);
    uint32_t v0 = v[0], v1 = v[1], sum = 0, i;
    uint32_t delta = 0x9e3779b9;
    uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 32; i++)
	{
        sum += delta;
        v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
    }
    v[0] = v0; v[1] = v1;
}

int main()
{
	std::cout << "Please input your flag:" << std::endl;

	std::string input;
	std::cin >> input;

	auto p = input.c_str();
	if (input.length() == 32 && !memcmp(p, "mayctf{", 7) && input[31] == '}')
	{
		for (int i = 0; i < 32; i += 8)
			encrypt(const_cast<char*>(p + i), "Welcome2MAYBECTF");

		unsigned char sn[] = 
		{
			0xd3, 0xbd, 0x3a, 0xba, 0x4d, 0x57, 0xdb, 0x15,
			0xa3, 0x30, 0xcd, 0x1e, 0x09, 0x85, 0x3e, 0x9b,
			0xa0, 0xf7, 0x17, 0x16, 0x7c, 0xd6, 0xc6, 0xa7,
			0xe8, 0x8f, 0xcb, 0xad, 0xc4, 0xfe, 0x9f, 0x79,
		};

		if (!memcmp(p, sn, 32))
			std::cout << "Congratulations!" << std::endl;
		else
			std::cout << "Oops, not this one." << std::endl;
	}
	else
		std::cout << "Seems you don't understand reverse at all!" << std::endl;

	return 0;
}
