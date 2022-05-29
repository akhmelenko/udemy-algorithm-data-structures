#include <iostream>
#include <cstring>
#include <vector>

struct Element
{
    int i;
    int j;
    int x;
};
class Sparse
{
    int iSize;
    int jSize;
    std::vector<Element> e;

public:
    Sparse(int iSize, int jSize) : iSize{iSize}, jSize{jSize} {}
    ~Sparse() {}
    friend std::ostream &operator<<(std::ostream &os, Sparse &s);
    int GetElement(int i, int j)
    {
        for (const auto &elem : e)
        {
            if (elem.i == i && elem.j == j)
                return elem.x;
        }
        return 0;
    }
    bool SetElement(int i, int j, int x)
    {
        if (i >= iSize || j >= jSize)
            return false;
        // check is free location
        for (auto &elem : e)
        {
            // already in vector e
            if (elem.i == i && elem.j == j)
            {
                elem.x = x;
                return true;
            }
            // not in vector, add new element
            if (elem.i == i && elem.j > j || elem.i > i)
            {
                Element temp = {i, j, x};
                int pos = &elem - &e[0]; // pos contains the position in the vector
                e.insert(e.begin() + pos, temp);
                return true;
            }
        }
        Element temp = {i, j, x};
        e.push_back(temp);
        return true;
    }
    Sparse operator+(const Sparse &rhs)
    {
        Sparse *res = new Sparse(iSize, jSize);
        if (iSize != rhs.iSize || jSize != rhs.jSize)
            return *res;
        int k = 0;
        int l = 0;
        Element r;
        while (k < e.size() && l < rhs.e.size())
        {
            if (e[k].i == rhs.e[l].i && e[k].j == rhs.e[l].j)
            {
                r = e[k++];
                r.x += rhs.e[l++].x;
                res->e.push_back(r);
            }
            else if (e[k].i == rhs.e[l].i && e[k].j < rhs.e[l].j || e[k].i < rhs.e[l].i)
            {
                r = e[k++];
                res->e.push_back(r);
            }
            else if (e[k].i == rhs.e[l].i && e[k].j > rhs.e[l].j || e[k].i > rhs.e[l].i)
            {
                r = rhs.e[l++];
                res->e.push_back(r);
            }
        }
        while (k < e.size())
        {
            r = e[k++];
            res->e.push_back(r);
            return *res;
        }
        while (l < rhs.e.size())
        {
            r = rhs.e[l++];
            res->e.push_back(r);
        }
        return *res;
    }
};

std::ostream &operator<<(std::ostream &os, Sparse &s)
{
    for (int i = 0; i < s.iSize; i++)
    {
        for (int j = 0; j < s.jSize; j++)
            os << s.GetElement(i, j) << " ";
        os << std::endl;
    }
    return os;
}

int main()
{
    printf("MAIN START\n\r");
    Sparse s1(3, 3);
    s1.SetElement(1, 1, 3);
    s1.SetElement(1, 0, 4);
    s1.SetElement(0, 0, 5);
    std::cout << "s1= " << std::endl
              << s1 << std::endl;

    Sparse s2(3, 3);
    s2.SetElement(2, 1, 3);
    s2.SetElement(0, 1, 4);
    s2.SetElement(0, 0, 5);
    std::cout << "s2= " << std::endl
              << s2 << std::endl;

    Sparse s3(3, 3);
    s3 = s1 + s2;
    std::cout << "s3= " << std::endl
              << s3 << std::endl;

    return 0;
}