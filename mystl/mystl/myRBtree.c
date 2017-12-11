#include <iostream>
using namespace std;
#define RED 1
#define BLACK 2


typedef struct rbtree_node
{
    struct rbtree_node* left;
    struct rbtree_node* right;
    struct rbtree_node* p;
    int key;
    int color; 
} rbtree_node;

struct rbtree
{
    rbtree_node *root;
    
    void rb_insert_fixup(rbtree_node* node)
    {
        while(node->p->color == RED)
        {
            if(node->p == node->p->p->left)
            {
                rbtree_node* uncle = node->p->p->right;
                if(uncle->color == RED)
                {
                    node->p->color = BLACK;
                    uncle->color = BLACK;
                    node->p->p->color = RED;
                    node = node->p->p;
                }
                else if(node == node->p->right)
                {
                    node = node->p;
                    left_rotate(node);
                }
                node->p->color = BLACK;
                node->p->p->color = RED;
                right_rotate(node->p->p);
            }
            else
            {}
        }
        root->color = BLACK;
    }
    
    void insert(int k)
    {
        rbtree_node *new_node = new rbtree_node;
        
        new_node->key = k;
        rbtree_node* x = root;
        rbtree_node *tmp = NULL;
        while(x != NULL)
        {
            tmp = x;
            if(new_node->key < x->key)
                x = x->left;
            else 
                x = x->right;
        }
        new_node->p = tmp;
        
        if(tmp == NULL)
            root = new_node; 
        else if(new_node->key < tmp->key)
            tmp->left = new_node;
        else
            tmp->right = new_node;
        
        new_node->color = RED;
        new_node->left = NULL;
        new_node->right = NULL;
        rb_insert_fixup(new_node);
    }
    
    void left_rotate(rbtree_node* x)
    {
        rbtree_node* y = x->right;
        x->right = y->left;
        if(y->left != NULL)
            y->left->p = x;
        
        if(x->p == NULL) 
            root = y;
        else if(x->p->left == x) 
            x->p->left = y;
        else 
            x->p->right = y;
        
        y->p = x->p;
        y->left = x;
        x->p = y;
    }
    
    void right_rotate(rbtree_node* y)
    {
        rbtree_node* x = y->left;
        y->left = x->right;
        if(x->right != NULL)
            x->right->p = y;
        
        if(y->p == NULL)
            root = x;
        else if(y->p->left == y)
            y->p->left = x;
        else
            y->p->right = x;
        
        x->p = y->p;
        x->right = y;
        y->p = x;
    }
};