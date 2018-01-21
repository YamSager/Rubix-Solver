///An algorithm to produce a string of instructions, in standard notation, 
///to solve a rubix cube.
///Author: Sam Yager -sly4758@rit.edu

#include <stdlib.h>
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define SIZE 3

int getIntSide(char side){	
        if (side == 'W' || side == 'w')
                return 0;
        else if (side == 'B' || side == 'b')
                return 1;
        else if (side == 'R' || side == 'r')
                return 2;
        else if (side == 'Y' || side == 'y')
                return 3;
        else if (side == 'G' || side == 'g')
                return 4;
        else if (side == 'O' || side == 'o')
                return 5;
	else
		return 6;
}

char getCharSide(int side){
        if (side == 0)
                return 'W';
        else if (side == 1)
                return 'B';
        else if (side == 2)
                return 'R';
        else if (side == 3)
                return 'Y';
        else if (side == 4)
                return 'G';
        else if (side == 5)
                return 'O';
        else
                return 6;	
}

void getNeighbors(int size, int LRTB[size], int side){
	switch(side){
		case 0:
			LRTB[0] = 5;
			LRTB[1] = 2;
			LRTB[2] = 1;
			LRTB[3] = 4;
			break;
		case 3:
                	LRTB[0] = 5;
                	LRTB[1] = 2;
	                LRTB[2] = 4;
        	        LRTB[3] = 1;
			break;
       	 	case 1:
	                LRTB[0] = 5;
        	        LRTB[1] = 2;
                	LRTB[2] = 3;
               		LRTB[3] = 0;
			break;
        	case 4:
	                LRTB[0] = 2;
        	        LRTB[1] = 5;
	                LRTB[2] = 3;
                	LRTB[3] = 0;
			break;
        	case 2:
	                LRTB[0] = 1;
        	        LRTB[1] = 4;
	                LRTB[2] = 3;
                	LRTB[3] = 0;
			break;
        	case 5:
               		LRTB[0] = 4;
                	LRTB[1] = 1;
                	LRTB[2] = 3;
                	LRTB[3] = 0;
			break;
        	default:
			//something has gone awfully wrong
			printf("FRACK, GO BRACK!");
	}
}

void copySide(int size, char cube[][size][size], int side, char newSide[][size]){
	//printf("Copy Bro\n");
	for (int row = 0; row < size; row++){
		for (int col = 0; col < size; col++){
			//printf("%c!=%c\n", cube[side][row][col], newSide[row][col]);
			cube[side][row][col] = newSide[row][col];
			//printf("%c==%c\n", cube[side][row][col], newSide[row][col]);
		}
	}
}

//Prints all sides of te cube as if looking at it head on with yellow at the top and white on the bottom (yellow side is green top, white side is blue top) 
void printCube(int size, char cube[][size][size]){
	for(int side = 0; side < 6; side++){
		char value = getCharSide(side);
		printf("Side: %c\n", value);
		for(int row = 0; row < size; row++){
	                for(int col = 0; col < size; col++){
				//If statements exist only for coloration of the cube representation (mostly for ease of testing purposes)
				if (cube[side][row][col] == 'W'){
					printf(ANSI_COLOR_RESET);
				} else if (cube[side][row][col] == 'B'){
					printf(ANSI_COLOR_BLUE);
				} else if (cube[side][row][col] == 'G'){
					printf(ANSI_COLOR_GREEN);
				} else if (cube[side][row][col] == 'R'){
					printf(ANSI_COLOR_RED);
				} else if (cube[side][row][col] == 'Y'){
					printf(ANSI_COLOR_YELLOW);
				} else if (cube[side][row][col] == 'O'){
					printf(ANSI_COLOR_MAGENTA);
				}
				printf("%c", cube[side][row][col]);
				printf(ANSI_COLOR_RESET);
			}
			printf("\n");
		}
	}
	printf("\n");
}

