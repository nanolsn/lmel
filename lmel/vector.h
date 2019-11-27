#pragma once

#include <type_traits>
#include <initializer_list>
#include <cassert>
#include <math.h>

namespace lmel
{
	template <
		typename T,
		unsigned N,
		typename = typename std::enable_if<std::is_arithmetic<T>::value && N != 0, T>::type
		>
	class vector
	{
	private:
		T data[N];

	public:
		static const unsigned size = N;

		// Constructor with init value
		explicit vector(T init = 0)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] = init;
		}

		// Initializer list constructor
		vector(std::initializer_list<T> il)
		{
			assert(il.size() == N);

			size_t i = 0;

			for (T v : il)
				data[i++] = v;
		}

		// Copy constructor
		vector(const vector & ref)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] = ref.data[i];
		}

		// Template copy constructor (for other types)
		template <typename O>
		vector(const vector<O, N> & ref)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] = ref(i);
		}

		// Assignment operator
		vector & operator=(const vector & val)
		{
			if (&val == this)
				return *this;

			for (size_t i = 0; i < size; ++i)
				data[i] = val.data[i];

			return *this;
		}

		// vector length
		double length() const
		{
			T sum = 0;

			for (size_t i = 0; i < size; ++i)
				sum += data[i] * data[i];

			return sqrt(sum);
		}

		// Normalize vector
		void normalize()
		{
			double len = length();

			for (size_t i = 0; i < size; ++i)
				data[i] /= len;
		}

		// Default math operations:

		vector operator+(const vector & val) const
		{
			vector result(0);

			for (size_t i = 0; i < size; ++i)
				result.data[i] = data[i] + val.data[i];

			return result;
		}

		vector operator-(const vector & val) const
		{
			vector result(0);

			for (size_t i = 0; i < size; ++i)
				result.data[i] = data[i] + val.data[i];

			return result;
		}

		vector operator*(const vector & val) const
		{
			T prod = 0;

			for (size_t i = 0; i < size; ++i)
				prod += data[i] * val.data[i];

			return prod;
		}

		vector & operator+=(const vector & val)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] += val.data[i];

			return *this;
		}

		vector & operator-=(const vector & val)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] -= val.data[i];

			return *this;
		}

		vector operator+(T val) const
		{
			vector result(0);

			for (size_t i = 0; i < size; ++i)
				result.data[i] = data[i] + val;

			return result;
		}

		vector operator-(T val) const
		{
			vector result(0);

			for (size_t i = 0; i < size; ++i)
				result.data[i] = data[i] - val;

			return result;
		}

		vector operator*(T val) const
		{
			vector result(0);

			for (size_t i = 0; i < size; ++i)
				result.data[i] = data[i] * val;

			return result;
		}

		vector operator/(T val) const
		{
			vector result(0);

			for (size_t i = 0; i < size; ++i)
				result.data[i] = data[i] / val;

			return result;
		}

		vector & operator+=(T val)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] += val;

			return *this;
		}

		vector & operator-=(T val)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] -= val;

			return *this;
		}

		vector & operator*=(T val)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] *= val;

			return *this;
		}

		vector & operator/=(T val)
		{
			for (size_t i = 0; i < size; ++i)
				data[i] /= val;

			return *this;
		}

		// Compare operations:

		bool operator==(const vector & v) const
		{
			for (size_t i = 0; i < size; ++i)
				if (data[i] != v.data[i])
					return false;

			return true;
		}

		bool operator!=(const vector & v) const
		{
			for (size_t i = 0; i < size; ++i)
				if (data[i] != v.data[i])
					return true;

			return false;
		}

		// get/set selected element:

		T & operator()(unsigned i)
		{
			assert(i < size);
			return data[i];
		}

		const T & operator()(unsigned i) const
		{
			assert(i < size);
			return data[i];
		}

		template <typename V>
		friend vector<V, 3> cross(const vector<V, 3> & v1, const vector<V, 3> & v2);
	};

	// Cross product
	template <typename T>
	vector<T, 3> cross(const vector<T, 3> & v1, const vector<T, 3> & v2)
	{
		return vector<T, 3>
		{
			v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1],
			v1.data[0] * v2.data[2] - v1.data[2] * v2.data[0],
			v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]
		};
	}

	template <typename T>
	using vector1d = vector<T, 1>;

	template <typename T>
	using vector2d = vector<T, 2>;

	template <typename T>
	using vector3d = vector<T, 3>;

	template <typename T>
	using vector4d = vector<T, 4>;

	template <typename T>
	using vector5d = vector<T, 5>;

	using int_vector1d = vector<int, 1>;
	using int_vector2d = vector<int, 2>;
	using int_vector3d = vector<int, 3>;
	using int_vector4d = vector<int, 4>;
	using int_vector5d = vector<int, 5>;

	using char_vector1d = vector<char, 1>;
	using char_vector2d = vector<char, 2>;
	using char_vector3d = vector<char, 3>;
	using char_vector4d = vector<char, 4>;
	using char_vector5d = vector<char, 5>;

	using double_vector1d = vector<double, 1>;
	using double_vector2d = vector<double, 2>;
	using double_vector3d = vector<double, 3>;
	using double_vector4d = vector<double, 4>;
	using double_vector5d = vector<double, 5>;

	using float_vector1d = vector<float, 1>;
	using float_vector2d = vector<float, 2>;
	using float_vector3d = vector<float, 3>;
	using float_vector4d = vector<float, 4>;
	using float_vector5d = vector<float, 5>;
}
