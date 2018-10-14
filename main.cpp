#include <iostream>
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

#include "test/Vector.cpp"
#include "test/SquareMatrix.cpp"
#include "test/determinant.cpp"

int main()
{
	testVector();
	testSquareMatrix();
	testDeterminant();

	DoubleVector3D v = { 3.0, 3.0, 7.0 };
	v.normalize();
	cout << v.length();
	cout << "\n";
	v.y() = 5;
	show(v);

	// double w = v.w();

	// SquareMatrix<int, 0> m(9);

	getchar();
	return 0;
}