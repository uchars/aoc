#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Binary space partitioning tree. */
typedef struct BSPTree {
	int range[2];
	struct BSPTree *lNode;
	struct BSPTree *rNode;
} BSPTree;


typedef struct LinkedList {
	int val;
	struct LinkedList *next;
	struct LinkedList *prev;
} LinkedList;


void day5Solve(char *fname);
BSPTree* createBSPTree(int depth);
BSPTree* _buildBSPTree(int depth, int rangeMin, int rangeMax);
LinkedList *add(int val, LinkedList *l);
LinkedList *sortLinkedList(LinkedList *l);
void swapNodes(LinkedList *A, LinkedList *A_next);
int getRowFromCode(char *code, BSPTree *rT);
int getColFromCode(char *code, BSPTree *cT);
int getSeatID(char *code, BSPTree *rT, BSPTree *ct);


int main(int argc, char *argv[])
{
	char *fname;
	
	if (argc != 2) 
	{
		printf("USAGE: day5 <input file>\n");
		exit(-1);
	}
	else 
	{
		fname = (char*)malloc(strlen(argv[1]));
		fname = argv[1];
		
		day5Solve(fname);
		printf("survived");
		free(fname);
	}
	
	return(0);
}


void day5Solve(char *fname)
{
	FILE *f;
	BSPTree *rT, *cT;
	LinkedList *seatIDS;
	char code[10];
	int seatID, max_seatID;
	
	f = fopen(fname, "r");
	if (f)
	{
		rT = createBSPTree(7);
		cT = createBSPTree(3);

		max_seatID = 0;
		seatIDS = NULL;
		while (!feof(f))
		{
			fscanf(f, "%s", code);
			seatID = getSeatID(code, rT, cT);
			seatIDS = add(seatID, seatIDS);
			if (seatID > max_seatID) max_seatID = seatID;
		}
		printf("Task a) The highest seatID is: %i\n", max_seatID);
		
		/* Task b) */
		seatIDS = sortLinkedList(seatIDS);
		while (seatIDS->next) seatIDS = seatIDS->next;
		
		while (seatIDS->prev)
		{
			if ((seatIDS->val - seatIDS->prev->val) == 2)
			{
				printf("Task b) My seatID is: %i\n", seatIDS->val - 1);
				break;
			}
			else seatIDS = seatIDS->prev;
		}
		
		fclose(f);
	}
	else printf("ERROR: Could not open '%s'!", fname);
}


LinkedList *add(int val, LinkedList *l)
{
	LinkedList *new_node;
	
	new_node = (LinkedList*)malloc(sizeof(LinkedList));
	new_node->val = val;

	if (l)
	{
		l->next = new_node;
		new_node->prev = l;
	}
	else
	{
		new_node->prev = NULL;
		new_node->next = NULL;
	}
	
	return(new_node);
}


void swapNodes(LinkedList *A_curr, LinkedList *A_next)
{
	LinkedList *A_curr_prev, *A_next_next;
	
	A_curr_prev = A_curr->prev;
	A_next_next = A_next->next;
	
	A_curr->prev = A_next;
	A_next->next = A_curr;
	
	A_curr->next = A_next_next;
	A_next->prev = A_curr_prev;
	
	if (A_next_next) A_next_next->prev = A_curr;
	if (A_curr_prev) A_curr_prev->next = A_next;
}


LinkedList *sortLinkedList(LinkedList *l)
{
	LinkedList *result, *curr_node, *next_node, *entry;
	int sorted;
	
	entry = l;
	
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		while (entry->prev) entry = entry->prev;
		curr_node = entry;
		
		do 
		{
			next_node = curr_node->next;
			
			if (curr_node->val > next_node->val) 
			{
				swapNodes(curr_node, next_node);
				sorted = 0;
			}
			else curr_node = next_node;
		}
		while (curr_node->next);
	}
	result = curr_node;
	
	while (result->next) result = result->next;
	
	return(result);
}


int getSeatID(char *code, BSPTree *rT, BSPTree *cT)
{
	int row, col, result;
	
	row = getRowFromCode(code, rT);
	col = getColFromCode(code, cT);
	
	result = (row * 8) + col;
	
	return(result);
}


int getRowFromCode(char *code, BSPTree *rT)
{
	BSPTree *curr;
	int i;
	
	curr = rT;
	i = 0;
	
	do 
	{
		if (code[i] == 'B') curr = curr->lNode;
		else curr = curr->rNode;
		
		i++;
	}
	while (curr->lNode && curr->rNode);
	
	return(curr->range[0]);
}


int getColFromCode(char *code, BSPTree *cT)
{
	BSPTree *curr;
	int i;
	
	curr = cT;
	i = 7;	/* todo make this dynamic. */
	
	do 
	{
		if (code[i] == 'R') curr = curr->lNode;
		else curr = curr->rNode;
		
		i++;
	}
	while (curr->lNode && curr->rNode);
	
	return(curr->range[0]);
}


BSPTree* _buildBSPTree(int depth, int rowMin, int rowMax)
{
	BSPTree *node;
	
	node = (BSPTree*)malloc(sizeof(BSPTree));
	if (depth == 0) 
	{
		node->range[0] = rowMin;
		node->range[1] = rowMax;
		node->rNode = NULL;
		node->lNode = NULL;
		
		return(node);	/* leaf */
	}
	else 
	{
		node->rNode = (BSPTree*)malloc(sizeof(BSPTree));
		node->lNode = (BSPTree*)malloc(sizeof(BSPTree));
		
		node->rNode = _buildBSPTree(depth-1, rowMin, rowMax - (rowMax-rowMin)/2 - 1);
		node->lNode = _buildBSPTree(depth-1, rowMin + (rowMax-rowMin)/2 + 1, rowMax);
		
		return(node);	/* entry node. */
	}
}


BSPTree* createBSPTree(int depth)
{
	BSPTree *new_rT;
	
	new_rT = _buildBSPTree(depth, 0, (int)pow(2, (double)depth) - 1);

	return(new_rT);
}