#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <crypt.h>


bool isNumber(char s[]);
char * generatePw(char pw[], int * pwLen, int currentChar);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: ./crack hash\n");
		return 1;
	}
	
	char hash[256];
	char salt[3];
	strcpy(hash, argv[1]);
	strncpy(salt, hash, 2);
	salt[2] = '\0';


	// why am i bruteforcing a password in DES...
	
	char pw[256] = "A";
	int pwLen = 1;

	while (strcmp(hash, crypt(pw, salt)))
	{
		strcpy(pw, generatePw(pw, &pwLen, pwLen - 1));
	}
	printf("%s\n", pw);
	return 0;
}

char * generatePw(char pw[], int * pwLen, int currentChar)
{
	pw[currentChar]++;

	// after pw ends at Z, start again from a
	if (pw[currentChar] == '[')
		pw[currentChar] = 'a';

	// after current char ends at z, set it to A, and work on next character
	if (pw[currentChar] == '{')
	{
		pw[currentChar] = 'A';
		if (currentChar != 0)
		{
			// there are still digits to the left
			generatePw(pw, pwLen, --currentChar);
			// this causes a recursive call on the character to the left
			// if the character to the left is also a 'z',
			// the recursive nature of this function calls itself again
		}
		else
		{
			// we are at the left edge. need to add digits.
			strncpy(&(pw[1]), pw, *pwLen);
			pw[0] = 'A';
			(*pwLen)++;
			// impt note here: i had lots of problems earlier because i
			// did not put parentheses when i incremented the pointer
			// so this is the right way to do it
			pw[*pwLen] = '\0';
			
		}
	}
	return pw;
}

bool isNumber(char s[])
{
	for(int i = 0, len = strlen(s); i < len; i++)
	{
		if (i == 0)
		{
			if (s[0] == '-')
				continue;
		}

		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

