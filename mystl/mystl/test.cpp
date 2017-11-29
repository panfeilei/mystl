#include <iostream>
#include ".\stl_vector.h"
#include <string.h>
using namespace std;
typedef _default_alloc_template<true, 0> alloc;
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
     h.push_back(4);
     vector<int>::iterator iter = h.begin();
     for(;iter != h.end(); iter++)
     {
         cout<< *iter;
         
     }
     
}