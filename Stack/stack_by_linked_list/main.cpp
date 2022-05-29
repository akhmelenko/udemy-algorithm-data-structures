#include <iostream>
#include <stack>

struct Node
{
    int data;
    Node *next;
};

class Stack
{

public:
    Stack()
    {
        top = nullptr;
        size = 0;
    }
    Stack(int size, int data)
    {
        this->size = size;
        for (int i = 0; i < size; i++)
        {
            Node *temp = new Node;
            temp->data = data;
            temp->next = top;
            top = temp;
        }
    }
    ~Stack()
    {
        while (top)
        {
            Node *temp = top;
            top = temp->next;
            delete temp;
        }
    }
    int Top()
    {
        if (!top)
            std::cerr << "Error: No top of empty stack!\n";
        return top->data;
    }
    int Pop()
    {
        if (!top)
            return -1;
        Node *temp = top;
        top = temp->next;
        delete temp;
        size--;
        return 0;
    }
    int Push(int data)
    {
        Node *temp = new Node;
        if (!temp)
            return -1;
        temp->data = data;
        temp->next = top;
        top = temp;
        size++;
        return 0;
    }
    int Size()
    {
        return size;
    }
    bool Empty()
    {
        if (size)
            return false;
        else
            return true;
    }
    void Display()
    {
        Node *node = top;
        std::cout << "[ ";
        while (node)
        {
            std::cout << node->data << " ";
            node = node->next;
        }
        std::cout << "]\n";
    }

private:
    Node *top;
    int size;
};

int main()
{
    std::cout << "st:\n";
    Stack st;
    st.Push(12);
    std::cout << st.Top() << " size=" << st.Size() << "\n";
    st.Push(1);
    std::cout << st.Top() << " size=" << st.Size() << "\n";
    st.Push(8);
    std::cout << st.Top() << " size=" << st.Size() << "\n";
    st.Push(15);
    std::cout << st.Top() << " size=" << st.Size() << "\n";
    st.Display();

    std::cout << "\nst2:\n";
    Stack st2(3, 5);
    st2.Display();
    for (int i = 0; i < 3; i++)
    {
        std::cout << st2.Top() << " size=" << st2.Size() << " Empty=" << st2.Empty() << "\n";
        st2.Pop();
    }
    std::cout << " size=" << st2.Size() << " Empty=" << st2.Empty() << "\n";

    return 0;
}