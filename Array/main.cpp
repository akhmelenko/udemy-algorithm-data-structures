#include <iostream>
#include <cstdarg>

template <typename T, int N>
class Array
{
    T *a;
    int size;

public:
    Array()
    {
        a = new T[N];
        size = N;
    }
    Array(int num, ...)
        : Array()
    {
        va_list valist;
        va_start(valist, num);
        for (int i = 0; i < num && i < N; i++)
        {
            //access all the arguments assigned to valist
            a[i] = va_arg(valist, T);
        }
        //clean memory reserved for valist
        va_end(valist);
    }
    ~Array()
    {
        delete[] a;
    }
    int Size()
    {
        return size;
    }
    void Display()
    {
        std::cout << "[ ";
        for (int i = 0; i < N; ++i)
            std::cout << a[i] << " ";
        std::cout << "]" << std::endl;
    }
    void Set(int idx, T x)
    {
        if (idx >= 0 && idx < N)
            a[idx] = x;
    }
    T Get(int idx)
    {
        return a[idx];
    }
    void Fill(T value)
    {
        for (int i = 0; i < N; ++i)
            a[i] = value;
    }
    void Swap(int idx0, int idx1)
    {
        T temp = a[idx0];
        a[idx0] = a[idx1];
        a[idx1] = temp;
    }
    int LinearSearch(T key)
    {
        for (int i = 0; i < N; ++i)
        {
            if (a[i] == key)
                return i;
        }
        return -1;
    }
    // BinarySearch - work only in sorted array
    int BinarySearch(T key)
    {
        int l, mid, h;
        l = 0;
        h = N - 1;
        while (l <= h)
        {
            mid = (h + l) / 2;
            if (a[mid] == key)
                return mid;
            else if (a[mid] > key)
                h = mid - 1;
            else
                l = mid + 1;
        }
        return -1;
    }
    void Reverse()
    {
        T temp;
        for (int i = 0, j = N - 1; i < j; ++i, --j)
        {
            Swap(i, j);
        }
    }
    bool IsSorted()
    {
        for (int i = 0; i < N - 1; ++i)
            if (a[i] > a[i + 1])
                return false;
        return true;
    }
    void RearangeBySign()
    {
        for (int i = 0, j = N - 1; i < j; ++i, --j)
        {
            while (a[i] < 0)
                i++;
            while (a[j] >= 0)
                j--;
            Swap(i, j);
        }
    }
};

int main()
{
    printf("MAIN START\n\r");
    Array<int, 3> ar;
    ar.Display();
    ar.Set(0, 10);
    ar.Set(1, 20);
    ar.Set(2, 30);
    ar.Display();
    ar.Swap(0, 2);
    ar.Display();
    ar.Swap(0, 2);
    std::cout << "ar[2] = " << ar.Get(2) << std::endl;
    std::cout << "key = 10, index = " << ar.LinearSearch(10) << std::endl;
    std::cout << "key = 40, index = " << ar.LinearSearch(40) << std::endl;
    std::cout << "key = 10, index = " << ar.BinarySearch(10) << std::endl;
    std::cout << "key = 40, index = " << ar.BinarySearch(40) << std::endl;

    Array<int, 3> ar2(3, 1, 2, 3);
    ar2.Display();
    std::cout << "Is sorted = " << ar2.IsSorted() << std::endl;
    ar2.Reverse();
    ar2.Display();
    std::cout << "Is sorted = " << ar2.IsSorted() << std::endl;

    Array<int, 4> ar3(4, -1, 5, 8, -9);
    ar3.Display();
    ar3.RearangeBySign();
    ar3.Display();

    return 0;
}