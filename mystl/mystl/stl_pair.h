#ifndef STL__PAIR_H
#define STL_PAIR_H
template<class T1, class T2>
struct myPair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	myPair():first(T1()), second(T2()){}
	myPair(const T1& a, const T2& b):first(a), second(b){}

	template<class U1, class U2>
	myPair(const myPair<U1, U2>& p):first(p.first), second(p.second){}
};

template<class T1, class T2>
inline bool operator==(const myPair<T1, T2>& x, const myPair<T1, T2>& y)
{
	return x.first == y.first && x.second == y.second;
}

template<class T1, class T2>
inline bool operator<(const myPair<T1, T2>& x, const myPair<T1, T2>& y)
{
	return x.first < y.first || (!(y.first < x.first) && (x.second < y.second));
}
template<class T1, class T2>
inline myPair<T1, T2> make_pair(const T1& x, const T2& y)
{
	return myPair<T1, T2>(x, y);
}


#endif
