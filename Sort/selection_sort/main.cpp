#include <iostream>
#include <vector>

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SelectionSort(std::vector<int> &v)
{
    if (!v.size() || v.size() == 1)
        return;
    for (int i = 0; i < v.size(); i++)
    {
        int curMinInd = i;
        for (int j = i; j < v.size(); j++)
        {
            if (v[j] < v[curMinInd])
                curMinInd = j;
        }
        Swap(v[i], v[curMinInd]);
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
    std::vector<int> v{8, 6, 3, 10, 9, 4, 12, 5, 2, 7};
    Display(v);
    // BubbleSort(v);
    SelectionSort(v);
    Display(v);

    return 0;
}