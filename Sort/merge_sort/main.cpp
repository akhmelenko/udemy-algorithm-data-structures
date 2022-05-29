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

void MergeTwoSorted(std::vector<int> &v, int start, int mid, int end)
{
    std::vector<int> res;
    if (!end || !(end - mid) || !(mid - start) || mid >= v.size())
        return;
    int i = start;
    int j = mid;
    while (i < mid && j < end)
    {
        if (v[i] <= v[j])
        {
            res.push_back(v[i]);
            i++;
        }
        else
        {
            res.push_back(v[j]);
            j++;
        }
    }
    // copy rest of v1
    while (i < mid)
    {
        res.push_back(v[i]);
        i++;
    }
    // copy rest of v2
    while (j < end)
    {
        res.push_back(v[j]);
        j++;
    }
    std::copy(res.begin(), res.end(), v.begin() + start);
    return;
}

void SortByMergeIter(std::vector<int> &v)
{
    if (!v.size() || v.size() == 1)
        return;
    // step increase
    for (int step = 2; step / 2 < v.size(); step <<= 1)
    {
        // merge with current step
        for (int low = 0, mid = step / 2; mid <= v.size(); mid += step, low += step)
        {
            int hi = low + step;
            if (hi > v.size())
                hi = v.size();
            MergeTwoSorted(v, low, mid, hi);
            int a = hi;
        }
    }
}

void SortByMergeRec(std::vector<int> &v, int start, int mid, int end)
{
    if (!v.size() || v.size() == 1 || mid >= end || mid <= start || mid > v.size() || end > v.size())
        return;
    SortByMergeRec(v, start, (mid + start) / 2, mid);
    SortByMergeRec(v, mid, (end + mid) / 2, end);
    MergeTwoSorted(v, start, mid, end);
}

void SortByMergeRecMain(std::vector<int> &v)
{
    SortByMergeRec(v, 0, v.size() / 2, v.size());
}

int main()
{
    std::vector<int> v{1, 3, 11, 19, 24, 32, 35, 37, 11, 16, 23, 30, 33, 38, 42, 45};
    Display(v);
    MergeTwoSorted(v, 0, 8, v.size());
    Display(v);

    std::cout << " Iterative megre sort\n";
    std::vector<int> v2{16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Display(v2);
    SortByMergeIter(v2);
    Display(v2);

    std::cout << " Iterative recursive sort\n";
    std::vector<int> v3{13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Display(v3);
    SortByMergeRecMain(v3);
    Display(v3);

    std::vector<int> v4{1, 3, 11, 19, 24, 32, 35, 37, 11, 16, 23, 30, 33, 38, 42, 45};
    Display(v4);
    SortByMergeRecMain(v4);
    Display(v4);

    // std::vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7, 99};
    // std::vector<int> a = {44, 42};

    // std::copy(std::begin(a), std::end(a), std::begin(input) + 3);
    // Display(input);

    return 0;
}