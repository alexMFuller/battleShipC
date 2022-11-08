#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/game.h"

void doprocessing (int sock);
int empty(char* buf);

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno;
   socklen_t  clilen;
   char buffer[256];
   struct sockaddr_in serv_addr;
   struct sockaddr  cli_addr;
   int n, pid;

   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);

   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 25800;

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }

   /* Now start listening for the clients, here
    * process will go in sleep mode and will wait
    * for the incoming connection
    */
   if(listen(sockfd, 5))
   {
      perror("ERROR on listening");
      exit(1);
   }

   clilen = sizeof(cli_addr);
   while (1) {
      newsockfd = accept(sockfd,  &cli_addr, &clilen);
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }

      /* Create child process */
      pid = fork();
      if (pid < 0) 
      {
         perror("ERROR on fork");
         exit(1);
      }

      if (pid == 0) 
      {
         /* This is the child  process */
         close(sockfd);
         doprocessing(newsockfd);
         exit(0);
      }
      else 
      {
         /* this is the parent process */
         close(newsockfd);
         listen(sockfd,5);
      }

   } /* end of while */
}

int empty(char buf[])
{
  int flag = 1;
  for(int i = 0; i < strlen(buf); ++i)
    flag = flag && isspace(buf[i]);

  return flag;
}


void doprocessing (int sock) {
  
	//write(STDOUT_FILENO,"\033[2J",4);
	char *name;
	char userOption[1];
	int userNameValid = 1;
	int userOptionValid = 1;

	setOUTIN(sock);

	do{
		prints("Please enter your username: ");
		inputs(&name,20);
		for (int i = 0; i<strlen(name);i++){
			if (!isalnum(name[i])){
				
				userNameValid = 0;
			}
		}
	}while(!userNameValid);

	int userActive = 1;

	do{
		//write(STDOUT_FILENO,"\033[2J",4);


		do{
			userOptionValid = 0;
			
			prints("Welcome!");
			prints("Please select your option!\n1.) Hide Ship\n2.) Find Ship\n3.) Quit\n\n");

			prints("Please enter your option(1,2,3): ");
			inputInt(userOption);

			//printc(userOption[0]);
			if(userOption[0]=='1'||userOption[0]=='2'||userOption[0]=='3'){
				userOptionValid = 1;
			}
			else{
				prints("That is not one of the options, try again!\n");
			}
			

		}while(!userOptionValid);

		if(userOption[0]=='1'){
			hideShip(name);
		}


		if(userOption[0]=='2'){
			
			int quitFind = 0;
			char *enemyName;
			do{
			//write(STDOUT_FILENO,"\033[2J",4);
			
			
			
			prints("Please select a player to play against: (Use ! to quit)\n");

			DIR *d;
  		struct dirent *dir;
  		d = opendir("playerFiles");
			if (d==NULL){
				prints("ERROR READING PLAYER FILES FOLDER");
			}
			
  		if (d) {
    		while ((dir = readdir(d)) != NULL) {
					char* read = dir->d_name;
					if (isalnum(read[0])){
						printc('-');
						prints(dir->d_name);
						println();
					}
      		
    		}
			
    	closedir(d);
 			}
			prints("Enter Player name: ");
			inputs(&enemyName,20);
			char quit = '!';

			printc(enemyName[0]);
			println();

			if (enemyName[0]==quit){
				//prints(enemyName);
				println();
				quitFind=1;
			}
			else{
				
				int done = findShip(enemyName);

			if(done==0){
				prints("Thats not a valid option!\n");
				}

			}
			
			}while(quitFind==0);

		}


		if(userOption[0]=='3'){
			userActive = 0;
			exit(0);
		}


	}while(userActive);


	

   
}
