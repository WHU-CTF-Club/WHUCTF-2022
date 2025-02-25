#include <stdio.h>

void decrypt(unsigned int* v, const unsigned int* k) 
{
    unsigned int v0 = v[0], v1 = v[1], sum = 0xc6ef3720, i;
    unsigned int delta = 0x9e3779b9;
    unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 32; i++)
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
		0xf0, 0x2e, 0xd2, 0x73, 0x04, 0xb6, 0x1a, 0xd3,
        0x59, 0xb2, 0xe3, 0x27, 0xa0, 0xda, 0x90, 0xd6,
        0xd2, 0x8c, 0x1c, 0x24, 0x00, 0xcb, 0x7e, 0x80,
        0x70, 0xf7, 0x35, 0xc2, 0x9d, 0x30, 0x3a, 0x3f,
        0x53, 0xb6, 0xf7, 0xbc, 0x29, 0x53, 0x5d, 0xec,
	};

	unsigned char key[] = 
	{
		0x40, 0x40, 0x6C, 0x67, 0x76, 0x6A, 0x6F, 0x63,
        0x57, 0x47, 0x6B, 0x7F, 0x3D, 0x7B, 0x6B, 0x2E
	};

	for (int i = 0; i < 16; ++i)
		key[i] ^= i;

	for (int i = 0; i < 40; i += 8)
		decrypt((unsigned int*)(code + i), (const unsigned int*)key);

	puts(code);

	return 0;
}