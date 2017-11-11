template<class _iterator>
struct iterator_traits
{
	typedef typename _iterator::iterator_category 	iterator_category;
	typedef typename _iterator::value_type 			value_type;
	typedef typename _iterator::pointer				pointer;
	typedef typename _iterator::difference_type 	difference_type;
	typedef typename _iterator::reference 			reference;
	
}

template<class Tp>
struct iterator_traits<Tp*>
{
	//typedef typename _iterator::iterator_category iterator_category;
	typedef  Tp 			value_type;
	typedef  Tp* 			pointer;
	typedef  ptrdiff_t 		difference_type;
	typedef  Tp& 			reference;
	
}

