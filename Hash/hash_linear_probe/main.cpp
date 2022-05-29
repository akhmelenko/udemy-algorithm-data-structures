#include <iostream>
#include <utility>

class HashLinearProbe
{
private:
    std::pair<bool, int> h[10];

public:
    HashLinearProbe()
    {
        for (int i = 0; i < 10; i++)
            h[i].first = false;
    }

    bool Insert(int val)
    {
        int ind = val % 10;
        int shift = 0;
        // search free space
        while (shift < 10 && h[(ind + shift) % 10].first == true)
            shift++;
        if (shift >= 10)
            return false;
        h[(ind + shift) % 10].first = true;
        h[(ind + shift) % 10].second = val;
        return true;
    }

    bool Search(int val)
    {
        int ind = val % 10;
        int shift = 0;
        while (shift < 10 && h[(ind + shift) % 10].first == true)
        {
            if (h[(ind + shift) % 10].second == val)
                return true;
            shift++;
        }
        return false;
    }

    void CheckAndReplaceRec(int freed)
    {
        // check next to fried
        if (h[(freed + 1) % 10].first == false || (h[(freed + 1) % 10].second % 10) == (freed + 1) % 10)
            return;
        // shift next to freed
        h[freed].first = true;
        h[freed].second = h[(freed + 1) % 10].second;
        h[(freed + 1) % 10].first = false;
        CheckAndReplaceRec((freed + 1) % 10);
    }

    bool Delete(int val)
    {
        int ind = val % 10;
        int shift = 0;
        while (shift < 10 && h[(ind + shift) % 10].first == true)
        {
            if (h[(ind + shift) % 10].second == val)
            {
                // deleting
                h[(ind + shift) % 10].first = false;
                CheckAndReplaceRec((ind + shift) % 10);
                return true;
            }
            shift++;
        }
        return false;
    }
};

class HashQuadraticProbe
{
private:
    std::pair<bool, int> h[10];

public:
    HashQuadraticProbe()
    {
        for (int i = 0; i < 10; i++)
            h[i].first = false;
    }

    bool Insert(int val)
    {
        int ind = val % 10;
        int shift = 0;
        // search free space
        while (shift < 10 && h[(ind + shift * shift) % 10].first == true)
            shift++;
        if (shift >= 10)
            return false;
        h[(ind + shift * shift) % 10].first = true;
        h[(ind + shift * shift) % 10].second = val;
        return true;
    }

    bool Search(int val)
    {
        int ind = val % 10;
        int shift = 0;
        while (shift < 10 && h[(ind + shift * shift) % 10].first == true)
        {
            if (h[(ind + shift * shift) % 10].second == val)
                return true;
            shift++;
        }
        return false;
    }

    // TODO - not sure
    void CheckAndReplaceRec(int freed)
    {
        // check next to fried
        if (h[(freed + 1) % 10].first == false || (h[(freed + 1) % 10].second % 10) == (freed + 1) % 10)
            return;
        // shift next to freed
        h[freed].first = true;
        h[freed].second = h[(freed + 1) % 10].second;
        h[(freed + 1) % 10].first = false;
        CheckAndReplaceRec((freed + 1) % 10);
    }

    bool Delete(int val)
    {
        int ind = val % 10;
        int shift = 0;
        while (shift < 10 && h[(ind + shift * shift) % 10].first == true)
        {
            if (h[(ind + shift * shift) % 10].second == val)
            {
                // deleting
                h[(ind + shift * shift) % 10].first = false;
                CheckAndReplaceRec((ind + shift * shift) % 10);
                return true;
            }
            shift++;
        }
        return false;
    }
};

int main()
{
    HashLinearProbe h;
    h.Insert(15);
    h.Insert(48);
    h.Insert(30);
    h.Insert(81);
    h.Insert(57);
    h.Insert(72);
    h.Insert(78);
    h.Insert(42);
    h.Insert(18);

    // h.Display();

    std::cout << " search 78 = " << h.Search(78) << "\n";
    std::cout << " search 16 = " << h.Search(16) << "\n";
    std::cout << " search 14 = " << h.Search(14) << "\n";

    h.Delete(72);
    std::cout << " search 18 = " << h.Search(18) << "\n";
    // std::cout << " search 38 = " << h.Search(38) << "\n";
    // std::cout << " search 19 = " << h.Search(19) << "\n";

    // std::cout << "delete 11 = " << h.Delete(11) << "\n";
    // std::cout << "delete 48 = " << h.Delete(48) << "\n";
    // std::cout << "delete 18 = " << h.Delete(18) << "\n";
    // h.Display();

    return 0;
}