#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool isNumber(char s[]);
bool hasNumber(char s[]);
void numberForm(char s[]);

int main(int argc, char *argv[])
{
    if (argc != 2 || hasNumber(argv[1]))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    char key[256] = "";
    strcpy(key, argv[1]);

    int keyLen = strlen(key);
    numberForm(key);
    printf("plaintext: ");


    // reading user input
    char pt[256];
    char line[256];
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%[^\n]", pt);	

    int ptLen = strlen(pt);

    int keyIndex = 0;
    for(int i = 0; i < ptLen; i++)
    {
        if ((pt[i] >= 'a' && pt[i] <= 'z') || (pt[i] >= 'A' && pt[i] <= 'Z'))
        {
            if (keyIndex == keyLen)
            {
                keyIndex = 0;
            }
            if(islower(pt[i]))
            {
                pt[i] += key[keyIndex];
                if (pt[i] > 'z')
                {
                    pt[i] = ((pt[i] - 'a') % 26) + 'a';
                }
            }
            if(isupper(pt[i]))
            {
                pt[i] += key[keyIndex];
                if (pt[i] > 'Z')
                {
                    pt[i] = ((pt[i] - 'A') % 26) + 'A';
                }
            }
            keyIndex++;

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

bool hasNumber(char s[])
{
    for(int i = 0, len = strlen(s); i < len; i++)
    {
        if (isdigit(s[i]))
            return true;
    }
    return false;
}

void numberForm(char s[])
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isupper(s[i]))
        {
            s[i] -= 'A';
        }
        else if (islower(s[i]))
        {
            s[i] -= 'a';
        }
    }
    return;
}
