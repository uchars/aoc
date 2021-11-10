#include <stdio.h>
#include <stdlib.h>


#define PREAMBLE_LENGTH 25


void day9Solve(char *fname);
int validate(int preamble[], int num);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("USAGE: day9 <input file>\n");
        exit(-1);
    }
    else
    {
        day9Solve(argv[1]);
        printf("Survived!\n");
    }

    return(0);
}


void day9Solve(char *fname)
{
    FILE *F;
    char num_buf[20];
    int preamble[PREAMBLE_LENGTH],
        num,
        i, j,
        numbers[1000],
        sum, smallest, largest,
        invalid_num_pos,
        invalid_num;

    F = fopen(fname, "r");
    if (F)
    {
        for (i = 0; i < 1000; i++)
        {
            fscanf(F, "%s\n", num_buf);
            numbers[i] = atoi(num_buf);
        }

        rewind(F);

        /* load initial preamble */
        for (i = 0; i < PREAMBLE_LENGTH; i++)
        {
            fscanf(F, "%s\n", num_buf);
            preamble[i] = atoi(num_buf);
        }

        /* Task a) */
        i = 0;
        invalid_num_pos = PREAMBLE_LENGTH;
        while (!feof(F))
        {
            fscanf(F, "%s\n", num_buf);
            num = atoi(num_buf);

            if (!validate(preamble, num))
            {
                invalid_num = num;
                printf("%3d is NOT VALID! (%d)\n", invalid_num, invalid_num_pos);
                break;
            }
            else
            {
                if (i < PREAMBLE_LENGTH)
                    preamble[i] = num;
                else
                {
                    i = 0;
                    preamble[i] = num;
                }
                i++;
                invalid_num_pos++;
            }
        }


        /* Task b) */
        for (i = 0; i < invalid_num_pos; i++)
        {
            sum = 0;
            smallest = numbers[i];
            largest = numbers[i];
            for (j = i; j < invalid_num_pos; j++)
            {
                if (smallest > numbers[j]) smallest = numbers[j];
                if (largest < numbers[j]) largest = numbers[j];

                sum += numbers[j];
                if (sum == invalid_num)
                {
                    printf("Invalid num was found with\n\ti: %d\n\tj: %d\n\tinvalid_num_pos: %d\n", i, j, invalid_num_pos);
                    printf("KEY = %d + %d = %d\n", smallest, largest, smallest + largest);
                    break;
                }
            }
        }
    }
    else printf("ERROR: Could not open '%s'!\n", fname);
}


int validate(int preamble[], int num)
{
    int i, j, sum;

    for (i = 0; i < PREAMBLE_LENGTH-1; i++)
    {
        for (j = i+1; j < PREAMBLE_LENGTH; j++)
        {
            sum = preamble[i] + preamble[j];
            if (sum == num) return(1);
            else continue;
        }
    }

    return(0);
}
