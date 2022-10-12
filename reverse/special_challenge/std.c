#include <stdio.h>

void decrypt(unsigned int* v, const unsigned int* k) 
{
    unsigned int v0 = v[0], v1 = v[1], sum = 0x1fe68f02, i;
    unsigned int delta = 0x9e3779b9;
    unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 18; i++)
	{
		v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
		v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		sum -= delta;                                   
    }
    v[0] = v0; v[1] = v1;
}

int main()
{
	unsigned char code[] = 
	{
		0xef, 0x6e, 0xec, 0x60, 0xeb, 0x84, 0x92, 0x00,
        0x42, 0x2f, 0x1a, 0x22, 0x20, 0xb2, 0xb4, 0x83,
        0xa1, 0xe8, 0x61, 0x06, 0xb3, 0x76, 0xaf, 0x8d,
        0xc4, 0x8f, 0x55, 0x8c, 0xc8, 0x71, 0x9b, 0x86,
	};

	for (int i = 0; i < 32; i += 8)
		decrypt((unsigned int*)(code + i), (const unsigned int*)"MAYCTF_REV_CUDA!");

	puts(code);

	return 0;
}