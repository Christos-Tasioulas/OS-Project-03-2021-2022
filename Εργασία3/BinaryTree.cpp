#include "BinaryTree.h"

// Constructor
BinaryTreeNode::BinaryTreeNode(void* value)
{
    this->value = value;
    this->parent = NULL;
    this->left_child = NULL;
    this->right_child = NULL;
}

// Destructor
BinaryTreeNode::~BinaryTreeNode()
{
}

// swaps the values of two nodes
void BinaryTree::swap_values(BinaryTreeNode* node1, BinaryTreeNode* node2)
{
    void *value1 = node1->get_value();
    void *value2 = node2->get_value();

    node1->set_value(value2);
    node2->set_value(value1);
}

// changing the value of a node to the given value
void BinaryTreeNode::set_value(void* v)
{
    this->value = v;
}

// returns the value of the node
void* BinaryTreeNode::get_value() const
{
    return this->value;
}

// sets the parent node for the node
void BinaryTreeNode::set_parent(BinaryTreeNode* node)
{
    this->parent = node;
}

// returns the parent of the node
BinaryTreeNode* BinaryTreeNode::get_parent() const
{
    return this->parent;
}

// sets the left child node of the node
void BinaryTreeNode::set_left_child(BinaryTreeNode* node)
{
    this->left_child = node;
}

// returns the left child of the node
BinaryTreeNode* BinaryTreeNode::get_left_child() const
{
    return this->left_child;
}

// sets the right child node of the node
void BinaryTreeNode::set_right_child(BinaryTreeNode* node)
{
    this->right_child = node;
}

// returns the right child of the node
BinaryTreeNode* BinaryTreeNode::get_right_child() const
{
    return this->right_child;
}

BinaryTree::BinaryTree()
{
    this->root = NULL;
    this->size = 0;
}

BinaryTree::~BinaryTree()
{
    this->clear_tree();
}

// clears the tree of all data
void BinaryTree::clear_tree()
{
    this->rec_clear_tree(this->root);
}

// recursive assisstant function to clear tree
void BinaryTree::rec_clear_tree(BinaryTreeNode* node)
{
    // base case if the node exists
    if(node != NULL)
    {
        // post order clearing of the tree
        rec_clear_tree(node->get_left_child());
        rec_clear_tree(node->get_right_child());
        delete node;
    }
    
}

//sets the node given as the root of the tree
void BinaryTree::set_root(BinaryTreeNode* node)
{
    this->root = node;
}

// returns the root of the tree
BinaryTreeNode* BinaryTree::get_root() const
{
    return this->root;
}

// increases the size by 1
void BinaryTree::increase()
{
    this->size++;
}

// decreases the size by 1
void BinaryTree::decrease()
{
    this->size--;
}

// returns the size of the tree
int BinaryTree::get_size() const
{
    return this->size;
}

// return the height of a node given from the bottom of the tree
int BinaryTree::get_height_of_node(BinaryTreeNode* node)
{
    // base case
    if (node == NULL)
        return 0;

    // calculating the height of each subtree 
    int LHeight = get_height_of_node(node->get_left_child());
    int RHeight = get_height_of_node(node->get_right_child());

    // using the larger one 
    if (LHeight > RHeight)
        return (LHeight + 1);
    else
        return (RHeight + 1);
    
}

// returns the height of the tree
int BinaryTree::get_height() 
{
    // returns the height of the root from the bottom
    return get_height_of_node(this->root);
}

// inserts a value as the root of a tree
void BinaryTree::InsertRoot(void* value)
{
    if(this->root != NULL)
    {
        cout << "Error root already exists" << endl;
    }
    else
    {
        // creating a new node for the new value
        BinaryTreeNode* node = new BinaryTreeNode(value); 

        this->root = node;  
        this->size++;
    }

}

