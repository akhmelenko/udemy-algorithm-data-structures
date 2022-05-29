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

void ShellSort(std::vector<int> &v)
{
    if (!v.size() || v.size() == 1)
        return;
    int gap = v.size() / 2;
    // gap reduce cycle
    while (gap >= 1)
    {
        // vector traverse cycle
        for (int i = 0; i + gap < v.size(); i++)
        {
            int j = i + gap;
            while ((j - gap) >= 0 && v[j - gap] > v[j])
            {
                Swap(v[j], v[j - gap]);
                j = j - gap;
            }
        }
        gap /= 2;
    }
}

int main()
{
    std::vector<int> v{815, 32, 3, 0, 3, 8150, 3, 5, 9};
    Display(v);
    ShellSort(v);
    Display(v);

    std::vector<int> v2{9, 5, 16, 8, 13, 6, 12, 10, 4, 2, 3};
    Display(v2);
    ShellSort(v2);
    Display(v2);

    return 0;
}