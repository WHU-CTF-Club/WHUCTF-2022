#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int wel(int a,int b,int c){
	printf("Hello, welcome to our game!\n");
}
void para(int a){
	return ;
}

int main(){
	//system("cat flag");
	char s[16];
	int num = 0;
	wel(0x207a,0x207a,num);
	printf("Please give me a string!\n");
	printf("Don't forget the length of int.\n");
	read(0,s,0x100);
	printf("okk\n");
	return 0;
}
int backdoor(){
	system("cat flag");
	printf("you can't get shell from here");
	printf(";;;;;;/bin/sh\x00");
	para(0x208a);
	return 0;
}
void additional_function(){
	printf("Hello, this function has many words.\n");
	printf("An I don't think you should find something directly.\n");
	printf("You'd better to use ROPgadget to find something.\n");
	printf("Next thing is some asm.\n");
	asm("popq %rdi\n\t"
		
		"ret");

}
