#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getDataCount(char *fname, char seperator)
{
	FILE *f;
	int count;
	char c;
	
	count = 0;
	f = fopen(fname, "r");
	
	if (f)
	{
		while(!feof(f))
		{
			c = fgetc(f);
			if (c == seperator) count++;
		}
	}
	else printf("ERROR: Could not open file '%s'\n", fname);
	
	fclose(f);
	
	return count;
}

int main(void)
{
	char **data, c;
	int data_count, i, j, k, num1, num2, num3, found;
	FILE *f;
	
	data_count = getDataCount("input", '\n');
	data = (char **)malloc(sizeof(char*) * data_count);
	for (i = 0; i < data_count; i++) data[i] = (char*) malloc(sizeof(char) * 5);
	
	/* read data from the input-file */
	f = fopen("input", "r");
	i = 0;
	while (i < data_count)
	{
		j = 0;
		while ((c = fgetc(f)) != '\n')
		{
			data[i][j] = c;
			j++;
		}
		data[i][j] = '\n';
		
		i++;
	}
	fclose(f);
	
	
	/* Check three two numbers whose sum of 2020 */
	found = 0;
	for (i = 0; i < data_count && !found; i++)
	{
		num1 = atoi(data[i]);
		for (j = i; j < data_count && !found; j++)
		{
			num2 = atoi(data[j]);
			for (k = j; k < data_count && !found; k++)
			{
				num3 = atoi(data[k]);
				if (num1 + num2 + num3 == 2020) found = 1;
			}
		}
	}
	printf("Task a) %i * %i = %i\n", num1, num2, num1*num2);
	printf("Task b) %i * %i * %i = %i\n", num1, num2, num3, num1*num2*num3);
	
	
	for (i = 0; i < data_count; i++) free(data[i]);
	free(data);
	
	return(0);
}
