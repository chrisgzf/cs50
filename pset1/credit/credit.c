#include <stdio.h>
#include <math.h>

int get_digit(long n, int a);
int get_total_digits(long n);
int sum_digits(int n);
long get_cc(void);

int main(void) {
    long cc = get_cc();
    int digits = get_total_digits(cc);
    int checksum = 0;
    
    for (int i = 1; i < digits; i+=2)
    {
        checksum += sum_digits(get_digit(cc, i) * 2);
    }
    
    for (int i = 0; i < digits; i+=2)
    {
        checksum += get_digit(cc, i);
    }
    
    if (checksum % 10 == 0)
    {
        if (get_digit(cc, digits - 1) == 5 && (get_digit(cc, digits - 2) > 0 && get_digit(cc, digits - 2) < 6) && digits == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (get_digit(cc, digits - 1) == 4 && (digits == 16 || digits == 13))
        {
            printf("VISA\n");
        }
        else if (get_digit(cc, digits - 1) == 3 && (get_digit(cc, digits - 2) == 4 || get_digit(cc, digits - 2) == 7) && digits == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

int get_digit(long n, int a)
{
    n /= pow(10, a);
    return n % 10;
}

int get_total_digits(long n)
{
    if (n % 10 == 0) n++;
    int i;
    for(i = 0; n != 0; i++)
    {
        n /= 10;
    }
    return i;
}

long get_cc(void)
{
    long l;
    char line[255];
    do
    {
        printf("Number: ");
        fgets(line, sizeof(line), stdin);
    } while (sscanf(line, "%ld", &l) != 1);
    return l;
}

int sum_digits(int n)
{
    int nDigits = get_total_digits(n);
    int sum = 0;
    for (int i = 0; i < nDigits; i++)
    {
        sum += get_digit(n, i);
    }
    return sum;
}

