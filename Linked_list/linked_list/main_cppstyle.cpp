#include <iostream>

struct Node
{
    int data;
    Node *next;
};

void _PrintRecursive(Node *node)
{
    if (!node)
    {
        std::cout << std::endl;
        return;
    }
    std::cout << node->data << " ";
    _PrintRecursive(node->next);
}

void _PrintCircularRecursive(Node *head, Node *node)
{
    static bool flag = false;
    if (node == head && flag)
    {
        std::cout << std::endl;
        return;
    }
    flag = true;
    std::cout << node->data << " ";
    _PrintCircularRecursive(head, node->next);
}

int _CountRecursive(struct Node *node)
{
    if (!node)
        return 0;
    return _CountRecursive(node->next) + 1;
}

int _SumRecursive(Node *node)
{
    if (!node)
        return 0;
    return _SumRecursive(node->next) + node->data;
}

Node *_SearchRecursive(Node *node, int &key)
{
    if (!node)
        return NULL;
    if (node->data == key)
        return node;
    return _SearchRecursive(node->next, key);
}

Node *_ReverseByMoveLinksRecursive(struct Node *prev, struct Node *node)
{
    if (!node)
        return prev;
    // traverse head from last element
    Node *_head = _ReverseByMoveLinksRecursive(node, node->next);
    node->next = prev;
    return _head;
}

int _MaxElementRecursive(Node *node)
{
    if (!node)
        return INT_MIN;
    static int currMax;
    currMax = _MaxElementRecursive(node->next);
    return currMax > node->data ? currMax : node->data;
}

class LinkedList
{
    Node *head = NULL;
    friend std::ostream &operator<<(std::ostream &os, LinkedList &l);

public:
    LinkedList() {}
    LinkedList(int arr[], int size)
    {
        CreateFromArray(arr, size);
    }
    LinkedList(int arr[], int size, bool sorted)
    {
        if (sorted)
            CreateSortedFromArray(arr, size);
        else
            CreateFromArray(arr, size);
    }
    ~LinkedList()
    {
        FreeLinkedList();
    }

    Node *GetHead()
    {
        return head;
    }

    // insert any way (if ind > length) and return head
    void InsertSorted(int data)
    {
        struct Node *node = new struct Node;
        node->data = data;
        // head is NULL
        if (!head)
        {
            node->next = NULL;
            head = node;
            return;
        }
        // data < head->data
        if (data < head->data)
        {
            node->next = head;
            return;
        }
        // data >= head->data
        Node *prev = head;
        while (prev->next)
        {
            if (data < prev->next->data)
            {
                node->next = prev->next;
                prev->next = node;
                return;
            }
            prev = prev->next;
        }
        // data > any element data
        prev->next = node;
        node->next = NULL;
        return;
    }

    // insert any way (if ind > length) and return head
    void Insert(int ind, int data)
    {
        Node *node = new Node;
        node->data = data;
        // head is NULL
        if (!head)
        {
            node->next = NULL;
            head = node;
            return;
        }
        // ind = 0
        if (ind == 0)
        {
            node->next = head;
            head = node;
            return;
        }
        // ind > 0
        int cnt = 1;
        Node *prev = head;
        while (prev->next)
        {
            if (cnt == ind)
            {
                node->next = prev->next;
                prev->next = node;
                return;
            }
            cnt++;
            prev = prev->next;
        }
        // ind > lenght
        prev->next = node;
        node->next = NULL;
        return;
    }

    void CreateSortedFromArray(int *arr, int size)
    {
        if (size < 1 || arr == NULL)
            return;
        for (int i = 0; i < size; i++)
        {
            InsertSorted(arr[i]);
        }
    }

    void *InsertLast(int data)
    {
        Insert(INT_MAX, data);
    }

    void *CreateFromArrayByInsert(int *arr, int size)
    {
        if (size < 1 || arr == NULL)
            return NULL;
        for (int i = 0; i < size; i++)
        {
            InsertLast(arr[i]);
        }
    }

    void *CreateFromArray(int *arr, int size)
    {
        if (size < 1 || arr == NULL)
            return NULL;
        head = new Node;
        Node *node = head;
        node->data = arr[0];
        for (int i = 1; i < size; i++)
        {
            node->next = new Node;
            node = node->next;
            node->data = arr[i];
        }
        node->next = NULL;
    }

    // delete any way (if ind > length, delete last) and return head
    void Delete(int ind)
    {
        // head is NULL
        if (!head)
            return;
        // ind = 0
        if (ind == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return;
        }
        // ind > 0
        int cnt = 1;
        Node *prev = head;
        while (prev->next)
        {
            if (cnt == ind)
            {
                Node *temp = prev->next;
                prev->next = prev->next->next;
                delete temp;
                return;
            }
            // check if prev is before last
            if (!prev->next->next)
            {
                // delete last
                delete prev->next;
                prev->next = NULL;
                return;
            }
            cnt++;
            prev = prev->next;
        }
        return;
    }

    void *DeleteLast()
    {
        Delete(INT_MAX);
    }

