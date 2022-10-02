#include <iostream>
#include <string>

int main()
{
	std::cout << "I'm trapped! Can you help me to get out of here?" << std::endl;
	std::string input;
	std::cin >> input;

	if (input.length() != 32)
	{
		std::cout << "You don't know how to do reverse, do you?" << std::endl;
		return 0;
	}

	char maze[10][11]
	{
		"*#########",
		"**########",
		"#*########",
		"***#######",
		"*#***##***",
		"**##****#*",
		"#**######*",
		"#*#*******",
		"**#*######",
		"###*******",
	};

	int pos_x = 0, pos_y = 0;

	for (const auto& opt : input)
	{
		switch (opt)
		{
			case 'W':
				--pos_y;
				break;
			case 'A':
				--pos_x;
				break;
			case 'S':
				++pos_y;
				break;
			case 'D':
				++pos_x;
				break;
			default:
				std::cout << "What are you doing?" << std::endl;
				return 0;
		}

		if (pos_x < 0 || pos_x > 9 || pos_y < 0 || pos_y > 9)
		{
			std::cout << "Oooooh! My head is hurt!" << std::endl;
			return 0;
		}
	}

	if (pos_x == 9 && pos_y == 9)
		std::cout << "Congratulations! Your flag is mayctf{sha256(input)}." << std::endl;
	else
		std::cout << "Oops, I'm still in the maaaaaze!" << std::endl;

	return 0;
}