#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct COMMAND {
    char operation[4];
    int value;
    int executed;
} COMMAND;

void day8Solve(char *fname);
int countLinesInFile(FILE *F);


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("USAGE: day8 <input file>\n");
        exit(-1);
    }
    else
    {
        day8Solve(argv[1]);
        printf("Survived!\n");
    }

    return(0);
}




void day8Solve(char *fname)
{
    FILE *F;
    int lines_count, i, acc;
    char val_buf[10], ope_buf[4];
    COMMAND *cmds;

    F = fopen(fname, "r");
    if (F)
    {
        lines_count = countLinesInFile(F);
        printf("There are %d commands in the file '%s'\n", lines_count, fname);
        cmds = (COMMAND*)malloc(sizeof(COMMAND) * lines_count);
        i = 0;

        /* read commands. */
        while (!feof(F))
        {
            fscanf(F, "%s %s\n", ope_buf, val_buf);
            strcpy(cmds[i].operation, ope_buf);
            cmds[i].value = atoi(val_buf);
            cmds[i].executed = 0;
            i++;
        }

        /* Task a). */
        acc = 0;
        for (i = 0; !cmds[i].executed && i < lines_count; i++)
        {
            cmds[i].executed = 1;

            if (strstr(cmds[i].operation, "acc"))
                acc += cmds[i].value;
            else if (strstr(cmds[i].operation, "jmp"))
                i += cmds[i].value - 1; /* -1 to circumvent the increase from i++ */
            else
                continue;
        }
        printf("Program stopped at Operation #: %d\n", i);
        printf("Task a) acc = %d\n", acc);

        for (i = 0; i < lines_count; i++) cmds[i].executed = 0;

        /* Task b) */
        acc = 0;
        for (i = 0; !cmds[i].executed && i < lines_count; i++)
        {
            cmds[i].executed = 1;

            if (strstr(cmds[i].operation, "acc"))
                acc += cmds[i].value;
            else if (strstr(cmds[i].operation, "jmp"))
            {
                /* if jump causes repetition, ignore. */
                if (cmds[i + cmds[i].value].executed)
                    continue;
                else
                    i += cmds[i].value - 1;
            }
            else
                continue;
        }
        printf("Task b) acc = %d\n", acc);
    }
    else printf("ERROR: Could not open file '%s'\n", fname);
}


int countLinesInFile(FILE *F)
{
    char c;
    int lines_count;

    rewind(F);

    lines_count = 0;
    while (!feof(F))
    {
        c = fgetc(F);
        if (c == '\n') lines_count++;
        else continue;
    }

    rewind(F);
    return(lines_count);
}
