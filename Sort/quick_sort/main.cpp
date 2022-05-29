#include <iostream>
#include <vector>

void Swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void SetPartitionRec(std::vector<int> &v, int start, int end)
{
    if (start >= end)
        return;
    int pivot = v[start];
    int i = start;
    int j = end;
    while (i < j)
    {
        while (v[i] <= pivot)
            i++;
        while (v[j] > pivot)
            j--;
        if (i < j)
            Swap(v[i], v[j]);
    }
    Swap(v[start], v[j]);
    SetPartitionRec(v, start, j - 1);
    SetPartitionRec(v, j + 1, end);
}

void QuickSort(std::vector<int> &v)
{
    SetPartitionRec(v, 0, v.size() - 1);
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
    QuickSort(v);
    Display(v);

    return 0;
}