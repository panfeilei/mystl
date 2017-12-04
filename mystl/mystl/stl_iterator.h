
#ifndef STL_ITERATOR_H
#define STL_ITERATOR_H
#include "stl_alloc.h"

struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_iterator_tag:public bidirectional_iterator_tag{};

template<class _iterator>
struct iterator_traits
{
	typedef typename _iterator::iterator_category 	iterator_category;
	typedef typename _iterator::value_type 			value_type;
	typedef typename _iterator::pointer				pointer;
	typedef typename _iterator::difference_type 	difference_type;
	typedef typename _iterator::reference 			reference;
	
};

template<class Tp>
struct iterator_traits<Tp*>
{
	typedef random_iterator_tag  	iterator_category;
	typedef  Tp 					value_type;
	typedef  Tp* 					pointer;
	typedef  std::ptrdiff_t 		difference_type;
	typedef  Tp& 					reference;
	
};

template<class Tp>
struct iterator_traits<const Tp*>
{
	typedef  random_iterator_tag	iterator_category;
	typedef  Tp 					value_type;
	typedef  const Tp* 				pointer;
	typedef  std::ptrdiff_t 		difference_type;
	typedef  const Tp& 				reference;
	
};

template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
	typedef typename iterator_traits<InputIterator>::iterator_category category;
	return __distance(first, last, category());
}


template<class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag)
{
	typename iterator_traits<InputIterator>::difference_type n = 0;
	while(first != last)
	{
		++first; ++n;
	}
	return n;
}

template<class RandomIterator>
inline typename iterator_traits<RandomIterator>::difference_type
__distance(RandomIterator first, RandomIterator last, random_iterator_tag)
{
	return last - first;
}



template <class InputIterator, class Distance>
inline void advance(InputIterator &i, Distance n, random_iterator_tag)
{
	_advance(i, n, iterator_categoty(i));
}


template <class InputIterator, class Distance>
inline void __advance(InputIterator &i, Distance n, input_iterator_tag)
{
	while(n--) ++i;
}

template <class bidirectionalIterator, class Distance>
inline void __advance(bidirectionalIterator &i, Distance n, bidirectional_iterator_tag)
{
	if(n >= 0)
		while(n--) ++i;
	else
		while(n++) --i;
}

template <class randomIterator, class Distance>
inline void __advance(randomIterator &i, Distance n, random_iterator_tag)
{
	i += n;
}


template <class It>
inline typename iterator_traits<It>::iterator_category
iterator_category(const It&)
{
	typedef typename iterator_traits<It>::iterator_category catrgory;
	return catrgory();
}


template <class Iter>
inline typename iterator_traits<Iter>::value_type*
value_type(const Iter&)
{
	return static_cast<typename iterator_traits<Iter>::value_type*>(0);
}

#endif



