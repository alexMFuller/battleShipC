#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//#include <stdio.h>

#include "../include/io.h"

int In = STDIN_FILENO;
int Out = STDOUT_FILENO;

;void setOUTIN(int c){
	In = c;
	Out = c;
	
}


void printc(char c) {
  // your code here
	 write(Out, &c , 1);
	 //printf("%d\n",c);
}

void prints(char* s) {
  write(Out, s, strlen(s));
}

void println() {
  printc('\n');
}

void inputs(char *dst[], int size) {
  // your code here
	char temp[20];
	read(In, temp , size);
	for (int i =0;i<strlen(temp);i++){
		if (!isalnum(temp[i])&&temp[0]!='!'){
			temp[i]= '\0';
		}
	}

	*dst = temp;
	//prints(temp);
}

void inputInt(char dst[]){
	
	read(In, dst , 2);
	//read(STDIN_FILENO,NULL,0);
	//close(STDIN_FILENO);
}