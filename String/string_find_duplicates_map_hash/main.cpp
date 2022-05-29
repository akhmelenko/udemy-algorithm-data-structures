#include <iostream>
#include <string>
#include <map>

void PrintMap(std::map<char, int> &m)
{
    for (const auto elem : m)
        std::cout << elem.first << " : " << elem.second << std::endl;
    std::cout << std::endl;
}

void FindDuplicates(char *s)
{
    std::map<char, int> map;
    for (int i = 0; s[i] != '\0'; ++i)
    {
        if (map.find(s[i]) == map.end())
            map.insert({s[i], 1});
        else
            map.at(s[i])++;
    }
    PrintMap(map);
}

int main()
{
    printf("MAIN START\n\r");

    char s1[] = "aaabcbaaa";
    FindDuplicates(s1);

    return 0;
}