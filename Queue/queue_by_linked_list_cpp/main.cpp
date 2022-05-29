#include <iostream>

struct Node
{
    int data;
    Node *next;
};

class Queue
{

public:
    Queue()
    {
        front = nullptr;
        back = nullptr;
        size = 0;
    }
    ~Queue()
    {
        while (front)
        {
            Node *temp = front;
            delete temp;
        }
    }
    int Front()
    {
        if (!front)
        {
            std::cerr << "Error: No front of empty queue!\n";
            return -1;
        }
        return front->data;
    }
    int Back()
    {
        if (!back)
        {
            std::cerr << "Error: No back of empty queue!\n";
            return -1;
        }
        return back->data;
    }
    int Pop()
    {
        if (!front)
            return -1;
        Node *temp = front;
        front = front->next;
        delete temp;
        size--;
        if (!front)
            back = front;
        return 0;
    }
    int Push(int data)
    {
        Node *temp = new Node;
        if (!temp)
            return -1;
        temp->data = data;
        temp->next = nullptr;
        if (!back)
            front = temp;
        else
            back->next = temp;
        back = temp;
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
        Node *node = front;
        std::cout << "[ ";
        while (node)
        {
            std::cout << node->data << " ";
            node = node->next;
        }
        std::cout << "]\n";
    }

private:
    Node *front;
    Node *back;
    int size;
};

int main()
{
    std::cout << "queue:\n";
    Queue q;
    q.Push(12);
    std::cout << "front=" << q.Front() << " back=" << q.Back() << " size=" << q.Size() << "\n";
    q.Display();
    q.Push(1);
    std::cout << "front=" << q.Front() << " back=" << q.Back() << " size=" << q.Size() << "\n";
    q.Display();
    q.Push(8);
    std::cout << "front=" << q.Front() << " back=" << q.Back() << " size=" << q.Size() << "\n";
    q.Display();
    q.Pop();
    std::cout << "front=" << q.Front() << " back=" << q.Back() << " size=" << q.Size() << "\n";
    q.Display();
    q.Push(15);
    std::cout << "front=" << q.Front() << " back=" << q.Back() << " size=" << q.Size() << "\n";
    q.Display();

    return 0;
}