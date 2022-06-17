/*
 * grid.c - CS50 'counter' module
 *
 * see grid.h for more information.
 *
 * CS50
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "tile.h"
#include "grid.h"
#include "memory.h"
#include "file.h"
#include "tile.h"
#include "bag.h"
#include "hashtable.h"
#include "counters.h"
#include "array_len.h"

void print(FILE *fp, void *item);

/**************** global types ****************/
typedef struct grid
{
    int N; // number of slots or bins in hashtable
    tile_t*** table; // head of the list of sets in hashtable
} grid_t;


/**************** grid_new() ****************/
/* see grid.h for description */
grid_t *grid_new(const int N){

    //start a random seed
    srand(time(NULL));
    grid_t *grid = malloc(sizeof(grid_t));
    
    //if error return null
    if (grid == NULL) return NULL;

    grid->N = N;
    grid->table = calloc(N, sizeof(tile_t**));

    //allocate memory for tiles
    for (int i = 0; i < N; i++){
        grid->table[i] = calloc(N, sizeof(tile_t*));
        for (int j = 0; j < N; j++){
            grid->table[i][j] = tile_new();
        }
    }

    return grid;
}

/**************** grid_delete() ****************/
/* see grid.h for description */
void grid_delete(grid_t *grid){
    int N = grid-> N;

    //loop through and delete tiles
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tile_delete(grid->table[i][j]);
        }
        free(grid->table[i]);
    }

    //free rest of struct
    free(grid->table);
    free(grid);
}

/**************** grid_print() ****************/
/* see grid.h for description */
void grid_print(grid_t *grid, bool play_mode){
    int N = grid -> N;

    // find out how many white spaces a number needs
    int length = snprintf(NULL, 0, "%d", N);

    // print the format for playing
    if (play_mode) {
        for (int i = 0; i < length; i++) {
            printf(" ");
        }
        printf(" |");
        for (int i = 0; i < N; i++) {
            printf("%*d ", length, i);
        }
        printf("\n");
        for (int i = 0; i < ((length+1) * N + length + 2); i++) {
            printf("-");
        }
        printf("\n");
    }

    //loop through tiles and print
    for (int i = 0; i < N; i++)
    {
        if (play_mode) {
            printf("%*d |", length, i);
        }

        for (int j = 0; j < N; j++)
        {
            tile_print(grid->table[i][j], length);
            printf(" ");
        }
        printf("\n");
    }
}

void grid_fprint(grid_t* grid, bool solved){
    FILE *fp;
    if (grid != NULL){
       
        if(solved){
            fp = fopen("solved.txt", "w");
            
        }else{
            fp = fopen("start.txt", "w");
        }

        for(int i = 0; i < grid->N; i++){
            for(int j = 0; j < grid->N; j ++){
                fprintf(fp, "%d ", tile_value(grid->table[i][j]));
            }
            fprintf(fp, "%s", "\n");
        }
    }

    fclose(fp);
}

/**************** grid_load() ****************/
/* see grid.h for description */
bool grid_load(grid_t *grid){
    int N = grid-> N;

    //prompt user
    printf("Enter your sudoku board:\n");

    //loop through and get feedback
    for (int i = 0; i < N; i++){

        //go line by line
        char *line = freadlinep(stdin);
        char *begining = line;
        for (int j = 0; j < N; j++){
            int val;
            int offset;

            //if theres an issue return false
            if (sscanf(line, "%d%n", &val, &offset) != 1){
                fprintf(stderr, "Invalid format of entered sudoku board\n");
                return false;
            }

            //otherwise increment your place in the line and set the tile value
            line += offset;
            if (val > 0){
                tile_set(grid->table[i][j], true, val);
            }
            else{
                tile_set(grid->table[i][j], false, 0);
            }
        }
        free(begining);
    }
    return true;
}

