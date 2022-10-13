// angstorm 2022 weebhunters2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_MAX 40
#define INPUT_STR_FORMAT "%39s"

#define inline __always_inline

char Intro[] = 
{
	"..................................................................................................]\n"
	".            ....                .                     .^ .,].  .............. .  ... .....,]]/[. .\n"
	".     ..                                               =.....,*]. .....   ........... . ,/......./.\n"
	".    .                                                 O..........*]]][[[`............,/......]/`=[\n"
	".     ..                                              .O.................................../`...,//\n"
	".                      ..  ....,]]]. .                 O.........**../*..................,^........\n"
	".                       ..,]OOO@@@@OOOO@@@*....        ,*...^..***.,@O/^................,^......*/.\n"
	". .              ..,oOOO@@@@@@@@@@@@@@@@@@@@*. ...     .*]`/..***./@@^***..............*..........,\n"
	". .          .]/*].*O@@@@@@@@@@@@@@@@@@@@@@@@O@].. .. ./**=^.***.@@@/O*.**....................../`.\n"
	".. ..     ..OO@@@@O*=OO@@@@@@@@@@@@@@@@@@@@@@O@@@@@` ...**O..**.=@@@O@O@@=..............*..........\n"
	".. ..    ./O@@@O@@@@OoOOO@@@@@@@@@@@@@@@@@@@@@@@@@@@* ..,O..**.=@@@@@@**@o^.....]]]]]].............\n"
	"..     .,OOOO@@@@@@@@OOOOO@@@@@@@@@@@@@@@@@@@@@@@@@@@@`..^@@/..,@@@@@@[OOO....@^.OO,,@@`.........,/\n"
	".. ,*..O@@@@@@@@@@@@@@@@OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@O*.^,@^*O^/@@@@^......./@*.,[./`/`....,...,/.\n"
	".      ,@O*]]/O@@@@@@@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^..**]/@O@`........=/[[...,/`....,^....O^.\n"
	".    ....O@@@@@@@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^***.@@@@.....................,/......O..\n"
	".   ..*..=O@@@@O@@O@@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.**.@@@`.^***....`.........,/.*.....=O`.\n"
	".    ,*O`.=OOOO@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O^***=@@.=***,......[........`..`....O`..\n"
	"...]OO@O[..=O@@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O*.**.=^.... .......................,O...\n"
	".  .,[[oOO`=OO@@OO@@@@@@@@@@@@@@@@@@@@@@@@@=@@@@@@@@@@@@@@@O.***=]@@@@@@@@^.................../^...\n"
	".  ...O@@@O/[[OO@@@@@@@@@@@@@@@@@/.O@@@@@@^=@@@@@@@@@@@@@@@^.***.*@@@@@@@`..........=........,@**..\n"
	".  ...O@@OOOOOO@@@@@@@@@@@@@@@`@/@@*@@*@@@@@@@@@@@O@@@@@@@@@*****...[*`.....`................//*...\n"
	".   .=@OO@@@OOO/[]]`*,[*@@@O*O[*@@]/@@@@*@..=@@@@*@*@@@@@@@O^***.....=*]...........`.........@^*...\n"
	".   .[[[O]]/O@@^OOOOO*oo*=O@^ooo=/*O*`.......,@@/..@@@@@@OO.=`**=`.]/......[[*]]//..........=O[o**.\n"
	".   ..[[*@@@@@O^**//.]@*/@/@O/oo/]*,@[/@/O*@OO`..../@@@@O@^..,*.**...,]]]@*].............../@O*****\n"
	".    .....*OO@O*o**[@]/OO*@@O/[**,@*=*][[,//.......@@@@@^,^....******.@@/.............../@@@@****=*\n"
	".       . .o/@O**^.****]`O/=^**...*,@O.......*/...=@@@O@.=......,*.***[`............,/@@@@@@@*****O\n"
	".        ..,OOO^*.........*^..................,..,/@@OO^.^........*^***..........,/@@@@@@@@@@****.O\n"
	".         .*OO*`*`.........^......................=@O,O./.....   ...*`*.......,/@@@@@@@@@@@@@.**,oO\n"
	".        . .OO@^*`.........^....,.................@@O`./....       ..,[[OOOO@@@@@@@@@[[.].,[[O]`.O/\n"
	".        .  .Oo/**.........,@]//............,..../...,^.....        .........=@/*]O[[`......[[*]`[@\n"
	".     .,`...]O]O`,`.........................*...=.../`.....        .......,O`,[....................\n"
	".        ,*@@@@@^.`............................,^...........       ....,/`.........................\n"
	".         ..,@@@@..........*O*OOO*`............/..........        ..,/`............................\n"
	".        ...... ........,[...,`....,[`......../........         . ..=[*OOO/O]`.....................\n"
	".        ........./`......**]]]`]//........../[^.........  ......../`*****,/[@]*@`...........,]OOO[\n"
	".        ....... =@O*.......*/@^.........../*O*,*.................O******......,**,@`...../@O/`....\n"
	".        ...... =@OO*@`.................,O`.@Oo`=@O@*`..........//*****..........*,*`*]O@/`........\n"
	".       ...... /@@Oooo@O`............./@^/.O*@o^=@@@@@@*......,@@.***......,`......*@@@.**.........\n"
	".     ......,]@@@@@OoooO@*.........]@`//^,OoO@oo=@@@@@@@@@`../@@.***...............=@@`*...........\n"
	"]]/@*`..,]@@@@@@@@@OooooO@O@@@@@@@@**@`,O*oo/Oo^/@@@@@@@@@@^/@@O.**................=@^.............\n"
	"@@@@@@@@@@@@@@@@@OO@OoooooO*=@@@@//.@*/OOOo^@Oo*O@@@@@@@@@^/@@@^***................=^*.............\n"
	"@@@@@@@@@@@@@@@@@Oo@@@ooooooO`@@OO.=*O/OOooO@^o/^@@@@@@@@@@@@@@^**.................O**.............\n"
	"@@@@@@@@@@@@@@@OOOoO@@@OoooooO`*@O.@ooO@ooo@OooO`*@@@@@@@@@@@@@O.*................,O**.............\n"
	"@@@@@@@@@@@@@@@@OOOoOO@@@OoOooooo*O*oO@OooO@*oo/*=@@@O@@@@@@@@@@@]................=^**.............\n"
	"@@@@@@@@@@@@@@@@OoOOooO@@@OoOOoooOOoO@Oooo@*oo/=^=@@@@@@O@@@@@@@@@@@@]`,@@@@@@@@*`=^**.............\n"
	"@@@@@@@@@@@@@@@@@OoOooOOO@@OooOOooOO@OoooOoooO*o^@@@O@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@^**.............\n"
	"@@@@@@@@@@@@@@@@@OooooooOOOOOooOOoo@OoooOoooO^Oo/@@@O@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@^**............\n"
	"@@@@@@@@@@@@@@@@@@OoooooooooOOooOOoOOooOooo@*OoO@@@@O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.............\n"
	"@@[`.....[[O@@@@@@@Oooooooooo@OooO@oO/@*oo@OOoO@@@@@OO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*............\n"
};

