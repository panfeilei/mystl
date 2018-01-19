#ifndef STL_MAP_H
#define STL_MAP_H
#include "./stl_function.h"
template<class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map
{
public:
	typedef Key key_type;
	typedef T data_type;
	typedef T mapped_type;
	typedef pair<const Key, T> value_type;
	typedef Compare key_compare;

	class value_compare: public binary_function<value_type, value_type, bool>
	{
		friend class map<Key, T, Compare, Alloc>;
		protected:
			Compare comp;
			value_compare(Compare c):comp(c) {}
		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
	};
private:
	typedef  rb_tree<key_type, value_type,
	select1st<value_type>, key_compare, Alloc> rep_type;
	rep_type t;
public:
	typedef typename rep_type::pointer pointer;
	typedef typename rep_type::const_pointer const_pointer;
	typedef typename rep_type::reference reference;
	typedef typename rep_type::const_reference const_reference;
	typedef typename rep_type::iterator iterator;
	typedef typename rep_type::const_iterator const_iterator;
	//typedef typename rep_type::reverse_iterator reverse_iterator;
	//typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
	typedef typename rep_type::size_type size_type;
	typedef typename rep_type::difference_type difference_type;

	map(): t(Compare()) {};
	explicit map(const Compare& comp): t(comp){}

	template <class InputIterator>
	map(InputIterator first, InputIterator last):t(Compare()) 
	{ t.insert_unique(first, last);}

	template<class InputIterator>
	map(InputIterator first, InputIterator last, const Compare& comp):t(comp)
	{ t.insert_unique(first, last);}

	map(const map<Key, T, Compare, Alloc>& x):t(x.t){}

	map<Key, T, Compare, Alloc>& operator=(const map<Key, T, Compare, Compare>& x)
	{
		t = x.t;
		return *this;
	}

	key_compare key_comp() const {return t.key_comp();}
	value_compare value_comp() const {return value_compare(t.key_comp());}
	iterator begin() {return t.begin();}
	const_iterator begin() const {return t.begin();}
	iterator end() {return t.end();}
	const_iterator end() const {return t.end();}
	//reverse_iterator rbegin() {return t.rbegin();}
	//const_reverse_iterator rbegin() const {return t.rbegin();}
	//reverse_iterator rbegin() const {return t.rend();}
	//const_reverse_iterator rbegin() const {return t.rend();}
 	bool empty() const {return t.empty();}
	size_type size() const {return t.size();}
	size_type max_size() const {return t.max_size();}
    T& operator[](const key_type& k)
    {
        return (*(insert(value_type(k, T())).first)).second;
    }
    
    pair<iterator, bool> insert(const value_type& x)
    {
        return t.insert_unique(x);
    }
    
};

#endif

