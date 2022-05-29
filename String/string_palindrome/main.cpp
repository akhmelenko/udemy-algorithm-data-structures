#include <iostream>
#include <string>

bool IsPalindrome(char *a)
{
    int i, j;
    for (j = 0; a[j] != '\0'; j++)
    {
    }
    j--;
    for (i = 0; i < j; ++i, --j)
    {
        if (a[i] != a[j])
            return false;
    }
    return true;
}

int main()
{
    printf("MAIN START\n\r");

    char c1[] = "aaabcbaaa";
    char c2[] = "anton";
    std::cout << c1 << "is palindrome - " << IsPalindrome(c1) << std::endl;
    std::cout << c2 << "is palindrome - " << IsPalindrome(c2) << std::endl;

    return 0;
}