#include <stdio.h>
#include <stdlib.h>
#include "rubix.h"
#include <unistd.h>

void usage(){
    printf("Usage: solve -Wconfig -Bconfig -Gconfig -Rconfig -Oconfig -Yconfig\n");
}

int main(int argc, char **argv){
    char cube[6][3][3];
    int c;
    char instructions[1500];
    for(int i = 0; i < 1500; i++){
        instructions[i] = '\0';
    }
    while ((c = getopt (argc, argv, "W:B:Y:R:G:O:")) != -1){
        switch (c){
            case 'W':
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        cube[0][i][j] = optarg[3 * i + j] - 32;
                    }
                }                
                break;
            case 'B':
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        cube[1][i][j] = optarg[3 * i + j] - 32;
                    }
                }                
                break;
            case 'R':
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        cube[2][i][j] = optarg[3 * i + j] - 32;
                    }
                }                
                break;
            case 'G':
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        cube[4][i][j] = optarg[3 * i + j] - 32;
                    }
                }                
                break;
            case 'O':
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        cube[5][i][j] = optarg[3 * i + j] - 32;
                    }
                }                
                break;
            case 'Y':
                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        cube[3][i][j] = optarg[3 * i + j] - 32;
                    }
                }                
                break;
            default:
                printf("Input Error\n");
                usage();
                return EXIT_FAILURE;
        }    
    }
    int white = 0;
    int blue = 0;
    int yellow = 0;
    int red = 0;
    int green = 0;
    int orange = 0;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                switch(cube[i][j][k]){
                    case 'W':
                        white++;
                        break;
                    case 'R':
                        red++;
                        break;
                    case 'G':
                        green++;
                        break;
                    case 'B':
                        blue++;
                        break;
                    case 'Y':
                        yellow++;
                        break;
                    case 'O':    
                        orange++;
                        break;
                    default:
                        //printCube(3, cube);
                        printf("Read Error\n");
                        usage();
                        return EXIT_FAILURE;                  
                }
            }
        }                
    }
    if(white == 9){
        if(blue == 9){
            if(green == 9){
                if(yellow == 9){
                    if(red == 9){
                        if(orange == 9){
                            printf("Solving\n");
                            printCube(3, cube);
                            printf("WTF\n");
                            solve(3, cube, 2000, instructions);
                            printf("%s\n", instructions);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    printf("Invalid Config\n");
    usage();
    return EXIT_FAILURE;                   
}
