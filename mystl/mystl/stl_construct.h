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
void (*_malloc_alloc_template::_malloc_alloc_oom_handler)() = 0; //分配内存失败的处理函�?

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
enum {_ALIGN = 8};
enum {_MAX_BYTES = 128};
enum {_NFREELISTS = _MAX_BYTES / _ALIGN};
template<bool threads,int inst>
class _default_alloc_template
{
private:
	static char* start_free = 0;
 	static char* end_free = 0;
	static heap_size = 0;
	static rsize_t ROUND_UP(rsize_t bytes)
	{
		return (bytes + _ALIGN - 1) & ~(_ALIGN - 1);
	} 
	
	union obj {
		union obj * free_list_link;
		char client_data[1];
	};

	static obj *volatile free_list[_NFREELISTS];
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return((bytes + _ALIGN - 1) / (_ALIGN - 1));
	}

	static void *allocate(size_t n)
	{
		obj * volatile *my_free_list;
		obj * result;

		if (n > (size_t)_MAX_BYTES)
		{
			return _malloc_alloc_template::allocate(n);
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if (result == 0)
		{
			void *r = refill(ROUND_UP(n));
			return r;
		}

		*my_free_list = result->free_list_link;
		return result;
	}

	static void deallocate(void *p, size_t n)
	{
		obj *q = (obj *)p;
		obj *volatile * my_free_list;

		if (n > (size_t)_MAX_BYTES)
		{
			_malloc_alloc_template::deallocate(p, n);
			return;
		}

		my_free_list = free_list + FREELIST_INDEX(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}

	void * refill(size_t n)
	{
		int nobj = 20;
		char *chunk = chunk_alloc(n, nobj);
		obj *volatile *my_free_list;
		obj *result;
		obj *curren_obj, *next_obj;
		int i;

		if (1 == nobj) return chunk;
		my_free_list = free_list + FREELIST_INDEX(n);

		result = (obj *)chunk;
		*my_free_list = next_obj = (obj *)(chunk + n);

		for (i = 1;; i++)
		{
			curren_obj = next_obj;
			next_obj = (obj *)((char *)next_obj + n);
			if (nobj - 1 == n)
			{
				curren_obj->free_list_link = 0;
				break;
			}
			else
				curren_obj->free_list_link = next_obj;

		}
		return result;
	}
    
    char * chunk_alloc(size_t size, int &nobj)
	{
		size_t *result;
		size_t total_byte = size * nobj;
		size_t left_byte = start_free - end_free;

		if(left_byte > total_byte)
		{
			result = start_free;
			start_free = start_free + total_byte;
			return result;
		}
		else if(left_byte > size)
		{
			nobj = left_byte / size;
			total_byte = nobj * size;
			result = start_free;
			start_free += total_byte;
			return result;
		}
		else
		{
			size_t byte_to_get = total_byte * 2;
			if(left_byte > 0)
			{
				obj* my_free_list = free_list + FREELIST_INDEX(left_byte);
				((obj*)start_free)->free_list = *my_free_list;
				*my_free_list = (obj*)start_free;
			}

			start_free = (char *)malloc(byte_to_get);
			if (start_free == 0)
			{
			}
			heap_size += byte_to_get;
			end_free = start_free + byte_to_get;
			return chunk_alloc(size, nobj);

		}

		
	}
};


 