#pragma once

#include <initializer_list>
#include <cassert>
#include "vector.h"

namespace lmel
{
	template <
		typename T,
		unsigned N,
		unsigned M,
		typename = typename std::enable_if<std::is_arithmetic<T>::value && N != 0 && M != 0, T>::type
		>
	class matrix
	{
	protected:
		T data[N][M];

	public:
		static const unsigned rows = N;
		static const unsigned cols = M;

		// Constructor with init value
		explicit matrix(T init = 0)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] = init;
		}

		// Initializer list constructor
		matrix(std::initializer_list<T> il)
		{
			assert(il.size() == N * M);

			auto it = il.begin();

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] = *it++;
		}

		// Copy constructor
		matrix(const matrix & ref)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] = ref.data[i][j];
		}

		// Template copy constructor
		template <typename O>
		matrix(const matrix<O, N, M> & ref)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] = ref(i, j);
		}

		// Assignment operator
		matrix & operator=(const matrix & val)
		{
			if (&val == this)
				return *this;

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] = val.data[i][j];

			return *this;
		}

		vector<T, M> get_row(const unsigned row) const
		{
			assert(row < rows);

			vector<T, M> result(0);

			for (size_t i = 0; i < cols; ++i)
				result(i) = data[row][i];

			return result;
		}

		vector<T, N> get_col(const unsigned col) const
		{
			assert(col < cols);

			vector<T, N> result(0);

			for (size_t i = 0; i < rows; ++i)
				result(i) = data[i][col];

			return result;
		}

		void set_row(unsigned row_num, const vector<T, M> & row)
		{
			assert(row_num < rows);

			for (size_t j = 0; j < cols; ++j)
				data[row_num][j] = row(j);
		}

		void set_col(unsigned col_num, const vector<T, N> & col)
		{
			assert(col_num < cols);

			for (size_t i = 0; i < rows; ++i)
				data[i][col_num] = col(i);
		}

		void swap_rows(unsigned a, unsigned b)
		{
			vector<T, M> tmp = get_row(a);
			set_row(a, get_row(b));
			set_row(b, tmp);
		}

		void swap_cols(unsigned a, unsigned b)
		{
			vector<T, N> tmp = get_col(a);
			set_col(a, get_col(b));
			set_col(b, tmp);
		}

		// Default math operations:

		matrix operator+(const matrix & val) const
		{
			matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] + val.data[i][j];

			return result;
		}

		matrix operator-(const matrix & val) const
		{
			matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] - val.data[i][j];

			return result;
		}

		template <unsigned K>
		matrix<T, N, K> operator*(const matrix<T, M, K> & val) const
		{
			matrix<T, N, K> result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					for (size_t k = 0; k < K; ++k)
						result(i, k) += data[i][j] * val(j, k);

			return result;
		}

		matrix & operator+=(const matrix & val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] += val.data[i][j];

			return *this;
		}

		matrix & operator-=(const matrix & val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] -= val.data[i][j];

			return *this;
		}

		matrix operator+(T val) const
		{
			matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] + val;

			return result;
		}

		matrix operator-(T val) const
		{
			matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] - val;

			return result;
		}

		matrix operator*(T val) const
		{
			matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] * val;

			return result;
		}

		matrix operator/(T val) const
		{
			matrix result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result.data[i][j] = data[i][j] / val;

			return result;
		}

		matrix & operator+=(T val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] += val;

			return *this;
		}

		matrix & operator-=(T val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] -= val;

			return *this;
		}

		matrix & operator*=(T val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] *= val;

			return *this;
		}

		matrix & operator/=(T val)
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					data[i][j] /= val;

			return *this;
		}

		// Vector product:
		vector<T, N> operator*(const vector<T, M> & vec) const
		{
			vector<T, N> result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					result(i) += data[i][j] * vec(j);

			return result;
		}

		// Compare operations:

		bool operator==(const matrix & m) const
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					if (data[i][j] != m.data[i][j])
						return false;

			return true;
		}

		bool operator!=(const matrix & m) const
		{
			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
					if (data[i][j] != m.data[i][j])
						return true;

			return false;
		}

		matrix<T, M, N> get_transpose() const
		{
			matrix<T, M, N> result(0);

			for (size_t i = 0; i < rows; ++i)
				for (size_t j = 0; j < cols; ++j)
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

		template <typename I, unsigned K, unsigned L>
		friend matrix<I, K, L> make_matrix_from_rows(std::initializer_list<vector<I, L>> il);

		template <typename I, unsigned K, unsigned L>
		friend matrix<I, K, L> make_matrix_from_cols(std::initializer_list<vector<I, K>> il);
	};

	template <unsigned N, unsigned M>
	using int_matrix = matrix<int, N, M>;

	template <unsigned N, unsigned M>
	using char_matrix = matrix<char, N, M>;

	template <unsigned N, unsigned M>
	using float_matrix = matrix<float, N, M>;

	template <unsigned N, unsigned M>
	using double_matrix = matrix<double, N, M>;

	template <typename T, unsigned N, unsigned M>
	matrix<T, N, M> make_matrix_from_rows(std::initializer_list<vector<T, M>> il)
	{
		assert(il.size() == N);

		auto it = il.begin();
		matrix<T, N, M> result(0);

		for (size_t i = 0; i < N; ++i)
		{
			vector<T, M> vec = *it;

			for (size_t j = 0; j < M; ++j)
				result.data[i][j] = vec(j);

			++it;
		}

		return result;
	}

	template <typename T, unsigned N, unsigned M>
	matrix<T, N, M> make_matrix_from_cols(std::initializer_list<vector<T, N>> il)
	{
		assert(il.size() == M);

		auto it = il.begin();
		matrix<T, N, M> result(0);

		for (size_t i = 0; i < M; ++i)
		{
			vector<T, N> vec = *it;

			for (size_t j = 0; j < N; ++j)
				result.data[j][i] = vec(j);

			++it;
		}

		return result;
	}
}
