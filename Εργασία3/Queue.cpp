#include "Queue.h"

Queue::Queue()
{
    List();
}

Queue::~Queue()
{
    //this->clear_list();
}

void Queue::Enqueue(void* value)
{
    this->ListInsertLast(value);
}

void Queue::Dequeue()
{
    this->RemoveFirst();
}

void Queue::PrintQueue(void (*visit)(void*))
{
    ListNode* node = this->get_first();
    while(node != NULL)
    {
        visit(node->get_value());
        node = node->get_next();
    }
}