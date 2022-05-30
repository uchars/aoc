#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int taskA_verify(char *passport);
int taskB_verify(char *passport);
void day4Solve(char *fname);
int _verify_key(char *passport, char *key);
char* _get_key_value(char *key, char *passport);
int _verify_byr_value(char *passport);
int _verify_iyr_value(char *passport);
int _verify_eyr_value(char *passport);
int _verify_hgt_value(char *passport);
int _verify_hcl_value(char *passport);
int _verify_ecl_value(char *passport);
int _verify_pid_value(char *passport);



int main(int argc, char *argv[])
{
	char *fname;
	
	if (argc != 2)
	{
		printf("USAGE: day4 <input file>\n");
		exit(EXIT_FAILURE);
	}
	else 
	{
		fname = (char*)malloc(sizeof(char) * strlen(argv[1]));
		fname = argv[1];
		day4Solve(fname);
	}
		
	return(0);
}


void day4Solve(char *fname)
{
	FILE *f;
	int taskA_valid_count, taskB_valid_count, i;
	char passport[150], c;
	
	f = fopen(fname, "r");
	if (f)
	{
		taskA_valid_count = 0;
		taskB_valid_count = 0;
		while (!feof(f))
		{
			c = fgetc(f);
			if (c == '\n')
			{
				c = fgetc(f);
				if (c == '\n' || c == EOF)
				{
					/* dataset end, verify passport. */
					passport[i] = '\0';
					i = 0;
					taskA_valid_count += taskA_verify(passport);
					taskB_valid_count += taskB_verify(passport);
				}
				else 
				{
					passport[i] = ' ';	/* add data-point seperator */
					passport[i+1] = c;
					i += 2;
				}
			}
			else 
			{
				passport[i] = c;
				i++;
			}
		}
		
		printf("Task a) %i passports are valid.\n", taskA_valid_count);
		printf("Task b) %i passports are valid.\n", taskB_valid_count);
	}
	else printf("ERROR: Could not open file '%s'!", fname);
}


int _verify_key(char *key, char *passport)
{
	int passport_len, key_len, i, j, isValid, isKey, occurence;
	
	passport_len = strlen(passport);
	key_len = strlen(key);
	occurence = 0;
	
	for (i = 0; i < passport_len - key_len; i++)
	{
		if (passport[i + key_len] == ':')
		{
			for (j = 0; j < key_len; j++) 
			{
				if (key[j] == passport[i+j]) isKey = 1;
				else 
				{ 
					isKey = 0;
					break;
				}
			}
			if (isKey) occurence++;
		}
	}
	
	if (occurence == 1) isValid = 1;
	else if (occurence <= 1 && key[0] == 'c' && key[1] == 'i' && key[2] == 'd') isValid = 1;
	else isValid = 0;
	
	return(isValid);
}


char* _get_key_value(char *key, char *passport)
{
	int passport_len, key_len, i, j, k, isKey;
	char *value, c;
	
	passport_len = strlen(passport);
	key_len = strlen(key);
	value = (char*)malloc(sizeof(char) * 80);
		
	for (i = 0; i < passport_len - key_len; i++)
	{
		if (passport[i + key_len] == ':')
		{
			for (j = 0; j < key_len; j++) 
			{
				if (key[j] == passport[i+j]) isKey = 1;
				else 
				{ 
					isKey = 0;
					break;
				}
			}
			if (isKey)
			{
				k = 0;
				/* start after the key-value seperator ':'*/
				for (j = i + key_len + 1; j < passport_len; j++)
				{
					c = passport[j];
					/* read until whitespace or newline */
					if (c == ' ' || c == '\n') 
					{
						value[k] = '\0';
						break;
					}
					else value[k] = c;
					k++;
				}
			}
		}
	}
	
	return(value);
}


int taskA_verify(char *passport)
{
	int byr_valid, iyr_valid, 
		eyr_valid, hgt_valid, 
		hcl_valid, ecl_valid,
		pid_valid, cid_valid,
		isValid;
	

	byr_valid = _verify_key("byr", passport);
	iyr_valid = _verify_key("iyr", passport);
	eyr_valid = _verify_key("eyr", passport);
	hgt_valid = _verify_key("hgt", passport);
	ecl_valid = _verify_key("ecl", passport);
	hcl_valid = _verify_key("hcl", passport);
	pid_valid = _verify_key("pid", passport);
	cid_valid = _verify_key("cid", passport);
	
	
	if ((byr_valid && iyr_valid) && (eyr_valid && hgt_valid) && (hcl_valid && ecl_valid) && (pid_valid && cid_valid)) 
		isValid = 1;
	else isValid = 0;
	
	return(isValid);
}


