#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool isNumber(char s[]);

int main(int argc, char *argv[])
{
	if (argc != 2 || !isNumber(argv[1]))
	{
		printf("Usage: ./caesar key\n");
		return 1;
	}
	
	printf("plaintext: ");


	// reading user input
	int key = atoi(argv[1]);
	unsigned char pt[256];
	char line[256];
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%[^\n]", pt);	

	int len = strlen(pt);

	for(int i = 0; i < len; i++)
	{
		if ((pt[i] >= 'a' && pt[i] <= 'z') || (pt[i] >= 'A' && pt[i] <= 'Z'))
		{
			if(islower(pt[i]))
			{
				pt[i] += key;
				if (pt[i] > 'z')
				{
					pt[i] = ((pt[i] - 'a') % 26) + 'a';
				}
			}
			if(isupper(pt[i]))
			{
				pt[i] += key;
				if (pt[i] > 'Z')
				{
					pt[i] = (pt[i] - 'A') % 26 + 'a';
				}
			}

		}		
	}

	printf("ciphertext: %s\n", pt);
	
	return 0;
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
