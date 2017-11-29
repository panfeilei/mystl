#include <iostream>
#include ".\stl_alloc.h"
#include <string.h>
using namespace std;
typedef _default_alloc_template<true, 0> alloc;
int main()
{
    
    _default_alloc_template<true,0> __data_allocator;
    char *p = (char*)__data_allocator.allocate(sizeof(char) * 64);
    memset(p, 0,sizeof(p));
    strcpy(p, "fff");
    cout<<p;
        
}