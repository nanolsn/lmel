#pragma once

#include <initializer_list>
#include <cassert>

namespace lmel
{
	template <typename T, unsigned N>
	class Vector
	{
	private:
		T data[N];

	public:
		static const unsigned size = N;

		// Constructor with init value
		explicit Vector(T init)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] = init;
		}

		// Initializer list constructor
		Vector(std::initializer_list<T> il)
		{
			assert(il.size() == N);

			auto it = il.begin();

			for (unsigned i = 0; i < size; ++i)
				data[i] = *it++;
		}

		// Copy constructor
		Vector(const Vector<T, N> & ref)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] = ref.data[i];
		}

		// Assignment operator
		Vector<T, N> & operator=(const Vector<T, N> & val)
		{
			if (&val == this)
				return *this;

			for (unsigned i = 0; i < size; ++i)
				data[i] = val.data[i];

			return *this;
		}

		// get/set selected element:

		T & operator()(const unsigned i)
		{
			assert(i < size);
			return data[i];
		}

		const T & operator()(const unsigned i) const
		{
			assert(i < size);
			return data[i];
		}
	};
}
