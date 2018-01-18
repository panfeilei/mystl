#include <iostream>
#include <string.h>
#include<functional>  
#include ".\stl_vector.h"
#include ".\stl_algobase.h"
#include ".\stl_tree.h"
#include ".\stl_map.h"


using namespace std;
void fun1(char* value)
{
    strcpy(value, "fun1 value");
}

void fun(char* value)
{
    strcpy(value, "fun value");
    fun1(value);
}

class gggg{

};

    bool operator==(gggg y, gggg x)
{

     cout<<"bot equal"<<endl;
     return 1;
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

    map<int, int> g;
}