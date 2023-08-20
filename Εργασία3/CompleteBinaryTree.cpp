#include "CompleteBinaryTree.h"

CompleteBinaryTree::CompleteBinaryTree()
{
    this->Q = new Queue();
    this->Last = NULL;
    BinaryTree();    
}

CompleteBinaryTree::~CompleteBinaryTree()
{
    delete this->Q;
    this->Last = NULL;
}

// Returns the last node of the tree
BinaryTreeNode* CompleteBinaryTree::get_last()
{
    return this->Last;
}

// Inserting a value at the last place to preserve the tree's completeness
void CompleteBinaryTree::Insert(void* value)
{
    BinaryTreeNode* new_node;
    // taking the case if this is the only value
    if(this->get_size() == 0)
    {
        this->InsertRoot(value);
        new_node = this->get_root();
        // inserting the node at the queue as a potential parent for the last node
        Q->Enqueue(new_node);
    }
    else
    {
        // the first node of the queue will be the parent of the new last node
        ListNode* front = Q->get_first();
        BinaryTreeNode* node_p = (BinaryTreeNode*) front->get_value();
        // case if the parent node has no children
        if(node_p->get_left_child() == NULL)
        {
            this->InsertLeft(value, node_p);
            new_node = node_p->get_left_child();
        }
        // case if the parent has only a left child
        else if(node_p->get_right_child() == NULL)
        {
            this->InsertRight(value, node_p);
            new_node = node_p->get_right_child();
            // removing the parent node from the queue since it will no longer be a potential parent at the future
            Q->Dequeue();
        }
        // inserting the last node as a potential parent for the new last node
        Q->Enqueue(new_node);

    }
    this->Last = new_node;
}

// We are allowed to remove only the last node of the tree in order to preserve its completeness
void CompleteBinaryTree::RemoveLast()
{
    // nothing will be removed if the tree is empty
    if(this->get_size() != 0)
    {
        // case if the tree has only its root
        if(this->get_size() == 1)
        {
            Q->Dequeue();
            this->RemoveLeaf(this->get_root());
            return;
        }

        BinaryTreeNode* Last = this->Last;
        BinaryTreeNode* Parent = Last->get_parent();

        // the parent gets automatically inserted at the top of the queue since it will be the potential parent of a new last node
        if(Parent->get_left_child() && Parent->get_right_child())
        {
            // STRUCTURE BENDING !!!!
            Q->ListInsertFirst(Parent);
        }

        // the node to be removed is the first one that entered the queue the last node of the queue will also be removed 
        // MORE STRUCTURE BENDING !!!
        Q->RemoveLast();
        this->RemoveLeaf(Last);

        // the current last node of the queue will be the new last node for the tree
        BinaryTreeNode* new_Last = (BinaryTreeNode*) Q->get_last()->get_value();
        this->Last = new_Last;
    } 
}