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

char getInstructSide(char side){
    switch(side){
        case 'W':
            return 'D';
        case 'B':
            return 'F';
        case 'R':
            return 'R';
        case 'Y':
            return 'T';
        case 'G':
            return 'B';
        case 'O':
            return 'L';
        default:
            return '!';
    }
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

int whiteCross(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace){
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
    return instructPlace;
}

void whiteCorners(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace){
	
}

int F2L(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace){
    while(cube[1][1][0] != cube[1][1][2] || cube[2][1][0] != cube[2][1][2] || cube[4][1][0] != cube[4][1][2] || cube[5][1][0] != cube[5][1][2]){
        int numYellow = 0;
        for(int i = 1; i < 6; i++){
            if(i != 3){
                if(cube[i][0][1] == 'Y'){
                    numYellow++;
                }
            } else {
                if(cube[i][0][1] == 'Y'){
                    numYellow++;
                }
                if(cube[i][1][0] == 'Y'){
                    numYellow++;
                }
                if(cube[i][1][2] == 'Y'){
                    numYellow++;
                }
                if(cube[i][2][1] == 'Y'){
                    numYellow++;
                }
            }
        }
        if(numYellow == 4){
            for(int i = 1; i <= 2; i++){
                int checkSide = i * i;
                if(cube[checkSide][1][0] != getCharSide(checkSide)){
                    int LRTB[4];
                    getNeighbors(4, LRTB, checkSide);
                    int left = LRTB[0];
                    pullDownLeft(3, cube, getCharSide(checkSide), getCharSide(left));
                    for(int i = 0; i < 8; i++){
                        if(i % 2 = 0){
                            if(i <= 2){
                                instructions[instructPlace] = 'T';
                                instructPlace++;
                            } else {
                                instructions[instructPlace] = 'T';
                                instructPlace++;
                                instructions[instructPlace] = ''';
                                instructPlace++;
                            }
                        } else {
                            if(i <= 3){
                                instructions[instructPlace] = getInstructSide(left);
                                instructPlace++;
                                if(i == 1){
                                    instructions[instructPlace] = ''';
                                    instructPlace++;
                                }
                            } else {
                                instructions[instructPlace] = getInstructSide(checkSide);
                                instructPlace++;
                                if(i == 7){
                                    instructions[instructPlace] = ''';
                                    instructPlace++;
                                }
                            }
                        }
                    }
                    break;
                } else if(cube[checkSide][1][2] != getCharSide(checkSide)){
                    int LRTB[4];
                    getNeighbors(4, LRTB, checkSide);
                    int right = LRTB[1];
                    pullDownRight(3, cube, side, top);
                    for(int i = 0; i < 8; i++){
                        if(i % 2 = 0){
                            if(i <= 2){
                                instructions[instructPlace] = 'T';
                                instructPlace++;
                            } else {
                                instructions[instructPlace] = 'T';
                                instructPlace++;
                                instructiions[instructPlace] = ''';
                                instructPlace++;
                            }
                        } else {
                            if(i <= 3){
                                instructions[instructPlace] = getInstructSide(right);
                                instructPlace++;
                                if(i == 1){
                                    instructions[instructPlace] = ''';
                                    instructPlace++;
                                }
                            } else {
                                instructions[instructPlace] = getInstructSide(checkSide);
                                instructPlace++;
                                if(i == 7){
                                    instructions[instructPlace] = ''';
                                    instructPlace++;
                                }
                            }
                        }
                    } 
                    break; 
                }
            }
        }
        int side = 1;
        for(int i = 1; i < 6; i++){
            if(i != 3){
                if(cube[i][0][1] == cube[i][1][1]){
                    break;
                }
            }
            side++;
        }
        if(side > 5){
            turn(3, cube, 'Y');
            instructions[instructPlace] = 'T';
            instructPlace++;
        } else {
            int yelloGuide[4];
            getNeighbors(4, yellowGuide, 3);
            char top;
            if(yellowGuide[0] == side){
                top = cube[3][1][0];
            } else if(yellowGuide[1] == side){
                top = cube[3][1][2];
            } else if(yellowGuide[2] == side){
                top = cube[3][0][1];
            } else if(yellowGuide[3] == side){
                top = cube[3][2][1]; 
            }
            if(top == 'Y'){
                continue;
            } else {
                int LRTB[4];
                getNeighbors(4, LRTB, side);
                if(getCharSide(LRTB[0]) == top){
                    pullDownLeft(3, cube, getCharSide(side), top);
                    for(int i = 0; i < 8; i++){
                        if(i % 2 = 0){
                            if(i <= 2){
                                instructions[instructPlace] = 'T';
                                instructPlace++;
                            } else {
                                instructions[instructPlace] = 'T';
                                instructPlace++;
                                instructions[instructPlace] = ''';
                                instructPlace++;
                            }
                        } else {
                            if(i <= 3){
                                instructions[instructPlace] = getInstructSide(top);
                                instructPlace++;
                                if(i == 1){
                                    instructions[instructPlace] = ''';
                                    instructPlace++;
                                }
                            } else {
                                instructions[instructPlace] = getInstructSide(side);
                                instructPlace++;
                                if(i == 7){
                                    instructions[instructPlace] = ''';
                                    instructPlace++;
                                }
                            }
                        }
                    }
                } else if(getCharSide(LRTB[1]) == top){
                    pullDownRight(3, cube, side, top);
                    for(int i = 0; i < 8; i++){
                        if(i % 2 = 0){
                            if(i <= 2){
                                instructions[instructPlace] = 'T';
                                instructPlace++;
                            } else {
                                instructions[instructPlace] = 'T';
                                instructPlace++;
                                instructions[instructPlace] = ''';
                                instructPlace++;
                            }
                        } else {
                            if(i <= 3){
                                instructions[instructPlace] = getInstructSide(top);
                                instructPlace++;
                                if(i == 1){
                                    instructions[instructPlace] = ''';
                                    instructPlace++;
                                }
                            } else {
                                instructions[instructPlace] = getInstructSide(side);
                                instructPlace++;
                                if(i == 7){
                                    instructions[instructPlace] = ''';
                                    instructPlace++;
                                }
                            }
                        }
                    } 
                }
            }
        }
    }
    return instructPlace;
}

void pullDownLeft(int size, char cube[][size][size], char side, char left){
    inverse(size, cube, 'Y');
    inverse(size, cube, left);
    inverse(size, cube, 'Y');
    turn(size, cube, left);  
    turn(size, cube, 'Y');
    turn(size, cube, side);
    turn(size, cube, 'Y');
    inverse(size, cube, side);  
}

void pullDownRight(int size, char cube[][size][size], char side, char right){
    turn(size, cube, 'Y');
    turn(size, cube, right);
    turn(size, cube, 'Y');
    inverse(size, cube, right);
    inverse(size, cube, 'Y');
    inverse(size, cube, side);
    inverse(size, cube, 'Y');
    turn(size, cube, side);
}

void yellowFace(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace){
    int numYellow = 0;
    if(cube[i][0][1] == 'Y'){
        numYellow++;
    } if(cube[i][1][0] == 'Y'){
        numYellow++;
    } if(cube[i][1][2] == 'Y'){
        numYellow++;
    } if(cube[i][2][1] == 'Y'){
        numYellow++;
    }
    if(numYellow < 4){
        if(numYellow = 0){
            instructPlace = yellowCrossMaker(3, cube, size2, instructions, instructPlace);
        } 
        if(cube[3][0][1] == 'Y' && cube[3][2][1] == 'Y'){
            instructPlace = yellowCrossMaker(3, cube, size2, instructions, instructPlace);
            instructPlace = yellowCrossMaker(3, cube, size2, instructions, instructPlace); 
        } else if (cube[3][1][0] == 'Y' && cube[3][1][2] == 'Y'){
            turn(3, cube, 'Y');
            instructions[instructPlace] = 'T';
            instructPlace++;
            instructPlace = yellowCrossMaker(3, cube, size2, instructions, instructPlace);
            instructPlace = yellowCrossMaker(3, cube, size2, instructions, instructPlace);
        } else {
            if (cube[3][1][0] == 'Y' && cube[3][2][1] == 'Y'){
                turn(3, cube, 'Y');
                instructions[instructPlace] = 'T';
                instructPlace++;
            } else if (cube[3][2][1] == 'Y' && cube[3][1][2] == 'Y'){
                turnOneEighty(3, cube, 'Y');
                instructions[instructPlace] = 'T';
                instructPlace++;
                instructions[instructPlace] = '2';
                instructPlace++;
            } else if (cube[3][1][2] == 'Y' && cube[3][0][1] == 'Y'){
                inverse(3, cube, 'Y')
                instructions[instructPlace] = 'T';
                instructPlace++;
                instructions[instructPlace] = ''';
                instructPlace++;
            }
            instructPlace = yellowCrossMaker(3, cube, size2, instructions, instructPlace);
        }
    }
    return instructPlace;
}

int yellowCrossMaker(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace){
    turn(3, cube, 'B');
    turn(3, cube, 'Y');
    turn(3, cube, 'R');
    inverse(3, cube, 'Y');
    inverse(3, cube, 'R');
    inverse(3, cube, 'B');
    instructions[instructPlace] = 'F';
    instructPlace++;
    instructions[instructPlace] = 'T';
    instructPlace++;
    instructions[instructPlace] = 'R';
    instructPlace++;
    instructions[instructPlace] = 'T';
    instructPlace++;
    instructions[instructPlace] = ''';
    instructPlace++;
    instructions[instructPlace] = 'R';
    instructPlace++;
    instructions[instructPlace] = ''';
    instructPlace++;
    instructions[instructPlace] = 'F';
    instructPlace++;
    instructions[instructPlace] = ''';
    instructPlace++;
}

void OOL(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace){
	
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
