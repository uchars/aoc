#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void day6solve(char *fname);


int main(int argc, char *argv[])
{
	char *fname;
	
	if (argc != 2)
	{
		printf("USAGE: day6 <input file>\n");
		exit(-1);
	}
	else 
	{
		fname = (char*)malloc(sizeof(char)*strlen(argv[1]));
		fname = argv[1];
		day6solve(fname);
	}
	
	free(fname);
	printf("I survived!\n");
	return(0);
}


void day6solve(char *fname)
{
	/* Questions a-z. (1) = yes ; (0) = no */
	FILE *f;
	char c;
	int questions[26], i, 
		taskA_count, taskB_count, 
		member_count; 
	
	f = fopen(fname, "r");
	if (f)
	{
		for (i = 0; i < 26; i++) questions[i] = 0;	/* as to not have random values. */
		taskA_count = 0;
		taskB_count = 0;
		member_count = 0;
		while (!feof(f))
		{
			c = fgetc(f);
			if (c == '\n')
			{
				member_count++;
				c = fgetc(f);
				if (c == '\n' || c == EOF)
				{
					/* new dataset: count & reset */
					for (i = 0; i < 26; i++)
					{
						/* Task a) */
						if (questions[i]) taskA_count++;
						
						/* Task b) */
						if (questions[i] == member_count) taskB_count++;
						
						questions[i] = 0;
					}
					member_count = 0; 
				}
				else
				{
					questions[(int)c - 97]++;
				}
			}
			else 
			{
				questions[(int)c - 97]++;
			}
		}
		printf("Task a) %i People answered 'yes'\n", taskA_count);
		printf("Task b) %i People answered 'yes'\n", taskB_count);
		
		fclose(f);
	}
	else printf("ERROR: File '%s' could not be opened.\n", fname);
}