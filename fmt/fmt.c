#include<stdio.h>
#include<stdlib.h>
int main(){
	char s[64];
	int a = 0;
	int b = 4;
	int c = 10;
	printf("Give me your attention ,please!\n");
	printf("There is a fmtstr, you can use it to change the value of a, b and c!\n");
	printf("Please give me a string!\n");
	scanf("%s",s);
	printf("Hhhh, I know you say:\n");
	
	printf(s, &a, &b, &c);
	printf("\nokk, let us see the result:\na==%d\nb==%d\nc==%d\n",a, b, c);
	if(a == 4){
		if(b != 6 ) return printf("The value of b is not right!\n");
		if(c != 8 ) return printf("The value of c is not right!\n");
		
		printf("Wonderful!\nYou have got a shell now!\n");
		printf("Try to cat the flag!\n");
		system("/bin/sh");
	}
	printf("The value of a is not right!\n");
	return 0;
}
