#ifndef STL_ALLOC_H
#define STL_ALLOC_H
#include "stl_construct.h"
#include "stdlib.h"

#define __THROW_BAD_ALLOC throw std::bad_alloc()
enum {_ALIGN = 8};
enum {_MAX_BYTES = 128};
enum {_NFREELISTS = _MAX_BYTES / _ALIGN};

template<int inst>
class _malloc_alloc_template
{
private:
	static void* oom_malloc(size_t);
	static void* oom_realloc(void *, size_t);
	static void (* _malloc_alloc_oom_handler)();
public:
	static void *allocate(size_t n)
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
void (* _malloc_alloc_template<inst>::_malloc_alloc_oom_handler)()=0;


template<int inst>
void* _malloc_alloc_template<inst>::oom_malloc(size_t n)
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
void* _malloc_alloc_template<inst>::oom_realloc(void* p, size_t n)
{
	void (*my_malloc_handler)();
	void *result;

	for (;;)  
	{
		my_malloc_handler = _malloc_alloc_oom_handler;
		if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = realloc(p, n);
		if (result) return(result);
	}
}

template<bool threads, int inst>
class _default_alloc_template
{
private:
	static char* start_free;
 	static char* end_free;
	static size_t heap_size;
public:
	static size_t ROUND_UP(size_t bytes)
	{
		return (bytes + _ALIGN - 1) & ~(_ALIGN - 1);
	} 
	
	union obj {
		union obj * free_list_link;
		char client_data[1];
	};

	static obj* volatile free_list[_NFREELISTS];
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return((bytes + _ALIGN - 1) / (_ALIGN - 1));
	}

	static void* allocate(size_t n)
	{
		obj* volatile* my_free_list;
		obj* result;

		if (n > (size_t)_MAX_BYTES)
		{
			return _malloc_alloc_template<0>::allocate(n);
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if (result == 0)
		{
			void* r = refill(ROUND_UP(n));
			return r;
		}

		*my_free_list = result->free_list_link;
		return result;
	}

	static void deallocate(void *p, size_t n)
	{
		obj* q = (obj *)p;
		obj* volatile* my_free_list;

		if (n > (size_t)_MAX_BYTES)
		{
			_malloc_alloc_template<0>::deallocate(p, n);
			return;
		}

		my_free_list = free_list + FREELIST_INDEX(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}

	static void* refill(size_t n)
	{
		int nobj = 20;
		char* chunk = chunk_alloc(n, nobj);
		obj* volatile* my_free_list;
		obj* result;
		obj* curren_obj;
		obj* next_obj;
		int i;

		if (1 == nobj) return chunk;
		my_free_list = free_list + FREELIST_INDEX(n);

		result = (obj *)chunk;
		*my_free_list = next_obj = (obj *)(chunk + n);

		for (i = 1;; i++)
		{
			curren_obj = next_obj;
			next_obj = (obj *)((char *)next_obj + n);
			if (nobj - 1 == i)
			{
				curren_obj->free_list_link = 0;
				break;
			}
			else
				curren_obj->free_list_link = next_obj;

		}
		return result;
	}
    
    static char* chunk_alloc(size_t size, int &nobj)
	{
		char *result;
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
				obj* volatile* my_free_list = free_list + FREELIST_INDEX(left_byte);
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj*)start_free;
			}

			start_free = (char *)malloc(byte_to_get);
			if(start_free == 0)
			{
				size_t i;
				obj* volatile* my_free_list;
				obj* p;

				for(i = size; i<_MAX_BYTES; i+= _ALIGN)
				{
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if(0 != p)
					{
						*my_free_list = p->free_list_link;
						start_free = (char*)p;
						end_free = start_free + i;
						return chunk_alloc(size, nobj);
					}
				}
				end_free = 0;
				start_free = (char*)_default_alloc_template::allocate(byte_to_get);
			}
			heap_size += byte_to_get;
			end_free = start_free + byte_to_get;
			return chunk_alloc(size, nobj);
		}
	}
};

template<bool threads, int inst>
char* _default_alloc_template<threads, inst>::start_free = 0;

template<bool threads, int inst>
char* _default_alloc_template<threads, inst>::end_free = 0;

template<bool threads, int inst>
size_t _default_alloc_template<threads, inst>::heap_size = 0;

template <bool threads, int inst>
typename _default_alloc_template<threads, inst>::obj* volatile
_default_alloc_template<threads, inst>::free_list[_NFREELISTS]=
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

template <class _TP, class _Alloc>
class simple_alloc
{
public:
	static _TP* allocate(size_t n)
	{
		return 0 == n ? 0 : (_TP*) _Alloc::allocate(n * sizeof(_TP));
	}
	static _TP* allocate(void)
	{
		return (_TP*) _Alloc::allocate(sizeof(_TP));
	}
	static _TP* deallocate(_TP* p)
	{
		_Alloc::deallocate(p,  sizeof(_TP));
	}
	static _TP* deallocate(_TP* p, size_t n)
	{
		if(0 != n) _Alloc::deallocate(p,  n * sizeof(_TP));
	}
	
};

#endif

 
