#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node_t;

typedef struct
{
    Node_t *front;
    Node_t *back;
    int size;
} Dqueue_t;

bool Init(Dqueue_t *d)
{
    d->front = NULL;
    d->back = NULL;
    d->size = 0;
    return true;
}

bool Push_front(Dqueue_t *d, int data)
{
    Node_t *temp = (Node_t *)malloc(sizeof(Node_t));
    if (!temp)
        return false;
    temp->data = data;
    temp->prev = NULL;
    if (d->back)
    {
        temp->next = d->back;
        d->back->prev = temp;
    }
    else
        d->front = temp;
    d->back = temp;
    d->size++;
    return true;
}

bool Push_back(Dqueue_t *d, int data)
{
    Node_t *temp = (Node_t *)malloc(sizeof(Node_t));
    if (!temp)
        return false;
    temp->data = data;
    temp->next = NULL;
    if (d->front)
    {
        temp->prev = d->front;
        d->front->next = temp;
    }
    else
        d->back = temp;
    d->front = temp;
    d->size++;
    return true;
}

bool Pop_front(Dqueue_t *d)
{
    if (!d->size)
        return false;
    Node_t *temp = d->front;
    d->front = d->front->prev;
    free(temp);
    if (!d->front)
        d->back = NULL;
    else
        d->front->next = NULL;
    d->size--;
}

bool Pop_back(Dqueue_t *d)
{
    if (!d->size)
        return false;
    Node_t *temp = d->back;
    d->back = d->back->next;
    free(temp);
    if (!d->back)
        d->front = NULL;
    else
        d->back->prev = NULL;
    d->size--;
}

int Front(Dqueue_t *d)
{
    if (!d->front)
        return -1;
    return d->front->data;
}

int Back(Dqueue_t *d)
{
    if (!d->back)
        return -1;
    return d->back->data;
}

int Size(Dqueue_t *d)
{
    return d->size;
}

bool Empty(Dqueue_t *d)
{
    if (!d->size)
        return true;
    return false;
}

void Display(Dqueue_t *d)
{
    printf("[ ");
    Node_t *node = d->front;
    while (node)
    {
        printf("%d ", node->data);
        node = node->prev;
    }
    printf("] \n");
}

int main()
{
    printf("dqueue:\n");
    Dqueue_t d;
    Init(&d);

    Push_front(&d, 12);
    printf("front=%d back=%d size=%d\n", Front(&d), Back(&d), Size(&d));
    Display(&d);
    Push_back(&d, 15);
    printf("front=%d back=%d size=%d\n", Front(&d), Back(&d), Size(&d));
    Display(&d);
    Push_front(&d, 5);
    printf("front=%d back=%d size=%d\n", Front(&d), Back(&d), Size(&d));
    Display(&d);
    Pop_back(&d);
    printf("front=%d back=%d size=%d\n", Front(&d), Back(&d), Size(&d));
    Display(&d);
    Pop_front(&d);
    printf("front=%d back=%d size=%d\n", Front(&d), Back(&d), Size(&d));
    Display(&d);
    Pop_front(&d);
    printf("front=%d back=%d size=%d\n", Front(&d), Back(&d), Size(&d));
    Display(&d);

    return 0;
}