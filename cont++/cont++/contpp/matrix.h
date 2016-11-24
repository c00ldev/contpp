#pragma once

#include <initializer_list>

namespace contpp
{
	template<class T, size_t R = 1, size_t C = R>
	class matrix
	{
		T d[R * C];
	public:
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type *;
		using const_pointer = const value_type *;

		using iterator = pointer;
		using const_iterator = const_pointer;
	public:
		matrix(std::initializer_list<T> il = {})
		{
			size_t n = size < il.size() ? size : il.size();
			for (auto it = il.begin(); it - il.begin() < (int)n; ++it)
				d[it - il.begin()] = *it;
			for (size_t i = n; i < size; ++i)
				d[i] = 0;
		}

		iterator begin()
		{
			return d;
		}

		const_iterator begin() const
		{
			return d;
		}

		const_iterator cbegin() const
		{
			return d;
		}
	public:
		reference operator()(size_t i, size_t j)
		{
			return d[i * C + j];
		}

		const_reference operator()(size_t i, size_t j) const
		{
			return d[i * C + j];
		}

		reference front()
		{
			return d[0];
		}

		const_reference front() const
		{
			return d[0];
		}

		reference back()
		{
			return d[size - 1];
		}

		const_reference back() const
		{
			return d[size - 1];
		}

		pointer data()
		{
			return d;
		}

		const_pointer data() const
		{
			return d;
		}
	public:
		static constexpr size_t size = R * C;
	};

	template<class T, size_t N>
	using row = matrix<T, 1, N>;

	template<class T, size_t N>
	using column = matrix<T, N, 1>;

	template<class T, size_t N>
	using vector = row<T, N>;
}