    void FreeLinkedList()
    {
        Node *node = head;
        if (!node)
            return;
        while (node)
        {
            Node *prev = node;
            node = node->next;
            delete prev;
        }
        head = NULL;
    }

    Node *SearchRecursive(int &key)
    {
        return _SearchRecursive(head, key);
    }

    Node *Search(int &key)
    {
        struct Node *node = head;
        while (node)
        {
            if (node->data == key)
                return node;
            node = node->next;
        }
        return NULL;
    }

    Node *SearchWithMoveToHead(int &key)
    {
        if (head->data == key)
            return head;
        struct Node *node = head->next;
        struct Node *prev = head;
        while (node)
        {
            if (node->data == key)
            {
                // prev link to next after node
                prev->next = node->next;
                // node link to current first
                node->next = head;
                // change head
                head = node;
                return node;
            }
            prev = node;
            node = node->next;
        }
        return NULL;
    }

    int MaxElementRecursive()
    {
        if (!head)
            return INT_MIN;
        return _MaxElementRecursive(head->next);
    }

    int MaxElement()
    {
        int max = INT_MIN;
        struct Node *node = head;
        while (node)
        {
            if (max < node->data)
                max = node->data;
            node = node->next;
        }
        return max;
    }

    int CountRecursive()
    {
        if (!head)
            return 0;
        return _CountRecursive(head) + 1;
    }

    int Count()
    {
        Node *node = head;
        int cnt = 0;
        while (node)
        {
            cnt++;
            node = node->next;
        }
        return cnt;
    }

    int SumRecursive()
    {
        if (!head)
            return 0;
        return _SumRecursive(head->next) + head->data;
    }

    int Sum()
    {
        Node *node = head;
        int sum = 0;
        while (node)
        {
            sum += node->data;
            node = node->next;
        }
        return sum;
    }

    bool IsSorted()
    {
        if (!head)
            return false;
        // 1 element in list
        if (!head->next)
            return true;
        // >1
        struct Node *node = head;
        while (node->next)
        {
            if (node->data > node->next->data)
                return false;
            node = node->next;
        }
        return true;
    }

    void RemoveDuplicatesFormSorted()
    {
        if (!head)
            return;
        // 1 element in list
        if (!head->next)
            return;
        struct Node *node = head;
        while (node && node->next)
        {
            if (node->data == node->next->data)
            {
                struct Node *temp = node->next;
                node->next = node->next->next;
                delete temp;
            }
            else
                node = node->next;
        }
        return;
    }

    void ReverseByMoveData()
    {
        if (!head)
            return;
        // 1 element in list
        if (!head->next)
            return;
        // create auxilary array
        int *arr = new int[Count()];
        // fill array by data
        struct Node *node = head;
        int i = 0;
        while (node)
        {
            arr[i] = node->data;
            i++;
            node = node->next;
        }
        // fill ll by array data
        node = head;
        i--;
        while (node)
        {
            node->data = arr[i];
            i--;
            node = node->next;
        }
        delete[] arr;
    }

    void ReverseByMoveLinks()
    {
        if (!head)
            return;
        // 1 element in list
        if (!head->next)
            return;
        // > 1
        struct Node *node0 = NULL;
        struct Node *node1 = NULL;
        struct Node *node2 = head;
        while (node2)
        {
            node0 = node1;
            node1 = node2;
            node2 = node2->next;
            node1->next = node0; //!!!
        }
        head = node1;
    }

    void ReverseByMoveLinksRecursive()
    {
        head = _ReverseByMoveLinksRecursive(NULL, head);
    }

    void PrintRecursive()
    {
        if (IsLoop())
            _PrintCircularRecursive(head, head);
        else
            _PrintRecursive(head);
    }

    void Concat(LinkedList &lSecond)
    {
        if (!head)
        {
            head = lSecond.GetHead();
            return;
        }
        // go to the and of first LL
        Node *node = head;
        while (node->next)
            node = node->next;
        // change nullptr to headB
        node->next = lSecond.GetHead();
    }

    void MergeSorted(LinkedList &lSecond)
    {
        if (!head)
        {
            head = lSecond.GetHead();
            return;
        }
        Node *first = head;
        Node *second = lSecond.GetHead();
        // get head
        if (head->data < second->data)
        {
            head = first;
            first = first->next;
        }
        else
        {
            head = second;
            second = second->next;
        }
        // merge
        Node *node = head;
        while (first && second)
        {
            if (first->data < second->data)
            {
                node->next = first;
                first = first->next;
            }
            else
            {
                node->next = second;
                second = second->next;
            }
            node = node->next;
        }
        // concat with remain (if exists)
        if (first)
            node->next = first;
        else
            node->next = second;
    }

    bool IsLoop()
    {
        if (!head)
            return false;
        Node *fast = head;
        Node *slow = head;
        while (fast->next && fast->next->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return true;
        }
        return false;
    }