/**************** grid_load_string() ****************/
/* see grid.h for description */
bool grid_load_string(grid_t *grid, char* board)
{
    //set variables
    int N = grid->N;
    char *line = board;

    //loop through rows
    for (int i = 0; i < N; i++)
    {
        //loop through columns
        for (int j = 0; j < N; j++)
        {
            int val;
            int offset;

            //throw error if issue
            if (sscanf(line, "%d%n", &val, &offset) != 1)
            {
                fprintf(stderr, "Invalid format of entered sudoku board\n");
                return false;
            }

            //set tile otherwise and move location in string
            line += offset;
            if (val > 0)
            {
                tile_set(grid->table[i][j], true, val);
            }
            else
            {
                tile_set(grid->table[i][j], false, 0);
            }
        }
    }
    return true;
}

/**************** valid_digits() ****************/
/* see grid.h for description */
array_len_t *valid_digits(grid_t *grid, int i, int j){
    int N = grid->N;

    //get structs prepared
    counters_t *invalid = counters_new();
    array_len_t *valid = array_len_new(N);

    //add invalid digits to counter from row/col
    for (int k = 0; k < N; k++){
        counters_add(invalid, tile_value(grid->table[i][k]));
        counters_add(invalid, tile_value(grid->table[k][j]));
    }

    //get invalid digits from boxes
    int box_size = sqrt(N);
    int quadx = i - (i % box_size);
    for (int k = quadx; k < quadx+box_size; k++){
        int quady = j - (j % box_size);
        for (int r = quady; r < quady + box_size; r++)
        {
            counters_add(invalid, tile_value(grid->table[k][r]));
        }
    }

    //add all the not invalid digits to the array len
    for (int k = 1; k <= N; k++)
    {
        if (counters_get(invalid, k) == 0)
        {
            array_len_insert(valid, k);
        }
    }

    //clean and return
    counters_delete(invalid);
    return valid;
}

static bool grid_solve_helper(grid_t *grid, int i, int j, int* sol);

/**************** grid_solve() ****************/
/* see grid.h for description */
int grid_solve(grid_t *grid){
    int sol = 0;
    grid_solve_helper(grid, 0, 0, &sol);

    //if theres only one solution get that actual solution
    if (sol == 1){
        sol = 1;
        grid_solve_helper(grid, 0, 0, &sol);
        return 1;
    }

    return sol;
}

/**************** grid_solve_helper() ****************/
static bool grid_solve_helper(grid_t *grid, int i, int j, int* sol){
    int N = grid->N;

    //increment through the grid
    if (i >= N){
        if (j == N - 1){
            //increment number of solutions
            (*sol) += 1;
            //if there are multiple solutions return true because we're done
            if ((*sol) > 1) return true;
            else return false;
        }
        else{
            j++;
            i = 0;
        }
    }

    //if its a confirmed tile skip over it
    if (tile_status(grid->table[i][j]))
        return grid_solve_helper(grid, i + 1, j, sol);

    array_len_t *valid = valid_digits(grid, i, j);

    //if no valid digits backtrack to tile before
    int val = array_len_get(valid);
    if (val == 0){
        array_len_delete(valid);
        tile_set(grid->table[i][j], false, 0);
        return false;
    }

    tile_set(grid->table[i][j], false, val);

    //while there's no solution for the next tile
    //try out different values for this tile
    while(grid_solve_helper(grid, i+1, j, sol) == false){
        int val = array_len_get(valid);
        tile_set(grid->table[i][j], false, val);
        if (val == 0)
        {
            array_len_delete(valid);
            tile_set(grid->table[i][j], false, 0);
            return false;
        }
    }

    array_len_delete(valid);

    //return true if we get here because there is a solution
    return true;
}

// return the count of empty tiles in a grid
int grid_empty_cnt(grid_t *grid) 
{   
    if (grid == NULL) {
        return -1;
    }

    int cnt = 0;
    int N = grid -> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            if (tile_value(grid->table[i][j]) == 0) {
                cnt++;
            }
        }
    }
    return cnt;
}

