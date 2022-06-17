/**
 * 
 * 
 * @param argc the number of arguments passed to the program
 * @param argv an array of strings, each string is one of the arguments you typed at the command line.
 */
/*
 * fuzzsudoku - generate n random using creator and solve them 
 * 
 * usage: fuzzsudoku [n] where n is the number of boards to be solved
 * 
 * CS50, Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/grid.h"


/***************** Local Functions *********************/
static void parse_inputs( int argsCount, const char *agrs[], int *n);


/***************** main *********************/
int main( const int argc, const char *argv[]){
    int n = 0; 
    parse_inputs(argc-1, argv, &n);

    printf("Generating %d sudoku boards... \n", n);
    for(int i = 0; i<n; i++){
        // creator code
        grid_t *grid = grid_new(9);
        grid_t *copy = grid_new(9); // create a copy of the generated grid to later compare to solver solution 
        grid_solve(grid);
        grid_copy(grid, copy);
        grid_random_clue(grid); // delete random keys
        
        int solved = grid_solve(grid);
        if(!grid_cmp(grid, copy)){
            fprintf(stderr,"Error: solver solution %d does not match creator's \n", i);
        }
        if (solved != 1){
            printf("Failed test %d, obtained %d solutions but expected 1\n", i, solved);
        }else{
            printf("Passed test %d\n", i);
        }
    }
    
    return 0;
}

/**
 * It takes in the number of arguments and the arguments themselves, and then parses the arguments to
 * get the number of iterations to run
 * 
 * @param argsCount the number of arguments passed to the program
 * @param args The array of arguments passed to the program.
 * @param n the number of processes to create
 */
static void parse_inputs( int argsCount, const char *args[], int *n){
    if ( argsCount != 1){
        fprintf(stderr,"Error invalid args, expected 1 got %d\n", argsCount-1);
        exit(1);
    }

    if(sscanf(args[1], "%d", n) != 1){
        fprintf(stderr,"please ender a number as your argument.\n");
        exit(2);
    }
}

