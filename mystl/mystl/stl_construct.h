#pragma once
#include <new.h>
template<class T1, class T2>
inline void costruct(T1 *p, const T2& value)
{
	new (p) T1(value);
}

template <class T>
inline void destory(T* pointer)
{
	pointer->~T();
}


template<class T>
inline destory(T first, T last)
{
	_destory(first, last, value_type(first));
}

template<class Forward,class T>
inline _destory(Forward first, Forward last, T*)
{
	//typedef typename _type_traits<T>::has_trivial_destructor trivial_destructor;
	_destory_aux(first, last, trivial_destructor());
}

template<class T>
inline _destory_aux(T first, T last, _false_type)
{
	for (; first < last; ++first)
		destory(&*first);
}

template<class T>
inline _destory_aux(T first, T last, _true_type)
{}

