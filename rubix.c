/**
An algorithm to produce a string of instructions to solve a rubix cube.
Author: Sam Yager -sly4758@rit.edu
**/

#include <stdlib.h>
#include <stdio.h>

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
	if(side == 0){
		LRTB[0] = 5;
		LRTB[1] = 2;
		LRTB[2] = 1;
		LRTB[3] = 4;
	} else if(side == 3){
                LRTB[0] = 2;
                LRTB[1] = 5;
                LRTB[2] = 4;
                LRTB[3] = 1;
        } else if(side == 1){
                LRTB[0] = 5;
                LRTB[1] = 2;
                LRTB[2] = 3;
                LRTB[3] = 0;
        } else if(side == 4){
                LRTB[0] = 2;
                LRTB[1] = 5;
                LRTB[2] = 3;
                LRTB[3] = 0;
        } else if(side == 2){
                LRTB[0] = 1;
                LRTB[1] = 4;
                LRTB[2] = 3;
                LRTB[3] = 0;
        } else if(side == 5){
                LRTB[0] = 4;
                LRTB[1] = 1;
                LRTB[2] = 3;
                LRTB[3] = 0;
        } else 
		printf("FUCK, GO BACK!");
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
		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 3; j++){
				if (intSide == 0){
					if (i == 0){
						left[j] = cube[LRTB[i]][2][j];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][2][j];
					} else if (i == 2){	
						top[j] = cube[LRTB[i]][2][j];
					} else if (i == 3){
						bot[j] = cube[LRTB[i]][2][j];
					}
				} else if (intSide == 3){
					if (i == 0){
						left[j] = cube[LRTB[i]][0][j];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][0][j];
					} else if (i == 2){	
						top[j] = cube[LRTB[i]][0][j];
					} else if (i == 3){
						bot[j] = cube[LRTB[i]][0][j];
					}
				} else {
					if (i == 0){
						left[j] = cube[LRTB[i]][j][2];
					} else if (i == 1){
						right[j] = cube[LRTB[i]][j][0];
					} else if (i == 2){
						if (intSide == 1){	
							top[j] = cube[LRTB[i]][2][j];
						} else if (intSide == 2){
							top[j] = cube[LRTB[i]][j][2];
						} else if (intSide == 4){
							top[j] = cube[LRTB[i]][0][j];
						} else if (intSide == 5){
							top[j] = cube[LRTB[i]][j][0];
						}
					} else if (i == 3){
						if (intSide == 1){	
							bot[j] = cube[LRTB[i]][0][j];
						} else if (intSide == 2){
							bot[j] = cube[LRTB[i]][j][2];
						} else if (intSide == 4){
							bot[j] = cube[LRTB[i]][2][j];
						} else if (intSide == 5){
							bot[j] = cube[LRTB[i]][j][0];
						}
					}
				}
			}
		}
		for(int i = 0; i < 4; i++){
                        for(int j = 0; j < 3; j++){
                                if(intSide == 0){
					if (i == 0){
                                		cube[LRTB[2]][2][j] = left[j];
                                	} else if (i == 1){
                                        	cube[LRTB[3]][2][j] = right[j];
                      		        } else if (i == 2){
                                	        cube[LRTB[1]][2][j] = top[j];
                              		} else if (i == 3){
                                        	cube[LRTB[0]][2][j] = bot[j];
                                	}
				} else if (intSide == 3){
					if (i == 0){
                                		cube[LRTB[2]][0][j] = left[j];
                                	} else if (i == 1){
                                        	cube[LRTB[3]][0][j] = right[j];
                      		        } else if (i == 2){
                                	        cube[LRTB[1]][0][j] = top[j];
                              		} else if (i == 3){
                                        	cube[LRTB[0]][0][j] = bot[j];
                                	}				
				} else {
					if (i == 0){
						if (intSide == 1){
                                			cube[LRTB[2]][2][j] = left[j];
						} else if (intSide == 2){
                                			cube[LRTB[2]][j][2] = left[j];
						} else if (intSide == 4){
                                			cube[LRTB[2]][0][j] = left[j];
						} else if (intSide == 5){
                                			cube[LRTB[2]][j][0] = left[j];
						}
                                	} else if (i == 1){	
						if (intSide == 1){
                                			cube[LRTB[3]][0][j] = right[j];
						} else if (intSide == 2){
                                			cube[LRTB[3]][j][2] = right[j];
						} else if (intSide == 4){
                                			cube[LRTB[3]][2][j] = right[j];
						} else if (intSide == 5){
                                			cube[LRTB[3]][j][0] = right[j];
						}
                      		        } else if (i == 2){
                                	        cube[LRTB[1]][j][0] = top[j];
                              		} else if (i == 3){
                                        	cube[LRTB[0]][j][2] = bot[j];
                                	}
				}
                        }
                }
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

void printCube(int size, char cube[6][size][size]){
	for(int side = 0; side < 6; side++){
		char value = getCharSide(side);
		printf("Side: %c\n", value);
		for(int row = 0; row < size; row++){
	                for(int col = 0; col < size; col++){
				printf("%c", cube[side][row][col]);
			}
			printf("\n");
		}
	}
	printf("\n");
}

int main(){
	char cube[6][3][3];
	for(int side = 0; side < 6; side++){
		char value = getCharSide(side);
		for(int row = 0; row < 3; row++){
			for(int col = 0; col < 3; col++){
				cube[side][row][col] = value;
			}
		} 
	}
	printCube(3, cube);
	turn(3, cube, 'Y');
	//printCube(3, cube);
	turn(3, cube, 'Y');
	turn(3, cube, 'W');
	//printCube(3, cube);
	turn(3, cube, 'W');
	//printCube(3, cube);
	turn(3, cube, 'R');
	//printCube(3, cube);
	turn(3, cube, 'R');
	//printCube(3, cube);
	turn(3, cube, 'O');
	//printCube(3, cube);
	turn(3, cube, 'O');
	//printCube(3, cube);
	turn(3, cube, 'B');
	//printCube(3, cube);
	turn(3, cube, 'B');
	//printCube(3, cube);
	turn(3, cube, 'G');
	//printCube(3, cube);
	turn(3, cube, 'G');
	printCube(3, cube);
	return 0;
}
