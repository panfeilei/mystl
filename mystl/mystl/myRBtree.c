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
        while(node->p && node->p->color == RED) //node.pΪ��ɫ    ��node.p.p�Ǻ�ɫ
        {                                       //node.p��Ϊ��  node.p.pҲ��Ϊ�գ���Ϊnode.p�Ǻ�ɫ���������Ǹ��ڵ�
            if(node->p == node->p->p->left)
            {
                rbtree_node* uncle = node->p->p->right;
                if(uncle->color == RED)         //node.p�Ǻ�ɫ����ڵ��Ǻ�ɫ
                {
                    node->p->color = BLACK;
                    uncle->color = BLACK;
                    node->p->p->color = RED;
                    node = node->p->p;
                }
                else if(uncle->color == BLACK)
                {
                    if(node == node->p->right)
                    {//node.p�Ǻ죬node����ڵ��Ǻڣ���node���Һ���
                        node = node->p;
                        left_rotate(node);
                    }
                    
                    //node�Ǻ죬node.p�Ǻ죬node����ڵ��Ǻڣ���node������
                    node->p->color = BLACK;
                    node->p->p->color = RED;
                    right_rotate(node->p->p);
                }
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
    
    void rb_transplant(rbtree_node* old, rbtree_node* new)
    {
        if(old.p == NULL)
            root = new;
        else if(old == old.p.left)
            old.p.left = new;
        else old.p.right = new;
        new.p = old.p;
    }
    rbtree_node* minimum(rbtree_node* x)
    {
        rbtree_node* t = x;
        while(t.left != NULL)
            t = t.left;
        return t;
    }

	//Ҫɾ���Ľڵ�Ϊz����y�滻ԭ��z��λ�ã�x�滻y��λ��
    void delete(rbtree_node* z)
    {
        rbtree_node* x = NULL;

        rbtree_node* y = z;
        int oldcolor = y.color;
        if(z.left == NULL)
        {
            x = z.right;
            rb_transplant(z, z.right);
        }	 
        else if(z.right == NULL)
        {
            x = z.left;
            rb_transplant(z, z.left);
        }
        else
        {
            y = minimum(z.right);

            oldcolor = y.color;
            x = y.right;
            if(y.p != z)
            {
                rb_transplant(y, y.right);
                y.right = z.right;
                y.right.p = y;
            }
            rb_transplant(z, y);
            y.left = z.left;
            y.left.p = y;
            y.color = z.color;
        }
        if(oldcolor == BLACK)
            rbdelete_fixup(x)
    }

	//���1��תΪ2��3��4
	//���2��ʹ��x�ֵ�w��һ��ڣ�����ƽ��
	//���3��תΪ���4
	//���4����ת��x�����һ���ڽڵ�
	void rbdelete_fixup(rbtree_node* x)
    {
		while(x!=root && x.color == BLACK)
		{
			if(x == x.p.left)
            {
                rbtree_node* w = x.p.right;
                if(w.color == RED)
                {
                    w.color = BLACK;
                    x.p = RED;
                    left_rotate(x.p);
                    w = x.p.right;
                }
                if(w.left.color == BLACK && w.right.color == BLACK)
                {
                    w.color = RED;
                    x = x.p;
                }
                else if(w.right = BLACK)
                {
                    
                }
                
            }
            else
            {
                
            }
		}
        x.color = BLACK;
	}


};