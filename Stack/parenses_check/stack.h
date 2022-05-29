#include <iostream>
#include <stack>

template <typename T>
struct Node
{
    T data;
    Node *next;
};

template <typename T>
class Stack
{

public:
    Stack()
    {
        top = nullptr;
        size = 0;
    }
    Stack(int size, T data)
    {
        this->size = size;
        for (int i = 0; i < size; i++)
        {
            Node<T> *temp = new Node<T>;
            temp->data = data;
            temp->next = top;
            top = temp;
        }
    }
    ~Stack()
    {
        while (top)
        {
            Node<T> *temp = top;
            top = temp->next;
            delete temp;
        }
    }
    T Top()
    {
        if (!top)
            std::cerr << "Error: No top of empty stack!\n";
        return top->data;
    }
    T Pop()
    {
        if (!top)
            return -1;
        Node<T> *temp = top;
        top = temp->next;
        delete temp;
        size--;
        return 0;
    }
    T Push(T data)
    {
        Node<T> *temp = new Node<T>;
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
        Node<T> *node = top;
        std::cout << "[ ";
        while (node)
        {
            std::cout << node->data << " ";
            node = node->next;
        }
        std::cout << "]\n";
    }

private:
    Node<T> *top;
    int size;
};