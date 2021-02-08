#include "../list.h"

USING_MATSOLV

template <typename T>
list<T>::list()
{
    head = nullptr;
    Size = 0;
}

template <typename T>
list<T>::~list()
{
    clear();
}

template <typename T>
void list<T>::push_back(T data)
{
    if (head == nullptr)
    {
        head = new Node(data);
    }
    else
    {
        Node *current = this->head;
        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node(data);
    }
    Size++;
}

template <typename T>
void list<T>::push_front(T data)
{
    head = new Node(data, head);
    Size++;
}

template <typename T>
void list<T>::pop_back()
{
    removeAt(Size - 1);
}

template <typename T>
void list<T>::pop_front()
{
    Node *temp = this->head;
    head = head->pNext;
    delete temp;
    Size--;
}

template <typename T>
void list<T>::clear()
{
    while (Size)
        pop_front();
}

template <typename T>
void list<T>::removeAt(int index)
{
    if (index == 0)
    {
        pop_front();
    }
    else
    {
        Node *previous = this->head;
        for (int i = 0; i < index - 1; i++)
            previous = previous->pNext;

        Node *ToDelete = previous->pNext;
        previous->pNext = ToDelete->pNext;

        delete ToDelete;
        Size--;
    }
}

template <typename T>
void list<T>::insert(int index, T data)
{
    if (index == 0)
    {
        push_front(data);
    }
    else
    {
        Node *previous = this->head;
        for (int i = 0; i < index - 1; i++)
            previous = previous->pNext;

        previous->pNext = new Node(data, previous->pNext);
        Size++;
    }
}

template <typename T>
T &list<T>::operator[](const int index)
{
    Node *current = this->head;
    for (int i = 0; i <= index; i++)
    {
        if (i == index)
            return current->data;
        current = current->pNext;
    }
}