// inserts a value as a left child of a node given if possible 
void BinaryTree::InsertLeft(void* value, BinaryTreeNode* parent)
{
    // checking if the tree is empty
    if(this->size == 0)
    {
        cout << "Error the tree is empty" << endl;
    }
    // checking whether the parent node given already has a left child
    else if(parent->get_left_child() != NULL)
    {
        cout << "Error: the node has already a left child" << endl;
    } 
    else
    {
        // creating a new node for the new value
        BinaryTreeNode* node = new BinaryTreeNode(value);

        // linking the nodes
        parent->set_left_child(node);
        node->set_parent(parent);

        this->size++;
    }
}

// inserts a value as a right child of a node given if possible
void BinaryTree::InsertRight(void* value, BinaryTreeNode* parent)
{
    // checking if the tree is empty
    if(this->size == 0)
    {
        cout << "Error the tree is empty" << endl;
    }
    // checking whether the parent node given already has a right child
    else if(parent->get_right_child() != NULL)
    {
        cout << "Error: the node has already a right child" << endl;
    } 
    else
    {
        // creating a new node for the new value
        BinaryTreeNode* node = new BinaryTreeNode(value);

        // linking the nodes
        parent->set_right_child(node);
        node->set_parent(parent);
        
        this->size++;
    }
}

// removes a leaf from the binary tree
void BinaryTree::RemoveLeaf(BinaryTreeNode* node)
{
    // checking if the tree is empty
    if(this->size == 0)
    {
        cout << "Error the tree is empty" << endl;
    }
    // checking whether the parent node given already is a leaf
    else if((node->get_right_child() != NULL) || (node->get_left_child() != NULL))
    {
        cout << "Error: the node has at least one child" << endl;
    } // If it was asked to delete the root of the tree
    else if(node == this->root)
    {
        this->root = NULL;
        
        delete node;
        this->size--;   
    }
    else
    {
        BinaryTreeNode* parent = node->get_parent();

        // checking if the node we want to remove is the left or the right children of its parent
        // in order to unlink the nodes with each other
        if(parent->get_left_child() == node) parent->set_left_child(NULL);
        else if(parent->get_right_child() == node) parent->set_right_child(NULL);

        node->set_parent(NULL);

        delete node;
        this->size--;
    }
}

// assisstant function for pre_order traversal
void pre_order(BinaryTreeNode* node, void (*visit)(void *))
{
    if(node != NULL)
    {
        visit(node->get_value());
        pre_order(node->get_left_child(), visit);
        pre_order(node->get_right_child(), visit);
    }    
}

// prints the tree with pre order traversal
void BinaryTree::print_pre_order(void (*visit)(void *))
{
    pre_order(this->root, visit);
}

// assisstant function for in_order traversal
void in_order(BinaryTreeNode* node, void (*visit)(void *))
{
    if(node != NULL)
    {
        in_order(node->get_left_child(), visit);
        visit(node->get_value());
        in_order(node->get_right_child(), visit);
    }
}

// prints the tree with in order traversal
void BinaryTree::print_in_order(void (*visit)(void *))
{
    in_order(this->root, visit);
}

// assisstant function for post_order traversal
void post_order(BinaryTreeNode* node, void (*visit)(void *))
{
    if(node != NULL)
    {
        post_order(node->get_left_child(), visit);
        post_order(node->get_right_child(), visit);
        visit(node->get_value());
    }
}

// prints the tree with post order traversal
void BinaryTree::print_post_order(void (*visit)(void *))
{
    post_order(this->root, visit);
}

// assistant function for printing each level
void print_level(BinaryTreeNode* node, int level,void (*visit)(void *))
{
    // base cases if the node is inexistent or if we reached the final level of recursion
    if(node == NULL) return;
    else if(level == 1) visit(node->get_value());
    else
    {
        // going down a level
        print_level(node->get_left_child(), level-1, visit);
        print_level(node->get_right_child(), level-1, visit);
    }
}

// prints the tree with level order traversal
void BinaryTree::print_level_order(void (*visit)(void *))
{
    // we need the heigh of the tree to traverse it level order
    int h = this->get_height();
    // printing each level separately
    for(int i=1; i<=h; i++)
    {
        print_level(this->root, i, visit);
        cout << endl;
    }
}