#include <iostream>
#include <string>

bool IsAnagram(char *a, char *b)
{
    // check length
    int i;
    for (i = 0; a[i] != '\0' || b[i] != '\0'; ++i)
    {
    }
    if (a[i] != '\0' || b[i] != '\0')
        return false;

    int h[26] = {0};
    // increment hash table from a
    for (i = 0; a[i] != '\0'; ++i)
        h[a[i] - 'a']++;
    // decrement hash table from b and check hash
    for (i = 0; b[i] != '\0'; ++i)
    {
        h[b[i] - 'a']--;
        if (h[b[i] - 'a'] < 0)
            return false;
    }
    return true;
}

int main()
{
    printf("MAIN START\n\r");

    char c1[] = "ddecimall";
    char c2[] = "meddicall";
    std::cout << c1 << " and " << c2 << " are anagram - " << IsAnagram(c1, c2) << std::endl;

    return 0;
}