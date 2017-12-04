#include "stl_alloc.h"
#include "stl_algobase.h"
#include "stl_uninitialized.h"
#include "stl_iterator.h"
typedef _default_alloc_template<true, 0> alloc;
#define MAX(x,y) ((x)>(y)?(x):(y))

template <class T, class Alloc = alloc>
class vector
{
public:
	typedef T 				value_type;
	typedef T* 				pointer;
	typedef const T* 		const_pointer;
	typedef T* 				iterator;
	typedef const T* 		const_iterator;
	typedef T& 				reference;
	typedef const T& 		const_reference;
	typedef size_t 			size_type;
 	typedef std::ptrdiff_t 		difference_type;
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
			construct_stl(finish, *(finish - 1));
			++finish;
			T x_copy = x;
			copy_backward_stl(position, finish - 2, finish - 1);
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
				new_finish = uninitialized_copy(start, position, new_start);
				construct_stl(new_finish, x);
				++new_finish;

				//��������Ƿ��б�Ҫ��
				/*������䲻�������Ʊ��ÿռ䣬�Ǵ�position��end������*/
				new_finish = uninitialized_copy(position, finish, new_finish);
			}
			catch(...)
			{
				destory_stl(new_start, new_finish);
				__data_allocator::deallocate(new_start, len);
				throw;
			}

			destory_stl(begin(), end());
			deallocate();

			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
			
		}
	 }
	 
	 void fill_initialliza(size_type n, const T& value)
	 {
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	 }

	 template<class Forward>
	 iterator allocate_and_copy(Forward first, Forward last, size_type n)
	 {
	 	iterator result = __data_allocator::allocate(n);
		uninitialized_copy(first, last, result);
		return result;
	 }

	 
	 void deallocate()
	 {
	 	if(start)
	 		__data_allocator::deallocate(start, end_of_storage - start);
	 }

	 iterator allocate_and_fill(size_type n, const T& value)
	 {
	 	iterator result = __data_allocator::allocate(n);
		uninitialized_fill_n(result, n, value);
		return result;
	 }

	 template<class Integer>
	 void initialize_aux(Integer n, Integer value, __true_type)
	 {
	 	fill_initialliza(n,value);
	 }

	template<class InputIterator>
	void initialize_aux(InputIterator first, InputIterator last, __false_type)
	{
		size_type n = 0;
		n = distance(first, last);
		start = __data_allocator::allocate(n);
		end_of_storage = start + n;
		finish = uninitialized_copy(first, last, start);
	}
	 
