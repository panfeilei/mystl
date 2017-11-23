#include "stl_alloc.h"

typedef _default_alloc_template<true, 0> alloc;


template <class T, Alloc = alloc>
class vector
{
public:
	typedef T 				value_type;
	typedef T* 				pointer;
	typedef const T* 		const_pointer;
	typedef T* 				iterator;
	typedef const T* 		const_iterator;
	typedef T& 				reference;
	typedef constT& 		const_reference;
	typedef size_t 			size_type;
 	typedef ptrdiff_t 		difference_type;
private:
	 iterator start;
	 iterator finish;
	 iterator end_of_storage;
protected:
	 typedef simple_alloc<T, Alloc> __data_allocator;
	 void insert_aux(iterator position, const T& x)
	 {
		if(finish != end_of_storage)
		{
			costruct(finish, *(finish - 1));
			++finish;
			T x_copy = x;
			//copy_backward(position, finish - 2, finish - 1);
			*position = x_copy;
		}
		else
		{
			size_type old_size = size();
			size_type len = old_size != 0 ?  2 *old_size : 1;
			iterator new_start = __data_allocator::allocate(len);
			iterator new_finish = new_start;
			try
			{
				//new_finish = ininitialized_copy();
			}
		}
	 }
	 void fill_initialliza(size_type n, const T& value)
	 {
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	 };
	 void deallocate()
	 {
	 	if(start)
	 		__data_allocator::deallocate(start, end_of_storage - start);
	 }

	 iterator allocate_and_fill(size_type n, const T& value)
	 {
	 	iterator result = __data_allocator::allocate(n);
		//uninitialized_fill_n(result, n, x);
		return result;
	 }
public:
	explicit vector():start(0), finish(0), end_of_storage(0){}
	vector(size_type n, const T& value){fill_initialliza(n,value);}
	vector(const vector<T, Alloc> &x)
	{
		//
	}
	
	template<class inputItertor>
	vector(inputItertor begin, inputItertor end)
	{
		//
	}

	~vector()
	{
		destory(start, finish);
		deallocate();
	}
	explicit vector(size_type n){fill_initialliza(n, T());}

	iterator begin(){return start;};
	iterator end(){return finish};
	size_type size(){return size_type(end() - begin());}
	size_type capacity() const {end_of_starage - begin();}
	bool empty(){return begin() == end();}
	reference operator[](size_type n){return *(begin() + n);} 
	reference front(){return *begin();}
	reference back(){return *(end() - 1);}
	void push_back(const T& x)
	{
		if(finish != end_of_storage)
		{
			construct(finish, x);
			++finish;
		}
		else
		{
			//insert_aux(end(), x);
		}
	}

	void pop_back()
	{
		--finish;
		destory(finish);
	}

	iterator erase(iterator position)
	{
		if(position + 1 != end())
			//copy(position + 1, finish, position);
		--finish;
		destory(finish);
		return position;
	}

	void resize(size_type new_size, const T& x)
	{
		if(new_size < size())
			//erase(begin() + new_size, end());
		
		else
			//insert(end(), new_size - size(), x);
	}

	void resize(size_type new_size){resize(new_size, T());}
	//void clear(){erase(begin(), end());}
};
