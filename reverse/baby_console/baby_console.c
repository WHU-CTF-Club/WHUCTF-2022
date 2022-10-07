// angstorm 2022 weenhunters2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_MAX 40
#define INPUT_STR_FORMAT "%39s"

#define inline __always_inline

void Welcome();
void First_Random_Seed();
void Get_Decoded_String(int idx, char buffer[]);
int Find_Action_Index(char action[]);
void No_Weapon_Fail(const char* Name);
void Fail(const char* Name);

char* RandomSentences1[5] =
{
	"A soft light emanates from above. All around you are trees, several times your height.",
	"You hear footsteps nearby, but you can't quite make out where they're coming from.",
	"A foreboding feeling washes over you. \"This can't be good,\" you think.",
	"You hear foreign babbling from all directions, sending chills down your spine.",
	"The forest has turned dark. You can barely make out your surroundings.",
};

char* RandomSentences2[5] =
{
	"The twisting passages of the forest make you wonder if you went the right way.",
	"You appear to be going the right way, but you lose track of your position.",
	"You glance down at your map. \"Where am I ?\" you wonder.",
	"The warped geometry of the forest makes navigation difficult.",
	"The darkness of the forest causes you to lose your way, and you're not sure where you are."
};

char* RandomNames[3] =
{
	"joshdabosh",
	"evilmuffinha",
	"pertark",
};

