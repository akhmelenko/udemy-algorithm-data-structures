#include <iostream>

bool IsValid(char *a)
{
    for (int i = 0; a[i] != '\0'; ++i)
    {
        if (!(a[i] >= 'A' && a[i] <= 'Z' || a[i] >= 'a' && a[i] <= 'z'))
            return false;
    }
    return true;
}

void PrintString(char *c)
{
    std::cout << "string = ";
    for (int i = 0; c[i] != '\0'; ++i)
        std::cout << c[i];
    std::cout << std::endl;
}

int main()
{
    printf("MAIN START\n\r");
    char *c = " abZzA";
    PrintString(c);
    std::cout << "words number = " << IsValid(c) << std::endl;

    char *c2 = "aAzaaaaaZ";
    PrintString(c2);
    std::cout << "words number = " << IsValid(c2) << std::endl;

    return 0;
}