#ifndef MYSTACK
#define MYSTACK

#include <iostream>
#include "node.h"

template<class T>

class Stack
{
public:
    Stack(T Item);
    Stack(node<T>* Head);
    Stack();
    void Push(T Item);
    T Pop();
    void Delete(node<T>* This);
    void Clear();
    node<T>* Search(T Key);
    T& Top();
    node<T>* Copy();
    bool Empty();
    void Print();
    int Size();

private:
    node<T>* head;

};

template<class T>
Stack<T>::Stack(T Item)
{
    head = new node<T>;
    head->next = NULL;
    head->item = Item;
}

template<class T>
Stack<T>::Stack(node<T>* Head)
{
    head = Head;
}
template<class T>
Stack<T>::Stack()
{
    head = NULL;
}

template<class T>
void Stack<T>::Push(T Item)
{    
    InsertHead(head, Item);
}

template<class T>
T Stack<T>::Pop()
{    
    if(!Empty())
    {
        T Temp = RemoveHead(head);
        return Temp;
    }
    throw 0;
}

template<class T>
void Stack<T>::Delete(node<T> *This)
{
    DeleteThis(This, head);
}

template<class T>
void Stack<T>::Clear()
{
    ClearList(head);
}

template<class T>
node<T> *Stack<T>::Search(T Key)
{
    node<T>* temp = SearchList(head, Key);
    return temp;
}

template<class T>
T& Stack<T>::Top()
{
    return head->item;
}

template<class T>
node<T>* Stack<T>::Copy()
{
    node<T>* temp = CopyList(head);
    return temp;
}

template<class T>
bool Stack<T>::Empty()
{
    if(head == NULL)
    {       
        return true;
    }    
    return false;
}

template<class T>
void Stack<T>::Print()
{
    node<T>* walker = head;
    while(walker->next != NULL)
    {
        cout << walker->item << endl;
        walker = walker->next;
    }
    cout << walker->item << endl;
}

template<class T>
int Stack<T>::Size()
{
    node<T>* walker = head;
    int i = 0;
    while(walker->next != NULL)
    {
        i++;
    }
    return i;
}

#endif // MYSTACK

