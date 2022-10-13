using System;

Console.WriteLine("Welcome to .NET world! Feel free to input something!");

if (Console.ReadLine() == "Hello .NET")
	Console.WriteLine("Your flag is mayctf{I_Think_NET_1S_S1mpler_Than_NATIVE!}");
else
	Console.WriteLine("Try again!");

Console.WriteLine("Press any key to exit the program!");
Console.ReadKey(true);
