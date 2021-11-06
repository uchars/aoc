#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int traverse_slope(char **slope, int height, int width, int right, int down);


int main(int argc, char *argv[])
{
	FILE *f;
	char *fname, c, **slope_matrix;
	int fname_len, file_height, file_width, i;
	
	if (argc != 2) 
	{
		printf("USAGE: day3 <filename>\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		fname_len = strlen(argv[1]);
		fname = (char*)malloc(sizeof(char) * fname_len);
		fname = argv[1];
	}
	
	
	f = fopen(fname, "r");
	if (f)
	{
		file_height = 1;	/* file has at least one line. */
		file_width = 0;
		
		/* count the chars/line once, since it is constant */
		for (c = fgetc(f); c != '\n'; c = fgetc(f)) file_width++;
		
		/* start counting the rest of the lines. */
		while (!feof(f))
		{
			c = fgetc(f);
			if (c == '\n') file_height++;
		}
		
		rewind(f);
		
		/* allocate. */
		slope_matrix = (char**)malloc(sizeof(char*) * file_height);
		for (i = 0; i < file_height; i++) 
			slope_matrix[i] = (char*)malloc(sizeof(char) * file_width);
		
		/* read data into the matrix */
		for (i = 0; i < file_height; i++)
			fscanf(f, "%s", slope_matrix[i]);
		
		/* Task a) */
		printf("Task a) 3R, 1D hits %i trees.\n", traverse_slope(slope_matrix, file_height, file_width, 3, 1));
		
		/* Task b) */
		printf("Task b) %i\n", 
			traverse_slope(slope_matrix, file_height, file_width, 1, 1) * 
			traverse_slope(slope_matrix, file_height, file_width, 3, 1) *
			traverse_slope(slope_matrix, file_height, file_width, 5, 1) *
			traverse_slope(slope_matrix, file_height, file_width, 7, 1) *
			traverse_slope(slope_matrix, file_height, file_width, 1, 2)
		);
		
		fclose(f);
	}
	else printf("ERROR: File '%s' could not be opened!\n", fname);
	
	return(0);
}


int traverse_slope(char **slope, int height, int width, int right, int down)
{
	/* count the trees encountered whilst traversing the slope. */
	int x, y, tree_count;
	
	x = 0;
	tree_count = 0;
	for (y = 0; y < height; y += down)
	{
		if (slope[y][x] == '#') tree_count++;
		x = (x + right) % width;
	}
	
	return(tree_count);
}
