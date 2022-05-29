#include <iostream>
#include <vector>

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void BubbleSort(std::vector<int> &v)
{
    if (!v.size())
        return;
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
                Swap(v[j], v[j + 1]);
        }
    }
}

void BubbleSortAdaptive(std::vector<int> &v)
{
    if (!v.size())
        return;
    bool swaped = false;
    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                Swap(v[j], v[j + 1]);
                swaped = true;
            }
        }
        if (!swaped)
            return;
    }
}

void Display(std::vector<int> &v)
{
    std::cout << "[ ";
    for (auto elem : v)
        std::cout << elem << " ";
    std::cout << "]\n";
}

int main()
{
    std::vector<int> v{7, 5, 8, 1, 9, 4};
    Display(v);
    // BubbleSort(v);
    BubbleSortAdaptive(v);
    Display(v);

    return 0;
}