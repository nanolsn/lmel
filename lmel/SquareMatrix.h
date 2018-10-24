#pragma once

#include <initializer_list>
#include <cassert>
#include "Matrix.h"
#include "Vector.h"

namespace lmel
{
	template <
		typename T,
		unsigned N,
		typename = typename std::enable_if<std::is_arithmetic<T>::value && N != 0, T>::type
	>
	class SquareMatrix : public Matrix<T, N, N>
	{
	private:
		typedef Matrix<T, N, N> Base;

	public:
		static const unsigned rows = N;
		static const unsigned cols = N;

		// Constructor with init value
		explicit SquareMatrix(T init = 0)
			: Base(init)
		{}

		// Initializer list constructor
		SquareMatrix(std::initializer_list<T> il)
			: Base(il)
		{}
		
		// Copy constructor
		SquareMatrix(const SquareMatrix & ref)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] = ref.data[i][j];
		}

		// Template copy constructor (for other types)
		template <typename O>
		SquareMatrix(const SquareMatrix<O, N> & ref)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] = ref(i, j);
		}

		// Constructor from Matrix
		SquareMatrix(const Base & ref)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] = ref(i, j);
		}

		Vector<T, N> getDiagonal() const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < N; ++i)
				result(i) = this->data[i][i];

			return result;
		}

		// Default math operations:

		SquareMatrix operator+(const SquareMatrix & val) const
		{
			SquareMatrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] + val.data[i][j];

			return result;
		}

		SquareMatrix operator-(const SquareMatrix & val) const
		{
			SquareMatrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] - val.data[i][j];

			return result;
		}

		SquareMatrix operator*(const SquareMatrix & val) const
		{
			SquareMatrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					for (unsigned k = 0; k < rows; ++k)
						result.data[i][j] += this->data[i][k] * val.data[k][j];

			return result;
		}

		SquareMatrix & operator+=(const SquareMatrix & val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] += val.data[i][j];

			return *this;
		}

		SquareMatrix & operator-=(const SquareMatrix & val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] -= val.data[i][j];

			return *this;
		}

		SquareMatrix & operator*=(const SquareMatrix & val)
		{
			SquareMatrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					for (unsigned k = 0; k < rows; ++k)
						result.data[i][j] += this->data[i][k] * val.data[k][j];

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] = result.data[i][j];

			return *this;
		}

		SquareMatrix operator+(T val) const
		{
			SquareMatrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] + val;

			return result;
		}

		SquareMatrix operator-(T val) const
		{
			SquareMatrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] - val;

			return result;
		}

		SquareMatrix operator*(T val) const
		{
			SquareMatrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] * val;

			return result;
		}

		SquareMatrix operator/(T val) const
		{
			SquareMatrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] / val;

			return result;
		}

		SquareMatrix & operator+=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] += val;

			return *this;
		}

		SquareMatrix & operator-=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] -= val;

			return *this;
		}

		SquareMatrix & operator*=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] *= val;

			return *this;
		}

		SquareMatrix & operator/=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] /= val;

			return *this;
		}

		// Vector product:
		Vector<T, N> operator*(const Vector<T, N> & vec) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result(i) += this->data[i][j] * vec(j);

			return result;
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

					result(x, y++) = this->data[i][j];
				}

				++x;
			}

			return result;
		}

		void transpose()
		{
			SquareMatrix tmp = *this;

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					this->data[i][j] = tmp.data[j][i];
		}

		template <typename T, unsigned N>
		friend T determinant(const SquareMatrix<T, N> & m);

		template <typename T>
		friend T determinant(const SquareMatrix<T, 2> & m);

		template <typename T, unsigned N>
		friend SquareMatrix<T, N> createIdentityMatrix();

		template <typename T, unsigned N>
		friend SquareMatrix<T, N> squareMatrixFromRows(std::initializer_list<Vector<T, N>> il);

		template <typename T, unsigned N>
		friend SquareMatrix<T, N> squareMatrixFromCols(std::initializer_list<Vector<T, N>> il);
	};

	// 1x1 matrix specialization
	template <typename T>
	class SquareMatrix<T, 1> : public Matrix<T, 1, 1>
	{
	private:
		typedef Matrix<T, 1, 1> Base;

	public:
		static const unsigned rows = 1;
		static const unsigned cols = 1;

		// Constructor with init value
		explicit SquareMatrix(T init = 0)
			: Base(init)
		{}

		// Initializer list constructor
		SquareMatrix(std::initializer_list<T> il)
			: Base(il)
		{}

		// Copy constructor
		SquareMatrix(const SquareMatrix & ref)
		{
			this->data[0][0] = ref.data[0][0];
		}

		// Template copy constructor (for other types)
		template <typename O>
		SquareMatrix(const SquareMatrix<O, 1> & ref)
		{
			this->data[0][0] = ref(0, 0);
		}

		// Constructor from Matrix
		SquareMatrix(const Base & ref)
		{
			this->data[0][0] = ref(0, 0);
		}

		Vector<T, 1> getDiagonal() const
		{
			return Vector<T, 1>(this->data[0][0]);
		}

		// Default math operations:

		SquareMatrix operator+(const SquareMatrix & val) const
		{
			return SquareMatrix(this->data[0][0] + val.data[0][0]);
		}

		SquareMatrix operator-(const SquareMatrix & val) const
		{
			return SquareMatrix(this->data[0][0] - val.data[0][0]);
		}

		SquareMatrix operator*(const SquareMatrix & val) const
		{
			return SquareMatrix(this->data[0][0] * val.data[0][0]);
		}

		SquareMatrix & operator+=(const SquareMatrix & val)
		{
			this->data[0][0] += val.data[0][0];
			return *this;
		}

		SquareMatrix & operator-=(const SquareMatrix & val)
		{
			this->data[0][0] -= val.data[0][0];
			return *this;
		}

		SquareMatrix & operator*=(const SquareMatrix & val)
		{
			this->data[0][0] *= val.data[0][0];
			return *this;
		}

		SquareMatrix operator+(T val) const
		{
			return SquareMatrix(this->data[0][0] + val);
		}

		SquareMatrix operator-(T val) const
		{
			return SquareMatrix(this->data[0][0] - val);
		}

		SquareMatrix operator*(T val) const
		{
			return SquareMatrix(this->data[0][0] * val);
		}

		SquareMatrix operator/(T val) const
		{
			return SquareMatrix(this->data[0][0] / val);
		}

		SquareMatrix & operator+=(T val)
		{
			this->data[0][0] += val;
			return *this;
		}

		SquareMatrix & operator-=(T val)
		{
			this->data[0][0] -= val;
			return *this;
		}

		SquareMatrix & operator*=(T val)
		{
			this->data[0][0] *= val;
			return *this;
		}

		SquareMatrix & operator/=(T val)
		{
			this->data[0][0] /= val;
			return *this;
		}

		// Vector product:
		Vector<T, 1> operator*(const Vector<T, 1> & vec) const
		{
			return Vector<T, 1>(this->data[0][0] * vec(0));
		}

		SquareMatrix minor(const unsigned row, const unsigned col) const
		{
			assert(!"Undefined minor matrix!");

			return SquareMatrix(0);
		}

		void transpose() {}

		template <typename T>
		friend T determinant(const SquareMatrix<T, 1> & m);

		template <typename T, unsigned N>
		friend SquareMatrix<T, N> createIdentityMatrix();

		template <typename T, unsigned N>
		friend SquareMatrix<T, N> squareMatrixFromRows(std::initializer_list<Vector<T, N>> il);

		template <typename T, unsigned N>
		friend SquareMatrix<T, N> squareMatrixFromCols(std::initializer_list<Vector<T, N>> il);
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

	template <typename T, unsigned N>
	SquareMatrix<T, N> createIdentityMatrix()
	{
		SquareMatrix<T, N> result(0);

		for (unsigned i = 0; i < N; ++i)
			result.data[i][i] = 1;

		return result;
	}

	template <typename T, unsigned N>
	SquareMatrix<T, N> squareMatrixFromRows(std::initializer_list<Vector<T, N>> il)
	{
		assert(il.size() == N);

		auto it = il.begin();
		SquareMatrix<T, N> result(0);

		for (unsigned i = 0; i < N; ++i)
		{
			Vector<T, N> vec = *it;

			for (unsigned j = 0; j < N; ++j)
				result.data[i][j] = vec(j);

			++it;
		}

		return result;
	}

	template <typename T, unsigned N>
	SquareMatrix<T, N> squareMatrixFromCols(std::initializer_list<Vector<T, N>> il)
	{
		assert(il.size() == N);

		auto it = il.begin();
		SquareMatrix<T, N> result(0);

		for (unsigned i = 0; i < N; ++i)
		{
			Vector<T, N> vec = *it;

			for (unsigned j = 0; j < N; ++j)
				result.data[j][i] = vec(j);

			++it;
		}

		return result;
	}
}
