#include <iostream>

int WordsCnt(char *a)
{
    int i, cnt = 0;
    bool prevIsSpace = true;
    for (i = 0; a[i] != '\0'; ++i)
    {
        if (a[i] == ' ' && prevIsSpace == false)
            prevIsSpace = true;
        else if (a[i] != ' ' && prevIsSpace == true)
        {
            cnt++;
            prevIsSpace = false;
        }
    }
    return cnt;
}

int WordsCntAbdul(char *a)
{
    int i, cnt = 0;
    for (i = 0; a[i] != '\0'; ++i)
    {
        if (i > 0 && a[i] == ' ' && a[i - 1] != ' ')
            cnt++;
    }
    return cnt;
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
    char *c = " ";
    PrintString(c);
    std::cout << "words number = " << WordsCntAbdul(c) << std::endl;

    char *c2 = "a   aaaa a";
    PrintString(c2);
    std::cout << "words number = " << WordsCntAbdul(c2) << std::endl;

    return 0;
}