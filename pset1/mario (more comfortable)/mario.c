#include <stdio.h>

int get_height(void);
void print_whitespace(int n);
void print_hash(int n);
void print_separator(void);
void print_newl(void);

int main(void)
{
    int height = get_height();

    for (int i = 1; i <= height; i++)
    {
        print_whitespace(height - i);
        print_hash(i);
        print_separator();
        print_hash(i);
        print_newl();
    }

    return 0;
}

int get_height(void)
{
    int c = 0;
    do
    {
        printf("Height: ");
        char line[255] = "";
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &c);
    }
    while (c < 1 || c > 8);
    return c;
}

void print_whitespace(int n)
{
    for (int i = 0; i < n; i++)
        printf(" ");
    return;
}

void print_hash(int n)
{
    for (int i = 0; i < n; i++)
        printf("#");
    return;
}

void print_separator(void)
{
    printf("  ");
    return;
}

void print_newl(void)
{
    printf("\n");
    return;
}

