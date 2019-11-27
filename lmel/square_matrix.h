#pragma once

#include <initializer_list>
#include <cassert>
#include "matrix.h"
#include "vector.h"

namespace lmel
{
	template <
		typename T,
		size_t N,
		typename = typename std::enable_if<std::is_arithmetic<T>::value && N != 0, T>::type
		>
	class square_matrix : public matrix<T, N, N>
	{
	private:
		typedef matrix<T, N, N> base;

	public:
		static const size_t rows = N;
		static const size_t cols = N;

		// Constructor with init value
		explicit square_matrix(T init = 0)
			: base(init)
		{}

		// Initializer list constructor
		square_matrix(std::initializer_list<T> il)
			: base(il)
		{}
		
		// Copy constructor
		square_matrix(const square_matrix & ref)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] = ref.data[i][j];
		}

		// Template copy constructor
		template <typename O>
		square_matrix(const square_matrix<O, N> & ref)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] = ref(i, j);
		}

		// Constructor from matrix
		square_matrix(const base & ref)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] = ref(i, j);
		}

		vector<T, N> get_diagonal() const
		{
			vector<T, N> result(0);

			for (size_t i = 0; i < N; ++i)
				result(i) = this->data[i][i];

			return result;
		}

		// Default math operations:

		square_matrix operator+(const square_matrix & val) const
		{
			square_matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] + val.data[i][j];

			return result;
		}

		square_matrix operator-(const square_matrix & val) const
		{
			square_matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] - val.data[i][j];

			return result;
		}

		square_matrix operator*(const square_matrix & val) const
		{
			square_matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					for (size_t k = 0; k < rows; ++k)
						result.data[i][j] += this->data[i][k] * val.data[k][j];

			return result;
		}

		square_matrix & operator+=(const square_matrix & val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] += val.data[i][j];

			return *this;
		}

		square_matrix & operator-=(const square_matrix & val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] -= val.data[i][j];

			return *this;
		}

		square_matrix & operator*=(const square_matrix & val)
		{
			square_matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					for (size_t k = 0; k < rows; ++k)
						result.data[i][j] += this->data[i][k] * val.data[k][j];

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] = result.data[i][j];

			return *this;
		}

		square_matrix operator+(T val) const
		{
			square_matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] + val;

			return result;
		}

		square_matrix operator-(T val) const
		{
			square_matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] - val;

			return result;
		}

		square_matrix operator*(T val) const
		{
			square_matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] * val;

			return result;
		}

		square_matrix operator/(T val) const
		{
			square_matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = this->data[i][j] / val;

			return result;
		}

		square_matrix & operator+=(T val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] += val;

			return *this;
		}

		square_matrix & operator-=(T val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] -= val;

			return *this;
		}

		square_matrix & operator*=(T val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] *= val;

			return *this;
		}

		square_matrix & operator/=(T val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] /= val;

			return *this;
		}

		// vector product:
		vector<T, N> operator*(const vector<T, N> & vec) const
		{
			vector<T, N> result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result(i) += this->data[i][j] * vec(j);

			return result;
		}

		square_matrix<T, N - 1> minor(const size_t row, const size_t col) const
		{
			assert(row < rows && col < cols);

			square_matrix<T, N - 1> result(0);

			for (size_t i = 0, x = 0; i < rows; ++i)
			{
				if (i == row)
					continue;

				for (size_t j = 0, y = 0; j < cols; ++j)
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
			square_matrix tmp = *this;

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					this->data[i][j] = tmp.data[j][i];
		}

		template <typename K, size_t L>
		friend K determinant(const square_matrix<K, L> & m);

		template <typename K>
		friend K determinant(const square_matrix<K, 2> & m);

		template <typename K, size_t L>
		friend square_matrix<K, L> make_id_matrix();

		template <typename K, size_t L>
		friend square_matrix<K, L> make_square_matrix_from_rows(std::initializer_list<vector<K, L>> il);

		template <typename K, size_t L>
		friend square_matrix<K, L> make_square_matrix_from_cols(std::initializer_list<vector<K, L>> il);
	};

	// 1x1 matrix specialization
	template <typename T>
	class square_matrix<T, 1> : public matrix<T, 1, 1>
	{
	private:
		typedef matrix<T, 1, 1> base;

	public:
		static const size_t rows = 1;
		static const size_t cols = 1;

		// Constructor with init value
		explicit square_matrix(T init = 0)
			: base(init)
		{}

		// Initializer list constructor
		square_matrix(std::initializer_list<T> il)
			: base(il)
		{}

		// Copy constructor
		square_matrix(const square_matrix & ref)
		{
			this->data[0][0] = ref.data[0][0];
		}

		// Template copy constructor (for other types)
		template <typename O>
		square_matrix(const square_matrix<O, 1> & ref)
		{
			this->data[0][0] = ref(0, 0);
		}

		// Constructor from matrix
		square_matrix(const base & ref)
		{
			this->data[0][0] = ref(0, 0);
		}

		vector<T, 1> get_diagonal() const
		{
			return vector<T, 1>(this->data[0][0]);
		}

		// Default math operations:

		square_matrix operator+(const square_matrix & val) const
		{
			return square_matrix(this->data[0][0] + val.data[0][0]);
		}

		square_matrix operator-(const square_matrix & val) const
		{
			return square_matrix(this->data[0][0] - val.data[0][0]);
		}

		square_matrix operator*(const square_matrix & val) const
		{
			return square_matrix(this->data[0][0] * val.data[0][0]);
		}

		square_matrix & operator+=(const square_matrix & val)
		{
			this->data[0][0] += val.data[0][0];
			return *this;
		}

		square_matrix & operator-=(const square_matrix & val)
		{
			this->data[0][0] -= val.data[0][0];
			return *this;
		}

		square_matrix & operator*=(const square_matrix & val)
		{
			this->data[0][0] *= val.data[0][0];
			return *this;
		}

		square_matrix operator+(T val) const
		{
			return square_matrix(this->data[0][0] + val);
		}

		square_matrix operator-(T val) const
		{
			return square_matrix(this->data[0][0] - val);
		}

		square_matrix operator*(T val) const
		{
			return square_matrix(this->data[0][0] * val);
		}

		square_matrix operator/(T val) const
		{
			return square_matrix(this->data[0][0] / val);
		}

		square_matrix & operator+=(T val)
		{
			this->data[0][0] += val;
			return *this;
		}

		square_matrix & operator-=(T val)
		{
			this->data[0][0] -= val;
			return *this;
		}

		square_matrix & operator*=(T val)
		{
			this->data[0][0] *= val;
			return *this;
		}

		square_matrix & operator/=(T val)
		{
			this->data[0][0] /= val;
			return *this;
		}

		// vector product:
		vector<T, 1> operator*(const vector<T, 1> & vec) const
		{
			return vector<T, 1>(this->data[0][0] * vec(0));
		}

		square_matrix minor(const size_t row, const size_t col) const
		{
			assert(!"Undefined minor matrix!");

			return square_matrix(0);
		}

		void transpose() {}

		template <typename K>
		friend K determinant(const square_matrix<K, 1> & m);

		template <typename K, size_t L>
		friend square_matrix<K, L> make_id_matrix();

		template <typename K, size_t L>
		friend square_matrix<K, L> make_square_matrix_from_rows(std::initializer_list<vector<K, L>> il);

		template <typename K, size_t L>
		friend square_matrix<K, L> make_square_matrix_from_cols(std::initializer_list<vector<K, L>> il);
	};

	template <typename T>
	using matrix1d = square_matrix<T, 1>;

	template <typename T>
	using matrix2d = square_matrix<T, 2>;

	template <typename T>
	using matrix3d = square_matrix<T, 3>;

	template <typename T>
	using matrix4d = square_matrix<T, 4>;

	template <typename T>
	using matrix5d = square_matrix<T, 5>;

	using int_matrix1d = square_matrix<int, 1>;
	using int_matrix2d = square_matrix<int, 2>;
	using int_matrix3d = square_matrix<int, 3>;
	using int_matrix4d = square_matrix<int, 4>;
	using int_matrix5d = square_matrix<int, 5>;

	using char_matrix1d = square_matrix<char, 1>;
	using char_matrix2d = square_matrix<char, 2>;
	using char_matrix3d = square_matrix<char, 3>;
	using char_matrix4d = square_matrix<char, 4>;
	using char_matrix5d = square_matrix<char, 5>;

	using double_matrix1d = square_matrix<double, 1>;
	using double_matrix2d = square_matrix<double, 2>;
	using double_matrix3d = square_matrix<double, 3>;
	using double_matrix4d = square_matrix<double, 4>;
	using double_matrix5d = square_matrix<double, 5>;

	using float_matrix1d = square_matrix<float, 1>;
	using float_matrix2d = square_matrix<float, 2>;
	using float_matrix3d = square_matrix<float, 3>;
	using float_matrix4d = square_matrix<float, 4>;
	using float_matrix5d = square_matrix<float, 5>;

	template <typename T, size_t N>
	square_matrix<T, N> make_id_matrix()
	{
		square_matrix<T, N> result(0);

		for (size_t i = 0; i < N; ++i)
			result.data[i][i] = 1;

		return result;
	}

    template <typename T, size_t N>
	square_matrix<T, N> make_square_matrix_from_rows(std::initializer_list<vector<T, N>> il)
	{
		assert(il.size() == N);

		auto it = il.begin();
		square_matrix<T, N> result(0);

		for (size_t i = 0; i < N; ++i)
		{
			vector<T, N> vec = *it;

			for (size_t j = 0; j < N; ++j)
				result.data[i][j] = vec(j);

			++it;
		}

		return result;
	}

	template <typename T, size_t N>
	square_matrix<T, N> make_square_matrix_from_cols(std::initializer_list<vector<T, N>> il)
	{
		assert(il.size() == N);

		auto it = il.begin();
		square_matrix<T, N> result(0);

		for (size_t i = 0; i < N; ++i)
		{
			vector<T, N> vec = *it;

			for (size_t j = 0; j < N; ++j)
				result.data[j][i] = vec(j);

			++it;
		}

		return result;
	}
}
