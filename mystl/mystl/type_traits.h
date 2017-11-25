struct __true_type {
};

struct __false_type {
};


template <class type>
struct __type_traits
{
	typedef __true_type this_dummy_member_must_be_first;
	typedef __false_type    has_trivial_default_constructor;
   	typedef __false_type    has_trivial_copy_constructor;
   	typedef __false_type    has_trivial_assignment_operator;
   	typedef __false_type    has_trivial_destructor;
   	typedef __false_type    is_POD_type;
};

template <>
struct __type_traits<char>
{
	typedef __true_type this_dummy_member_must_be_first;
	typedef __false_type    has_trivial_default_constructor;
   	typedef __false_type    has_trivial_copy_constructor;
   	typedef __false_type    has_trivial_assignment_operator;
   	typedef __false_type    has_trivial_destructor;
   	typedef __false_type    is_POD_type;
};

template <>
struct __type_traits<int>
{
	typedef __true_type this_dummy_member_must_be_first;
	typedef __false_type    has_trivial_default_constructor;
   	typedef __false_type    has_trivial_copy_constructor;
   	typedef __false_type    has_trivial_assignment_operator;
   	typedef __false_type    has_trivial_destructor;
   	typedef __false_type    is_POD_type;
};

template <>
struct __type_traits<double>
{
	typedef __true_type this_dummy_member_must_be_first;
	typedef __false_type    has_trivial_default_constructor;
   	typedef __false_type    has_trivial_copy_constructor;
   	typedef __false_type    has_trivial_assignment_operator;
   	typedef __false_type    has_trivial_destructor;
   	typedef __false_type    is_POD_type;
};


template <>
struct __type_traits<char*>
{
	typedef __true_type this_dummy_member_must_be_first;
	typedef __false_type    has_trivial_default_constructor;
   	typedef __false_type    has_trivial_copy_constructor;
   	typedef __false_type    has_trivial_assignment_operator;
   	typedef __false_type    has_trivial_destructor;
   	typedef __false_type    is_POD_type;
};

template <>
struct __type_traits<int*>
{
	typedef __true_type this_dummy_member_must_be_first;
	typedef __false_type    has_trivial_default_constructor;
   	typedef __false_type    has_trivial_copy_constructor;
   	typedef __false_type    has_trivial_assignment_operator;
   	typedef __false_type    has_trivial_destructor;
   	typedef __false_type    is_POD_type;
};

template <>
struct __type_traits<double*>
{
	typedef __true_type this_dummy_member_must_be_first;
	typedef __false_type    has_trivial_default_constructor;
   	typedef __false_type    has_trivial_copy_constructor;
   	typedef __false_type    has_trivial_assignment_operator;
   	typedef __false_type    has_trivial_destructor;
   	typedef __false_type    is_POD_type;
};













