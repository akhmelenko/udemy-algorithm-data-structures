#include <iostream>

#define MAX_STRING_LENGTH 10

void Permutation(char *str, int k)
{
    static int avail[MAX_STRING_LENGTH] = {0};
    static char res[MAX_STRING_LENGTH];
    if (str[k] == '\0')
    {
        res[k] = '\0';
        std::cout << res << std::endl;
    }
    else
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (avail[i] == 0)
            {
                res[k] = str[i];
                avail[i] = 1;
                Permutation(str, k + 1);
                avail[i] = 0;
            }
        }
    }
}

void Swap(char *str, int idx0, int idx1)
{
    char temp = str[idx0];
    str[idx0] = str[idx1];
    str[idx1] = temp;
}

void PermutationSwap(char *str, int l, int h) // l - low, h - high
{
    if (l == h)
    {
        std::cout << str << std::endl;
    }
    else
    {
        for (int i = l; i <= h; i++)
        {
            Swap(str, l, i);
            PermutationSwap(str, l + 1, h);
            Swap(str, l, i);
        }
    }
}

int main()
{
    printf("MAIN START\n\r");
    char c[] = "abc";
    PermutationSwap(c, 0, 2);

    return 0;
}