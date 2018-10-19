#pragma once

#include <initializer_list>
#include <cassert>
#include "Vector.h"

namespace lmel
{
	template <
		typename T,
		unsigned N,
		typename = typename std::enable_if<std::is_arithmetic<T>::value && N != 0, T>::type
	>
	class SquareMatrix
	{
	private:
		T data[N][N];

	public:
		static const unsigned rows = N;
		static const unsigned cols = N;

		// Constructor with init value
		explicit SquareMatrix(T init)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = init;
		}

		// Initializer list constructor
		SquareMatrix(std::initializer_list<T> il)
		{
			assert(il.size() == N * N);

			auto it = il.begin();

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = *it++;
		}

		// Initializer list constructor (From vectors) 
		SquareMatrix(std::initializer_list<Vector<T, N>> il)
		{
			assert(il.size() == N);

			auto it = il.begin();

			for (unsigned i = 0; i < rows; ++i)
			{
				Vector<T, N> v = *it;

				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = v(j);

				it++;
			}
		}
		
		// Copy constructor
		SquareMatrix(const SquareMatrix<T, N> & ref)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = ref.data[i][j];
		}

		// Assignment operator
		SquareMatrix<T, N> & operator=(const SquareMatrix<T, N> & val)
		{
			if (&val == this)
				return *this;

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = val.data[i][j];

			return *this;
		}

		Vector<T, N> getRow(const unsigned row) const
		{
			assert(row < rows);

			Vector<T, N> result(0);

			for (unsigned i = 0; i < cols; ++i)
				result(i) = data[row][i];

			return result;
		}

		Vector<T, N> getCol(const unsigned col) const
		{
			assert(col < cols);

			Vector<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				result(i) = data[i][col];

			return result;
		}

		Vector<T, N> getDiagonal() const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < N; ++i)
				result(i) = data[i][i];

			return result;
		}

		// Default math operations:

		SquareMatrix<T, N> operator+(const SquareMatrix<T, N> & val) const
		{
			SquareMatrix<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] + val.data[i][j];

			return result;
		}

		SquareMatrix<T, N> operator-(const SquareMatrix<T, N> & val) const
		{
			SquareMatrix<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] - val.data[i][j];

			return result;
		}

		SquareMatrix<T, N> operator*(const SquareMatrix<T, N> & val) const
		{
			SquareMatrix<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					for (unsigned k = 0; k < rows; ++k)
						result.data[i][j] += data[i][k] * val.data[k][j];

			return result;
		}

		SquareMatrix<T, N> & operator+=(const SquareMatrix<T, N> & val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] += val.data[i][j];

			return *this;
		}

		SquareMatrix<T, N> & operator-=(const SquareMatrix<T, N> & val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] -= val.data[i][j];

			return *this;
		}

		SquareMatrix<T, N> & operator*=(const SquareMatrix<T, N> & val)
		{
			SquareMatrix<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					for (unsigned k = 0; k < rows; ++k)
						result.data[i][j] += data[i][k] * val.data[k][j];

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = result.data[i][j];

			return *this;
		}

		SquareMatrix<T, N> operator+(T val) const
		{
			SquareMatrix<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] + val;

			return result;
		}

		SquareMatrix<T, N> operator-(T val) const
		{
			SquareMatrix<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] - val;

			return result;
		}

		SquareMatrix<T, N> operator*(T val) const
		{
			SquareMatrix<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] * val;

			return result;
		}

		SquareMatrix<T, N> operator/(T val) const
		{
			SquareMatrix<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] / val;

			return result;
		}

		SquareMatrix<T, N> & operator+=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] += val;

			return *this;
		}

		SquareMatrix<T, N> & operator-=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] -= val;

			return *this;
		}

		SquareMatrix<T, N> & operator*=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] *= val;

			return *this;
		}

		SquareMatrix<T, N> & operator/=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] /= val;

			return *this;
		}

		// Vector product:
		Vector<T, N> operator*(const Vector<T, N> & vec) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result(i) += data[i][j] * vec(j);

			return result;
		}

		// Compare operations:

		bool operator==(const SquareMatrix<T, N> & m) const
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					if (data[i][j] != m.data[i][j])
						return false;

			return true;
		}

		bool operator!=(const SquareMatrix<T, N> & m) const
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					if (data[i][j] != m.data[i][j])
						return true;

			return false;
		}

		SquareMatrix<T, N - 1> minor(const unsigned row, const unsigned col) const
		{
			assert(row < rows && col < cols);

			SquareMatrix<T, N - 1> result(0);

			for (unsigned i = 0, x = 0; i < rows; ++i)
			{
				if (i == row)
					continue;

				for (unsigned j = 0, y = 0; j < cols; ++j)
				{
					if (j == col)
						continue;

					result(x, y++) = data[i][j];
				}

				++x;
			}

			return result;
		}

		void transpose()
		{
			SquareMatrix<T, N> tmp = *this;

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = tmp.data[j][i];
		}

		// get/set selected element:

		T & operator()(const unsigned row, const unsigned col)
		{
			assert(row < rows && col < cols);
			return data[row][col];
		}

		const T & operator()(const unsigned row, const unsigned col) const
		{
			assert(row < rows && col < cols);
			return data[row][col];
		}

		template <typename T, unsigned N>
		friend T determinant(const SquareMatrix<T, N> & m);

		template <typename T>
		friend T determinant(const SquareMatrix<T, 2> & m);
	};

	// 1x1 matrix specialization
	template <typename T>
	class SquareMatrix<T, 1>
	{
	private:
		T data;

	public:
		static const unsigned rows = 1;
		static const unsigned cols = 1;

		// Constructor with init value
		explicit SquareMatrix(T init)
		{
			data = init;
		}

		// Initializer list constructor
		SquareMatrix(std::initializer_list<T> il)
		{
			assert(il.size() == 1);

			auto it = il.begin();
			data = *it;
		}

		// Copy constructor
		SquareMatrix(const SquareMatrix<T, 1> & ref)
		{
			data = ref.data;
		}

		// Assignment operator
		SquareMatrix<T, 1> & operator=(const SquareMatrix<T, 1> & val)
		{
			if (&val == this)
				return *this;

			data = val.data;
			return *this;
		}

		Vector<T, 1> getRow(const unsigned row) const
		{
			assert(row == 0);

			return Vector<T, 1>(data);
		}

		Vector<T, 1> getCol(const unsigned col) const
		{
			assert(col == 0);

			return Vector<T, 1>(data);
		}

		Vector<T, 1> getDiagonal() const
		{
			return Vector<T, 1>(data);
		}

		// Default math operations:

		SquareMatrix<T, 1> operator+(const SquareMatrix<T, 1> & val) const
		{
			return SquareMatrix<T, 1>(data + val.data);
		}

		SquareMatrix<T, 1> operator-(const SquareMatrix<T, 1> & val) const
		{
			return SquareMatrix<T, 1>(data - val.data);
		}

		SquareMatrix<T, 1> operator*(const SquareMatrix<T, 1> & val) const
		{
			return SquareMatrix<T, 1>(data * val.data);
		}

		SquareMatrix<T, 1> & operator+=(const SquareMatrix<T, 1> & val)
		{
			data += val.data;
			return *this;
		}

		SquareMatrix<T, 1> & operator-=(const SquareMatrix<T, 1> & val)
		{
			data -= val.data;
			return *this;
		}

		SquareMatrix<T, 1> & operator*=(const SquareMatrix<T, 1> & val)
		{
			data *= val.data;
			return *this;
		}

		SquareMatrix<T, 1> operator+(T val) const
		{
			return SquareMatrix<T, 1>(data + val);
		}

		SquareMatrix<T, 1> operator-(T val) const
		{
			return SquareMatrix<T, 1>(data - val);
		}

		SquareMatrix<T, 1> operator*(T val) const
		{
			return SquareMatrix<T, 1>(data * val);
		}

		SquareMatrix<T, 1> operator/(T val) const
		{
			return SquareMatrix<T, 1>(data / val);
		}

		SquareMatrix<T, 1> & operator+=(T val)
		{
			data += val;
			return *this;
		}

		SquareMatrix<T, 1> & operator-=(T val)
		{
			data -= val;
			return *this;
		}

		SquareMatrix<T, 1> & operator*=(T val)
		{
			data *= val;
			return *this;
		}

		SquareMatrix<T, 1> & operator/=(T val)
		{
			data /= val;
			return *this;
		}

		// Vector product:
		Vector<T, 1> operator*(const Vector<T, 1> & vec) const
		{
			return Vector<T, 1>(data * vec(0));
		}

		// Compare operations:

		bool operator==(const SquareMatrix<T, 1> & m) const
		{
			return data == m.data;
		}

		bool operator!=(const SquareMatrix<T, 1> & m) const
		{
			return data != m.data;
		}

		SquareMatrix<T, 1> minor(const unsigned row, const unsigned col) const
		{
			assert(!"Undefined minor matrix!");

			return SquareMatrix<T, 1>(0);
		}

		void transpose() {}

		// get/set selected element:

		T & operator()(const unsigned row, const unsigned col)
		{
			assert(row == 0 && col == 0);
			return data;
		}

		const T & operator()(const unsigned row, const unsigned col) const
		{
			assert(row == 0 && col == 0);
			return data;
		}

		template <typename T>
		friend T determinant(const SquareMatrix<T, 1> & m);
	};

	template <typename T>
	using Matrix1D = SquareMatrix<T, 1>;

	template <typename T>
	using Matrix2D = SquareMatrix<T, 2>;

	template <typename T>
	using Matrix3D = SquareMatrix<T, 3>;

	template <typename T>
	using Matrix4D = SquareMatrix<T, 4>;

	template <typename T>
	using Matrix5D = SquareMatrix<T, 5>;

	using IntMatrix1D = SquareMatrix<int, 1>;
	using IntMatrix2D = SquareMatrix<int, 2>;
	using IntMatrix3D = SquareMatrix<int, 3>;
	using IntMatrix4D = SquareMatrix<int, 4>;
	using IntMatrix5D = SquareMatrix<int, 5>;

	using DoubleMatrix1D = SquareMatrix<double, 1>;
	using DoubleMatrix2D = SquareMatrix<double, 2>;
	using DoubleMatrix3D = SquareMatrix<double, 3>;
	using DoubleMatrix4D = SquareMatrix<double, 4>;
	using DoubleMatrix5D = SquareMatrix<double, 5>;

	using FloatMatrix1D = SquareMatrix<float, 1>;
	using FloatMatrix2D = SquareMatrix<float, 2>;
	using FloatMatrix3D = SquareMatrix<float, 3>;
	using FloatMatrix4D = SquareMatrix<float, 4>;
	using FloatMatrix5D = SquareMatrix<float, 5>;
}
