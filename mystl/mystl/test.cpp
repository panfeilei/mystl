#include <iostream>
#include <string.h>
#include<functional> 
#include <stdlib.h> 
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
    cout<<t->key<<" ";
    beprin(t->left);
    beprin(t->right);
}

void midprin(node* t)
{
    if(t == NULL)
        return;
    midprin(t->left);
    cout<<t->key<<" ";
    midprin(t->right);
}

void afprin(node* t)
{
    if(t == NULL)
        return;
    afprin(t->left);
    afprin(t->right);
    cout<<t->key<<" ";
}

node* buildtree(char* bes, char* mids)
{
    if(strlen(mids) == 0)
        return NULL;
    int root_index=0;
    char* tmp = mids;
    
    while(tmp[root_index]!='\0')
    {
        if(tmp[root_index] == (*bes))
            break;
        root_index++;
    }
    int rooti = tmp[root_index] - '0';
    node* root = new node(rooti);
    char* leftbes = new char[128];
    char* rightbes = new char[128];
    char* leftmids = new char[128];
    char* rightmids = new char[128];
    memset(leftbes, 0, 128);
    memset(rightbes, 0, 128);
    memset(leftmids, 0, 128);
    memset(rightmids, 0, 128);

    strncpy(leftbes, bes+1, root_index);
    strncpy(leftmids, mids, root_index);
    
    strcpy(rightbes, bes+root_index+1);
    strcpy(rightmids, mids+root_index+1);
    
    root->left = buildtree(leftbes, leftmids);
    root->right = buildtree(rightbes, rightmids);
    return root;
}

node* buildtree1(string bes, string mids)
{
    if(mids.length() == 0)
        return NULL;
    int root_index=0;
    string tmp = mids;
    
    while(tmp[root_index]!='\0')
    {
        if(tmp[root_index] == bes[0])
            break;
        root_index++;
    }
    int rooti = tmp[root_index] - '0';
     node* root = new node(rooti);
    
    string leftbe(bes.c_str()+1, root_index);
    string leftmid(mids.c_str(), root_index);
    
    string rightbe(bes.c_str()+root_index+1);
    string rightmid(mids.c_str()+root_index+1);
    root->left = buildtree1(leftbe, leftmid);
    root->right = buildtree1(rightbe, rightmid);
    return root;
}

void swap1(int* x, int* y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

template<class T>
void quicksort(T& num, int begin, int end)
{
    if(begin >= end)
        return;
    int len = sizeof(num)/sizeof(num[0]);
    int mid = begin;
    for(int i = begin;i<end;i++)
    {
        if(num[i] < num[end])
        {
            swap(num[i], num[mid++]);
        }
    }
    swap(num[end], num[mid]);
    quicksort(num, begin, mid-1);
    quicksort(num, mid+1, end);
}

template<class T>
void mergesort(T& num, int begin, int end)
{
    if(begin >= end)
        return;
    
    int mid = (begin + end)/2;
    mergesort(num, begin, mid);
    mergesort(num, mid+1, end);
    int i= begin;
    int j = mid+1;
    while(i < j && j < end)
    {
        if(num[i] > num[j])
        {
            swap(num[i], num[j]);
            i++;
        }
    }    
}

struct list_node{
    list_node* next;
    int key;
    list_node(int k):key(k),next(NULL)
    {}
};
struct List{
    list_node* root;
    list_node* tail;
    List():root(NULL), tail(NULL)
    {}
    void insert(int key)
    {
        list_node* tmp = new list_node(key);
        if(root==NULL)
        {
            root = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail=tmp;
        }
    }
    
    void lprint()
    {
        if(root!=NULL)
        {
            list_node* t = root;
            while(t!= NULL)
            {
                cout<<t->key<<" ";
                t=t->next;
            }
        }
    }
  
};

void reverlist(List& l)
{
    list_node* prev = NULL;
    list_node* curr = l.root;
    list_node* next = NULL;
    while(curr!=NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        if(next != NULL)
            curr=next;  
        else
            break;
    }
    l.root = curr;
    
}
int main()
{
    // int t[12]={9,4,7,6,2,1,9,2, 8, 25,46, 82};
    // quicksort(t, 0, 10);
    // for(int i=0; i< 12; i++)
        // cout<<t[i]<<" ";
    
    //node* r = buildtree1("12473568", "47215386");
    //afprin(r);
    // tree t;
    // t.insert(6);
    // t.insert(9);
    // t.insert(2);
    // t.insert(5);
    // midprin(t.troot());
    List l;
    l.insert(1);
    l.insert(3);
    l.insert(8);
    l.insert(4);
    reverlist(l);
    l.lprint();
}