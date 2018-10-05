#pragma once

#include <initializer_list>
#include <cassert>

namespace lmel
{
	template <typename T, unsigned N>
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
		
		// Copy constructor (it doesn't work)
		SquareMatrix(const SquareMatrix<T, N> & ref)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = ref.data[i][j];
		}

		// Empty destructor
		virtual ~SquareMatrix() {}

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

		double determinant() const
		{
			// TODO: Write recursive determinant method
			return 0.0;
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
	};
}
