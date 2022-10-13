using System;

int counter = 0;

Console.WriteLine("Can you figure out what I have?");

while (counter != 114514)
{
	if (Console.ReadLine() == "1919810")
	{
		++counter;
	}
}

Console.WriteLine("Wow, your key is \"S1mpleFirstRound\"");
