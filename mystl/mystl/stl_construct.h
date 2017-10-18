#pragma once
#include <new.h>
#include <iostream>

#define __THROW_BAD_ALLOC throw bad_alloc

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


template<int inst>
class _malloc_alloc_template
{
private:
	static void *oom_malloc(size_t);
	static void *oom_realloc(void *, size_t);
	static void(*_malloc_alloc_oom_handler)();
public:
	static void *allocate(rsize_t n)
	{
		void *result = malloc(n);
		if (0 == result) result = oom_malloc(n);
		return result;
	}

	static void deallocate(void *p, size_t)
	{
		free(p);
	}

	static void *reallocate(void *p, size_t new_sz)
	{
		void *result = realloc(p, new_sz);
		if (result == 0) result = oom_realloc(p, new_sz);
		return result;
	}

	static void (* set_malloc_handler(void (*f))) ()
	{
		void(*old)() = _malloc_alloc_oom_handler;
		_malloc_alloc_oom_handler = f;
		return (old);
	}
};


template<int inst>
void (*_malloc_alloc_template::_malloc_alloc_oom_handler)() = 0; //分配内存失败的处理函数

template<int inst>
void *_malloc_alloc_template::oom_malloc(rsize_t n)
{
	void (*my_malloc_handler)();
	void *result;

	for (;;)
	{
		my_malloc_handler = _malloc_alloc_oom_handler;
		if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = malloc(n);
		if (result) return(result);
	}
}

template<int inst>
void *_malloc_alloc_template::oom_realloc()
{
	void (*my_malloc_handler)();
	void *result;

	for (;;)  
	{
		my_malloc_handler = _malloc_alloc_oom_handler;
		if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = realloc(n);
		if (result) return(result);
	}
}


 