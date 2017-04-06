#ifndef NODE
#define NODE

#include <iostream>
#include <iomanip>


using namespace std;

template<typename T>

struct node
{
    T item;
    node<T>* next;
    node()
    {
        next = NULL;
    }
    node(T myItem)
    {
        item = myItem;
        next = NULL;
    }

    friend ostream& operator << (ostream& outs, const node<T>*& printMe)
    {
        outs << printMe->item;
        return outs;
    }

//    friend bool operator < (const node<T>*& left, const node<T>*& right)
//    {
//        if(left->item < right->item)
//        {
//            return true;
//        }
//        return false;
//    }
};


template<typename T>
void InsertHead(node<T>*& Head, T Item)
{
    node<T>* temp = new node<T>;
    temp->item = Item;
    temp->next = Head;
    Head = temp;    
}

template<class T>
T RemoveHead(node<T>*& Head)
{
    T temp = Head->item;
    node<T>* nextNode = Head->next;    
    delete Head;
    Head = nextNode;    
    return temp;
}

template<class T>
void InsertAfter(node<T>* AfterMe, T Item)
{
    node<T>* newnode = new node<T>;
    node<T>* temp = AfterMe->next;
    newnode->item = Item;
    newnode->next = temp;
    AfterMe->next = newnode;
}

template<class T>
void InsertBefore(node<T>* BeforeMe, node<T>* Head, T Item)
{
    node<T>* temp = Head;
    while(temp->next != BeforeMe)
    {
        temp = temp->next;
    }
    temp->next = new node<T>;
    temp = temp->next;
    temp->item = Item;
    temp->next = BeforeMe;
}

template<class T>
void DeleteThis(node<T>* DeleteMe, node<T>* Head)
{
    node<T>* temp = Head;
    while(temp->next != DeleteMe && temp->next != NULL)
    {

        temp = temp->next;
    }
    if(temp->next != NULL)
    {
        temp->next = DeleteMe->next;
        delete DeleteMe;
    }
}

template<class T>
void ClearList(node<T>*& Head)
{
    node<T>* previous = Head;
    node<T>* next = Head->next;
    while(next != NULL)
    {
        delete previous;
        previous = next;
        next = previous->next;
    }
    delete previous;
    Head = NULL;
}

template<class T>
node<T>* SearchList(node<T>* Head, T Key)
{
    node<T>* walker = Head;
    while(walker != NULL)
    {
        if(walker->item == Key)
        {
            return walker;
        }
        else
        {
            walker = walker->next;
        }
    }
    return NULL;
}

template<class T>
void PrintList(node<T>* Head)
{
    node<T>* Walker = Head;
    while(Walker->next != NULL)
    {
        cout << setw(4);
        cout << "|" << Walker->item << "| " << endl;
        Walker = Walker->next;
    }    
}

template<class T>
node<T>* PreviousNode(node<T>* Head, node<T>* toThis)
{
    node<T>* Walker = Head;
    if(Walker == toThis)
    {
        throw 0;
    }
    while(Walker->next != toThis && Walker->next != NULL)
    {
        Walker = Walker->next;
    }
    if(Walker->next == toThis)
    {
        return Walker;
    }
    throw 1;
}

template<class T>
node<T>* WhereThisGoes(node<T>* head, T item)
{
    node<T>* previous = head;
    node<T>* current = previous->next;
    if(item < previous->item)
    {
        throw 0;
    }
    while(item > current->item && current->next != NULL)
    {
        previous = previous->next;
        current = current->next;
    }
    if(current->item < item)
    {
        throw 1;
    }
    return previous;
}

template<class T>
node<T>* CopyList(node<T>* sourceHead)
{
    node<T>* sourceWalker = sourceHead;
    node<T>* destHead = new node<T>;
    node<T>* destWalker = destHead;

    while(sourceWalker->next != NULL)
    {
        destWalker->item = sourceWalker->item;
        destWalker->next = sourceWalker->next;
        sourceWalker = sourceWalker->next;
        destWalker = destWalker->next;
    }
    destWalker->item = sourceWalker->item;
    destWalker->next = sourceWalker->next;

    return destHead;
}

template<class T>
node<T>* At(node<T>* head, int n)
{
    node<T>* walker = head;
    int i;
    for(i = 0; i <= n && walker->next != NULL; i++)
    {
        walker = walker->next;
    }
    if(i == n)
    {
        return walker;
    }
    throw 0;
}

template<class T>
bool inList(node<T>* head, node<T>* This)
{
    node<T>* walker = head;
    while(walker->next != This && walker->next != NULL)
    {
        walker = walker->next;
    }
    if(walker->next == NULL)
    {
        return false;
    }
    return true;
}


#endif // NODE