// Turns the cube clockwise on the side specified
// W = 0, B = 1, R = 2, Y = 3, G = 4, O = 5
void turn(int size, char cube[][size][size], char side){
	int intSide = getIntSide(side);
	char newSide[size][size];
	int LRTB[4];
	char right[3];
	char left[3];
	char top[3];
	char bot[3];
	for (int row = 0; row < size; row++){
       		for (int col = 0; col < size; col++){
               		newSide[col][row] = '*';
               	}
       	}
	if (intSide <= 5){
		for (int row = 0; row < size; row++){
			for (int col = 0; col < size; col++){
				//printf("%c!=%c\n", cube[intSide][row][col], newSide[col][2 - row]);
				newSide[col][2 - row] = cube[intSide][row][col];
				//printf("%c!=%c\n", cube[intSide][row][col], newSide[col][2 - col]);
			}
		}
		copySide(size, cube, intSide, newSide);
		getNeighbors(4, LRTB, intSide);
		for(int i = 0; i < 4; i++){//problem may be in for loop
			for(int j = 0; j < 3; j++){
				if (intSide == 0){//should not have any problem
					if (i == 0){
						left[j] = cube[LRTB[i]][2][j];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][2][j];
					} else if (i == 2){	
						top[j] = cube[LRTB[i]][2][j];
					} else if (i == 3){
						bot[j] = cube[LRTB[i]][2][j];
					}
				} else if (intSide == 1){
					if (i == 0){
						left[j] = cube[LRTB[i]][j][2];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][j][0];
					} else if (i == 2){	
						top[j] = cube[LRTB[i]][2][j];
					} else if (i == 3){
						bot[j] = cube[LRTB[i]][0][j];
					}
				} else if (intSide == 2){
					if (i == 0){
						left[j] = cube[LRTB[i]][j][2];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][j][0];
					} else if (i == 2){	
						top[j] = cube[LRTB[i]][j][2];
					} else if (i == 3){
						bot[j] = cube[LRTB[i]][j][2];
					}
				} else if (intSide == 3) {
					if (i == 0){
						left[j] = cube[LRTB[i]][0][j];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][0][j];
					} else if (i == 2){	
						top[j] = cube[LRTB[i]][0][j];
					} else if (i == 3){
						bot[j] = cube[LRTB[i]][0][j];
					}
				} else if (intSide == 4) {
					if (i == 0){
						left[j] = cube[LRTB[i]][j][2];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][j][0];
					} else if (i == 2){	
						top[j] = cube[LRTB[i]][0][j];
					} else if (i == 3){
						bot[j] = cube[LRTB[i]][2][j];
					}
				} else if (intSide == 5) {
					if (i == 0){
						left[j] = cube[LRTB[i]][j][2];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][j][0];
					} else if (i == 2){	
						top[j] = cube[LRTB[i]][j][0];
					} else if (i == 3){
						bot[j] = cube[LRTB[i]][j][0];
					}
				}
			}
		}
                for(int j = 0; j < 3; j++){
			if(intSide == 0){
                               	cube[LRTB[2]][2][j] = left[j];
                                cube[LRTB[3]][2][j] = right[j];
                               	cube[LRTB[1]][2][j] = top[j];
                                cube[LRTB[0]][2][j] = bot[j];
			} else if (intSide == 3){
                           	cube[LRTB[2]][0][j] = left[j];
                                cube[LRTB[3]][0][j] = right[j];
                               	cube[LRTB[1]][0][j] = top[j];
                                cube[LRTB[0]][0][j] = bot[j];
                        } else if (intSide == 1){	
                               	cube[LRTB[2]][2][j] = left[2 - j];
                               	cube[LRTB[3]][0][j] = right[2 - j];
                                cube[LRTB[1]][j][0] = top[j];
                                cube[LRTB[0]][j][2] = bot[j];
			} else if (intSide == 2){
                              	cube[LRTB[2]][j][2] = left[j];
                               	cube[LRTB[3]][j][2] = right[2 - j];
                     	        cube[LRTB[1]][j][0] = top[2 - j];
                       	        cube[LRTB[0]][j][2] = bot[j];
			} else if (intSide == 4){
                              	cube[LRTB[2]][0][j] = left[j];
                               	cube[LRTB[3]][2][j] = right[j];
                                cube[LRTB[1]][j][0] = top[2 - j];
                                cube[LRTB[0]][j][2] = bot[2 - j];
			} else if (intSide == 5){
                               	cube[LRTB[2]][j][0] = left[2 - j];
                               	cube[LRTB[3]][j][0] = right[j];
                                cube[LRTB[1]][j][0] = top[j];
                        	cube[LRTB[0]][j][2] = bot[2 - j];
			}
                }
	}	
}

