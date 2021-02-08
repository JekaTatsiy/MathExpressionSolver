#ifndef LIST_H
#define LIST_H
#include <iostream>

template <typename T>
class list
{
    struct Node
    {
        Node *pNext;
        T data;
        Node(T data = T(), Node *pNext = nullptr) : data(data), pNext(pNext) {}
    };
    Node *head;
    int Size;

public:
    list();
    ~list();
    int GetSize() { return Size; }
    void push_back(T data);
    void push_front(T data);
    void pop_back();
    void pop_front();
    void clear();
    void removeAt(int index);
    void insert(int index, T data);
    T &operator[](const int index);
};

#include "src/list.cpp"

#endif