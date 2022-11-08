#include "../include/record.h"
//#include <stdio.h>
#include <errno.h>

int validateUsername(char* user){
	for (int i=0;i<strlen(user);i++){
		if (!isalnum(user[i])){
			return 0;
		}
	}

	return 1;
}

int writeFile(char* user, int* bowCords, int*innerBowCords ,int*innerSternCords,int*sternCords){
	char path[50]; //= "playerFiles/";
	
	char newLine[1] = {'\n'};
	strcpy(path,"playerFiles/");
	
	strcat(path, user); 

  int file = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);

	//printf("%d,%d\n",bowCords[0],bowCords[1]);
	//printf("%d,%d\n",sternCords[0],sternCords[1]);
	//printf("%d,%d\n",innerBowCords[0],innerBowCords[1]);
  //printf("%d,%d\n",innerSternCords[0],innerSternCords[1]);


	char bow[3] = {bowCords[0]+'0',',',bowCords[1]+'0'};
	char stern[3] = {sternCords[0]+'0',',',sternCords[1]+'0'};
	char innerB[3] = {innerBowCords[0]+'0',',',innerBowCords[1]+'0'};;
	char innerS[3]= {innerSternCords[0]+'0',',',innerSternCords[1]+'0'};;

	write(file,bow,3);
	write(file,newLine,1);
	write(file,innerB,3);
	write(file,newLine,1);
	write(file,innerS,3);
	write(file,newLine,1);
	write(file,stern,3);

	close(file);
	//prints("at end of write\n");
	return 1;
}

int readFile(char* user, char*** dest){
	
	char path[50]; //= "playerFiles/";
	
	//char newLine[1] = {'\n'};
	strcpy(path,"playerFiles/");
	
	strcat(path, user); 

	int infile = open(path,O_RDWR, 0777);
	if (infile==-1){
		//printf("%d\n",errno);
		//printf("here\n");
		return 0;
	}

	char *temp = malloc(50*sizeof(char));


	//printf("%d\n",size);
	//	printf("%d\n",errno);

	read(infile,temp,50);

//	printf("%d\n",t);

	char **wordArray = malloc(4*sizeof(char*));
	char* formStr= strtok(temp, " \n");
	for (int i = 0;i<4;i++){

		wordArray[i] = malloc(10*sizeof(char));

		strncpy(wordArray[i],formStr,3);

		//prints(wordArray[i]);
		//println();

		formStr= strtok(NULL, " \n");
	}
	
	*dest = wordArray;
	close(infile);

	return 1;
}

