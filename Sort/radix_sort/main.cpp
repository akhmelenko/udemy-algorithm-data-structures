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

struct Node
{
    int val;
    Node *next;
};

Node *InsertToLL(Node *root, int val)
{
    if (!root)
    {
        root = new Node;
        root->val = val;
        root->next = nullptr;
        return root;
    }
    Node *node = root;
    // find nullptr node
    while (node->next)
        node = node->next;
    node->next = new Node;
    node->next->val = val;
    node->next->next = nullptr;
    return root;
}

void DeleteLLRec(Node *node)
{
    if (!node)
        return;
    DeleteLLRec(node->next);
    delete node;
}

void DeleteLL(Node *head)
{
    DeleteLLRec(head);
    int a = (size_t)head;
}

void RadixSort(std::vector<int> &v)
{
    if (!v.size() || v.size() == 1)
        return;
    // find the max element
    int max = INT_MIN;
    for (auto elem : v)
    {
        if (elem > max)
            max = elem;
    }
    int decimal = 1;
    Node *table[10] = {nullptr};
    // increase decimal cycle
    while (max > decimal / 10)
    {
        // fill table cycle
        for (auto elem : v)
        {
            int tableNum = (elem / decimal) % 10;
            table[tableNum] = InsertToLL(table[tableNum], elem);
        }
        // rewrite vector
        v.clear();
        for (int i = 0; i < 10; i++)
        {
            Node *node = table[i];
            while (node)
            {
                v.push_back(node->val);
                node = node->next;
            }
        }
        // clear table
        for (int i = 0; i < 10; i++)
        {
            if (table[i])
            {
                DeleteLL(table[i]);
                table[i] = nullptr;
            }
        }
        // next decimal
        decimal *= 10;
    }
}

int main()
{
    std::vector<int> v{815, 32, 3, 0, 3, 8150, 3, 5, 9};
    Display(v);
    RadixSort(v);
    Display(v);

    return 0;
}