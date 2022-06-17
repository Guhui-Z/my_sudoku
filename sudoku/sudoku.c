/*
 * sudoku - Solve and create sudoku boards! For more see
 * DESIGN.md, REQUIREMENTS.md, IMPLEMENTATION.md, and
 * README.md
 *
 * usage: sudoku [mode]
 * 
 * mode can be "solver" or "create" or "play"
 *
 * CS50, Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h> // read, write, close
#include <string.h> // memcpy, memset
#include <netdb.h>  // socket-related structures
#include "../libcs50/tile.h"
#include "../libcs50/grid.h"
#include "../libcs50/memory.h"
#include "../libcs50/file.h"
#include "../libcs50/numbers.h"

/**************** file-local constants ****************/
#define BUFSIZE 1024 // read/write buffer size
#define HOSTNAME "plank"
#define PORT 3345

// function prototypes 
void play_grid(int N, grid_t *grid_answer, grid_t *grid_puzzle, grid_t *grid_user);
grid_t *get_grid();
int get_sudoku_size();

    int main(int argc, char *argv[])
{
    // check number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: ./sudoku mode\n");
        exit(1);
    }

    if (!strcmp(argv[1], "create")) {
        printf("Sudoku mode: create\n");
        int N = 0;
        grid_t *grid = get_grid(&N);

        grid_print(grid, false);

        printf("Empty tiles count: %d\n", grid_empty_cnt(grid));
        grid_delete(grid);

    } else if (!strcmp(argv[1], "solver")) {
        printf("Sudoku mode: solver\n");

        int N = get_sudoku_size();
        grid_t *grid = grid_new(N);
        // grid_print(grid, false);

        // load sudoku from input
        if (! grid_load(grid)) {
            exit(4);
        }
        grid_fprint(grid, false);

        int sol = grid_solve(grid);
        if (sol == 0) {
            printf("Sudoku solution not found\n");
        } else if (sol == 1){
            printf("Unique Sudoku Solution found:\n");
            grid_print(grid, false);
            grid_fprint(grid, true);
        }
        else
        {
            printf("Multiple Sudoku Solutions found:\n");
            grid_print(grid, false);
            grid_fprint(grid, true);
        }
        grid_delete(grid);

    } else if (!strcmp(argv[1], "play")) {
        // generate a sudoku puzzle
        int N = 0;
        grid_t *grid_puzzle = get_grid(&N);
        grid_t *grid_answer = grid_new(N);
        grid_copy(grid_puzzle, grid_answer);

        grid_solve(grid_answer);

        grid_print(grid_puzzle, true);

        grid_t *grid_user = grid_new(N); // stores the user input
        assertp(grid_user, "Failed to allocate memory for grid");
        grid_copy(grid_puzzle, grid_user);

        play_grid(N, grid_answer, grid_puzzle, grid_user);

        grid_delete(grid_answer);
        grid_delete(grid_puzzle);
        grid_delete(grid_user);
    } else {
        fprintf(stderr, "Unknown mode. Mode can be solver or create or play\n");
        exit(5);
    }

    return 0;
}

