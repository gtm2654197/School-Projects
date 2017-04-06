#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "node.h"

template<class T>

class Queue
{
public:
    Queue(node<T>* Head);
    Queue(T Item);
    Queue();

    void Insert(T Item);
    T Pop();
    void Delete(node<T>* This);
    void Clear();
    node<T>* Search(T Key);
    T Top();
    node<T>* Copy();
    bool Empty();
    void Print();

private:
    node<T>* head;
    node<T>* tail;
};

template<class T>
Queue<T>::Queue(T Item)
{
    head = new node<T>;
    tail = head;
    head->item = Item;
    tail->next = NULL;
}

template<class T>
Queue<T>::Queue(node<T>* Head)
{
    head = Head;
    node<T>* walker = head;
    while(walker->next != NULL)
    {
        walker = walker->next;
    }
    tail = walker;
}
template<class T>
Queue<T>::Queue()
{
    head = NULL;
    tail = head;
}

template<class T>
void Queue<T>::Insert(T Item)
{
    if(head == NULL)
    {
        InsertHead(head, Item);
        tail = head;
        tail->next = NULL;
    }
    else
    {
        InsertAfter(tail, Item);
        tail = tail->next;
    }
}

template<class T>
T Queue<T>::Pop()
{
//    if(!Empty())
//    {
        T Temp = RemoveHead(head);
        return Temp;
//    }
//    throw 0;
}

template<class T>
void Queue<T>::Delete(node<T> *This)
{
    DeleteThis(This, head);
    if(This == tail)
    {
        node<T>* walker = head;
        while(walker->next != NULL)
        {
            walker = walker->next;
        }
        tail = walker;
    }
}

template<class T>
void Queue<T>::Clear()
{
    ClearList(head);
    tail = head;
}

template<class T>
node<T> *Queue<T>::Search(T Key)
{
    node<T>* temp = SearchList(head, Key);
    return temp;
}

template<class T>
T Queue<T>::Top()
{
    return head->item;
}

template<class T>
node<T>* Queue<T>::Copy()
{
    node<T>* temp = CopyList(head);
    return temp;
}

template<class T>
bool Queue<T>::Empty()
{
    if(head == NULL)
    {
        return true;
    }
    return false;
}

template<class T>
void Queue<T>::Print()
{
    node<T>* walker = head;
    while(walker->next != NULL)
    {
        cout << walker->item << endl;
        walker = walker->next;
    }
    cout << walker->item << endl;
}

#endif // QUEUE_H
