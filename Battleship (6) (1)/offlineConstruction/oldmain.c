//#include <stdio.h>
#include "include/game.h"

int main(void) {
	//write(STDOUT_FILENO,"\033[2J",4);
	char *name;
	char userOption[1];
	int userNameValid = 1;
	int userOptionValid = 1;
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

  return 0;
	
}