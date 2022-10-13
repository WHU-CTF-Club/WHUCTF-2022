#include <iostream>
#include <string>
#include <exception>

#include <cstring>

int main()
{
	std::string input;

	std::cin >> input;

	if (input.length() != 39)
	{
		std::cout << "Nonono!" << std::endl;
		return 1;
	}

	try
	{
		if (input.at(6) != '{' || input.at(39) != '}')
		{
			std::cout << "Nononono!" << std::endl;
			return 1;
		}

		for (auto& ch : input)
		{
			if (ch >= 'a' && ch <= 'z')
				ch = ch - 'a' + 'A';
			else if (ch >= 'A' && ch <= 'Z')
				ch = ch - 'A' + 'a';
		}

		if (input == "MAYCTF{A_rEaLlY_fAA@@@aaakkkkk_FLAG!!!}")
		{
			std::cout << "It's quite simple! isn't it?" << std::endl;
			return 2;
		}
	}
	catch (...)
	{
		if (!memcmp(input.c_str(), "mayctf{", 7) && input[38] == '}')
		{
			input = input.substr(7, 31);
			for (auto& ch : input)
			{
				if (ch >= 'a' && ch <= 'z')
					ch = (ch - 'a' + 13) % 26 + 'a';
				else if (ch >= 'A' && ch <= 'Z')
					ch = (ch - 'A' + 13) % 26 + 'A';
			}

			unsigned char secret[] =
			{
				0x4C, 0x31, 0x6A, 0x66, 0x5B, 0x56, 0x70, 0x62,
				0x6E, 0x6E, 0x55, 0x59, 0x67, 0x7D, 0x3D, 0x6C,
				0x77, 0x20, 0x70, 0x72, 0x4B, 0x5B, 0x77, 0x79,
				0x61, 0x75, 0x7C, 0x69, 0x3D, 0x3C, 0x3F
			};

			for (int i = 0; i < 31; ++i)
				secret[i] ^= i;

			// Correct
			if (input == (const char*)secret)
			{
				putchar('C');
				putchar('o');
				putchar('n');
				putchar('g');
				putchar('r');
				putchar('a');
				putchar('t');
				putchar('u');
				putchar('l');
				putchar('a');
				putchar('t');
				putchar('i');
				putchar('o');
				putchar('n');
				putchar('s');
				putchar('!');
				putchar('\n');
				return 0;
			}
		}
	}

	std::cout << "Nono!" << std::endl;
	return 1;
}