char PlayerName[BUFFER_MAX];

void Welcome();
void First_Random_Seed();
void Get_Decoded_String(int idx, char buffer[]);
int Find_Action_Index(char action[]);
void No_Weapon_Fail(const char* Name);
void Fail(const char* Name);

char* RandomSentences1[5] =
{
	"柔和的光线从上方发出。你周围都是你身高的几倍树。",
	"你听到附近有脚步声，但你不太清楚它们是从哪里来的。",
	"不祥的预感笼罩着你。",
	"你听到杂音自四面八方涌来，让你后背一凉。",
	"天黑了下来，你无法看清周围的环境。",
};

char* RandomSentences2[5] =
{
	"森林中蜿蜒曲折的通道让你怀疑自己走的路是否正确。",
	"你似乎走在正确的道路上，但是你忘了自己的位置。",
	"你看了眼地图：“我在哪？”你想到。",
	"然日卡被烟雾缭绕，导航成了大问题。",
	"黑暗使你丢失了目标，你完全不知道自己在哪。"
};

char* RandomNames[3] =
{
	"josh雪豹",
	"evil鸡",
	"pert香烟",
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
			printf("%s\n", RandomSentences1[rand() % 5]);
			if (MindPoint <= 0)
				printf("你掉到了一个全是传统香烟的洞中，你知道自己已经回天无力了。\n"), Fail(RandomNames[0]);
			else if (MindPoint <= 25)
				printf("在传统香烟之中很难坚持自我，但是你还在继续坚持着。\n");
			else if (MindPoint <= 50)
				printf("你开始逐渐难以集中注意，传统香烟正在逐步侵蚀着你的心智。\n");
			else if (MindPoint <= 75)
				printf("你开始怀疑你能否完成你的任务。\n");
			else if (MindPoint < 100)
				printf("一个挥之不去的疑问出现在了你的脑海中，但是你决定继续前进。\n");
			else if (MindPoint == 100)
				printf("你的内心十分清醒，你已经做好了消灭传统香烟的准备。\n");

			printf("你要从那一条路走？\n> ");
			scanf(INPUT_STR_FORMAT, Action);
			for (int i = 0; i < strlen(Action); ++i)
			{
				if (Action[i] < 32 || Action[i] == 127)
				{
					printf("你试图向一股名为PWN的神秘力量，但是你的力量还不够强大，遭到了反噬！\n");
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
				printf("%s\n", RandomSentences2[rand() % 5]);
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
					printf("你找到了丁真先生告诉你的雪豹朋友，\"这么多年来，我都在等待一个人与我一起消灭传统香烟。\"他说。\n");
					if (STATUS_NEWSPAPER != LOST)
					{
						printf("\"我可以帮你强化这本语文书，让它具有初中的知识。祝你好运！\"你获得了一把强力的武器！\n");
						STATUS_NEWSPAPER = ENCHANCED;
					}
					else
						printf("\"把你的语文书带来，我可以让它满足你初中的知识需要。\"但是你身上并没有带语文书。\n");
				}
				else if (HASH == 0x33C458487662651A)
				{
					printf("你找到了丁真先生告诉你的狐狸朋友，\"这么多年来，我都在等待一个人与我一起消灭传统香烟。\"他说。\n");
					if (STATUS_SWORD != LOST)
					{
						printf("\"我可以帮你强化这把剑，让它变得更加锋利。祝你好运！\"你获得了一把强力的武器！\n");
						STATUS_SWORD = ENCHANCED;
					}
					else
						printf("\"把你的剑带来，我可以让它变得更加锋利。\"但是你身上并没有带剑。\n");
				}
				else if (HASH == 0xD3385C606D740964)
				{
					printf("你找到了丁真先生开设的电子烟公司分部，\"这么多年来，我都在等待一个人与我一起消灭传统香烟。\"分部的经理说。\n");
					if (STATUS_FIST == HAVE)
					{
						printf("\"我可以帮你重新装填烟弹，祝你好运！\"你的烟弹已经准备好了。\n");
						STATUS_FIST = ENCHANCED;
					}
					else if (STATUS_FIST == ENCHANCED)
						printf("\"我已经把我能做的都做了，祝你好运！\"\n");
					else
					{
						printf("\"把你的烟弹带来，我可以帮你重新装填。\"但是你身上并没有带之前扔掉的烟弹。\n");
					}
				}
				else if (HASH == 0xDBE762ED608E186C)
				{
					printf("你找到了丁真先生告诉你的猞猁朋友，\"这么多年来，我都在等待一个人与我一起消灭传统香烟。\"他说。\n");
					if (STATUS_WHISTLE != LOST)
					{
						printf("\"我可以帮你烘焙这根理塘特色烟草，让它变得更加强大。祝你好运！\"你获得了一把强力的武器！\n");
						STATUS_WHISTLE = ENCHANCED;
					}
					else
						printf("\"把你的理塘特色烟草带来，我可以让它变得更加强大。\"但是你身上并没有带理塘特色烟草。\n");
				}

				else if ((((unsigned char)HASH2 ^ (unsigned char)HASH1) & 7) != 0)
				{
					if (HASH % 8 == 1)
					{
						int Item = HASH / 8 % 4;
						if (Item == 2)
						{
							printf("你找到了理塘特色烟草！\n");
							if (STATUS_WHISTLE == LOST)
								STATUS_WHISTLE = HAVE;
						}
						else if (Item == 0)
						{
							printf("你找到了一把剑！\n");
							if (STATUS_SWORD == LOST)
								STATUS_SWORD = HAVE;
						}
						else if (Item == 1)
						{
							printf("你找到了一本语文书！\n");
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
				printf("突然，一只巨大的鸡抽着一支传统香烟从天而降！\n");
				printf(
					"%s：差不多得了😅屁大点事都要拐上丁真，丁真一没招你惹你，二没干伤天害理的事情，"
					"到底怎么你了让你一直无脑抹黑，丁真每天费尽心思的保护理塘，你这种喷子只会在网上敲键盘诋毁丁真，理塘的未来就是被你这种人毁掉的😅\n",
					PlayerName
					);
				
				strcpy(CurrentWeebName, "坤坤");
				STATUS_GAME = IN_FIGHT;
				BOSS = 1;
				CurrentWeebHP = 400;
			}
		}

		if (STATUS_GAME == PREP_FIGHT)
		{
			strcpy(CurrentWeebName, RandomNames[HASH2 * HASH1 % 3]);
			printf("你听见了一声巨响！\"%s\"向你冲了过来！\n", CurrentWeebName);
			CurrentWeebHP = *(int*)CurrentWeebName % 100;
			STATUS_GAME = IN_FIGHT;
		}

		// In Fight Loop
		printf("选择你的行动：");
		scanf(INPUT_STR_FORMAT, Action);

		switch (Find_Action_Index(Action))
		{
		case 0:
			if (STATUS_SWORD == LOST)
				No_Weapon_Fail(CurrentWeebName);
			printf("你用剑砍向了敌人，它掉落了8根传统香烟！\n");
			CurrentWeebHP -= 8;
			break;
		case 1:
			if (STATUS_WHISTLE == LOST)
				No_Weapon_Fail(CurrentWeebName);
			printf("你用理塘特色烟草扔向了敌人，它掉落了6根传统香烟！\n");
			CurrentWeebHP -= 6;
			break;
		case 2:
			if (STATUS_NEWSPAPER == LOST)
				No_Weapon_Fail(CurrentWeebName);
			printf("你用你的语文书上面的知识开始辱骂敌人，它掉落了1根传统香烟！\n");
			CurrentWeebHP -= 1;
			break;
		case 3:
			if (STATUS_SWORD != ENCHANCED)
				No_Weapon_Fail(CurrentWeebName);
			printf("你用剑砍向了敌人，它掉落了100根传统香烟！\n");
			CurrentWeebHP -= 100;
			if (BOSS)
			{
				printf("坤坤反应很快，它一脚就把你的剑踹飞了。\n");
				STATUS_SWORD = LOST;
			}
			break;
		case 4:
			if (STATUS_WHISTLE != ENCHANCED)
				No_Weapon_Fail(CurrentWeebName);
			printf("你用理塘特色烟草扔向了敌人，它掉落了100根传统香烟！\n");
			CurrentWeebHP -= 100;
			if (BOSS)
			{
				printf("坤坤反应很快，它一脚就把你的理塘特色烟草踩在了脚下。\n");
				STATUS_WHISTLE = LOST;
			}
			break;
		case 5:
			if (STATUS_NEWSPAPER != ENCHANCED)
				No_Weapon_Fail(CurrentWeebName);
			printf("你用你的语文书上面的知识开始辱骂敌人，它掉落了100根传统香烟！\n");
			CurrentWeebHP -= 100;
			if (BOSS)
			{
				printf("坤坤反应很快，它一脚就把你的语文书给干碎了。\n");
				STATUS_NEWSPAPER = LOST;
			}
			break;
		case 6:
			if (STATUS_FIST == LOST)
			{
				printf("你试图使用烟弹攻击敌人，但是你想起来你在上一场战斗中把它丢掉了！\n");
				Fail(CurrentWeebName);
			}
			else if (STATUS_FIST == HAVE)
			{
				printf("你的烟弹还没装到身上！\n");
				Fail(CurrentWeebName);
			}
			else if (BOSS &&
				STATUS_NEWSPAPER == LOST && STATUS_WHISTLE == LOST && STATUS_SWORD == LOST
				&& CurrentWeebHP <= 100)
			{
				printf("你使用烟弹攻击了坤坤，最终击败了它。随着王源缉捕计划的开展，理塘电子烟公司开始愈发繁荣，逐渐走向全球。\n");
				printf("丁真先生将flag告知于你: ");
				system("cat ./flag");
				return 0;
			}
			else
				printf("你使用烟弹攻击了敌人，但是好像并没有什么用。\n");
			break;
		case 7:
			printf("你意识到这个拥有%d根传统香烟的敌人是你无法打败的，于是你头也不回尽可能快的跑了 —— 但你没有机会带走你的武器了。\n", CurrentWeebHP);
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
			printf("%s点燃了它的传统香烟！随着传统香烟的点燃，你被笼罩在了烟雾之中。\n", CurrentWeebName);
			MindPoint -= 20;
			if (MindPoint <= 0)
				Fail(CurrentWeebName);
		}
		else
		{
			printf("%s听取了你的劝告，扔下了它的传统香烟。你成功地打败了一个ikun！\n", CurrentWeebName);
			if (STATUS_FIST == LOST)
			{
				printf("你翻找了%s的随身物品， 发现了你之前落下的烟弹。\n", CurrentWeebName);
				STATUS_FIST = HAVE;
			}
			STATUS_GAME = EXPLORING;
		}
	}

	return 0;
}

inline void Welcome()
{
	printf("%s", Intro);
	printf("欢迎来到《烟神》！\n");
	printf("请输入你的姓名：");
	scanf(INPUT_STR_FORMAT, PlayerName);
	printf(
		"《烟神》是由丁真珍珠自主研发的一款全新开放世界冒险游戏。\n"
		"游戏发生在一个被称作「理塘」的幻想世界，在这里被神选中的人将被授予「电子烟」，引导尼古丁之力。\n"
		"你，%s，将扮演一位名为「锐刻5」的神秘角色，在自由的旅行中邂逅性格各异、能力独特的动物朋友们，\n"
		"和它们一起击败强敌，找回不存在的亲人的同时，逐步发掘「理塘」的真相。\n",
		PlayerName);
}

inline void First_Random_Seed()
{
	char Keys[11 * 12] = { 0 };
	for (int i = 0; i < 11; ++i)
		memcpy(Keys + i * 12, "《烟神》", 12);
	int Seed = time(NULL);
	for (int i = 0; i < 32; ++i)
		Seed = Keys[4 * i] ^ (Seed >> 1);
	srand(Seed - 36);
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
	printf("你试图使用道具，但是什么都没有找到。\n");
	Fail(Name);
}

inline void Fail(const char* Name)
{
	printf("%s开始在你的面前使用传统香烟，而你也逐渐迷失在了其中，成为了传统香烟的受害者。\n", Name);
	exit(0);
}
