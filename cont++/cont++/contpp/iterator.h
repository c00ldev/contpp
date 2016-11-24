#pragma once

namespace contpp
{

#ifdef _WIN64
	typedef unsigned __int64 size_t;
	typedef __int64          ptrdiff_t;
	typedef __int64          intptr_t;
#else
	typedef unsigned int     size_t;
	typedef int              ptrdiff_t;
	typedef int              intptr_t;
#endif

	template<class Category,
		class T,
		class Diff = ptrdiff_t,
		class Pointer = T *,
		class Reference = T&>
		struct iterator
	{
		using iterator_category = Category;
		using value_type = T;
		using difference_type = Diff;

		using pointer = Pointer;
		using reference = Reference;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag, output_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	template<class, class = void>
	struct iterator_traits_base {};

	template<class...>
	struct param_tester
	{
		using type = void;
	};

	template<class... Types>
	using void_t = param_tester<Types>::type;

	template<class It>
	struct iterator_traits_base<It, void_t<
		It::iterator_category,
		It::value_type,
		It::difference_type,
		It::pointer,
		It::reference>>
	{
		using iterator_category = It::iterator_category;
		using value_type = It::value_type;
		using difference_type = It::difference_type;

		using pointer = It::pointer;
		using reference = It::reference;
	};

	template<class It>
	struct iterator_traits
		: iterator_traits_base<It>
	{};

	template<class It>
	class reverse_iterator
		: public iterator<
		iterator_traits<It>::iterator_category,
		iterator_traits<It>::value_type,
		iterator_traits<It>::difference_type,
		iterator_traits<It>::pointer,
		iterator_traits<It>::reference>
	{
		template<class _It = It>
		using rev = reverse_iterator<_It>;
	public:
		using difference_type = iterator_traits<It>::difference_type;
		using pointer = iterator_traits<It>::pointer;
		using reference = iterator_traits<It>::reference;
		using iterator_type = It;

		reverse_iterator()
			: current()
		{}

		explicit reverse_iterator(It it)
			: current(it)
		{}

		template<class Other>
		reverse_iterator(const reverse_iterator<Other>& it)
			: current(it.base())
		{}

		template<class Other>
		rev<>& operator=(const reverse_iterator<Other>& it)
		{
			current = it.base();
			return (*this);
		}

		It base() const
		{
			return (current);
		}

		reference operator*() const
		{
			It tmp = current;
			return (*--tmp);
		}

		pointer operator->() const
		{
		}
	};

}