public:
	explicit vector():start(0), finish(0), end_of_storage(0){}
	vector(size_type n, const T& value){fill_initialliza(n,value);}
	vector(const vector<T, Alloc> &x)
	{
		size_type n = x.size();
		start = __data_allocator::allocate(n);
		end_of_storage = start + n;
		finish = uninitialized_copy(x.begin(), x.end(), start);
	}
	
	template<class inputItertor>
	vector(inputItertor first, inputItertor last)
	{
		typedef typename Is_integer<inputItertor>::_integer is_integer;
		initialize_aux(first, last, is_integer());
	}

	~vector()
	{
		destory_stl(start, finish);
		deallocate();
	}
	explicit vector(size_type n){fill_initialliza(n, T());}

	iterator begin() const {return start;}
	iterator end() const {return finish;}
	size_type size() const {return size_type(end() - begin());}
	size_type capacity() const {end_of_storage - begin();}
	bool empty(){return begin() == end();}
	reference operator[](size_type n){return *(begin() + n);} 
	reference front(){return *begin();}
	reference back(){return *(end() - 1);}
	
	template<class Tp>
	vector<Tp>& operator=(const vector<T, Alloc> &x)
	{
		if(this != &x)
		{
			size_type n = x.size();
			if(n > capacity())
			{
				iterator tmp = allocate_and_copy(x.begin(), x.end(), n);
				destory_stl(start, finish);
				deallocate();
				start = tmp;
				end_of_storage = start + n;
			}
			else if(size() > n)
			{
				iterator i = copy_stl(x.begin(), x.end(), start);
				destory_stl(i, finish);
			}
			else
			{
				copy_stl(x.begin(), x.begin() + size(), start);
				uninitialized_copy(x.begin() + size(), x.end(), finish);
			}
			finish = start + n;
		}
		return *this;	
	}
	
	void push_back(const T& x)
	{
		if(finish != end_of_storage)
		{
			construct_stl(finish, x);
			++finish;
		}
		else
		{
			insert_aux(end(), x);
		}
	}

	void pop_back()
	{
		--finish;
		destory_stl(finish);
	}

	iterator erase(iterator position)
	{
		if(position + 1 != end())
			copy_stl(position + 1, finish, position);
		--finish;
		destory_stl(finish);
		return position;
	}
	
	iterator erase(iterator first, iterator last)
	{
		iterator i;
		i = copy_stl(last, finish, first);
		destory_stl(i, finish);
		finish = finish - (last - first);
		return first;
	}

	void resize(size_type new_size, const T& x)
	{
		if(new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - size(), x);
	}

	void resize(size_type new_size){resize(new_size, T());}
	void clear(){erase(begin(), end());}
	
	iterator insert(iterator pos, const T& x)
	{
		size_type n = pos - begin();
		if(finish != end_of_storage && pos == end())
		{
			construct_stl(finish, x);
			++finish;
		}
		else
		{
			insert_aux(pos, x);
		}
		return begin() + n;
	}

	template<class CopyIterator>
	void insert(iterator position, const CopyIterator _first, const CopyIterator _last)
	{
		if(_first != _last)
		{
			iterator old_finish = finish;
			size_type n = distance(_first, _last);
			if(end_of_storage - finish > n)
			{
			
				size_type elem_after = finish - position;
				if(elem_after > n)
				{
					uninitialized_copy(finish - n, finish, finish);
					finish += n;
					copy_backward(position, old_finish - n, finish);
					copy_stl(_first, _last, position);
				}
				else
				{
					uninitialized_copy(_first + elem_after, _last, finish);
					finish += n - elem_after;
					uninitialized_copy(position, old_finish, finish);
					finish += elem_after;
					copy_stl(_first, _first + elem_after, position);
				}
				
			}
			else
			{
				size_type old_size = size(); 
				size_type new_len = old_size + MAX(old_size, n);
				iterator new_start = __data_allocator::allocate(new_len);
				iterator new_finish = new_start;
				try
				{
					new_finish = uninitialized_copy(start, position, new_start);
					new_finish = uninitialized_copy(_first, _last, new_finish);
					new_finish = uninitialized_copy(position, finish, new_finish);
				}
				catch(...)
				{
					destory_stl(new_start, new_finish);
					__data_allocator::deallocate(new_start, n);
					throw;
				}
				destory_stl(start, finish);
				deallocate();
				start = new_start;
				finish = new_finish;
				end_of_storage = new_start + new_len;
			}
		}
	}

	
	void insert(iterator position, size_type n, const T& x)
	{
		if(n != 0)
		{
			if(size_type(end_of_storage - finish) >= n)
			{
				T x_copy = x;
				const size_type elems_after = finish - position;
				iterator old_finish = finish;
				if(elems_after > n)
				{
					uninitialized_copy(finish - n, finish, finish);
					finish += n;
					copy_backward(position, old_finish - n, old_finish);
					fill(position, position + n, x_copy);
				}
				else
				{
					uninitialized_fill_n(finish, n - elems_after, x_copy);
					finish += n - elems_after;
					uninitialized_copy(position, old_finish, finish);
					finish += elems_after;
					fill(position, old_finish, x_copy);
				}

				//������Ϊ���������ifelse��������滻Ϊ���´���
				/*
				copy_backward(position, finish, finish + n);
				uninitialized_copy(position, position + n, x_copy);
				*/
			}
			else
			{
				const size_type old_size = size();
				const size_type len = old_size + MAX(old_size, n);
				iterator new_start = __data_allocator::allocate(len);
				iterator new_finish = new_start;
				try
				{
					new_finish = uninitialized_copy(start, position, new_start);
					new_finish = uninitialized_fill_n(new_finish, n, x);
					new_finish = uninitialized_copy(position, finish, new_finish);
				}
				catch(...)
				{
					destory_stl(new_start, new_finish);
					__data_allocator::deallocate(new_start, len);
					throw;
				}

				/*��Ҫ������������*/
				destory_stl(start, finish);
				/*��Ҫ�ͷű���ռ���ڴ�*/
				deallocate();
				start = new_start;
				finish = new_finish;
				end_of_storage = new_start + len;
			}
		}
	}
};
