#include <iostream>
#include <string>

int CompareStrings(char *a, char *b)
{
    int i;
    for (i = 0; a[i] != '\0' && b[i] != '\0'; ++i)
    {
        if (a[i] != b[i])
            break;
    }
    if (a[i] < b[i])
        return -1;
    else if (a[i] > b[i])
        return 1;
    else
    {
        if (a[i] == '\0' && b[i] != '\0')
            return -1;
        else if (a[i] != '\0' && b[i] == '\0')
            return 1;
        else
            return 0;
    }
}

int main()
{
    printf("MAIN START\n\r");

    std::string str1 = "aant";
    std::string str2 = "anton";
    std::cout << str1.compare(str2) << std::endl;

    char c1[] = "aant";
    char c2[] = "anton";
    std::cout << CompareStrings(c1, c2) << std::endl;

    return 0;
}