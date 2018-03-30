#include <stdlib.h>
#include <stdio.h>

int getIntSide(char side); 

char getCharSide(int side);

char getInstructSide(char side);

void getNeighbors(int size, int LRTB[size], int side);

void copySide(int size, char cube[][size][size], int side, char newSide[][size]);

void printCube(int size, char cube[][size][size]);

void turnFace(int size, char cube[][size][size], char side);

int turn(int size, char cube[][size][size], char side, int size2, char instructions[size2], int instructPlace);

int inverse(int size, char cube[][size][size], char side, int size2, char instructions[size2], int instructPlace);

int turnOneEighty(int size, char cube[][size][size], char side, int size2, char instructions[size2], int instructPlacee);

int whiteCross(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

int whiteCorners(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

int whiteFaceMaker(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace, int right, char side);

int F2L(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

int pullDownLeft(int size, char cube[][size][size], char side, char left, int size2, char instructions[size2], int instructPlace);

int pullDownRight(int size, char cube[][size][size], char side, char right, int size2, char instructions[size2], int instructPlace);

int yellowFace(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

int yellowFaceMaker(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

int yellowCrossMaker(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

int finish(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

int switchCorners(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

int finishSide(int size, char cube[][size][size], int size2, char instructions[size2], int instructPlace);

void solve(int size, char cube[][size][size], int size2, char instructions[size2]);