// randomly set tiles to zero in a complete grid to produce a sudoku puzzle
void grid_random_clue(grid_t *grid) 
{
    if ((grid == NULL) || (grid_empty_cnt(grid) > 0)) {
        ;
    } else {
        int N = grid -> N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                tile_set(grid->table[i][j], true, tile_value(grid->table[i][j]));
            }
        }
        int total_cnt = N*N;
        int pos[total_cnt];
        for (int k = 0; k < total_cnt; k++) {
            pos[k] = k;
        }

        // randomly shuffle the position array
        // modified from https://stackoverflow.com/questions/6127503/shuffle-array-in-c
        srand(time(NULL));
        for (int i = 0; i < total_cnt - 1; i++) {
            int j = i + rand() / (RAND_MAX / (total_cnt - i) + 1);
            int temp = pos[j];
            pos[j] = pos[i];
            pos[i] = temp;
        }

        int k = 0;
        grid_t *grid_temp = grid_new(N); // a backup grid to store the current grid
        while (k < total_cnt) {
            int i = (int) pos[k]/N;
            int j = pos[k] % N;

            // copy the current grid to the backup grid
            grid_copy(grid, grid_temp);
            // set a randomly selected tile to 0
            tile_set(grid_temp->table[i][j], false, 0);
            int solutions_cnt = grid_solve(grid_temp);
            if (solutions_cnt == 1) {
                // if unique solution, set the tile to 0 in the original grid
                tile_set(grid->table[i][j], false, 0);
            };
            k++;
        }
        grid_delete(grid_temp);
    }
}

// copy the contents of grid1 to grid2
void grid_copy(grid_t *grid1, grid_t *grid2) {
    if ((grid1 != NULL) && (grid2 != NULL)) {
        int N1 = grid1->N;
        int N2 = grid2->N;
        //make sure same dimensions
        if (N1 == N2) {
            //copy over each tiles value
            for (int i = 0; i < N1; i++) {
                for (int j = 0; j < N1; j++) {
                    tile_set(grid2->table[i][j], 
                        tile_status(grid1->table[i][j]), 
                        tile_value(grid1->table[i][j]));
                }
            }
        }
    }
}

// set a given tile in a grid
void grid_set_tile(grid_t *grid, int i, int j, bool confirmed, int value)
{
    if (grid != NULL) {
        int N = grid->N;
        if ((i >= 0) && (i < N) && (j >= 0) && (j < N)) {
            tile_set(grid->table[i][j], confirmed, value);
        }
    }
}

// return the value of a given tile in a grid
int grid_get_value(grid_t *grid, int i, int j) 
{
    if (grid != NULL) {
        int N = grid->N;
        if ((i >= 0) && (i < N) && (j >= 0) && (j < N)) {
            return tile_value(grid->table[i][j]);
        }
    }
    return -1;
}

// return the status of a given tile in a grid
bool grid_get_status(grid_t *grid, int i, int j) 
{
    if (grid != NULL) {
        int N = grid->N;
        if ((i >= 0) && (i < N) && (j >= 0) && (j < N)) {
            return tile_status(grid->table[i][j]);
        }
    }
    return false;
}

bool grid_cmp(grid_t *grid1, grid_t *grid2){

    if(grid1 != NULL && grid2 != NULL && grid1->N == grid2->N){
        for (int i = 0; i < grid1->N; i++){
            for (int j = 0; j < grid1->N; j++){
                if(tile_value(grid1->table[i][j]) != tile_value(grid2->table[i][j])){
                    return false;
                }
            }
        }
    }else{
        return false;
    }
    return true;
}


#ifdef UNIT_TEST
#include <stdio.h>
#include <math.h>
#include "unittest.h"
#include "set.h"
#include "jhash.h"
#include "grid.h"
#include "tile.h"
#include "memory.h"
#include "file.h"
#include "bag.h"
#include "hashtable.h"
#include "counters.h"

