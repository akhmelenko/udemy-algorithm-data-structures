#include <iostream>
#include <cstring>
#include <map>
#include <math.h>

class Poly
{
    std::map<int, int> m; // (exp, coef)
public:
    Poly() {}
    void SetMember(const int &exp, const int &coef)
    {
        if (coef != 0)
            m[exp] = coef; // change old or add new element
    }
    int GetCoeff(const int &exp)
    {
        if (m.find(exp) == m.end())
            return 0;
        else
            return m[exp];
    }
    friend std::ostream &operator<<(std::ostream &os, const Poly &p);
    Poly operator+(const Poly &rhs) const
    {
        Poly *res = new Poly;
        auto itl = m.begin();
        auto itr = rhs.m.begin();
        while (itl != m.end() && itr != rhs.m.end())
        {
            if (itl->first == itr->first)
            {
                if (itl->second + itr->second != 0)
                    res->m[itl->first] = itl->second + itr->second;
                itl++;
                itr++;
            }
            else if (itl->first < itr->first)
            {
                res->m[itl->first] = itl->second;
                itl++;
            }
            else
            {
                res->m[itr->first] = itr->second;
                itr++;
            }
        }
        return *res;
    }
    Poly operator*(const Poly &rhs) const
    {
        Poly *res = new Poly;
        for (const auto meml : m)
        {
            for (const auto memr : rhs.m)
            {
                int coef = meml.second * memr.second;
                int exp = meml.first + memr.first;
                auto it = res->m.find(exp);
                if (it != res->m.end())
                {
                    if (res->m.at(exp) + coef == 0)
                    {
                        res->m.erase(it);
                        continue;
                    }
                    res->m.at(exp) += coef;
                }
                else
                    res->m[exp] = coef;
            }
        }
        return *res;
    }
    int Eval(const int &x)
    {
        int sum = 0;
        for (const auto &member : m)
            sum += member.second * pow(x, member.first);
        return sum;
    }
};

std::ostream &operator<<(std::ostream &os, const Poly &p)
{
    auto it = p.m.rbegin();
    while (it != p.m.rend())
    {
        os << it->second << "x^" << it->first << " ";
        it++;
    }
    return os;
}

int main()
{
    printf("MAIN START\n\r");
    Poly p1;
    p1.SetMember(3, 4);
    p1.SetMember(2, 3);
    p1.SetMember(1, 2);
    p1.SetMember(0, 1);
    std::cout << p1 << std::endl;

    Poly p2;
    p2.SetMember(3, 2);
    p2.SetMember(2, 1);
    p2.SetMember(1, 0);
    p2.SetMember(0, -1);
    std::cout << p2 << std::endl;
    std::cout << "x=2 p2=" << p2.Eval(2) << std::endl;

    Poly p3 = p1 + p2;
    std::cout << p3 << std::endl;
    std::cout << "x=2 p3=" << p3.Eval(2) << std::endl;

    Poly p4 = p1 * p2;
    std::cout << p4 << std::endl;
    std::cout << "x=2 p4=" << p4.Eval(2) << std::endl;

    return 0;
}