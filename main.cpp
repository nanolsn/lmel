#include <iostream>
#include "lmel/Matrix.h"
#include "lmel/SquareMatrix.h"
#include "lmel/Vector.h"

using namespace lmel;
using namespace std;

template <typename T, unsigned N>
void show(const Vector<T, N> & vec)
{
	for (unsigned i = 0; i < vec.size; ++i)
		cout << vec(i) << " ";
}

template <typename T, unsigned N>
void show(const SquareMatrix<T, N> & mat)
{
	for (unsigned i = 0; i < mat.rows; ++i)
	{
		for (unsigned j = 0; j < mat.cols; ++j)
			cout << mat(i, j) << " ";

		cout << "\n";
	}
}

template <typename T, unsigned N, unsigned M>
void show(const Matrix<T, N, M> & mat)
{
	for (unsigned i = 0; i < mat.rows; ++i)
	{
		for (unsigned j = 0; j < mat.cols; ++j)
			cout << mat(i, j) << " ";

		cout << "\n";
	}
}

#include "test/Vector.cpp"
#include "test/Matrix.cpp"
#include "test/SquareMatrix.cpp"
#include "test/determinant.cpp"

int main()
{
	cout << "Run tests:\n";
	testVector();
	testMatrix();
	testSquareMatrix();
	testDeterminant();

	getchar();
	return 0;
}