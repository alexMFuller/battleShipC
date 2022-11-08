#include "../include/game.h"
#include <stdio.h>

int isValidGuess(int x, int y) {
		

		if (x>9||x<0||y>9||y<0) {
			prints("Invalid guess. Outside of grid.\n");
			return 0;
		}
		else if(gameMap[y][x]=='X'||gameMap[y][x]=='O') {
			prints("Invalid guess. Location already guessed.\n");
			return 0;
		}
		
		return 1;
}

void display() {
  // your code here
		prints(" ");
		for(int i=0; i<10; i++) {
			prints(" ");
			printc((i+'0'));
		}
		println();
	  for(int i=0; i<10; i++) {
    // inner loop for column
			printc((i+'0'));
			prints(" ");

    for(int j=0; j<10; j++) {
			if (j==0){
				//printc((i+'0'));
			}
			printc((gameMap[i][j]));
			
      printc(' ');
    }
     println();// new line
  }


}

void setMap(){
	for(int i=0; i<10; i++) {
    // inner loop for column
    for(int j=0; j<10; j++) {

			gameMap[i][j] = '.';
			
    }
     
  }
}

int isValidShip(int bbx,int bby,int ssx,int ssy){


	if (!(bbx == ssx || bby == ssy)) {
			prints("Invalid coordinates. Bow & stern must have the same value for either x or y.\n");
			return 0;
		}
		else if (bbx>9||bby>9||ssx>9||ssy>9||bbx<0||bby<0||ssx<0||ssy<0) {
			prints("Invalid coordinates. Bow & stern must be within 0-9.\n");
			return 0;
		}
		else if (bbx == ssx) {
			if (abs(bby-ssy)!=3) {
				prints("Invalid coordinates. Bow & stern must have a total difference of 3 to make a vaild ship.\n");
				return 0;
			}
		}
		else if (bby == ssy) {
			if (abs(bbx-ssx)!=3) {
				prints("Invalid coordinates. Bow & stern must have a total difference of 3 to make a vaild ship.\n");
				return 0;
			}
		}

return 1;
}

int hideShip(char* user){
	write(STDOUT_FILENO,"\033[2J",4);
	//char path[] = "playerFiles/";
	//char* filepath = strncat(path, user, 20);
	//char* newLine = "\n";
	do {
		
		prints("Enter x coordinate for the bow of your ship: ");
		inputInt(bx);
		prints("Enter y coordinate for the bow of your ship: ");
		inputInt(by);
		prints("Enter x coordinate for the stern of your ship: ");
		inputInt(sx);
		prints("Enter y coordinate for the stern of your ship: ");
		inputInt(sy);
		
		//printf("in loop: %lu\n",  ); 
		
	} while(isValidShip(atoi(bx),atoi(by),atoi(sx),atoi(sy))==0);
	
	
	bowCords[0]= atoi(bx);
	bowCords[1]= atoi(by);

	sternCords[0]= atoi(sx);
	sternCords[1]= atoi(sy);
	

	
	if (atoi(sx)>atoi(bx)) {
		innerSternCords[0] = atoi(sx)-1;
		
		innerSternCords[1] = atoi(sy);

		innerBowCords[0] = atoi(bx)+1;
		
		innerBowCords[1] = atoi(by);

	}
	else if(atoi(bx)>atoi(sx)) {
		innerSternCords[0] = atoi(sx)+1;
		
		innerSternCords[1] = atoi(sy);

		innerBowCords[0] = atoi(bx)-1;
		
		innerBowCords[1] = atoi(by);

	}
	else if (atoi(sy)>atoi(by)) {
		innerSternCords[0] = atoi(sx);
		
		innerSternCords[1] = atoi(sy)-1;

		innerBowCords[0] = atoi(bx);
		
		innerBowCords[1] = atoi(by)+1;
	}
	else{
		innerSternCords[0] = atoi(sx);
		
		innerSternCords[1] = atoi(sy)+1;

		innerBowCords[0] = atoi(bx);
		
		innerBowCords[1] = atoi(by)-1;
	}
	

	writeFile(user, bowCords, innerBowCords, innerSternCords,sternCords);


	return 1;
}

int findShip(char* user){
	
	char** dest;
	int read = readFile(user,&dest);
	if (read==0){
		return 0;
	}

	write(STDOUT_FILENO,"\033[2J",4);
	
	int i=0;
	int player2Win =0;

	setMap();
	
	int numHits = 0;

	while(i<8){

		display();
		prints("Please enter an X coordinate: ");
		inputInt(userX);
		prints("Please enter an Y coordinate: ");
		inputInt(userY);
		//printf("%d\n",atoi(userX));
		//printf("%s\n",(userY));
		if (isValidGuess(atoi(userX),atoi(userY))){
			int gotHit = 0;
			
			for(int i = 0;i<4;i++){
				if(dest[i][0]==userX[0]&&dest[i][2]==userY[0]){
					gotHit=1;
					gameMap[atoi(userX)][atoi(userY)] = 'X';
					numHits++;
				}
				
			}
			if (!gotHit){
				gameMap[atoi(userX)][atoi(userY)] = 'O';
			}

			if (numHits>=4){
				player2Win = 1;
				i=8;
			}

			i++;
		}

	}
	
	if (player2Win){
		prints("Player Two Wins!");
	}
	else{
		prints("Player Two loses...");
	}

	
	return 1;
}
