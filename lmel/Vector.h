#pragma once

#include <type_traits>
#include <initializer_list>
#include <cassert>

namespace lmel
{
	template <
		typename T,
		unsigned N,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
	>
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

		// Default math operations:

		Vector<T, N> operator+(const Vector<T, N> & val) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] + val.data[i];

			return result;
		}

		Vector<T, N> operator-(const Vector<T, N> & val) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] + val.data[i];

			return result;
		}

		Vector<T, N> operator*(const Vector<T, N> & val) const
		{
			T prod = 0;

			for (unsigned i = 0; i < size; ++i)
				prod += data[i] * val.data[i];

			return prod;
		}

		Vector<T, N> & operator+=(const Vector<T, N> & val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] += val.data[i];

			return *this;
		}

		Vector<T, N> & operator-=(const Vector<T, N> & val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] -= val.data[i];

			return *this;
		}

		Vector<T, N> operator+(T val) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] + val;

			return result;
		}

		Vector<T, N> operator-(T val) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] - val;

			return result;
		}

		Vector<T, N> operator*(T val) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] * val;

			return result;
		}

		Vector<T, N> operator/(T val) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] / val;

			return result;
		}

		Vector<T, N> & operator+=(T val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] += val;

			return *this;
		}

		Vector<T, N> & operator-=(T val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] -= val;

			return *this;
		}

		Vector<T, N> & operator*=(T val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] *= val;

			return *this;
		}

		Vector<T, N> & operator/=(T val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] /= val;

			return *this;
		}

		// Compare operations:

		bool operator==(const Vector<T, N> & v) const
		{
			for (unsigned i = 0; i < size; ++i)
				if (data[i] != v.data[i])
					return false;

			return true;
		}

		bool operator!=(const Vector<T, N> & v) const
		{
			for (unsigned i = 0; i < size; ++i)
				if (data[i] != v.data[i])
					return true;

			return false;
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

	template <typename T>
	using Vector1D = Vector<T, 1>;

	template <typename T>
	using Vector2D = Vector<T, 2>;

	template <typename T>
	using Vector3D = Vector<T, 3>;

	template <typename T>
	using Vector4D = Vector<T, 4>;

	template <typename T>
	using Vector5D = Vector<T, 5>;

	using IntVector1D = Vector<int, 1>;
	using IntVector2D = Vector<int, 2>;
	using IntVector3D = Vector<int, 3>;
	using IntVector4D = Vector<int, 4>;
	using IntVector5D = Vector<int, 5>;

	using DoubleVector1D = Vector<double, 1>;
	using DoubleVector2D = Vector<double, 2>;
	using DoubleVector3D = Vector<double, 3>;
	using DoubleVector4D = Vector<double, 4>;
	using DoubleVector5D = Vector<double, 5>;

	using FloatVector1D = Vector<float, 1>;
	using FloatVector2D = Vector<float, 2>;
	using FloatVector3D = Vector<float, 3>;
	using FloatVector4D = Vector<float, 4>;
	using FloatVector5D = Vector<float, 5>;
}
