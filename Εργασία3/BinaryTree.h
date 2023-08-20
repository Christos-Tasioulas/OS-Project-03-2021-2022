#ifndef BINARYTREE
#define BINARYTREE
#include <iostream>

using namespace std;

// Binary Tree Node
class BinaryTreeNode
{
private:
    void* value;
    BinaryTreeNode* parent;
    BinaryTreeNode* left_child;
    BinaryTreeNode* right_child;
    
public:
    // Constructor
    BinaryTreeNode(void* value);
    // Destructor
    ~BinaryTreeNode();
    // changing the value of a node to the given value
    void set_value(void* v);
    // returns the value of the node
    void* get_value() const;
    // sets the parent node for the node
    void set_parent(BinaryTreeNode* node);
    // returns the parent of the node
    BinaryTreeNode* get_parent() const;
    // sets the left child node of the node
    void set_left_child(BinaryTreeNode* node);
    // returns the left child of the node
    BinaryTreeNode* get_left_child() const;
    // sets the right child node of the node
    void set_right_child(BinaryTreeNode* node);
    // returns the right child of the node
    BinaryTreeNode* get_right_child() const;
};

// Binary Tree
class BinaryTree
{
private:
    BinaryTreeNode* root;
    int size;

    // recursive assisstant function to clear tree
    void rec_clear_tree(BinaryTreeNode* node);

protected:
    // swaps the values of two nodes
    void swap_values(BinaryTreeNode* node1, BinaryTreeNode* node2);

public:
    // Constructor
    BinaryTree();
    // Destructor
    ~BinaryTree();
    // clears the tree of all nodes
    void clear_tree();
    //sets the node given as the root of the tree
    void set_root(BinaryTreeNode* node);
    // returns the root of the tree
    BinaryTreeNode* get_root() const; 
    // increases the size by 1
    void increase();
    // decreases the size by 1
    void decrease();
    // returns the size of the tree
    int get_size() const;
    // returns the height of the tree
    int get_height();
    // return the height of a node given from the bottom of the tree
    int get_height_of_node(BinaryTreeNode* node);
    // inserts a value as the root of a tree
    void InsertRoot(void* value);
    // inserts a value as a left child of a node given if possible 
    void InsertLeft(void* value, BinaryTreeNode* parent);
    // inserts a value as a right child of a node given if possible
    void InsertRight(void* value, BinaryTreeNode* parent);
    // removes a leaf from the binary tree
    void RemoveLeaf(BinaryTreeNode* node);
    // prints the tree with pre order traversal
    void print_pre_order(void (*visit)(void *));
    // prints the tree with in order traversal
    void print_in_order(void (*visit)(void *));
    // prints the tree with post order traversal
    void print_post_order(void (*visit)(void *));
    // prints the tree with level order traversal
    void print_level_order(void (*visit)(void *));
};

#endif