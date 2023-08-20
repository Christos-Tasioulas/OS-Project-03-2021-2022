#include "Heap.h"

// Constructor
Heap::Heap()
{
    CompleteBinaryTree();
}

// Destructor
Heap::~Heap()
{
}

// Returns the min value
void* Heap::get_min()
{
    // the minimum item is at the root of the heap
    return this->get_root()->get_value();
}

// Inserts at the end of the heap and sorts out accordingly
void Heap::HeapInsert(void* value, int (*compare)(void *, void *))
{
    // inserting the element at the end of the tree
    this->Insert(value);

    // sorting the last element at the place where it should be
    this->heapify_up(this->get_last(), compare);
}

// Removes the minimum element of the heap and sorts out accordingly
void Heap::RemoveMin(int (*compare)(void *, void *))
{
    // we won't remove anything if nothing exists in the heap
    if(!this->get_size()) return;

    // swapping the min value with the last value added to the heap
    // the heap is a complete binary tree after all
    swap_values(this->get_root(), this->get_last());

    // removing the now last node
    this->RemoveLast();

    // we won't heapify anything if nothing exists in the heap
    if(!this->get_size()) return;

    // sorting the new root at the place where it should be
    this->heapify_down(this->get_root(), compare);
}

// function that sorts the items of the tree from the leaves and up
void Heap::heapify_up(BinaryTreeNode* node, int (*compare)(void *, void *))
{
    // base case if we reached the root
    if(node == this->get_root()) return;

    BinaryTreeNode* parent = node->get_parent();

    // if the value of the current node is less than the value of its parent we swap the values and we keep on sorting upwards
    if(compare(parent->get_value(), node->get_value()) > 0)
    {
        swap_values(parent, node);
        this->heapify_up(parent, compare);
    }
}

// function that sorts the items of the tree from the root and down
void Heap::heapify_down(BinaryTreeNode* node, int (*compare)(void *, void *))
{
    BinaryTreeNode* Left = node->get_left_child();
    BinaryTreeNode* Right = node->get_right_child();

    // base case if a left child does not exist (a right child would not exist if a left one does not exist because it is a complete binary tree)
    // the node is a leaf
    if(!Left) return;

    // the left child is by default the min because at this stage it is the only child we are 100% sure it exists
    BinaryTreeNode* Min;
    Min = Left;

    // examining if the right child exists and its value is less than its left wing sibling
    // that's when it is the min
    if(Right && (compare(Right->get_value(), Left->get_value()) < 0)) Min = Right;

    // if the current node's value is greater than its min child's value we swap the values and we keep on sorting downwards
    if(compare(node->get_value(), Min->get_value()) > 0)
    {
        swap_values(node, Min);
        this->heapify_down(Min, compare);
    }

}

// assistant function
void Heap::heapify_all_rec(BinaryTreeNode* node, int (*compare)(void *, void *))
{
    if(node == NULL) return;

    heapify_all_rec(node->get_left_child(), compare);
    heapify_all_rec(node->get_right_child(), compare);
    heapify_down(node, compare);
}

// function that sorts the whole tree
void Heap::heapify_all(int (*compare)(void *, void *))
{
    heapify_all_rec(this->get_root(), compare);
}