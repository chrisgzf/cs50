#include <stdio.h>
#include <math.h>

#define NO_OF_DENOMINATIONS 4

int main(void)
{
    double input;
    int change, nCoins = 0;
    const int denominations[NO_OF_DENOMINATIONS] = { 25, 10, 5, 1 };

    // Read user input
    int r;
    do
    {
        printf("Changed owed: ");
        char line[20];
        fgets(line, sizeof(line), stdin);
        r = sscanf(line, "%lf", &input); 
    } while (input < 0 || r != 1);


    // Convert double input to reliable int for manipulation
    change = round(input * 100);

    while (change != 0)
    {
        for (int i = 0; i < NO_OF_DENOMINATIONS; i++)
        {
            if (change >= denominations[i])
            {
                change -= denominations[i];
                nCoins++;
                break;
            }
        }
    }

    printf("%d\n", nCoins);
    return 0;

}

