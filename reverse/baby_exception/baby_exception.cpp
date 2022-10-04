#include <iostream>
#include <string>
#include <exception>

#include <cstring>
#include <cstdlib>

std::string b64encode(const std::string& src)
{
	constexpr auto _encoder = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	constexpr auto _pad = '=';
	constexpr auto PacketChars = 4;
	union PacketType
	{
		struct
		{
			unsigned char C3;
			unsigned char C2;
			unsigned char C1;
			unsigned char pad;
		} Char;
		struct
		{
			unsigned O4 : 6;
			unsigned O3 : 6;
			unsigned O2 : 6;
			unsigned O1 : 6;
			unsigned pad : 8;
		} SubCode;
		unsigned int Raw;
	} packet;

	std::string dest;

	size_t slen = src.length();

	auto sptr = (unsigned char const*)src.c_str();
	while (slen > 0)
	{
		int pad = 0;
		packet.Raw = 0;
		packet.Char.C1 = *sptr++;
		slen--;
		if (slen)
		{
			packet.Char.C2 = *sptr++;
			slen--;
		}
		else
			pad++;
		if (slen)
		{
			packet.Char.C3 = *sptr++;
			slen--;
		}
		else
			pad++;

		dest += _encoder[packet.SubCode.O1];
		dest += _encoder[packet.SubCode.O2];
		if (pad < 2)
			dest += _encoder[packet.SubCode.O3];
		else
			dest += _pad;
		if (pad < 1)
			dest += _encoder[packet.SubCode.O4];
		else
			dest += _pad;
	}

	return dest;
}

std::string nothing(const std::string& src)
{
	constexpr auto _encoder = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	constexpr auto _pad = '=';
	constexpr auto PacketChars = 4;
	union PacketType
	{
		struct
		{
			unsigned char C3;
			unsigned char C2;
			unsigned char C1;
			unsigned char pad;
		} Char;
		struct
		{
			unsigned O4 : 6;
			unsigned O3 : 6;
			unsigned O2 : 6;
			unsigned O1 : 6;
			unsigned pad : 8;
		} SubCode;
		unsigned int Raw;
	} packet;

	std::string dest;

	size_t slen = src.length();

	auto sptr = (unsigned char const*)src.c_str();
	while (slen > 0)
	{
		int pad = 0;
		packet.Raw = 0;
		packet.Char.C1 = *sptr++;
		slen--;
		if (slen)
		{
			packet.Char.C2 = *sptr++;
			slen--;
		}
		else
			pad++;
		if (slen)
		{
			packet.Char.C3 = *sptr++;
			slen--;
		}
		else
			pad++;

		dest += _encoder[packet.SubCode.O1] + 1;
		dest += _encoder[packet.SubCode.O2] + 1;
		if (pad < 2)
			dest += _encoder[packet.SubCode.O3] + 1;
		else
			dest += _pad;
		if (pad < 1)
			dest += _encoder[packet.SubCode.O4] + 1;
		else
			dest += _pad;
	}

	return dest;
}

void what()
{
	std::cout << "flag{What_Are_U_Looking_At?}" << std::endl;
}

void func(const std::string& input)
{
	// flag{This_1s_A_Faaaake_Flag};
	auto str = "FiAVFwsoHB0DL0UDLzUvNhUVFRUbGS82IBUXEQ==";

	if (b64encode(input) == str)
	{
		std::cout << "Right?" << std::endl;
		exit(0);
	}
	
	std::cout << input.at(28) << std::endl;
}

// flag{CrAzy_Th4vsday_V_me_50}
int main()
{
	std::cout << "Today is Thursday! And you happened to be at MeiYuan..." << std::endl;

	std::string input;
	std::cin >> input;

	try
	{
		if (input.length() == 28)
		{
			if (!strncmp(input.c_str(), "flag{", 5) && input[27] == '}')
			{
				for (auto& ch : input)
					ch = static_cast<char>((ch ^ 114) + 514);

				func(input);
			}
		}
	}
	catch (...)
	{
		auto str = nothing(input);

		for (auto& ch : str)
			ch = static_cast<char>((ch ^ 191) + 9810);

		unsigned char AnaNoSleep[] =
		{
			0x4A, 0x27, 0x4F, 0x3A, 0x4A, 0x19, 0x1D, 0x16, 
			0x4F, 0x26, 0x3B, 0x45, 0x4C, 0x3D, 0xD8, 0x21, 
			0x48, 0x4B, 0x29, 0x49, 0x4F, 0x18, 0x29, 0x3A,
			0x4C, 0x3D, 0xD8, 0x23, 0x44, 0x17, 0x4B, 0x36, 
			0x44, 0xE0, 0x24, 0x4B, 0x4B, 0x3F, 0xD4, 0xD4,
		};

		if (!strncmp(str.c_str(), (const char*)AnaNoSleep, str.length()))
		{
			std::cout << "U r Right! now Vivo the money!" << std::endl;
			exit(0);
		}
	}
	
	std::cout << "U don't have enough money!" << std::endl;
	exit(0);
}
