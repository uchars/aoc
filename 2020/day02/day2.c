#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int taskA_validate(char *rule, char *pwd)
{
	/* rule is of the following format:
	* 	x-y c: 
	* where x and y are the integer lower and upper bounds 
	* of the occurences of char c.*/
	int ruleLen, pwdLen, lowerBound, upperBound, i, j, c_count, isValid;
	char c, lowerBound_str[80], upperBound_str[80];
	
	
	/* read data from rule. */
	ruleLen = strlen(rule);
	c = rule[ruleLen-2];
	
	for (i = 0; i < ruleLen; i++)
	{
		if (rule[i] == '-') break;
		else lowerBound_str[i] = rule[i];
	}
	lowerBound = atoi(lowerBound_str);
	
	for (j = 0; j < ruleLen; j++)
	{
		if (rule[i] == ' ') break;
		else upperBound_str[j] = rule[i+1];
		i++;
	}
	upperBound = atoi(upperBound_str);

	
	/* Count occurences of c. */
	pwdLen = strlen(pwd);
	c_count = 0;
	
	for (i = 0; i < pwdLen; i++) 
		if (pwd[i] == c) c_count++;
	
	/* validation. */
	if (lowerBound <= c_count && c_count <= upperBound) isValid = 1;
	else isValid = 0;
	
	return(isValid);
}



int taskB_validate(char *rule, char *pwd)
{
	/* rule is of the following format:
	* 	x-y c: 
	* where x and y are the integer lower and upper bounds (thus x <= y)
	* of the occurences of char c.*/
	int ruleLen, pwdLen, letterPos1, letterPos2, i, j, isValid;
	char c, letterPos1_str[80], letterPos2_str[80];
	
	
	/* read data from rule. */
	ruleLen = strlen(rule);
	c = rule[ruleLen-2];
	
	for (i = 0; i < ruleLen; i++)
	{
		if (rule[i] == '-') break;
		else letterPos1_str[i] = rule[i];
	}
	letterPos1 = atoi(letterPos1_str) - 1; /* -1 due to indexing in pwd. */
	
	for (j = 0; j < ruleLen; j++)
	{
		if (rule[i] == ' ') break;
		else letterPos2_str[j] = rule[i+1];
		i++;
	}
	letterPos2 = atoi(letterPos2_str) - 1;

	
	/* Count occurences of c at the given positions. */
	pwdLen = strlen(pwd);
	for (i = 0; i < pwdLen; i++) 
	{
		if (i == letterPos1 && pwd[i] == c) isValid = 1;
		else if (i == letterPos2 && pwd[i] == c)
		{
			if (isValid) isValid = 0; /* c allready occured at position 1. */
			else isValid = 1; /* c did not occur at position 1. */
		}
	}
	
	return(isValid);
}


int getRuleLen(char *str)
{
	int i, str_len, rule_len;
	
	str_len = strlen(str);
	rule_len = 0;
	
	/* count the length of the rule. */
	for (i = 0; i < str_len; i++)
	{
		if (str[i] == ':') break;
		else rule_len++;
	}
	
	return(rule_len);
}


char *getRule(char *str)
{
	char *rule;
	int i, rule_len;
	
	rule_len = getRuleLen(str);
	rule = (char*)malloc(sizeof(char) * rule_len + 1);
	
	/* write data into the rule. */
	for (i = 0; i < rule_len + 1; i++) rule[i] = str[i];
	rule[i] = '\0';
	
	return(rule);
}


char *getPwd(char *str)
{
	char *pwd;
	int i, j, str_len, pwd_len;
	
	str_len = strlen(str);
	
	/* -1 to ignore the space after the ':'*/
	pwd_len = str_len - getRuleLen(str) - 1;
	
	/* +1 to make space for NUL('\0'). */
	pwd = (char*)malloc(sizeof(char) * pwd_len + 1);
	
	/* write data into the rule. */
	j = 0;
	for (i = str_len - pwd_len + 1; i < str_len; i++) 
	{
		pwd[j] = str[i];
		j++;
	}
	pwd[j] = '\0';
	
	return(pwd);
}


int main(void)
{
	FILE *f;
	char buf[100], c;
	int taskA_valid_count, taskB_valid_count, i;
	
	f = fopen("input.txt", "r");
	if (f)
	{
		taskA_valid_count = 0;
		taskB_valid_count = 0;
		i = 0;
		while (!feof(f))
		{
			c = fgetc(f);
			
			if (c == '\n') 
			{
				buf[i] = '\0';
				taskA_valid_count += taskA_validate(getRule(buf), getPwd(buf));
				taskB_valid_count += taskB_validate(getRule(buf), getPwd(buf));
				i = 0;
			}
			else 
			{
				buf[i] = c;
				i++;
			}
		}
		fclose(f);
	}
	else printf("ERROR: Could not open file!\n");
	
	printf("Task a) %i passwords are valid.\n", taskA_valid_count);
	printf("Task b) %i passwords are valid.\n", taskB_valid_count);
	
	return(0);
}