    bool MakeLoop(int loopStart)
    {
        if (!head)
            return false;
        int cnt = 0;
        Node *node = head;
        Node *loopFirst = NULL;
        while (node->next)
        {
            if (cnt == loopStart)
                loopFirst = node;
            node = node->next;
            cnt++;
        }
        if (loopFirst)
        {
            node->next = loopFirst;
            return true;
        }
        return false;
    }
};

std::ostream &operator<<(std::ostream &os, LinkedList &l)
{
    Node *node = l.GetHead();
    if (l.IsLoop())
    {
        do
        {
            os << node->data << " ";
            node = node->next;
        } while (node != l.GetHead());
    }
    else
    {
        while (node)
        {
            os << node->data << " ";
            node = node->next;
        }
    }
    return os;
}

int main()
{
    printf("MAIN START\n\r");
    int arr[] = {10, 20, 30, 40, 150, 60, 70};
    LinkedList l(arr, sizeof(arr) / sizeof(arr[0]));
    std::cout << l << std::endl;
    l.PrintRecursive();
    std::cout << "cnt=" << l.Count() << std::endl;
    std::cout << "cnt=" << l.CountRecursive() << std::endl;
    std::cout << "sum=" << l.Sum() << std::endl;
    std::cout << "sum=" << l.SumRecursive() << std::endl;
    std::cout << "max=" << l.MaxElement() << std::endl;
    std::cout << "max=" << l.MaxElementRecursive() << std::endl;
    int key = 150;
    struct Node *node = l.Search(key);
    std::cout << "search(150) node ptr=" << (void *)node << " node->data=" << (node ? node->data : NULL) << std::endl;
    node = l.SearchRecursive(key);
    std::cout << "search(150) node ptr=" << (void *)node << " node->data=" << (node ? node->data : NULL) << std::endl;
    node = l.SearchWithMoveToHead(key);
    std::cout << "search(150) node ptr=" << (void *)node << " node->data=" << (node ? node->data : NULL) << std::endl;
    l.PrintRecursive();
    node = l.SearchWithMoveToHead(key);
    std::cout << "search(150) node ptr=" << (void *)node << " node->data=" << (node ? node->data : NULL) << std::endl;
    l.Insert(3, 88);
    l.PrintRecursive();
    printf("free:\n");
    l.FreeLinkedList();
    l.PrintRecursive();
    Node *head = NULL;
    int arr2[] = {4, 9, 3, 1, 15, 6, 7, 9, 15, 15, 15, 15};
    // head = CreateFromArrayByInsert(arr2, sizeof(arr2) / sizeof(arr2[0]));
    struct Node *headSorted = NULL;
    std::cout << "is sorted=" << l.IsSorted() << std::endl;
    LinkedList l2(arr2, sizeof(arr2) / sizeof(arr2[0]), true); // create sorted
    l2.PrintRecursive();
    l2.InsertSorted(11);
    std::cout << "is sorted=" << l2.IsSorted() << std::endl;
    l2.PrintRecursive();
    l2.Delete(0);
    l2.PrintRecursive();
    printf("!!\n");
    l2.DeleteLast();
    l2.PrintRecursive();
    l2.RemoveDuplicatesFormSorted();
    l2.PrintRecursive();
    printf("!!\n");
    l2.ReverseByMoveData();
    l2.PrintRecursive();
    l2.FreeLinkedList();
    l2.PrintRecursive();

    int arr3[] = {1, 2, 3};
    LinkedList l3(arr3, sizeof(arr3) / sizeof(arr3[0]), true);
    l3.PrintRecursive();
    l3.ReverseByMoveLinksRecursive();
    l3.PrintRecursive();

    l3.FreeLinkedList();
    l3.PrintRecursive();

    // Concat
    int arr4[] = {1, 2, 3};
    LinkedList l4(arr4, sizeof(arr4) / sizeof(arr4[0]), true);
    l4.PrintRecursive();
    int arr5[] = {11, 12, 13};
    LinkedList l5(arr5, sizeof(arr5) / sizeof(arr5[0]), true);
    l5.PrintRecursive();
    l4.Concat(l5);
    l4.PrintRecursive();

    // Merge sorted
    std::cout << "Merge\n";
    int arr6[] = {1, 12, 13};
    LinkedList l6(arr6, sizeof(arr6) / sizeof(arr6[0]), true);
    l6.PrintRecursive();
    int arr7[] = {8, 9, 18};
    LinkedList l7(arr7, sizeof(arr7) / sizeof(arr7[0]), true);
    l7.PrintRecursive();
    l6.MergeSorted(l7);
    l6.PrintRecursive();

    // Looped LL
    int arr9[] = {1, 12, 13, 15};
    LinkedList l9(arr9, sizeof(arr9) / sizeof(arr9[0]), true);
    std::cout << "LL is looped: " << l9.IsLoop() << std::endl;
    std::cout << l9 << std::endl;
    l9.MakeLoop(0); // !!!! 0
    std::cout << "LL is looped: " << l9.IsLoop() << std::endl;
    std::cout << l9 << std::endl;

    return 0;
}