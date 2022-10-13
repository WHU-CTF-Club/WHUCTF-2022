#include <iostream>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <cstring>

bool depth0_sword(short HASH1, short HASH2, long long HASH)
{
	if ((((unsigned char)HASH2 ^ (unsigned char)HASH1) & 7) != 0)
	{
		if (HASH % 8 == 1)
		{
			if (HASH / 8 % 4 == 0)
				return true;
		}
	}

	return false;
}
bool depth1_newspaper(short HASH1, short HASH2, long long HASH)
{
	if ((((unsigned char)HASH2 ^ (unsigned char)HASH1) & 7) != 0)
	{
		if (HASH % 8 == 1)
		{
			if (HASH / 8 % 4 == 1)
				return true;
		}
	}

	return false;
}
bool depth2_whistle(short HASH1, short HASH2, long long HASH)
{
	if ((((unsigned char)HASH2 ^ (unsigned char)HASH1) & 7) != 0)
	{
		if (HASH % 8 == 1)
		{
			if (HASH / 8 % 4 == 2)
				return true;
		}
	}

	return false;
}
bool depth3_sword(short HASH1, short HASH2, long long HASH)
{
	if (
		HASH1 == 0x08B6 && HASH2 == 0x6DAC || 
		HASH1 == 0x6DAC && HASH2 == 0x08B6 ||
		HASH1 == 0x88B6 && HASH2 == 0xEDAC ||
		HASH1 == 0xEDAC && HASH2 == 0x88B6
		)
		return true;
		

	return false;
}
bool depth4_whistle(short HASH1, short HASH2, long long HASH)
{
	if (
		HASH1 == 0x2439 && HASH2 == 0x3C55 ||
		HASH1 == 0x3C55 && HASH2 == 0x2439 ||
		HASH1 == 0xA439 && HASH2 == 0xBC55 ||
		HASH1 == 0xBC55 && HASH2 == 0xA439
		)
		return true;


	return false;
}
bool depth5_newspaper(short HASH1, short HASH2, long long HASH)
{
	if (
		HASH1 == 0x2F58 && HASH2 == 0x46FB ||
		HASH1 == 0x46FB && HASH2 == 0x2F58
		)
		return true;


	return false;
}
bool depth6_fist(short HASH1, short HASH2, long long HASH)
{
	if (
		HASH1 == 0x332C && HASH2 == 0x3A48 ||
		HASH1 == 0x3A48 && HASH2 == 0x332C ||
		HASH1 == 0xB32C && HASH2 == 0xBA48 ||
		HASH1 == 0xBA48 && HASH2 == 0xB32C
		)
		return true;


	return false;
}


bool (*stepfuncs[])(short, short, long long) =
{
	depth0_sword,
	depth1_newspaper,
	depth2_whistle,
	// depth3_sword,
	// depth4_whistle,
	// depth5_newspaper,
	// depth6_fist
};

char recoder[100][10] = { 0 };

void Search(const int depth, const int t, const short HASH1, const short HASH2)
{
	if (depth == sizeof(stepfuncs) / sizeof(void*))
	{
		for (int i = 0; i < depth; ++i)
			printf("%s->", recoder[i]);
		printf("\n");
		return;
	}

	char INT[5] = { 0 };
	for (INT[0] = 32; INT[0] < 127; ++INT[0]) {
	for (INT[1] = 32; INT[1] < 127; ++INT[1]) {
	for (INT[2] = 32; INT[2] < 127; ++INT[2]) {
	for (INT[3] = 32; INT[3] < 127; ++INT[3]) {
		srand(t ^ *(int*)INT);

		int H1 = HASH1, H2 = HASH2;
		short HASH1DELTA = rand();
		short HASH2DELTA = rand();
		if (HASH1DELTA > 0)
			H1 += HASH1DELTA;
		if (HASH2DELTA > 0)
			H2 += HASH2DELTA;
		rand();
		long long HASH = ((long long)(short)(H1 * H2) << 32) | (short)(H2 ^ H1) | (unsigned long long)((long long)(short)((H2 & H1) + (H2 | H1)) << 16) | ((long long)(short)((H2 & H1) + (H2 | H1) + (H2 ^ H1) + H1 * H2) << 48);
		
		if (stepfuncs[depth](H1, H2, HASH))
		{
			strcpy(recoder[depth], INT);
			rand();
			Search(depth + 1, rand(), H1, H2);
		}
	}
	}
	}
	}


	
}

int main()
{
	srand(66);
	rand();
	Search(0, rand(), 0xDEAD, 0xBEEF);
}