// read user input and play the grid
void play_grid(int N, grid_t *grid_answer, grid_t *grid_puzzle, grid_t *grid_user)
{
    int empty_cnt = grid_empty_cnt(grid_puzzle);
    int wrong_cnt = empty_cnt;
    printf("Empty tiles count: %d\n", empty_cnt);

    while (wrong_cnt > 0) { // while the user has not found the correct answer
        while (empty_cnt > 0) { // while the user sudoku has not been filled
            int i;
            int j;
            int num;
            char excess;

            // read and validate input
            printf("Enter your next step (row col num):");
            char *line = freadlinep(stdin);
            if (!strcmp(line, "q")) {
                printf("Quit program\n");
                free(line);
                return;
            }
            if (sscanf(line, "%d %d %d%c", &i, &j, &num, &excess) != 3) {
                fprintf(stderr, "Invalid input. Try again\n");
                free(line);
                continue;
            }
            if ((i < 0) || (i >= N)) {
                fprintf(stderr, "Row %d must be between [0, %d]. Try again\n", i, N-1);
                free(line);
                continue;
            }
            if ((j < 0) || (j >= N)) {
                fprintf(stderr, "Col %d must be between [0, %d]. Try again\n", j,  N-1);
                free(line);
                continue;
            }
            if ((num < 1) || (num > N)) {
                fprintf(stderr, "Num %d must be between [1, %d]. Try again\n", num, N);
                free(line);
                continue;
            }
            if (grid_get_status(grid_user, i, j)) {
                fprintf(stderr, "Tile (%d, %d) is fixed (a clue). Try again\n", i, j);
                free(line);
                continue;
            }
            // store the previous number in the specified tile
            int prev_num = grid_get_value(grid_user, i, j);
            // set the value in the user grid
            grid_set_tile(grid_user, i, j, false, num);

            // increment empty_cnt if a nonzero tile is set to zero
            if  ((prev_num != 0) && (num == 0)) {
                empty_cnt++;
            // decrement empty_cnt if a zero tile is set to nonzero
            } else if  ((prev_num == 0) && (num != 0)) {
                empty_cnt--;
            } // otherwise no changes to empty_cnt

            int correct_num = grid_get_value(grid_answer, i, j);
            // decrement wrong_cnt if an incorrect tile is set to correct
            if ((prev_num != correct_num) && (num == correct_num)) {
                grid_set_tile(grid_puzzle, i, j, false, num);
                wrong_cnt--;
            // increment wrong_cnt if a correct tile is set to incorrect
            } else if ((prev_num == correct_num) && (num != correct_num)) {
                grid_set_tile(grid_puzzle, i, j, false, 0);
                wrong_cnt++;
            } // otherwise no changes to wrong_cnt

            free(line);
            grid_print(grid_user, true);
        }
        if (wrong_cnt == 0) {
            printf("Success! You solved the sudoku!\n");
            break;
        } else {
            printf("Uh oh...Incorrect solution. We've kept the correct tiles. Try again!\n");
            
            // restart game
            // copy puzzle grid (that has correct user input) to the user grid
            grid_copy(grid_puzzle, grid_user);
            grid_print(grid_user, true);
            empty_cnt = grid_empty_cnt(grid_puzzle);
            wrong_cnt = empty_cnt;
            printf("Empty tiles count: %d\n", empty_cnt);
        }
    }
}


grid_t *get_grid(int *N){
    // code taken from inserver/inclient assignment
    *N = get_sudoku_size();
    char *hostname = HOSTNAME; // server hostname
    int port = PORT;           // server port

    // 1. Create socket
    int comm_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (comm_sock < 0)
    {
        perror("opening socket");
        exit(2);
    }

    // 2. Initialize the fields of the server address
    struct sockaddr_in server; // address of the server
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    // Look up the hostname specified on command line
    struct hostent *hostp = gethostbyname(hostname); // server hostname
    if (hostp == NULL)
    {
        fprintf(stderr, "unknown host '%s'\n", hostname);
        exit(3);
    }
    memcpy(&server.sin_addr, hostp->h_addr_list[0], hostp->h_length);

    // 3. Connect the socket to that server
    if (connect(comm_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connecting stream socket");
        exit(4);
    }
    printf("Connected!\n");

    char buf[BUFSIZE];       // a buffer for reading data from stdin
    memset(buf, 0, BUFSIZE); // clear up the buffer

    freopen("/dev/null", "a", stdout);
    setbuf(stdout, buf);
    printf("%d", *N);
    freopen("/dev/tty", "a", stdout);


    write(comm_sock, buf, BUFSIZE-1);

    memset(buf, 0, BUFSIZE); // clear up the buffer

    read(comm_sock, buf, BUFSIZE - 1);

    grid_t *grid = grid_new(*N);
    assertp(grid, "Failed to allocate memory for grid");

    grid_load_string(grid, buf);
    
    close(comm_sock);

    return grid;
}

// get and check the size of the sudoku from user input
int get_sudoku_size()
{

    printf("Enter the size of the sudoku (4, 9, 16, ...): ");
    int N;
    char excess;
    char *line = freadlinep(stdin);

    if (sscanf(line, "%d%c", &N, &excess) != 1)
    {
        fprintf(stderr, "Invalid input: must be an integer\n");
        free(line);
        exit(3);
        return 0;
    }

    if ((N <= 0) || (!is_perfect_square(N)))
    {
        fprintf(stderr, "Invalid input: must be a positive perfect square\n");
        free(line);
        exit(4);
        return 0;
    }
    printf("Sudoku size: %d\n", N);
    free(line);
    return N;
}