#include "List.h"

//Class List

// List constructor
List::List()
{
    this->head = NULL;
    this->last = NULL;
    this->size = 0;
}

// List destructor
List::~List()
{
    this->clear_list();
}

// clears the list of all nodes and data
void List::clear_list()
{
    this->size = 0;
    this->last = NULL;
    ListNode* node;
    node = this->head;
    // destroying each node of the list
    while(node != NULL)
    {
        this->head = node->get_next();
        delete node; 
        node = this->head; 
    }
}

// Returning the first node of the list
ListNode* List::get_first(void) const
{
    return this->head;
}

// Returning the first node of the list
ListNode* List::get_last(void) const
{
    return this->last;
}

// Returning the size of the list
int List::get_size(void) const
{
    return this->size;
}

// Inserting a value inside the list
void List::ListInsertFirst(void* value)
{

    ListNode* node;
    node = new ListNode(value);

    // this is the only node
    if(this->head == NULL)
    {   
        this->last = node;
    }
    else 
    {
        this->head->set_prev(node);
        node->set_next(this->head);
    }

    // inserting the node at the start
    this->head = node;
    this->size++;
}

// Inserting a value as the end of the list
void List::ListInsertLast(void* value)
{
    ListNode* node;
    node = new ListNode(value);

    // this is the only node
    if(this->size == 0)
    {
        this->head = node;
    }
    else 
    {
        this->last->set_next(node);
        node->set_prev(this->last);
    }
    // inserting the node at the end
    this->last = node;
    this->size++;
}

// Inserting a value after a value given in the list if it exists
void List::ListInsertAfter(void* value, void* value_before, int (*compare)(void *, void *))
{

    // if there is no value given in the second argument we will agree the new value will be placed at the start of the list
    if(value_before == NULL)
    {
        this->ListInsertFirst(value);
    }
    else
    {
        // searching the value given in the list
        ListNode* node_before = this->ListSearch(value_before, compare);

        // inserting the new value only if the other one exists
        if(node_before != NULL)
        {
            // if we need to insert it after the last node
            if(node_before == this->last) ListInsertLast(value);
            else
            {
                /* setting the nodes we will link together */

                // creating a new node
                ListNode* node = new ListNode(value);

                ListNode* next = node_before->get_next();

                // linking the nodes
                node->set_next(next);
                node->set_prev(node_before);
                
                node_before->set_next(node);
                next->set_prev(node);

                this->size++;
            }
            
            
        } // value does not exist
        else cout << "Error: value does not exist" << endl;
        
    }
}

// Inserting a value before a value given in the list if it exists
void List::ListInsertBefore(void* value, void* value_after, int (*compare)(void *, void *))
{
    // if there is no value given in the second argument we will agree the new value will be placed at the end of the list
    if(value_after == NULL)
    {
        this->ListInsertLast(value);
    }
    else
    {
        // Asserting the existence of the value to be inserted in the list
        
        ListNode* temp = this->ListSearch(value, compare);
        // the value exists if the search function returns anything other than NULLS
        if(temp != NULL)
        {
            cout << "Error: value already exists" << endl;
            return;
        }

        // searching the value given in the list
        ListNode* node_after = this->ListSearch(value_after, compare);

        // inserting the new value only if the other one exists
        if(node_after != NULL)
        {
            // if we need to insert it before the starting node
            if(node_after == this->head) ListInsertFirst(value);
            else
            {
                /* setting the nodes we will link together */

                // creating a new node
                ListNode* node = new ListNode(value);

                ListNode* prev = node_after->get_prev();

                // linking the nodes
                node->set_prev(prev);
                node->set_next(node_after);
                
                node_after->set_prev(node);
                prev->set_next(node);

                this->size++;
            }
        } // value does not exist
        else cout << "Error: value does not exist" << endl;
        
    }
}

// Searching the value on the list
ListNode* List::ListSearch(void* value, int (*compare)(void *, void *))
{
    ListNode* node;
    node = this->head;
    // traversing the list node by node
    while(node != NULL)
    {
        // We found it 
        if(compare(value, node->get_value()) == 0) return node;
        node = node->get_next();
    }
    // it doesn't exist
    return NULL;
}

// removing a node with given value if it exists
void List::Remove(void* value, int (*compare)(void *, void *))
{
    // searching the value given in the list
    ListNode* node = this->ListSearch(value, compare);
    if(node != NULL)
    {
        // Base Case if it is the only node
        if(this->size == 1)
        {
            this->head = NULL;
            this->last = NULL;
            delete node;
            this->size--;
        }

        // Redirecting to the other cases
        if(node == this->head) this->RemoveFirst();
        else if(node == this->last) this->RemoveLast();

        // removing only if the value exists
        else 
        {
            // linking the previous and the next node with each other
            ListNode* prev = node->get_prev();
            ListNode* next = node->get_next();

            if(prev) prev->set_next(next);
            if(next) next->set_prev(prev);

            delete node;
            this->size--;

        }
    }
     // value does not exist
    else cout << "Error: value does not exists" << endl;
}

// removing the first node
void List::RemoveFirst()
{
    // checking if the first node sxists
    if(this->head == NULL) return;

    ListNode* first = this->head;
    ListNode* next = this->head->get_next();

    // unlinking the node and changing the first one as the next one
    if(next) next->set_prev(NULL);
    first->set_next(NULL);

    this->head = next;

    delete first;
    this->size--;    
}

// removing the last node
void List::RemoveLast()
{
    // checking if the last node sxists
    if(this->last == NULL) return;

    ListNode* last = this->last;
    ListNode* prev = this->last->get_prev();

    // unlinking the node and changing the last one as the previous one
    if(prev) prev->set_next(NULL);
    last->set_prev(NULL);

    this->last = prev;

    delete last;
    this->size--;
}

// printing a list visiting the value
void List::print1(void (*visit)(void *))
{
    ListNode* node;
    node = head;
    while(node != NULL)
    {
        // printing each node 
        node->print(visit);
        node = node->get_next();
    }
}

// printing a list visiting the value
void List::print2(void (*visit)(void *))
{
    ListNode* node;
    node = last;
    while(node != NULL)
    {
        // printing each node 
        node->print(visit);
        node = node->get_prev();
    }
}

//Class ListNode

// ListNode constructor 
ListNode::ListNode(void* v)
{
    this->value = v;
    this->next = NULL;
    this->prev = NULL;
}

// ListNode destructor
ListNode::~ListNode()
{
    this->next = NULL;
    this->prev = NULL;
}

// changing the value of a node to the given value
void ListNode::set_value(void* v)
{
    this->value = v;
}

// getting the value of the node
void* ListNode::get_value() const
{
    return this->value;
}

// changing the next node to the given node
void ListNode::set_next(ListNode* node)
{
    this->next = node;
}

// getting the next node
ListNode* ListNode::get_next(void) const
{
    return this->next;
}

// changing the previous node to the given node
void ListNode::set_prev(ListNode* node)
{
    this->prev = node;
}

// getting the previous node
ListNode* ListNode::get_prev(void) const
{
    return this->prev;
}

// printing the node value
void ListNode::print(void (*visit)(void *))
{
    visit(this->value);
}