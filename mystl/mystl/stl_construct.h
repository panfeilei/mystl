
#ifndef STL_CONSTRUCT_H
#define STL_CONSTRUCT_H

#include <new>
#include <iostream>
#include "type_traits.h"
template<class T>
inline void _destory_aux_stl(T first, T last, __true_type)
{}
template<class Forward,class T>
inline void _destory_stl(Forward first, Forward last, T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	_destory_aux_stl(first, last, trivial_destructor());
}

template<class T1, class T2>
inline void costruct_stl(T1 *p, const T2& value)
{
	new (p) T1(value);
}


template <class T>
inline void destory_stl(T* pointer)
{
	pointer->~T();
}


template<class T>
inline void destory_stl(T first, T last)
{
	_destory_stl(first, last, value_type(first));
}


template<class T>
inline void _destory_aux_stl(T first, T last, __false_type)
{
	for (; first < last; ++first)
		destory_stl(&*first);
}

#endif


