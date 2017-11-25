
#ifndef STL_ALGOBASE_H
#define STL_ALGOBASE_H

#include "stl_iterator.h"
template <class InputIterator, clss OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator first, OutputIterator result)
{
	return __copy_dispatch<InputIterator, OutputIterator>(first, last, result);
}

inline char* copy(char* first, char* last, char* result)
{
	memmove(result, first, last - first);
	return result + (last - first);
}


inline char* copy(const wchar_t* first, const wchar_t* last, const wchar_t* result)
{
	memmove(result, first, last - first);
	return result + (last - first);
}

template<class InputIterator, class OutputIterator>
struct __copy_dispatch
{
	OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result)
	{
		//return  __copy(first, last, result, iterator_traits(first));
	}
};

template<class T>
struct __copy_dispatch<T*, T*>
{
	T* operator()(T* first, T* last, T* result)
	{
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		//return __copy_t(first, last, result, t());
	}
};

template<class T>
struct __copy_dispatch<const T*, T*>
{
	T* operator()(const T* first, const T* last, const T* result)
	{
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		//return __copy_t(first, last, result, t());
	}
};


#endif
