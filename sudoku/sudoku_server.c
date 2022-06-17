/*
 * sudoku_server - server for sudoku project
 *
 * This program accepts connections forever in an infinite loop and sends
 *  a sudoku board to the client after the client sends the server the size
 *  if the size is invalid or anything else is sent it closes the socket
 *
 * usage: sudoku_server
 *  and ctrl-C to exit.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>   // bool type
#include <string.h>    // memcpy, memset
#include <unistd.h>    // read, write, close
#include <arpa/inet.h> // socket-related calls
#include "../libcs50/grid.h"
#include "../libcs50/memory.h"
#include "../libcs50/numbers.h"

/**************** file-local constants ****************/
#define SERV_PORT 3345   // server port number
#define LISTEN_BACKLOG 5 // number of connections to keep waiting
#define BUFSIZE 1024     // read/write buffer size

// function prototypes
grid_t *grid_create(int N);

/**************** main() ****************/
int main(const int argc, char *argv[])
{
    // code taken from inserver/inclient assignment
    int list_sock, comm_sock;
    struct sockaddr_in server; // server address
    char buf[BUFSIZE];         // buffer for reading data from socket

    // 1. Create socket on which to listen (file descriptor)
    list_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (list_sock < 0)
    {
        perror("opening socket stream");
        exit(1);
    }

    // 2. Initiate the fields of the server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERV_PORT);

    // 3. bind the socket to the given server address
    if (bind(list_sock, (struct sockaddr *)&server, sizeof(server)))
    {
        perror("binding socket name");
        exit(2);
    }
    printf("Listening at port %d\n", ntohs(server.sin_port));

    // 4. Start accepting connections, and allow one connection at a time
    listen(list_sock, LISTEN_BACKLOG);

    while (true)
    {
        
        // accept connection and receive communication socket (file descriptor)
        comm_sock = accept(list_sock, 0, 0);
        if (comm_sock == -1)
            perror("accept");
        else
        {
            printf("Connection started\n");
            int N;
            memset(buf, 0, sizeof(buf)); // fill buffer with nulls
            read(comm_sock, buf, BUFSIZE - 1);
            char excess;

            if (sscanf(buf, "%d%c", &N, &excess) != 1){
                printf("%d%c is an invalid input format\n", N, excess);
                close(comm_sock);
                continue;
            }
            memset(buf, 0, sizeof(buf)); // fill buffer with nulls

            if ((! is_perfect_square(N)) || (N <= 0))
            {
                close(comm_sock);
                printf("%d is not a positive perfect square\n", N);
                printf("Connection ended\n");
                continue;
            }

            printf("Sudoku size: %d\n", N);

            grid_t *grid = grid_create(N);

            printf("Sudoku generated\n");

            //pipe output of grid to the buffer string
            freopen("/dev/null", "a", stdout);
            setbuf(stdout, buf);
            grid_print(grid, false);
            freopen("/dev/tty", "a", stdout);

            printf("%s", buf);

            printf("Sending sudoku to client\n");

            //send grid to client
            write(comm_sock, buf, BUFSIZE-1);
            grid_delete(grid);

            printf("Sudoku sent to client\n");

            close(comm_sock);

            printf("Connection ended\n");
        }
    }

    close(list_sock);
    /* Note that if the server doesn't explicitly exit or close the socket,
     * the socket will be closed when the program is killed or terminates. */
}

// create a grid
grid_t *grid_create(int N)
{
    grid_t *grid = grid_new(N);
    assertp(grid, "Failed to allocate memory for grid");
    grid_solve(grid);

    // generate sudoku puzzle
    grid_random_clue(grid);

    if (N == 9) {
        while (grid_empty_cnt(grid) < 40) {
            printf("9*9 grid has less than 40 empty tiles. Trying again.\n");
            grid_delete(grid);
            grid_t *grid = grid_new(N);
            assertp(grid, "Failed to allocate memory for grid");
            grid_solve(grid);
            grid_random_clue(grid);
        }
    }
    return grid;
}