int EncodedStringData[8][32] =
{
	// sword
	0x00039A53, 0x00097E4F, 0x000155AC, 0x000A60AC, 0x0004E93F, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	// whistle
	0x000044BB, 0x0002415F, 0x000483FE, 0x000094BB, 0x0007341E, 0x000109C7, 0x0001B7E1, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	// newspaper
	0x0004010C, 0x0001CC9F, 0x00097EFB, 0x0003758B, 0x000077D3, 0x0003CEBA, 0x0002B9BF, 0x0001C7A9,
	0x000A753F, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	// 54fcfbc921e8b735
	0x00009EC7, 0x00004FB6, 0x00036153, 0x00029479, 0x00034F19, 0x000798A4, 0x00029937, 0x00019798,
	0x0002A719, 0x000163CE, 0x0001B947, 0x0000D1DE, 0x00014CA9, 0x00025EAB, 0x0000EE87, 0x0000A375,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	// 111c7ab93a8cbcae
	0x00016352, 0x00016384, 0x000163B8, 0x00029A6E, 0x00025BDA, 0x0003B8EC, 0x00014464, 0x0001A0E5,
	0x0000ED07, 0x0003CEC9, 0x0000CA32, 0x00027B79, 0x00013DA7, 0x0002749F, 0x0003D938, 0x0001A78F,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	// a8cdae3240310bdd
	0x0003DD43, 0x0000C9AB, 0x00006E1F, 0x00051194, 0x0003BA72, 0x0001B9FF, 0x0000ED01, 0x0000785B,
	0x0001C9FF, 0x0000B37B, 0x0000E29B, 0x00016429, 0x00001FE1, 0x000155BF, 0x0004FB69, 0x00051160,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	// fist
	0x00036BC2, 0x000482CE, 0x00009D1B, 0x0007241F, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	// flee
	0x00036049, 0x0005D7DE, 0x0001C86C, 0x0001C7A7, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

typedef enum
{
	EXPLORING = 0,
	PREP_FIGHT,
	IN_FIGHT,
} GAME_STATUS;

typedef enum
{
	LOST = 0,
	HAVE,
	ENCHANCED,
} ITEM_STATUS;

int main()
{
	Welcome();
	First_Random_Seed();

	short HASH1 = 0xDEAD, HASH2 = 0xBEEF;
	int BOSS = 0;
	int MindPoint = 100;
	char Action[BUFFER_MAX];
	char CurrentWeebName[BUFFER_MAX];
	int CurrentWeebHP;
	GAME_STATUS STATUS_GAME = EXPLORING;
	ITEM_STATUS
		STATUS_FIST = HAVE,
		STATUS_NEWSPAPER = LOST,
		STATUS_SWORD = LOST,
		STATUS_WHISTLE = LOST;

	while (1)
	{
		while (STATUS_GAME == EXPLORING)
		{
			puts(RandomSentences1[rand() % 5]);
			if (MindPoint <= 0)
				puts("You fall to the ground in exhaustion. Weebs surround you, but you are helpless to defend yourself."), Fail(RandomNames[0]);
			else if (MindPoint <= 25)
				puts("It's hard to keep your mind off of anime, and you fear you have almost become a weeb yourself.");
			else if (MindPoint <= 50)
				puts("Your ears ring with the sounds of anime, and it's hard to focus.");
			else if (MindPoint <= 75)
				puts("You're starting to wonder whether you can complete your mission.");
			else if (MindPoint < 100)
				puts("A lingering doubt is at the back of your mind. You press onwards.");
			else if (MindPoint == 100)
				puts("Your mind is clear of any distractions, and you are prepared for your quest.");

			printf("Which way would you like to go?\n> ");
			scanf(INPUT_STR_FORMAT, Action);
			for (int i = 0; i < strlen(Action); ++i)
			{
				if (Action[i] < 32 || Action[i] == 127)
				{
					puts("Babbling incoherently, you try to invoke the dark art known as \"pwn\", but your will isn't strong enough.");
					MindPoint = 0;
				}
			}

			if (HASH1 || HASH2 || strcmp(Action, "a12caf3cba1e5f13"))
			{
				int t = rand();
				srand(t ^ *(int*)Action);
				short HASH1DELTA = rand();
				short HASH2DELTA = rand();
				if (HASH1DELTA > 0)
					HASH1 += HASH1DELTA;
				if (HASH2DELTA > 0)
					HASH2 += HASH2DELTA;
				puts(RandomSentences2[rand() % 5]);
				long long HASH = ((long long)(short)(HASH1 * HASH2) << 32) | (short)(HASH2 ^ HASH1) | (unsigned long long)((long long)(short)((HASH2 & HASH1) + (HASH2 | HASH1)) << 16) | ((long long)(short)((HASH2 & HASH1) + (HASH2 | HASH1) + (HASH2 ^ HASH1) + HASH1 * HASH2) << 48);
				
				// H1	 H2    HASH              ENCHANCE_ITEM
				// 08B6, 6DAC, 33C458487662651A, SWORD
				// 2439, 3C55, DBE762ED608E186C, WHISTLE
				// 2F58, 46FB, 5B3E7B48765369A3, NEWSPAPER
				// 332C, 3A48, D3385C606D740964, FIST
				// 3A48, 332C, D3385C606D740964, FIST
				// 3C55, 2439, DBE762ED608E186C, WHISTLE
				// 46FB, 2F58, 5B3E7B48765369A3, NEWSPAPER
				// 6DAC, 08B6, 33C458487662651A, SWORD
				// 88B6, EDAC, 33C458487662651A, SWORD
				// A439, BC55, DBE762ED608E186C, WHISTLE
				// B32C, BA48, D3385C606D740964, FIST
				// BA48, B32C, D3385C606D740964, FIST
				// BC55, A439, DBE762ED608E186C, WHISTLE
				// EDAC, 88B6, 33C458487662651A, SWORD
				
				if (HASH == 0x5B3E7B48765369A3)
				{
					puts(
						"You find a wizard's tower in the depths of the forest. \"For years, I have waited for somebody to defeat the"
						" weebs that haunt this forest,\" he says.");
					if (STATUS_NEWSPAPER != LOST)
					{
						puts(
							"\"I can enchant your newspaper and cause it to hurt the weebs. Good luck!\" You've been equipped with a powerful weapon.");
						STATUS_NEWSPAPER = ENCHANCED;
					}
					else
					{
						puts("\"Bring me a newspaper, and I can give it mystical powers.\" You don't have any newspapers on you.");
					}
				}
				else if (HASH == 0x33C458487662651A)
				{
					puts(
						"You find a blacksmith's house in the depths of the forest. \"For years, I have waited for somebody to de"
						"feat the weebs that haunt this forest,\" he says.");
					if (STATUS_SWORD != LOST)
					{
						puts(
							"\"I can improve your sword and make it sharper. Good luck!\" You've been equipped with a powerful weapon.");
						STATUS_SWORD = ENCHANCED;
					}
					else
					{
						puts(
							"\"Bring me a sword, and I can make it more deadly towards the weebs.\" You don't have any swords on you.");
					}
				}
				else if (HASH == 0xD3385C606D740964)
				{
					puts(
						"You find a doctor's hut in the depths of the forest. \"For years, I have waited for somebody to defeat"
						" the weebs that haunt this forest,\" he says.");
					if (STATUS_FIST == HAVE)
					{
						puts("\"I can reattach your fist to your arm. Good luck!\" Your fist is back on!");
						STATUS_FIST = ENCHANCED;
					}
					else if (STATUS_FIST == ENCHANCED)
					{
						puts("\"I have already done all I can do for your mission. Good luck!\"");
					}
					else
					{
						puts(
							"You remember that you left your fist behind in your previous quest, and ask the doctor if he can hel"
							"p. \"If you bring me your fist, I can reattach it to your arm,\" he says.");
					}
				}
				else if (HASH == 0xDBE762ED608E186C)
				{
					puts(
						"You find a engineer's shack in the depths of the forest. \"For years, I have waited for somebody to de"
						"feat the weebs that haunt this forest,\" he says.");
					if (STATUS_WHISTLE != LOST)
					{
						puts(
							"\"I can improve your whistle and make it more damaging to the weebs. Good luck!\" You've been equipp"
							"ed with a powerful weapon.");
						STATUS_WHISTLE = ENCHANCED;
					}
					else
					{
						puts("\"Bring me a whistle and I can make its sound more painful.\" You don't have any whistles on you.");
					}
				}

				else if ((((unsigned char)HASH2 ^ (unsigned char)HASH1) & 7) != 0)
				{
					if (HASH % 8 == 1)
					{
						int Item = HASH / 8 % 4;
						if (Item == 2)
						{
							puts("You found a whistle!");
							if (STATUS_WHISTLE == LOST)
								STATUS_WHISTLE = HAVE;
						}
						else if (Item == 0)
						{
							puts("You found a sword!");
							if (STATUS_SWORD == LOST)
								STATUS_SWORD = HAVE;
						}
						else if (Item == 1)
						{
							puts("You found a newspaper!");
							if (STATUS_NEWSPAPER == LOST)
								STATUS_NEWSPAPER = HAVE;
						}
					}
				}
				else
					STATUS_GAME = PREP_FIGHT;

				--MindPoint;
			}
			else
			{
				puts("You utter the incantation and the ground shakes. A set of stairs lead down into the darkness...");
				puts("You walk into the dungeon, and you see a single figure standing before you! As you prepare to face your opponent, you know that this is the final battle!");
				strcpy(CurrentWeebName, "kmh");
				STATUS_GAME = IN_FIGHT;
				BOSS = 1;
				CurrentWeebHP = 400;
			}
		}

		if (STATUS_GAME == PREP_FIGHT)
		{
			strcpy(CurrentWeebName, RandomNames[HASH2 * HASH1 % 3]);
			printf("You hear a noise behind you... \"BAKA!!!\" %s comes charging at you.\n", CurrentWeebName);
			CurrentWeebHP = *(int*)CurrentWeebName % 100;
			STATUS_GAME = IN_FIGHT;
		}

		// In Fight Loop
		printf("Choose your action: ");
		scanf(INPUT_STR_FORMAT, Action);

		switch (Find_Action_Index(Action))
		{
		case 0:
			if (STATUS_SWORD == LOST)
				No_Weapon_Fail(CurrentWeebName);
			puts(
				"You slash the weeb's arm off. \"'tis but a scratch,\" he claims, but it's obviously a little worse than that. In"
				" the intense pain, he has forgotten 8 days worth of anime.");
			CurrentWeebHP -= 8;
			break;
		case 1:
			if (STATUS_WHISTLE == LOST)
				No_Weapon_Fail(CurrentWeebName);
			puts(
				"You blow into the whistle and the piercing sound engulfs the weeb's sensory system. He forgets 6 days worth of anime.");
			CurrentWeebHP -= 6;
			break;
		case 2:
			if (STATUS_NEWSPAPER == LOST)
				No_Weapon_Fail(CurrentWeebName);
			puts(
				"You bop the weeb on the head with the rolled up newspaper. He suffers minor brain damage and forgets a single day of anime.");
			CurrentWeebHP -= 1;
			break;
		case 3:
			if (STATUS_SWORD != ENCHANCED)
				No_Weapon_Fail(CurrentWeebName);
			puts(
				"You slash the weeb's arm off. \"'tis but a scratch,\" he claims, but it's obviously a little worse than that. In"
				" the intense pain, he has forgotten 100 days worth of anime.");
			CurrentWeebHP -= 100;
			if (BOSS)
			{
				puts("The boss retaliates quickly and disarms you with a sweeping blow of anime. You've lost your sword.");
				STATUS_SWORD = LOST;
			}
			break;
		case 4:
			if (STATUS_WHISTLE != ENCHANCED)
				No_Weapon_Fail(CurrentWeebName);
			puts(
				"You blow into the whistle and the piercing sound engulfs the weeb's sensory system. He forgets 100 days worth of anime.\n");
			CurrentWeebHP -= 100;
			if (BOSS)
			{
				puts("The boss retaliates quickly and disarms you with a sweeping blow of anime. You've lost your whistle.");
				STATUS_WHISTLE = LOST;
			}
			break;
		case 5:
			if (STATUS_NEWSPAPER != ENCHANCED)
				No_Weapon_Fail(CurrentWeebName);
			puts(
				"You bop the weeb on the head with the rolled up newspaper. He suffers minor brain damage and forgets 100 days of anime.");
			CurrentWeebHP -= 100;
			if (BOSS)
			{
				puts("The boss retaliates quickly and disarms you with a sweeping blow of anime. You've lost your newspaper.");
				STATUS_NEWSPAPER = LOST;
			}
			break;
		case 6:
			if (STATUS_FIST == LOST)
			{
				puts("You try to hit the weeb with your fist, but then you realize that you left it behind in the last battle!");
				Fail(CurrentWeebName);
			}
			else if (STATUS_FIST == HAVE)
			{
				puts("Your fist is still not attached to your arm yet!");
				Fail(CurrentWeebName);
			}
			else if (BOSS &&
				STATUS_NEWSPAPER == LOST && STATUS_WHISTLE == LOST && STATUS_SWORD == LOST
				&& CurrentWeebHP <= 100)
			{
				puts(
					"You hit the weeb with your fist, vanquishing it forever into the void. You have restored peace to this land "
					"and destroyed forever the reign of the weebs.");
				printf("You also got the flag: ");
				system("cat ./flag");
				return 0;
			}
			else
			{
				puts("You hit the weeb with your fist, but you don't deal any damage.");
			}
			break;
		case 7:
			printf(
				"Knowing you have no chance of defeating someone who's watched %d days of anime, you run away as fast as you can."
				" In your haste, you leave your weapons behind.\n",
				CurrentWeebHP);
			STATUS_GAME = EXPLORING;
			STATUS_SWORD = LOST;
			STATUS_NEWSPAPER = LOST;
			STATUS_WHISTLE = LOST;
			if (STATUS_FIST != ENCHANCED)
				STATUS_FIST = LOST;
			break;
		default:
			break;
		}

		if (STATUS_GAME == EXPLORING)
			continue;

		if (CurrentWeebHP > 0)
		{
			printf("%s emits a piercing scream. \"Explosion\"! You are engulfed in a fireball as the sounds of anime begin to close in...\n", CurrentWeebName);
			MindPoint -= 20;
			if (MindPoint <= 0)
				Fail(CurrentWeebName);
		}
		else
		{
			printf("%s stiffens as he realizes that he doesn't remember any anime anymore. You have vanquished a weeb!\n", CurrentWeebName);
			if (STATUS_FIST == LOST)
			{
				printf("You search %s's possessions and find your fist that you left behind.\n", CurrentWeebName);
				STATUS_FIST = HAVE;
			}
			STATUS_GAME = EXPLORING;
		}
	}

	return 0;
}

inline void Welcome()
{
	puts("Welcome to the new Weeb Hunters 2: The Flag of Power!");
	printf("Enter your name: ");
	char Name[BUFFER_MAX];
	scanf(INPUT_STR_FORMAT, Name);
	printf(
		"You are %s, a valiant weeb hunter. "
		"You will be traversing the dangerous Otaku Forest, "
		"where weebs surround you in every direction.\n",
		Name
	);
	puts("Along the way, you will find many friends and foes on your quest to destroy the weebs once and for all.");
	puts("You will collect magical artifacts, but you can only use them if you find out the right command phrase!");
}

inline void First_Random_Seed()
{
	char Keys[11 * 12] = { 0 };
	for (int i = 0; i < 11; ++i)
		memcpy(Keys + i * 12, "weebhunters2", 12);
	int Seed = time(NULL);
	for (int i = 0; i < 32; ++i)
		Seed = Keys[4 * i] ^ (Seed >> 1);
	srand(Seed);
}

inline void Get_Decoded_String(int idx, char buffer[])
{
	int i;
	for (i = 0; EncodedStringData[idx][i]; ++i)
	{
		char v20 = 0;
		int v21 = EncodedStringData[idx][i];
		while (v21 != 1)
		{
			if ((v21 & 1) != 0)
				v21 = 3 * v21 + 1;
			else
				v21 >>= 1;
			++v20;
		}
		buffer[i] = v20 + 0x80;
	}
	buffer[i] = 0;
}

inline int Find_Action_Index(char action[])
{
	char DecodeBuffer[BUFFER_MAX];
	for (int i = 0; i < 8; ++i)
	{
		Get_Decoded_String(i, DecodeBuffer);
		if (!strcmp(action, DecodeBuffer))
			return i;
	}
	return -1;
}

inline void No_Weapon_Fail(const char* Name)
{
	puts("You grasp for your weapon, but you can't find anything.");
	Fail(Name);
}

inline void Fail(const char* Name)
{
	printf(
		"%s begins watching anime in front of you and you become entranced."
		"Otaku, kawaii, senpai... you have become one of them.\n",
		Name
	);
	exit(0);
}
