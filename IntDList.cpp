#include "IntDList.hpp"
#include <sstream>
//g++ -std=c++17 -Wall
//This program has the purpose of defining all the needed methods for the IntDList class declared in IntDList.hpp

//constructor
IntDLList::IntDLList()
{
    //initialize ListHead as a head/tail sentinel
    ListHead = new IntDLLNode;

    //initially list is empty
    ListHead->next = ListHead; //next will points to first node (head)
    ListHead->prev = ListHead; //prev will points to last node (tail)
}

//destructor
IntDLList::~IntDLList()
{
    //properly destruct the list

    while (!isEmpty())
    {
        deleteFromHead();
    }
    delete ListHead;
}
//add to front of list
void IntDLList::addToHead(int a)
{
    //create new node between head and first element
    IntDLLNode *node = new IntDLLNode(a, ListHead->next, ListHead);

    //update prev pointer, of Listhead->next(now the second node), to point to new node
    ListHead->next->prev = node;

    //update next pointer, of ListHead, to point to new node
    ListHead->next = node;
}
//insert new element to list in order
void IntDLList::insertInOrder(int a)
{
    //declare node to iterate through the list
    IntDLLNode *node = ListHead->next;

    //search for a node which's info is larger or equal to "a"
    while (node != ListHead && node->info < a)
    {
        //iterate through list
        node = node->next;
    }

    if (node == ListHead) // if node == ListHead, there is no node which's info is greater than "a", or the list is empty
    {
        //then, just add to tail
        addToTail(a);
    }
    else
    {
        IntDLLNode *n_node = new IntDLLNode(a, node, node->prev); //create a new node, before the found node
        //make the previous node's *next point to new node
        node->prev->next = n_node;

        //make node *prev point to new node
        node->prev = n_node;
    }
}
//Append to list
void IntDLList::addToTail(int a)
{
    //declare new node between ListHead->prev and ListHead
    IntDLLNode *node = new IntDLLNode(a, ListHead, ListHead->prev);

    //update the header prev node's *next pointer point to the new node
    ListHead->prev->next = node;
    // update header *prev point to new node
    ListHead->prev = node;
}
//remove front
int IntDLList::deleteFromHead()
{
    if (!isEmpty()) //if list not empty
    {
        IntDLLNode *node = ListHead->next; //pointer to first node on list, which will be deleted
        int a = node->info;                // save node's info

        //update pointers to safely delete node
        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node; //delete first node on the list
        return a;    //return its value
    }
    else //else, list is empty throw
    {
        throw;
    }
}
//remove from back
int IntDLList::deleteFromTail()
{
    if (isEmpty()) //if list is empty throw
    {
        throw;
    }
    else // else
    {
        IntDLLNode *node = ListHead->prev; //pointer to last node on list, which will be deleted
        int a = node->info;                //safe node's info

        //update pointers to safely delete node
        node->prev->next = node->next;
        node->next->prev = node->prev;

        delete node; //delete last node on the list
        return a;    //return its value
    }
}
//delete a given node
void IntDLList::deleteNode(int a)
{
    IntDLLNode *node = ListHead->next; //temporary node

    while (node != ListHead && node->info != a) //search for node with desired value
    {
        node = node->next; //iterate through list
    }
    if (node == ListHead) //value not found in list
    {
        return;
    }

    node->prev->next = node->next;
    node->next->prev = node->prev;

    delete node;
}
//check if a value is in list
bool IntDLList::isInList(int a) const
{
    IntDLLNode *node = ListHead->next;          //create temporary node
    while (node != ListHead && node->info != a) //search for node with desired value
    {
        node = node->next; //iterate through list
    }

    return node->next != ListHead ? true : false; // return whether value is in list
}
//concatonate list elements into a string
string IntDLList::addToString() const
{
    stringstream iss;                  //declare string stream
    IntDLLNode *node = ListHead->next; //temporary node

    while (node != ListHead)
    {
        iss << node->info; //concatonate integers into strings
        node = node->next; //iterate through list
    }

    return iss.str();
}