int taskB_verify(char *passport)
{
	int byr_valid, iyr_valid, 
		eyr_valid, hgt_valid, 
		hcl_valid, ecl_valid,
		pid_valid, cid_valid,
		isValid;
	

	if (taskA_verify(passport))
	{
		byr_valid = _verify_byr_value(passport);
		iyr_valid = _verify_iyr_value(passport);
		eyr_valid = _verify_eyr_value(passport);
		hgt_valid = _verify_hgt_value(passport);
		ecl_valid = _verify_ecl_value(passport);
		hcl_valid = _verify_hcl_value(passport);
		pid_valid = _verify_pid_value(passport);
		
		if ((byr_valid && iyr_valid) && (eyr_valid && hgt_valid) && (hcl_valid && ecl_valid) && (pid_valid && cid_valid))
			isValid = 1;
		else isValid = 0;
	}
	else isValid = 0;
	
	return(isValid);
}


int _verify_byr_value(char *passport)
{
	char *value_str;
	int value, isValid;
	
	value_str = _get_key_value("byr", passport);
	value = atoi(value_str);
	
	if (value >= 1920 && value <= 2002) isValid = 1;
	else isValid = 0;
	
	return(isValid);
}

int _verify_iyr_value(char *passport)
{
	char *value_str;
	int value, isValid;

	value_str = _get_key_value("iyr", passport);
	value = atoi(value_str);
	
	if (value >= 2010 && value <= 2020) isValid = 1;
	else isValid = 0;
	
	return(isValid);
}

int _verify_eyr_value(char *passport)
{
	char *value_str;
	int value, isValid;

	value_str = _get_key_value("eyr", passport);
	value = atoi(value_str);
	
	if (value >= 2020 && value <= 2030) isValid = 1;
	else isValid = 0;
	
	return(isValid);
}

int _verify_hgt_value(char *passport)
{
	char *value_str, *height_str;
	int value_str_len, max_val, min_val, isValid, height, i;
	
	value_str = _get_key_value("hgt", passport);
	value_str_len = strlen(value_str);
	
	
	/* -2 to ignore unit*/
	height_str = (char*)malloc(sizeof(char) * (value_str_len - 2));
	for (i = 0; i < (value_str_len - 2); i++)
		height_str[i] = value_str[i];
	height = atoi(height_str);
	
	
	if (value_str[value_str_len - 2] == 'c' && value_str[value_str_len - 1] == 'm')
	{
		min_val = 150;
		max_val = 193;
	}
	else if (value_str[value_str_len - 2] == 'i' && value_str[value_str_len - 1] == 'n')
	{
		min_val = 59;
		max_val = 76;
	}
	else return(0);
	
	
	if (height >= min_val && height <= max_val) isValid = 1;
	else isValid = 0;
	
	return(isValid);
}

int _verify_hcl_value(char *passport)
{
	char *value_str;
	int value_str_len, isValid, i;

	value_str = _get_key_value("hcl", passport);
	value_str_len = strlen(value_str);
	
	if (value_str[0] == '#')
	{
		if (value_str_len == 7)
		{
			for (i = 1; i < value_str_len; i++)
			{
				if ((int)value_str[i] >= 48 && (int)value_str[i] <= 57) 
					isValid = 1;
				else if ((int)value_str[i] >= 97 && (int)value_str[i] <= 102) 
					isValid = 1;
				else 
				{
					isValid = 0;
					break;
				}
			}
		}
		else isValid = 0;
	}
	else isValid = 0;
	
	return(isValid);
}

int _verify_ecl_value(char *passport)
{
	char *value_str;
	int isValid;
	
	value_str = _get_key_value("ecl", passport);
	
	if (strlen(value_str) != 3) isValid = 0;
	else if (value_str[0] == 'a' && value_str[1] == 'm' && value_str[2] == 'b') 
		isValid = 1;
	else if (value_str[0] == 'b' && value_str[1] == 'l' && value_str[2] == 'u') 
		isValid = 1;
	else if (value_str[0] == 'b' && value_str[1] == 'r' && value_str[2] == 'n') 
		isValid = 1;
	else if (value_str[0] == 'g' && value_str[1] == 'r' && value_str[2] == 'y') 
		isValid = 1;
	else if (value_str[0] == 'g' && value_str[1] == 'r' && value_str[2] == 'n') 
		isValid = 1;
	else if (value_str[0] == 'h' && value_str[1] == 'z' && value_str[2] == 'l') 
		isValid = 1;
	else if (value_str[0] == 'o' && value_str[1] == 't' && value_str[2] == 'h') 
		isValid = 1;
	else isValid = 0;
	
	return(isValid);
}

int _verify_pid_value(char *passport)
{
	char *value_str;
	int value_str_len, i, isValid;
	
	value_str = _get_key_value("pid", passport);
	value_str_len = strlen(value_str);
	
	if (value_str_len == 9)
	{
		for (i = 0; i < value_str_len; i++)
		{
			if (isdigit(value_str[i])) isValid = 1;
			else 
			{
				isValid = 0;
				break;
			}
		}
	}
	else isValid = 0;
	
	return(isValid);
}
