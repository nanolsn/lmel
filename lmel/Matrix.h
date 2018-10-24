#pragma once

#include <initializer_list>
#include <cassert>
#include "Vector.h"

namespace lmel
{
	template <
		typename T,
		unsigned N,
		unsigned M,
		typename = typename std::enable_if<std::is_arithmetic<T>::value && N != 0 && M != 0, T>::type
	>
	class Matrix
	{
	protected:
		T data[N][M];

	public:
		static const unsigned rows = N;
		static const unsigned cols = M;

		// Constructor with init value
		explicit Matrix(T init = 0)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = init;
		}

		// Initializer list constructor
		Matrix(std::initializer_list<T> il)
		{
			assert(il.size() == N * M);

			auto it = il.begin();

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = *it++;
		}

		// Copy constructor
		Matrix(const Matrix & ref)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = ref.data[i][j];
		}

		// Template copy constructor (for other types)
		template <typename O>
		Matrix(const Matrix<O, N, M> & ref)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = ref(i, j);
		}

		// Assignment operator
		Matrix & operator=(const Matrix & val)
		{
			if (&val == this)
				return *this;

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = val.data[i][j];

			return *this;
		}

		Vector<T, M> getRow(const unsigned row) const
		{
			assert(row < rows);

			Vector<T, M> result(0);

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

		void setRow(unsigned rowNum, const Vector<T, M> & row)
		{
			assert(rowNum < rows);

			for (unsigned j = 0; j < cols; ++j)
				data[rowNum][j] = row(j);
		}

		void setCol(unsigned colNum, const Vector<T, N> & col)
		{
			assert(colNum < cols);

			for (unsigned i = 0; i < rows; ++i)
				data[i][colNum] = col(i);
		}

		void swapRows(unsigned a, unsigned b)
		{
			Vector<T, M> tmp = getRow(a);
			setRow(a, getRow(b));
			setRow(b, tmp);
		}

		void swapCols(unsigned a, unsigned b)
		{
			Vector<T, N> tmp = getCol(a);
			setCol(a, getCol(b));
			setCol(b, tmp);
		}

		// Default math operations:

		Matrix operator+(const Matrix & val) const
		{
			Matrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] + val.data[i][j];

			return result;
		}

		Matrix operator-(const Matrix & val) const
		{
			Matrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] - val.data[i][j];

			return result;
		}

		template <unsigned K>
		Matrix<T, N, K> operator*(const Matrix<T, M, K> & val) const
		{
			Matrix<T, N, K> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					for (unsigned k = 0; k < K; ++k)
						result(i, k) += data[i][j] * val(j, k);

			return result;
		}

		Matrix & operator+=(const Matrix & val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] += val.data[i][j];

			return *this;
		}

		Matrix & operator-=(const Matrix & val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] -= val.data[i][j];

			return *this;
		}

		Matrix operator+(T val) const
		{
			Matrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] + val;

			return result;
		}

		Matrix operator-(T val) const
		{
			Matrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] - val;

			return result;
		}

		Matrix operator*(T val) const
		{
			Matrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] * val;

			return result;
		}

		Matrix operator/(T val) const
		{
			Matrix result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] / val;

			return result;
		}

		Matrix & operator+=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] += val;

			return *this;
		}

		Matrix & operator-=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] -= val;

			return *this;
		}

		Matrix & operator*=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] *= val;

			return *this;
		}

		Matrix & operator/=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] /= val;

			return *this;
		}

		// Vector product:
		Vector<T, N> operator*(const Vector<T, M> & vec) const
		{
			Vector<T, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result(i) += data[i][j] * vec(j);

			return result;
		}

		// Compare operations:

		bool operator==(const Matrix & m) const
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					if (data[i][j] != m.data[i][j])
						return false;

			return true;
		}

		bool operator!=(const Matrix & m) const
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					if (data[i][j] != m.data[i][j])
						return true;

			return false;
		}

		Matrix<T, M, N> getTranspose() const
		{
			Matrix<T, M, N> result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result(j, i) = data[i][j];

			return result;
		}

		// get/set selected element:

		T & operator()(unsigned row, unsigned col)
		{
			assert(row < rows && col < cols);
			return data[row][col];
		}

		const T & operator()(unsigned row, unsigned col) const
		{
			assert(row < rows && col < cols);
			return data[row][col];
		}

		template <typename T, unsigned N, unsigned M>
		friend Matrix<T, N, M> matrixFromRows(std::initializer_list<Vector<T, M>> il);

		template <typename T, unsigned N, unsigned M>
		friend Matrix<T, N, M> matrixFromCols(std::initializer_list<Vector<T, N>> il);
	};

	template <unsigned N, unsigned M>
	using IntMatrix = Matrix<int, N, M>;

	template <unsigned N, unsigned M>
	using FloatMatrix = Matrix<float, N, M>;

	template <unsigned N, unsigned M>
	using DoubleMatrix = Matrix<double, N, M>;

	template <typename T, unsigned N, unsigned M>
	Matrix<T, N, M> matrixFromRows(std::initializer_list<Vector<T, M>> il)
	{
		assert(il.size() == N);

		auto it = il.begin();
		Matrix<T, N, M> result(0);

		for (unsigned i = 0; i < N; ++i)
		{
			Vector<T, M> vec = *it;

			for (unsigned j = 0; j < M; ++j)
				result.data[i][j] = vec(j);

			++it;
		}

		return result;
	}

	template <typename T, unsigned N, unsigned M>
	Matrix<T, N, M> matrixFromCols(std::initializer_list<Vector<T, N>> il)
	{
		assert(il.size() == M);

		auto it = il.begin();
		Matrix<T, N, M> result(0);

		for (unsigned i = 0; i < M; ++i)
		{
			Vector<T, N> vec = *it;

			for (unsigned j = 0; j < N; ++j)
				result.data[j][i] = vec(j);

			++it;
		}

		return result;
	}
}