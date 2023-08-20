#ifndef HEAP
#define HEAP
#include "CompleteBinaryTree.h"

class Heap : public CompleteBinaryTree
{
private:
public:
    // Constructor
    Heap();
    // Destructor
    ~Heap();
    // Returns the min value
    void* get_min();
    // Inserts at the end of the heap and sorts out accordingly
    void HeapInsert(void* value, int (*compare)(void *, void *));
    // Removes the minimum element of the heap and sorts out accordingly
    void RemoveMin(int (*compare)(void *, void *));
    // function that sorts the items of the tree from the leaves and up
    void heapify_up(BinaryTreeNode* node, int (*compare)(void *, void *));
    // function that sorts the items of the tree from the root and down
    void heapify_down(BinaryTreeNode* node, int (*compare)(void *, void *));
    // function that sorts the whole tree
    void heapify_all(int (*compare)(void *, void *));
    // assistant function
    void heapify_all_rec(BinaryTreeNode* node, int (*compare)(void *, void *));
};

#endif