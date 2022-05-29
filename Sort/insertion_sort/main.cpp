#include <iostream>
#include <vector>

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void InsertionSort(std::vector<int> &v)
{
    if (!v.size() || v.size() == 1)
        return;
    for (int i = 1; i < v.size(); i++)
    {
        int current = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > current)
        {
            // shift sorted j elements left by 1
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = current;
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
    InsertionSort(v);
    Display(v);

    return 0;
}