void inverse(int size, char cube[][size][size], char side){
	turn(size, cube, side);
	turn(size, cube, side);
	turn(size, cube, side);
}

void turnOneEighty(int size, char cube[][size][size], char side){
	turn(size, cube, side);	
	turn(size, cube, side);
}

int isSolved(int size, char cube[][size][size]){
	char charSide;
	for(int side = 0; side < 6; side++){
		charSide = getCharSide(side);
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(cube[side][i][j] != charSide)
					return 0;
			}
		}
	}
	return 1;
}

char* solve(int size, char config[][size][size], char instructions[]){
	if(isSolved(SIZE, config)){
		return instructions;
	} else {
		return NULL;	
	}
}

void whiteCross(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace){
	char steps[50];
	int stepPlace = 0;
	for(int s = 0; s < 50; s++){
		steps[s] = '\0';	
	}		
	while(cube[3][0][1] != 'W' && cube[3][1][0] != 'W' && cube[3][1][3] != 'W' && cube[3][2][1] != 'W'){
		for(int i = 0; i < 6; i++){
			if(i != 3){
				if(cube[i][1][0] == 'W'){
					if(i == 1) {
						while(cube[3][1][0] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						inverse(3, cube, 'O');
						steps[stepPlace] = 'L';
						stepPlace++;
						steps[stepPlace] = 'i';
						stepPlace++;
					} else if(i == 2) {
						while(cube[3][2][1] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						inverse(3, cube, 'B');
						steps[stepPlace] = 'F';
						stepPlace++;
						steps[stepPlace] = 'i';
						stepPlace++;
					} else if(i == 4) {
						while(cube[3][1][2] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						inverse(3, cube, 'R');
						steps[stepPlace] = 'R';
						stepPlace++;
						steps[stepPlace] = 'i';
						stepPlace++;
					} else if(i == 5) {
						while(cube[3][0][1] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						inverse(3, cube, 'G');
						steps[stepPlace] = 'B';
						stepPlace++;
						steps[stepPlace] = 'i';
						stepPlace++;
					} else {
						while(cube[3][0][1] == 'W'){
                                                        turn(3, cube, 'Y');
                                                        steps[stepPlace] = 'T';
                                                        stepPlace++;
                                                }
                                                turnOneEighty(3, cube, 'O');
                                                steps[stepPlace] = 'L';
                                                stepPlace++;
                                                steps[stepPlace] = '2';
                                                stepPlace++;
					}
				}
				if(cube[i][1][2] == 'W'){
					if(i == 1) {
						while(cube[3][1][2] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						turn(3, cube, 'R');
						steps[stepPlace] = 'R';
						stepPlace++;
					} else if(i == 2) {
						while(cube[3][0][1] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						turn(3, cube, 'G');
						steps[stepPlace] = 'B';
						stepPlace++;
					} else if(i == 4) {
						while(cube[3][1][0] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						turn(3, cube, 'O');
						steps[stepPlace] = 'L';
						stepPlace++;
					} else if(i == 5) {
						while(cube[3][2][1] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						turn(3, cube, 'B');
						steps[stepPlace] = 'F';
						stepPlace++;
					} else {
						while(cube[3][1][2] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						turnOneEighty(3, cube, 'R');
						steps[stepPlace] = 'R';
						stepPlace++;
                                                steps[stepPlace] = '2';
                                                stepPlace++;	
					} 
				}
 				if(cube[i][0][1] == 'W'){
					if(i == 1){
						turn(3, cube, 'B');
						steps[stepPlace] = 'F';
						stepPlace++;
						inverse(3, cube, 'Y');
                                                steps[stepPlace] = 'T';
                                                stepPlace++;
                                                steps[stepPlace] = 'i';
                                                stepPlace++;
						turn(3, cube, 'R');						
                                                steps[stepPlace] = 'R';
                                                stepPlace++;
					} else if(i == 2){
						turn(3, cube, 'R');
						steps[stepPlace] = 'R';
						stepPlace++;
						inverse(3, cube, 'Y');
                                                steps[stepPlace] = 'T';
                                                stepPlace++;
                                                steps[stepPlace] = 'i';
                                                stepPlace++;
						turn(3, cube, 'G');						
                                                steps[stepPlace] = 'B';
                                                stepPlace++;
					} else if(i == 4){
						turn(3, cube, 'G');
						steps[stepPlace] = 'B';
						stepPlace++;
						inverse(3, cube, 'Y');
                                                steps[stepPlace] = 'T';
                                                stepPlace++;
                                                steps[stepPlace] = 'i';
                                                stepPlace++;
						turn(3, cube, 'O');						
                                                steps[stepPlace] = 'L';
                                                stepPlace++;
					} else if(i == 5){
						turn(3, cube, 'O');
						steps[stepPlace] = 'L';
						stepPlace++;
						inverse(3, cube, 'Y');
                                                steps[stepPlace] = 'T';
                                                stepPlace++;
                                                steps[stepPlace] = 'i';
                                                stepPlace++;
						turn(3, cube, 'B');						
                                                steps[stepPlace] = 'F';
                                                stepPlace++;
					} else { 
						while(cube[3][2][1] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;
						}
						turnOneEighty(3, cube, 'B');
						steps[stepPlace] = 'F';
						stepPlace++;
						steps[stepPlace] = '2';
						stepPlace++;
					}
				}
				if(cube[i][2][1] == 'W'){
					if(i == 1){
						while(cube[3][2][1] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;	
						}
						turn(3, cube, 'B');
						steps[stepPlace] = 'F';
						stepPlace++;	
						turn(3, cube, 'Y');
						steps[stepPlace] = 'T';
						stepPlace++;
						inverse(3, cube, 'O');
						steps[stepPlace] = 'L';
						stepPlace++;
						steps[stepPlace] = 'i';
						stepPlace++;
					}
					if(i == 2){
						while(cube[3][1][2] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;	
						}
						turn(3, cube, 'R');
						steps[stepPlace] = 'R';
						stepPlace++;	
						turn(3, cube, 'Y');
						steps[stepPlace] = 'T';
						stepPlace++;
						inverse(3, cube, 'B');
						steps[stepPlace] = 'F';
						stepPlace++;
						steps[stepPlace] = 'i';
						stepPlace++;
					}
					if(i == 4){
						while(cube[3][0][1] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;	
						}
						turn(3, cube, 'G');
						steps[stepPlace] = 'B';
						stepPlace++;	
						turn(3, cube, 'Y');
						steps[stepPlace] = 'T';
						stepPlace++;
						inverse(3, cube, 'R');
						steps[stepPlace] = 'R';
						stepPlace++;
						steps[stepPlace] = 'i';
						stepPlace++;
					}
					if(i == 5){
						while(cube[3][1][0] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;	
						}
						turn(3, cube, 'O');
						steps[stepPlace] = 'L';
						stepPlace++;	
						turn(3, cube, 'Y');
						steps[stepPlace] = 'T';
						stepPlace++;
						inverse(3, cube, 'G');
						steps[stepPlace] = 'B';
						stepPlace++;
						steps[stepPlace] = 'i';
						stepPlace++;
					}
					else{
						while(cube[3][0][1] == 'W'){
							turn(3, cube, 'Y');
							steps[stepPlace] = 'T';
							stepPlace++;	
						}
						turnOneEighty(3, cube, 'G');
						steps[stepPlace] = 'B';
						stepPlace++;
						steps[stepPlace] = '2';
						stepPlace++;	
					}
				}
			}		
		}
	}
	for(int j = 0; j < 6; j++){
		if(j == 1){
			while(cube[j][0][1] != 'B'){ // || cube[3][2][1] != 'W'){
				turn(3, cube, 'Y');
				steps[stepPlace] = 'T';
				stepPlace++;	
			}
			turnOneEighty(3, cube, 'B');
			steps[stepPlace] = 'F';
			stepPlace++;
			steps[stepPlace] = '2';
			stepPlace++;	
		} else if(j == 2){
			while(cube[j][0][1] != 'R'){ // || cube[3][1][2] != 'W'){
				turn(3, cube, 'Y');
				steps[stepPlace] = 'T';
				stepPlace++;	
			}
			turnOneEighty(3, cube, 'R');
			steps[stepPlace] = 'R';
			stepPlace++;
			steps[stepPlace] = '2';
			stepPlace++;	
		} else if(j == 4){
			while(cube[j][0][1] != 'G'){ // || cube[3][0][1] != 'W'){
				turn(3, cube, 'Y');
				steps[stepPlace] = 'T';
				stepPlace++;	
			}
			turnOneEighty(3, cube, 'G');
			steps[stepPlace] = 'B';
			stepPlace++;
			steps[stepPlace] = '2';
			stepPlace++;	
		} else if(j == 5){
			while(cube[j][0][1] != 'O'){ // || cube[3][1][0] != 'W'){
				turn(3, cube, 'Y');
				steps[stepPlace] = 'T';
				stepPlace++;	
			}
			turnOneEighty(3, cube, 'O');
			steps[stepPlace] = 'L';
			stepPlace++;
			steps[stepPlace] = '2';
			stepPlace++;	
		}
	}
	for(int ele = 0; ele < stepPlace; ele++){
		instructions[instructPlace] = steps[ele];
		instructPlace++;
	}
}

void whiteCorners(){
	
}

int main(){
	char cube[6][3][3];
	char instructions[1000];
	for(int i = 0; i < 1000; i++){
		instructions[i] = '\0';
	}
	for(int side = 0; side < 6; side++){
		char value = getCharSide(side);
		for(int row = 0; row < SIZE; row++){
			for(int col = 0; col < SIZE; col++){
				cube[side][row][col] = value;
			}
		} 
	}
	if(isSolved(SIZE, cube)){
		printf("Solved Works MotherFucker!\n");
	}
	//printCube(SIZE, cube);
	//turn(SIZE, cube, 'Y');
	printCube(SIZE, cube);
	printf("%d\n", isSolved(SIZE, cube));
	//turn(SIZE, cube, 'Y');
	//printCube(SIZE, cube);
	//turn(SIZE, cube, 'W');
	//printCube(3, cube);
	//turn(3, cube, 'W');
	//printCube(3, cube);
	//turn(3, cube, 'R');
	//printCube(3, cube);
	//turn(3, cube, 'R');
	//printCube(3, cube);
	//turn(3, cube, 'O');
	//printCube(3, cube);
	//turn(3, cube, 'O');
	//printCube(3, cube);
	turn(3, cube, 'B');
	//printCube(3, cube);
	//turn(3, cube, 'B');
	//printCube(3, cube);
	//turn(3, cube, 'G');
	//printCube(3, cube);
	//turn(3, cube, 'G');
	printCube(SIZE, cube);
	whiteCross(3, cube, 1000, instructions, 0);
	printf("%s\n", instructions);
	printCube(3, cube);
	printf("%d\n", isSolved(SIZE, cube));
	return 0;
}
