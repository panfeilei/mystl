#include <iostream>
#include <string.h>
#include<functional>  
#include ".\stl_vector.h"
#include ".\stl_algobase.h"
#include ".\stl_tree.h"
#include ".\stl_map.h"
using namespace std;


struct node{
	node* left;
	node* right;
	int key;
public:
	node(int k):key(k){
		left = NULL;
		right = NULL;
	}
};
class tree{
	node *root;
public:
	tree(){root = NULL;}
    node* troot(){return root;}
	void insert(int key)
	{
		node* tmp = new node(key);
		node* i = root;
        node* p;
		if(i == NULL)
		{
            root = tmp;
            return;
        }
		else
		{
			while(i != NULL)
			{
                p = i;
				if(key > i->key)
					i = i->right;
				else 
					i = i->left;
			}
            
            if(key < p->key)
                p->left = tmp;
            else 
                p->right = tmp;
		}
	}
};

void beprin(node* t)
{
    if(t == NULL)
        return;
    cout<<t->key;
    beprin(t->left);
    beprin(t->right);
}

void midprin(node* t)
{
    if(t == NULL)
        return;
    midprin(t->left);
    cout<<t->key;
    midprin(t->right);
}

void afprin(node* t)
{
    if(t == NULL)
        return;
    afprin(t->left);
    afprin(t->right);
    cout<<t->key;
}

int main()
{
    
    /*
    _default_alloc_template<true,0> __data_allocator;
    char *p = (char*)__data_allocator.allocate(sizeof(char) * 64);
    memset(p, 0,sizeof(p));
    strcpy(p, "fff");
    cout<<p;
        */

    /*
    vector<int> h;
    h.push_back(1);
    h.push_back(2);
    h.push_back(3);
    h.push_back(4);
    h.push_back(5);
    h.push_back(6);
    vector<int> g(4, 5);
    g.insert(g.begin(), 8);
    vector<int>::iterator iter;
    for(iter = g.begin(); iter != g.end(); iter++)
        cout<< *iter;
    cout<<" "<<g.size();
    */
    
    /*
    int y[10] = {1,2,3,4,5,6,7,8,9,10};
    cout<<"d   ";
    copy_backward_stl(y, y+3, y+5);
    for(int i =0; i< 10; i++)
        cout<<*(y+i) << " ";
    */

    map<string, int> g;
    g["rrr"] = 4;
    cout<<"s "<<g["rrr"];
}