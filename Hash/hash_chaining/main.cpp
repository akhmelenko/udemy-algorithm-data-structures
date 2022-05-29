#include <iostream>

struct Node
{
    int val;
    Node *next;
};

// use hash function h(x) = x % 10 (also possible to use (x / 10) % 10; (x/100) % 10,...)
class HashChaining
{
private:
    Node *h[10];

public:
    HashChaining()
    {
        for (int i = 0; i < 10; i++)
            h[i] = nullptr;
    }
    ~HashChaining()
    {
        Clear();
    }

    void Clear()
    {
        for (int i = 0; i < 10; i++)
        {
            Node *node = h[i];
            Node *prev;
            while (node)
            {
                prev = node;
                node = node->next;
                delete prev;
            }
            h[i] = nullptr;
        }
    }

    void Insert(int val)
    {
        Node *newNode = new Node;
        newNode->val = val;
        if (!h[val % 10])
        {
            newNode->next = nullptr;
            h[val % 10] = newNode;
            return;
        }
        Node *node = h[val % 10];
        Node *prev = node;
        while (node)
        {
            if (val <= node->val)
            {
                newNode->next = node;
                if (node = h[val % 10]) // first node in LL
                    h[val % 10] = newNode;
                else
                    prev->next = newNode;
                return;
            }
            prev = node;
            node = node->next;
        }
        // add as last node in LL
        prev->next = newNode;
        newNode->next = nullptr;
    }

    bool Search(int val)
    {
        Node *node = h[val % 10];
        while (node)
        {
            if (val == node->val)
                return true;
            node = node->next;
        }
        return false;
    }

    void Swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    void Display()
    {
        std::cout << "[ ";
        for (int i = 0; i < 10; i++)
        {
            if (h[i])
            {
                Node *node = h[i];
                while (node)
                {
                    std::cout << node->val << " ";
                    node = node->next;
                }
            }
        }
        std::cout << "]\n";
    }

    bool Delete(int val)
    {
        Node *node = h[val % 10];
        Node *prev = node;
        while (node)
        {
            if (val == node->val)
            {
                if (node == h[val % 10]) // first
                {
                    if (!node->next) // single
                        h[val % 10] = nullptr;
                    else
                        h[val % 10] = node->next;
                }
                else
                    prev->next = node->next;
                delete node;
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }
};

int main()
{
    {
        HashChaining h;
        h.Insert(15);
        h.Insert(48);
        h.Insert(30);
        h.Insert(81);
        h.Insert(57);
        h.Insert(72);
        h.Insert(78);
        h.Insert(42);
        h.Insert(18);
        h.Display();

        std::cout << " search 78 = " << h.Search(78) << "\n";
        std::cout << " search 38 = " << h.Search(38) << "\n";
        std::cout << " search 19 = " << h.Search(19) << "\n";

        std::cout << "delete 11 = " << h.Delete(11) << "\n";
        std::cout << "delete 48 = " << h.Delete(48) << "\n";
        std::cout << "delete 18 = " << h.Delete(18) << "\n";
        h.Display();
    }

    return 0;
}