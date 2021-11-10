#include <stdio.h>
#include <stdlib.h>


#define WIDTH 97
#define HEIGHT 99


typedef struct SEAT_MATRIX {
    char seat[HEIGHT+1][WIDTH+1]; /* +1 to account for padding. */
} SEAT_MATRIX;


void day11Solve(char *fname);
SEAT_MATRIX* initSeatMatrix(char *fname);
void printSeatMatrix(SEAT_MATRIX *SM);
int developSeatMatrix(SEAT_MATRIX *SM);
int countAdjacentOccupied(SEAT_MATRIX *Mat, int row, int column);
int countOccupiedSeats(SEAT_MATRIX *SM);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("USAGE: day11 <input file>\n");
        exit(-1);
    }
    else
    {
        day11Solve(argv[1]);
        printf("I survived!\n");
    }

    return(0);
}


void day11Solve(char *fname)
{
    SEAT_MATRIX *SM;
    int stabilized;

    SM = initSeatMatrix(fname);
    printSeatMatrix(SM);
    printf("\n\n");

    do
    {
        stabilized = developSeatMatrix(SM);
        printSeatMatrix(SM);
        printf("\n\n");
    }
    while (!stabilized);

    printf("Task a) %d will be occupied.\n", countOccupiedSeats(SM));
    free(SM);
}


int developSeatMatrix(SEAT_MATRIX *SM)
{
    /* Changes every seat in the matrix SM (simultaniously!!!)
     * according to the following rules:
     *   1) If a seat is not occupied and there are no occupied seats
     *      adjacent to it, it becomes occupied.
     *
     *   2) If there are >4 occupied seats adjacent to seat A, it will
     *      become empty.
     *
     *
     * simultaniously means that the algorithm works on a snapshot basis,
     * i.e. a Change does not affect another change during a Cycle.
     */
    SEAT_MATRIX *snapshot;
    int stabilized, row, column, adjacent_occupied_count;

    snapshot = (SEAT_MATRIX*)malloc(sizeof(SEAT_MATRIX));
    *snapshot = *SM;

    stabilized = 1;
    /* row 0, row HEIGHT & col 0, col WIDTH contain padding */
    for (row = 1; row < HEIGHT; row++)
    {
        for (column = 1; column < WIDTH; column++)
        {
            /* only look at actual seats. */
            if (snapshot->seat[row][column] != '.')
            {
                adjacent_occupied_count = countAdjacentOccupied(snapshot, row, column);

                /* rule 1) */
                if (!adjacent_occupied_count && SM->seat[row][column] != '#')
                {
                    SM->seat[row][column] = '#';
                    stabilized = 0;
                }
                else if (adjacent_occupied_count >= 4 && SM->seat[row][column] != 'L')
                {
                    /* rule 2) */
                    SM->seat[row][column] = 'L';
                    stabilized = 0;
                }
                else continue;
            }
            else continue;
        }
    }

    free(snapshot);
    return(stabilized);
}


int countAdjacentOccupied(SEAT_MATRIX *Mat, int row, int column)
{
    int result, i, j;

    result = 0;
    for (i = -1; i <= 1; i++)
    {
        for (j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;
            else
            {
                if (Mat->seat[row+i][column+j] == '#')
                    result++;
                else continue;
            }
        }
    }

    return(result);
}


int countOccupiedSeats(SEAT_MATRIX *SM)
{
    int row, column, result;

    result = 0;
    for (row = 1; row < HEIGHT; row++)
        for (column = 1; column < WIDTH; column++)
            if (SM->seat[row][column] == '#')
                result++;

    return(result);
}

SEAT_MATRIX* initSeatMatrix(char *fname)
{
    SEAT_MATRIX *SM;
    FILE *F;
    int row, column;
    char c;

    SM = NULL;
    row = 1;    /* row 0 & row "max" will contain padding */
    column = 1; /* col 0 & col "max" will contain padding */

    F = fopen(fname, "r");
    if (F)
    {
        SM = (SEAT_MATRIX*)malloc(sizeof(SEAT_MATRIX));
        while (!feof(F))
        {
            c = fgetc(F);
            SM->seat[row][column] = c;

            if (c == '\n')
            {
                column = 1;
                row++;
            }
            else column++;
        }

        /* Apply the padding */
        for (row = 0; row < HEIGHT; row++)
        {
            SM->seat[row][0] = '.';
            SM->seat[row][WIDTH] = '.';
        }

        for (column = 0; column < WIDTH; column++)
        {
            SM->seat[0][column] = '.';
            SM->seat[HEIGHT][column] = '.';
        }
        SM->seat[HEIGHT][WIDTH] = '.';

    }
    else printf("ERROR: Could not open '%s'\n", fname);

    return(SM);
}


void printSeatMatrix(SEAT_MATRIX *SM)
{
    int row, column;

    for (row = 0; row < HEIGHT+1; row++)
    {
        for (column = 0; column < WIDTH+1; column++)
            printf("%c", SM->seat[row][column]);
        printf("\n");
    }
}
