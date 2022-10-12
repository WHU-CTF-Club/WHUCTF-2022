#include <stdio.h>

const char* key1 = "It's 07:55 a.m.!";
const char* key2 = "Almost 23:55 now";

unsigned char ans1[] = 
{
	0xd1, 0x77, 0xdc, 0xfb, 0xe9, 0xd5, 0xce, 0xfd,
	0x02, 0x1a, 0xbc, 0xc7, 0x86, 0x00, 0x01, 0x6b,
	0x5d, 0xad, 0xc0, 0x4a, 0x57, 0xa8, 0xf2, 0x2e,
	0
};

unsigned char ans2[] = 
{
	0xd4, 0xef, 0xa1, 0xa1, 0x45, 0x1f, 0x6e, 0xa0,
	0xe5, 0xf5, 0xc6, 0xe7, 0x89, 0x66, 0x8c, 0xdd,
	0xaf, 0xf2, 0x73, 0x59, 0x3f, 0x79, 0x8c, 0x82,
	0
};

void encrypt(unsigned int* v, const unsigned int* k) 
{
    unsigned int v0 = v[0], v1 = v[1], sum = 0, i;
    unsigned int delta = 0x9e3779b9;
    unsigned int k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];
    for (i = 0; i < 32; i++)
	{
		sum += delta;  
		v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
		v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);                                 
    }
    v[0] = v0; v[1] = v1;
}

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
	for (int i = 0; i < 24; i += 8)
		decrypt((unsigned int*)(ans1 + i), (const unsigned int*)key1);
	for (int i = 0; i < 24; i += 8)
		encrypt((unsigned int*)(ans2 + i), (const unsigned int*)key2);

	printf("%s%s\n", ans1, ans2);

	return 0;
}