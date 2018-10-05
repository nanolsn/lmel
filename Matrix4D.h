#pragma once

#include <initializer_list>
#include <cassert>

namespace lmel
{
	template <typename T>
	class Matrix4D
	{
	private:
		static const unsigned dimension = 4;
		T data[dimension][dimension];

	public:
		static const unsigned rows = dimension;
		static const unsigned cols = dimension;

		// Constructor with init value
		explicit Matrix4D(T init)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = init;
		}

		// Initializer list constructor
		Matrix4D(std::initializer_list<T> il)
		{
			assert(il.size() == dimension * dimension);

			auto it = il.begin();

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = *it++;
		}
		
		// Copy constructor (it doesn't work)
		Matrix4D(const Matrix4D<T> & ref)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = ref.data[i][j];
		}

		// Empty destructor
		virtual ~Matrix4D() {}

		// Assignment operator
		Matrix4D<T> & operator=(const Matrix4D<T> & val)
		{
			if (&val == this)
				return *this;

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = val.data[i][j];

			return *this;
		}

		// Default math operations:

		Matrix4D<T> operator+(const Matrix4D<T> & val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] + val.data[i][j];

			return result;
		}

		Matrix4D<T> operator-(const Matrix4D<T> & val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] - val.data[i][j];

			return result;
		}

		Matrix4D<T> operator*(const Matrix4D<T> & val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					for (unsigned k = 0; k < rows; ++k)
						result.data[i][j] += data[i][k] * val.data[k][j];

			return result;
		}

		Matrix4D<T> & operator+=(const Matrix4D<T> & val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] += val.data[i][j];

			return *this;
		}

		Matrix4D<T> & operator-=(const Matrix4D<T> & val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] -= val.data[i][j];

			return *this;
		}

		Matrix4D<T> & operator*=(const Matrix4D<T> & val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					for (unsigned k = 0; k < rows; ++k)
						result.data[i][j] += data[i][k] * val.data[k][j];

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = result.data[i][j];

			return *this;
		}

		Matrix4D<T> operator+(T val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] + val;

			return result;
		}

		Matrix4D<T> operator-(T val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] - val;

			return result;
		}

		Matrix4D<T> operator*(T val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] * val;

			return result;
		}

		Matrix4D<T> operator/(T val)
		{
			Matrix4D result(0);

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] / val;

			return result;
		}

		Matrix4D<T> & operator+=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] += val;

			return *this;
		}

		Matrix4D<T> & operator-=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] -= val;

			return *this;
		}

		Matrix4D<T> & operator*=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] *= val;

			return *this;
		}

		Matrix4D<T> & operator/=(T val)
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] /= val;

			return *this;
		}

		// Compare operations:

		bool operator==(const Matrix4D<T> & m) const
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					if (data[i][j] != m.data[i][j])
						return false;

			return true;
		}

		bool operator!=(const Matrix4D<T> & m) const
		{
			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					if (data[i][j] != m.data[i][j])
						return true;

			return false;
		}

		double determinant() const
		{
			return
				data[0][3] * data[1][2] * data[2][1] * data[3][0] -
				data[0][2] * data[1][3] * data[2][1] * data[3][0] -
				data[0][3] * data[1][1] * data[2][2] * data[3][0] +
				data[0][1] * data[1][3] * data[2][2] * data[3][0] +
				data[0][2] * data[1][1] * data[2][3] * data[3][0] -
				data[0][1] * data[1][2] * data[2][3] * data[3][0] -
				data[0][3] * data[1][2] * data[2][0] * data[3][1] +
				data[0][2] * data[1][3] * data[2][0] * data[3][1] +
				data[0][3] * data[1][0] * data[2][2] * data[3][1] -
				data[0][0] * data[1][3] * data[2][2] * data[3][1] -
				data[0][2] * data[1][0] * data[2][3] * data[3][1] +
				data[0][0] * data[1][2] * data[2][3] * data[3][1] +
				data[0][3] * data[1][1] * data[2][0] * data[3][2] -
				data[0][1] * data[1][3] * data[2][0] * data[3][2] -
				data[0][3] * data[1][0] * data[2][1] * data[3][2] +
				data[0][0] * data[1][3] * data[2][1] * data[3][2] +
				data[0][1] * data[1][0] * data[2][3] * data[3][2] -
				data[0][0] * data[1][1] * data[2][3] * data[3][2] -
				data[0][2] * data[1][1] * data[2][0] * data[3][3] +
				data[0][1] * data[1][2] * data[2][0] * data[3][3] +
				data[0][2] * data[1][0] * data[2][1] * data[3][3] -
				data[0][0] * data[1][2] * data[2][1] * data[3][3] -
				data[0][1] * data[1][0] * data[2][2] * data[3][3] +
				data[0][0] * data[1][1] * data[2][2] * data[3][3];
		}

		void transpose()
		{
			Matrix4D<T> tmp = *this;

			for (unsigned i = 0; i < rows; ++i)
				for (unsigned j = 0; j < cols; ++j)
					data[i][j] = tmp.data[j][i];
		}

		// get/set selected element:

		T & operator()(const unsigned & row, const unsigned & col)
		{
			assert(row < rows && col < cols);
			return data[row][col];
		}

		const T & operator()(const unsigned & row, const unsigned & col) const
		{
			assert(row < rows && col < cols);
			return data[row][col];
		}
	};
}
