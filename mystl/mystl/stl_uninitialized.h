#ifndef STL_UNINITIALIZED_H
#define STL_UNINITIALIZED_H

template<class Input, class Forward>
Forward uninitialized_copy(Input first, Input last, Forward result)
{
	return __uninitialized_copy(first, last, result, value_type(result));
}


inline wchar_t* uninitialized_copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
{
	memmove(result, first, last-first);
	return result + (last - first);
}


template<class Input, class Forward, class T>
Forward __uninitialized_copy(Input first, Input last, Forward result, T*)
{
	typedef typename __type_traits<T>::is_POD_type is_POD;
	return __uninitialized_copy_aux(first, last, result, is_POD());
}



template<class Input, class Forward>
Forward __uninitialized_copy_aux(Input first, Input last, Forward result, __true_type)
{
	//return copy_stl(first, last, result);
}

template<class Input, class Forward>
Forward __uninitialized_copy_aux(Input first, Input last, Forward result, __false_type)
{
	Forward cur = result;
	for(; first != last; ++first, ++cur)
		consturct(&*cur, *first);
	return cur;
}

template<class Forward, class T>
void uninitialized_fill(Forward first, Forward last, const T& x)
{
	__uninitialized_fill(first, last, x, value_type(first));
}

template<class Forward, class T, class T1>
void __uninitialized_fill(Forward first, Forward last, const T& x)
{
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	__uninitialized_fill_aux(first, last, x, is_POD());
}


template<class Forward, class T>
void __uninitialized_fill_aux(Forward first, Forward last, const T& x, __true_type)
{
	//fill(first, last, x);
}

template<class Forward, class T>
void __uninitialized_fill_aux(Forward first, Forward last, const T& x, __false_type)
{
	Forward cur = first;
	for(; cur != last; ++cur)
		construct(&*cur, x);
}


template<class Forward, class Size ,class T>
void uninitialized_fill_n(Forward first, Size n, const T& x)
{
	return __uninitialized_fill_n(first, n, x, value_type(first))
}

template<class Forward, class Size ,class T, class T1>
inline Forward __uninitialized_fill_n(Forward first, Size n, const T& x, T1*)
{
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first, n, x, is_POD());
}

template<class Forward, class Size ,class T>
inline Forward __uninitialized_fill_n_aux(Forward first, Size n, const T& x, __true_type)
{
	//return fill_n(first, n, x);
}

template<class Forward, class Size ,class T>
inline Forward __uninitialized_fill_n_aux(Forward first, Size n, const T& x, __false_type)
{
	Forward cur = first;
	for(; n > 0; --n, ++cur)
		construct(&*cur, x);
	return cur;
}

#endif
