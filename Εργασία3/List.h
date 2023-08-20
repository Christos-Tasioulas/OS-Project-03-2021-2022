#ifndef LIST
#define LIST
#include <iostream>

using namespace std;

// ListNode
class ListNode
{
private:
    void* value;
    ListNode* next;
    ListNode* prev;
public:
    // ListNode constructor 
    ListNode(void* v);
    // ListNode destructor
    ~ListNode();
    // changing the value of a node to the given value
    void set_value(void* v);
    // getting the value of the node
    void* get_value() const;
    // changing the next node to the given node
    void set_next(ListNode* node);
    // getting the next node
    ListNode* get_next(void) const;
    // changing the previous node to the given node
    void set_prev(ListNode* node);
    // getting the previous node
    ListNode* get_prev(void) const;
    // printing the node value
    void print(void (*visit)(void *));
};

// List
class List
{
private:
    ListNode* head;
    ListNode* last;
    int size;
public:
    // List constructor
    List();
    // List destructor
    ~List();
    // clears the list of all nodes and data
    void clear_list();
    // Returning the first node of the list
    ListNode* get_first(void) const;
    // Returning the first node of the list
    ListNode* get_last(void) const;
    // Returning the size of the list
    int get_size(void) const;
    // Inserting a value as the head of the list
    void ListInsertFirst(void* value);
    // Inserting a value as the end of the list
    void ListInsertLast(void* value);
    // Inserting a value after a value given in the list if it exists
    void ListInsertAfter(void* value, void* value_before, int (*compare)(void *, void *));
    // Inserting a value before a value given in the list if it exists
    void ListInsertBefore(void* value, void* value_after, int (*compare)(void *, void *));    
    // Searching the value on the list 
    ListNode* ListSearch(void* value, int (*compare)(void *, void *));
    // removing a node with given value if it exists
    void Remove(void* value, int (*compare)(void *, void *));
    // removing the first node
    void RemoveFirst();
    // removing the last node
    void RemoveLast();
    // printing a list visiting the value
    void print1(void (*visit)(void *));
    // printing a list visiting the value
    void print2(void (*visit)(void *));
};

#endif