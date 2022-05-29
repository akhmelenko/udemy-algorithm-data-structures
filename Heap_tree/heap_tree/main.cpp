#include <iostream>

class MaxHeap
{
private:
    int *h;
    int size;
    int sizeSorted;
    int capacity;

private:
    void swap(int ind0, int ind1)
    {
        int temp = h[ind0];
        h[ind0] = h[ind1];
        h[ind1] = temp;
    }

public:
    MaxHeap(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        h = new int[capacity];
    }

    bool AddFromArray(int arr[], int _size)
    {
        if (_size > capacity)
            return false;
        for (int i = 0; i < _size; i++)
        {
            Insert(arr[i]);
        }
        return true;
    }

    bool Insert(int val)
    {
        if (size == capacity)
        {
            std::cout << "overflow\n";
            return false;
        }
        int temp = val;
        int i = size++;
        while (i && temp > h[i / 2])
        {
            h[i] = h[i / 2];
            i /= 2;
        }
        h[i] = temp;
        return true;
    }

    bool DeleteRoot()
    {
        if (!size)
            // empty tree
            return false;
        if (size == 1)
        {
            size = 0;
            return true;
        }
        h[0] = h[size - 1];
        size--;
        int i = 0;
        int j = (i + 1) * 2 - 1;
        while (j < size)
        {
            if ((j + 1) < size && h[j] < h[j + 1])
                j++;
            if (h[i] < h[j])
                swap(i, j);
            i = j;
            j = (i + 1) * 2 - 1;
        }
        return true;
    }

    void Sort()
    {
        sizeSorted = size;
        int i = size;
        while (i--)
        {
            int root = h[0];
            DeleteRoot();
            // put root to end
            h[size] = root;
        }
    }

    void Display()
    {
        std::cout << "[ ";
        for (int i = 0; i < size; i++)
            std::cout << h[i] << " ";
        std::cout << "]\n";
    }

    void DisplaySorted()
    {
        std::cout << "[ ";
        for (int i = 0; i < sizeSorted; i++)
            std::cout << h[i] << " ";
        std::cout << "]\n";
    }
};

int main()
{
    MaxHeap h(15);
    h.Insert(5);
    h.Insert(10);
    h.Insert(15);
    h.Insert(25);
    h.Insert(30);
    h.Display();
    int arr[] = {50, 7, 28};
    h.AddFromArray(arr, sizeof(arr) / sizeof(arr[0]));
    h.Display();
    h.DeleteRoot();
    h.Display();
    h.Sort();
    h.DisplaySorted();
    int arr2[] = {5, 10, 30, 20, 35, 40, 15};
    MaxHeap h2(15);
    h2.Heapify(arr2, sizeof(arr2) / sizeof(arr2[0]));
    h2.Display();

    return 0;
}