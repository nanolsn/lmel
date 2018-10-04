#include "Matrix.h"


template<typename T>
lmel::Matrix<T>::Matrix(T init)
	: mat
	{
		init, init, init, init,
		init, init, init, init,
		init, init, init, init,
		init, init, init, init
	}
{
}

template<typename T>
lmel::Matrix<T>::Matrix(const Matrix<T> & ref)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] = ref[i];
}

template<typename T>
lmel::Matrix<T>::~Matrix()
{
}

template<typename T>
lmel::Matrix<T> & lmel::Matrix<T>::operator=(const lmel::Matrix<T> & val)
{
	if (&val == this)
		return *this;

	for (unsigned i = 0; i < size; ++i)
		mat[i] = val[i];

	return *this;
}

template<typename T>
lmel::Matrix<T> lmel::Matrix<T>::operator+(const lmel::Matrix<T> & val)
{
	Matrix result(0.0);

	for (unsigned i = 0; i < size; ++i)
		result[i] = mat[i] + val[i];

	return result;
}

template<typename T>
lmel::Matrix<T> lmel::Matrix<T>::operator-(const lmel::Matrix<T> & val)
{
	Matrix result(0.0);

	for (unsigned i = 0; i < size; ++i)
		result[i] = mat[i] - val[i];

	return result;
}

template<typename T>
lmel::Matrix<T> lmel::Matrix<T>::operator*(const lmel::Matrix<T> & val)
{
	Matrix result(0.0);

	for (unsigned i = 0; i < size; ++i)
		result[i] = mat[i] * val[i];

	return result;
}

template<typename T>
lmel::Matrix<T> & lmel::Matrix<T>::operator+=(const lmel::Matrix<T> & val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] += val[i];

	return *this;
}

template<typename T>
lmel::Matrix<T> & lmel::Matrix<T>::operator-=(const lmel::Matrix<T> & val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] -= val[i];

	return *this;
}

template<typename T>
lmel::Matrix<T> & lmel::Matrix<T>::operator*=(const lmel::Matrix<T> & val)
{
	for (unsigned i = 0; i < size; ++i)
		mat[i] *= val[i];

	return *this;
}

template<typename T>
lmel::Matrix<T> lmel::Matrix<T>::operator+(T val)
{
	Matrix result(0.0);

	for (unsigned i = 0; i < size; ++i)
		result[i] = mat[i] + val;

	return result;
}

template<typename T>
lmel::Matrix<T> lmel::Matrix<T>::operator-(T val)
{
	Matrix result(0.0);

	for (unsigned i = 0; i < size; ++i)
		result[i] = mat[i] - val;

	return result;
}

template<typename T>
lmel::Matrix<T> lmel::Matrix<T>::operator*(T val)
{
	Matrix result(0.0);

	for (unsigned i = 0; i < size; ++i)
		result[i] = mat[i] * val;

	return result;
}

template<typename T>
lmel::Matrix<T> lmel::Matrix<T>::operator/(T val)
{
	Matrix result(0.0);

	for (unsigned i = 0; i < size; ++i)
		result[i] = mat[i] / val;

	return result;
}

template<typename T>
lmel::Matrix<T> lmel::Matrix<T>::transpose()
{
	Matrix tmp(this);

	for (unsigned i = 0; i < rows; ++i)
		for (unsigned j = 0; j < cols; ++j)
			mat[i * cols + j] = tmp.mat[j * cols + i];
}

template<typename T>
T lmel::Matrix<T>::get(unsigned n)
{
	return mat[n];
}

