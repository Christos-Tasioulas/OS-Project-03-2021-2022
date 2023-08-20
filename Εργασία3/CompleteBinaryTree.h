#ifndef COMPLETEBINARYTREE
#define COMPLETEBINARYTREE
#include "BinaryTree.h"
#include "Queue.h"

class CompleteBinaryTree : public BinaryTree
{
private:
    Queue* Q;
    BinaryTreeNode* Last;
public:
    // Constructor
    CompleteBinaryTree();
    // Destructor
    ~CompleteBinaryTree();
    // Returns the last node of the tree
    BinaryTreeNode* get_last();
    // Inserting a value at the last place to preserve the tree's completeness
    void Insert(void* value);
    // We are allowed to remove only the last node of the tree in order to preserve its completeness
    void RemoveLast();
};


#endif 