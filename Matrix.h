#pragma once


namespace lmel
{
	template <typename T>
	class Matrix
	{
	private:
		static const unsigned size = 4 * 4;
		T mat[size];

	public:
		static const unsigned rows = 4;
		static const unsigned cols = 4;

		explicit Matrix(T init);
		Matrix(const Matrix<T> & ref);
		virtual ~Matrix();

		Matrix<T> & operator=(const Matrix<T> & val);
                                                                                                                                                                                              
		Matrix<T> operator+(const Matrix<T> & val);
		Matrix<T> operator-(const Matrix<T> & val);
		Matrix<T> operator*(const Matrix<T> & val);

		Matrix<T> & operator+=(const Matrix<T> & val);
		Matrix<T> & operator-=(const Matrix<T> & val);
		Matrix<T> & operator*=(const Matrix<T> & val);

		Matrix<T> operator+(T val);
		Matrix<T> operator-(T val);
		Matrix<T> operator*(T val);
		Matrix<T> operator/(T val);

		Matrix<T> & operator+=(T val);
		Matrix<T> & operator-=(T val);
		Matrix<T> & operator*=(T val);
		Matrix<T> & operator/=(T val);

		bool operator==(const Matrix<T> & m) const;
		bool operator!=(const Matrix<T> & m) const;

		void transpose();

		T & operator()(const unsigned & row, const unsigned & col);
		const T & operator()(const unsigned & row, const unsigned & col) const;

		T get(unsigned n) const;
	};
}

template<typename T>
inline lmel::Matrix<T>::Matrix(T init)
	: mat
{
	init, init, init, init,
	init, init, init, init,
	init, init, init, init,
	init, init, init, init
}
{}

template<typename T>
inline lmel::Matrix<T>::Matrix(const Matrix<T> & ref)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] = ref.mat[i];
}

template<typename T>
inline lmel::Matrix<T>::~Matrix() {}

template<typename T>
inline lmel::Matrix<T> & lmel::Matrix<T>::operator=(const lmel::Matrix<T> & val)
{
	if (&val == this)
		return *this;

	for (unsigned i = 0; i < size; ++i)
		mat[i] = val.mat[i];

	return *this;
}

template<typename T>
inline lmel::Matrix<T> lmel::Matrix<T>::operator+(const lmel::Matrix<T> & val)
{
	Matrix result(0);

	for (unsigned i = 0; i < size; ++i)
		result.mat[i] = mat[i] + val.mat[i];

	return result;
}

template<typename T>
inline lmel::Matrix<T> lmel::Matrix<T>::operator-(const lmel::Matrix<T> & val)
{
	Matrix result(0);

	for (unsigned i = 0; i < size; ++i)
		result.mat[i] = mat[i] - val.mat[i];

	return result;
}

template<typename T>
inline lmel::Matrix<T> lmel::Matrix<T>::operator*(const lmel::Matrix<T> & val)
{
	Matrix result(0);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			for (unsigned k = 0; k < rows; k++)
				result.mat[i * cols + j] += mat[i * cols + k] * val.mat[k * cols + j];

	return result;
}

template<typename T>
inline lmel::Matrix<T> & lmel::Matrix<T>::operator+=(const lmel::Matrix<T> & val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] += val.mat[i];

	return *this;
}

template<typename T>
inline lmel::Matrix<T> & lmel::Matrix<T>::operator-=(const lmel::Matrix<T> & val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] -= val.mat[i];

	return *this;
}

template<typename T>
inline lmel::Matrix<T> & lmel::Matrix<T>::operator*=(const lmel::Matrix<T> & val)
{
	Matrix result(0);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < cols; j++)
			for (unsigned k = 0; k < rows; k++)
				result.mat[i * cols + j] += mat[i * cols + k] * val.mat[k * cols + j];

	for (unsigned i = 0; i < size; ++i)
		mat[i] = result.mat[i];

	return *this;
}

template<typename T>
inline lmel::Matrix<T> lmel::Matrix<T>::operator+(T val)
{
	Matrix result(0);

	for (unsigned i = 0; i < size; ++i)
		result.mat[i] = mat[i] + val;

	return result;
}

template<typename T>
inline lmel::Matrix<T> lmel::Matrix<T>::operator-(T val)
{
	Matrix result(0);

	for (unsigned i = 0; i < size; ++i)
		result.mat[i] = mat[i] - val;

	return result;
}

template<typename T>
inline lmel::Matrix<T> lmel::Matrix<T>::operator*(T val)
{
	Matrix result(0);

	for (unsigned i = 0; i < size; ++i)
		result.mat[i] = mat[i] * val;

	return result;
}

template<typename T>
inline lmel::Matrix<T> lmel::Matrix<T>::operator/(T val)
{
	Matrix result(0);

	for (unsigned i = 0; i < size; ++i)
		result.mat[i] = mat[i] / val;

	return result;
}

template<typename T>
inline lmel::Matrix<T> & lmel::Matrix<T>::operator+=(T val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] += val;

	return *this;
}

template<typename T>
inline lmel::Matrix<T> & lmel::Matrix<T>::operator-=(T val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] -= val;

	return *this;
}

template<typename T>
inline lmel::Matrix<T> & lmel::Matrix<T>::operator*=(T val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] *= val;

	return *this;
}

template<typename T>
inline lmel::Matrix<T> & lmel::Matrix<T>::operator/=(T val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] /= val;

	return *this;
}

template<typename T>
inline bool lmel::Matrix<T>::operator==(const lmel::Matrix<T> & m) const
{
	for (unsigned i = 0; i < size; ++i)
		if (mat[i] != m.mat[i])
			return false;

	return true;
}

template<typename T>
inline bool lmel::Matrix<T>::operator!=(const lmel::Matrix<T> & m) const
{
	for (unsigned i = 0; i < size; ++i)
		if (mat[i] != m.mat[i])
			return true;

	return false;
}

template<typename T>
inline void lmel::Matrix<T>::transpose()
{
	Matrix tmp(0);

	for (unsigned i = 0; i < size; ++i)
		tmp.mat[i] = mat[i];

	for (unsigned i = 0; i < rows; ++i)
		for (unsigned j = 0; j < cols; ++j)
			mat[i * cols + j] = tmp.mat[j * cols + i];
}

template<typename T>
inline T & lmel::Matrix<T>::operator()(const unsigned & row, const unsigned & col)
{
	return mat[row * rows + col];
}

template<typename T>
inline const T & lmel::Matrix<T>::operator()(const unsigned & row, const unsigned & col) const
{
	return mat[row * rows + col];
}

template<typename T>
inline T lmel::Matrix<T>::get(unsigned n) const
{
	return mat[n];
}
