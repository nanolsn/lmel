#pragma once

#include <initializer_list>
#include <cassert>
#include <algorithm>

namespace lmel
{
	template <typename T>
	class Matrix4D
	{
	private:
		static const unsigned size = 4 * 4;
		T data[size];

	public:
		static const unsigned rows = 4;
		static const unsigned cols = 4;

		explicit Matrix4D(T init)
			: data
		{
			init, init, init, init,
			init, init, init, init,
			init, init, init, init,
			init, init, init, init
		}
		{}

		Matrix4D(std::initializer_list<std::initializer_list<T>> il)
		{
			assert(il.size() == 4);
			assert(std::all_of(
				il.begin(),
				il.end(),
				[](std::initializer_list<T> l)
				{
					return l.size() == 4;
				}
			));

			unsigned i = 0;
			for (std::initializer_list<T> l : il)
				for (T n : l)
					data[i++] = n;
		}

		Matrix4D(const Matrix4D<T> & ref)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] = ref.data[i];
		}

		virtual ~Matrix4D() {}

		Matrix4D<T> & operator=(const Matrix4D<T> & val)
		{
			if (&val == this)
				return *this;

			for (unsigned i = 0; i < size; ++i)
				data[i] = val.data[i];

			return *this;
		}
                                                                                                                                                                                              
		Matrix4D<T> operator+(const Matrix4D<T> & val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] + val.data[i];

			return result;
		}

		Matrix4D<T> operator-(const Matrix4D<T> & val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] - val.data[i];

			return result;
		}

		Matrix4D<T> operator*(const Matrix4D<T> & val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; i++)
				for (unsigned j = 0; j < cols; j++)
					for (unsigned k = 0; k < rows; k++)
						result.data[i * cols + j] += data[i * cols + k] * val.data[k * cols + j];

			return result;
		}

		Matrix4D<T> & operator+=(const Matrix4D<T> & val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] += val.data[i];

			return *this;
		}

		Matrix4D<T> & operator-=(const Matrix4D<T> & val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] -= val.data[i];

			return *this;
		}

		Matrix4D<T> & operator*=(const Matrix4D<T> & val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; i++)
				for (unsigned j = 0; j < cols; j++)
					for (unsigned k = 0; k < rows; k++)
						result.data[i * cols + j] += data[i * cols + k] * val.data[k * cols + j];

			for (unsigned i = 0; i < size; ++i)
				data[i] = result.data[i];

			return *this;
		}

		Matrix4D<T> operator+(T val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] + val;

			return result;
		}

		Matrix4D<T> operator-(T val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] - val;

			return result;
		}

		Matrix4D<T> operator*(T val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] * val;

			return result;
		}

		Matrix4D<T> operator/(T val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < size; ++i)
				result.data[i] = data[i] / val;

			return result;
		}

		Matrix4D<T> & operator+=(T val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] += val;

			return *this;
		}

		Matrix4D<T> & operator-=(T val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] -= val;

			return *this;
		}

		Matrix4D<T> & operator*=(T val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] *= val;

			return *this;
		}

		Matrix4D<T> & operator/=(T val)
		{
			for (unsigned i = 0; i < size; ++i)
				data[i] /= val;

			return *this;
		}

		bool operator==(const Matrix4D<T> & m) const
		{
			for (unsigned i = 0; i < size; ++i)
				if (data[i] != m.data[i])
					return false;

			return true;
		}

		bool operator!=(const Matrix4D<T> & m) const
		{
			for (unsigned i = 0; i < size; ++i)
				if (data[i] != m.data[i])
					return true;

			return false;
		}

		void transpose()
		{
			Matrix4D tmp(0);

			for (unsigned i = 0; i < size; ++i)
				tmp.data[i] = data[i];

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i * cols + j] = tmp.data[j * cols + i];
		}

		T & operator()(const unsigned & row, const unsigned & col)
		{
			assert(row < rows && col < cols);
			return data[row * rows + col];
		}

		const T & operator()(const unsigned & row, const unsigned & col) const
		{
			assert(row < rows && col < cols);
			return data[row * rows + col];
		}
	};
}
