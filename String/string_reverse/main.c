#include <stdio.h>

char *ReverseString(char *a)
{
    char temp;
    int i, j;
    for (j = 0; a[j] != '\0'; ++j)
    {
    }
    j--;
    for (i = 0; i < j; i++, j--)
    {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    return a;
}

void PrintString(char *c)
{
    printf("string = ");
    for (int i = 0; c[i] != '\0'; ++i)
        printf("%c", c[i]);
    printf("\n");
}

int main()
{
    printf("MAIN START\n\r");
    char c[] = "reverse me";
    PrintString(c);
    char *r = ReverseString(c);
    // PrintString(r);
    printf("%s\n", r);

    char c2[] = "aAzaZ";
    printf("%s\n", c2);
    // PrintString(c2);
    // PrintString(ReverseString(c2));
    printf("%s\n", ReverseString(c2));

    return 0;
}