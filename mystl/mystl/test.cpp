#include <iostream>
#include <string.h>

#include ".\stl_vector.h"
#include ".\stl_algobase.h"

//#include <vector>
//#include <algorithm>

using namespace std;
int main()
{
    
    /*
    _default_alloc_template<true,0> __data_allocator;
    char *p = (char*)__data_allocator.allocate(sizeof(char) * 64);
    memset(p, 0,sizeof(p));
    strcpy(p, "fff");
    cout<<p;
        */
    
    
    vector<int> h;
    
    h.push_back(1);
    h.push_back(2);
    h.push_back(3);
    h.push_back(4);
    h.push_back(5);
    vector<int> g(h);
    vector<int>::iterator iter;
    for(iter = g.begin(); iter != g.end(); iter++)
        cout<< *iter;
    cout<<" "<<g.size();
    
    
    /*
    int y[10] = {1,2,3,4,5,6,7,8,9,10};
    cout<<"d   ";
    copy_backward_stl(y, y+5, y+9);
    for(int i =0; i< 10; i++)
        cout<<*(y+i);*/
    /*
    for(int i =0; i< 10; ++i)
        cout << i;
    */
}