int test_solver1();
int test_solver2();
int test_creator();

int main(const int argc, const char *argv[]){
    int failed = 0; 

    printf("Testing solver...\n");
    failed += test_solver1();
    failed += test_solver2();
    printf("Testing creator...\n");
    failed += test_creator();
    if (failed) {
        printf("FAIL %d test case\n", failed);
        return failed;
    } else {
        printf("PASS all test cases\n");
        return 0; 
    }
}


int test_solver1(){

    START_TEST_CASE("solver");
    grid_t *grid = grid_new(9);
    EXPECT(grid != NULL);
    EXPECT(grid->N == 9);
    EXPECT(grid->table != NULL);

    grid_load(grid); // Multiple solutions 
    /* enter the following grid */
    /* 
        9 0 6 0 7 0 4 0 3
        0 0 0 4 0 0 2 0 0 
        0 7 0 0 2 3 0 1 0
        5 0 0 0 0 0 1 0 0 
        0 4 0 2 0 8 0 6 0 
        0 0 3 0 0 0 0 0 5
        0 3 0 7 0 0 0 5 0 
        0 0 7 0 0 5 0 0 0 
        4 0 5 0 1 0 7 0 8
    */
    for (int i = 0; i < grid->N; i++){
        for (int j = 0; j < grid->N; j++){
            EXPECT(tile_value(grid->table[i][j]) >= 0);
        }
    }

    int sol = grid_solve(grid);
    EXPECT(sol == 2);
    for (int i = 0; i < grid->N; i++){
        for (int j = 0; j < grid->N; j++){
            EXPECT(tile_value(grid->table[i][j]) > 0);
        }
    }
    
    grid_delete(grid);
    END_TEST_CASE;
    return TEST_RESULT;
}

int test_solver2(){

    START_TEST_CASE("solver");
    grid_t *grid = grid_new(9);
    EXPECT(grid != NULL);
    EXPECT(grid->N == 9);
    EXPECT(grid->table != NULL);

    grid_load(grid); // Multiple solutions 
    /* enter the following grid */
    /* 
        0 0 0 2 6 0 7 0 1
        6 8 0 0 7 0 0 9 0
        1 9 0 0 0 4 5 0 0
        8 2 0 1 0 0 0 4 0
        0 0 4 6 0 2 9 0 0
        0 5 0 0 0 3 0 2 8
        0 0 9 3 0 0 0 7 4
        0 4 0 0 5 0 0 3 6
        7 0 3 0 1 8 0 0 0
    */
    for (int i = 0; i < grid->N; i++){
        for (int j = 0; j < grid->N; j++){
            EXPECT(tile_value(grid->table[i][j]) >= 0);
        }
    }

    int sol = grid_solve(grid);
    EXPECT(sol == 1);
    for (int i = 0; i < grid->N; i++){
        for (int j = 0; j < grid->N; j++){
            EXPECT(tile_value(grid->table[i][j]) > 0);
        }
    }
    
    grid_delete(grid);
    END_TEST_CASE;
    return TEST_RESULT;
}

int test_creator(){ 

    START_TEST_CASE("creator");
    grid_t *grid = grid_new(9);
    EXPECT( grid != NULL);

    grid_solve(grid);
    for (int i = 0; i < grid->N; i++){
        for (int j = 0; j < grid->N; j++){
            EXPECT(tile_value(grid->table[i][j]) > 0);
        }
    }
    grid_print(grid, false);

    grid_random_clue(grid);
    int empty = 0;
    for (int i = 0; i < grid->N; i++){
        for (int j = 0; j < grid->N; j++){
           if(tile_value(grid->table[i][j]) == 0){
                empty++;
           }
        }
    }
    EXPECT(empty == grid_empty_cnt(grid));
    grid_print(grid, false);
    grid_delete(grid);

    return TEST_RESULT;
}
#endif // UNIT_TEST

