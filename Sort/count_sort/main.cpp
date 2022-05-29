#include <iostream>
#include <vector>

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void Display(std::vector<int> &v)
{
    std::cout << "[ ";
    for (auto elem : v)
        std::cout << elem << " ";
    std::cout << "]\n";
}

void CountSort(std::vector<int> &v)
{
    if (!v.size() || v.size() == 1)
        return;
    // find the max element
    int max = INT_MIN;
    int min = INT_MAX;
    for (auto elem : v)
    {
        if (elem > max)
            max = elem;
        if (elem < min)
            min = elem;
    }
    // fill the hash table
    int size;
    size = max - min + 1;
    int hash[size] = {0};
    for (auto elem : v)
        hash[elem - min]++;
    // rewrite vector
    v.clear();
    for (int i = 0; i < sizeof(hash) / sizeof(hash[0]); i++)
    {
        while (hash[i] > 0)
        {
            v.push_back(i + min);
            hash[i]--;
        }
    }
}

int main()
{
    std::vector<int> v{-8, 3, 3, 0, 3, 8, -3, 5, 9};
    Display(v);
    CountSort(v);
    Display(v);

    return 0;
}