
#ifndef STL_ALGOBASE_H
#define STL_ALGOBASE_H

#include "stl_iterator.h"
#include <string.h>
#include "type_traits.h"

template<class Forward, class Tp>
void fill(Forward first, Forward last, const Tp& value)
{
	for(;first != last; ++first)
		*first = value;
}

template<class Forward, class Size,class Tp>
void fill_n(Forward first, Size n, const Tp& value)
{
	for(; n > 0; --n, ++first)
		*first = value;
	return first;
}


template<class InputIterator, class OutputIterator, class Distance>
inline OutputIterator __copy_d(InputIterator first, InputIterator last,
								OutputIterator result, Distance *)
{
	for(Distance n = last - first; n > 0; --n, ++result, ++first)
		*result = *first;
	return result;
}


template<class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last,
								OutputIterator result, input_iterator_tag)
{
	for(; first != last; ++result, ++first)
		*result = *first;
	return result;
}
								
template<class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last,
								OutputIterator result, random_iterator_tag)
{
	__copy_d(first, last, result, distance_type(first));
}


/*class point*/
template<class T>
inline T* __copy_t(const T* first, const T* last, T* result, __false_type)
{
	return __copy_d(first, last, result, (std::ptrdiff_t*)0);
}


/*normal point*/
template<class T>
inline T* __copy_t(const T* first, const T* last, T* result, __true_type)
{
	memmove(result, first, sizeof(T) * (last - first));
	return result + (last - first);
}

template<class InputIterator, class OutputIterator>
struct __copy_dispatch
{
	static OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		return  __copy(first, last, result, iterator_category(first));
	}
};

template<class T>
struct __copy_dispatch<T*, T*>
{
	static T* copy(T* first, T* last, T* result)
	{
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}
};

template<class T>
struct __copy_dispatch<const T*, T*>
{
	T* copy(const T* first, const T* last, const T* result)
	{
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}
};
	
template <class InputIterator, class OutputIterator>
inline OutputIterator copy_stl(InputIterator first, InputIterator last, OutputIterator result)
{
	return __copy_dispatch<InputIterator, OutputIterator>::copy(first, last, result);
}

inline char* copy_stl(char* first, char* last, char* result)
{
	memmove(result, first, last - first);
	return result + (last - first);
}


inline wchar_t* copy_stl(const wchar_t* first, const wchar_t* last, wchar_t* result)
{
	memmove(result, first, last - first);
	return result + (last - first);
}

template<class InputIterator, class OutputIterator, class Distance>
inline OutputIterator __copy_backward_d(InputIterator first, InputIterator last,
								OutputIterator result, Distance *)
{
	for(Distance n = last - first; n > 0; --n)
		*--result = *--last;
	return result;
}

/*class point*/
template<class T>
inline T* __copy_backward_t(const T* first, const T* last, T* result, __false_type)
{
	return __copy_backward_d(first, last, result, (std::ptrdiff_t*)0);
}

/*normal point*/
template<class T>
inline T* __copy_backward_t(const T* first, const T* last, T* result, __true_type)
{
	const ptrdiff_t num = last - first;
	memmove(result - num, first, sizeof(T) * num);
	return result - num;
}


template<class InputIterator, class OutputIterator>
inline OutputIterator __copy_backward(InputIterator first, InputIterator last,
								OutputIterator result, input_iterator_tag)
{
	while(last != first)
		*--result = *--first;
	return result;
}
								
template<class InputIterator, class OutputIterator>
inline OutputIterator __copy_backward(InputIterator first, InputIterator last,
										OutputIterator result, random_iterator_tag)
{
	__copy_backward_d(first, last, result, distance_type(first));
}

template<class InputIterator, class OutputIterator>
struct __copy_backward_dispatch
{
	static OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		return  __copy_backward(first, last, result, iterator_category(first));
	}
};

template<class T>
struct __copy_backward_dispatch<T*, T*>
{
	static T* copy(T* first, T* last, T* result)
	{
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_backward_t(first, last, result, t());
	}
};

template <class InputIterator, class OutputIterator>
inline OutputIterator copy_backward_stl(InputIterator first, InputIterator last, OutputIterator result)
{
	return __copy_backward_dispatch<InputIterator, OutputIterator>::copy(first, last, result);
}

#endif
