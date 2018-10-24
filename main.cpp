
#include <iostream>
#include "lmel/matrix.h"
#include "lmel/square_matrix.h"
#include "lmel/vector.h"

using namespace lmel;
using namespace std;

template <typename T, unsigned N>
void show(const vector<T, N> & vec)
{
	for (unsigned i = 0; i < vec.size; ++i)
		cout << vec(i) << " ";
}

template <typename T, unsigned N>
void show(const square_matrix<T, N> & mat)
{
	for (unsigned i = 0; i < mat.rows; ++i)
	{
		for (unsigned j = 0; j < mat.cols; ++j)
			cout << mat(i, j) << " ";

		cout << "\n";
	}
}

template <typename T, unsigned N, unsigned M>
void show(const matrix<T, N, M> & mat)
{
	for (unsigned i = 0; i < mat.rows; ++i)
	{
		for (unsigned j = 0; j < mat.cols; ++j)
			cout << mat(i, j) << " ";

		cout << "\n";
	}
}

#include "test/vector.cpp"
#include "test/matrix.cpp"
#include "test/square_matrix.cpp"
#include "test/determinant.cpp"

int main()
{
	cout << "Run tests:\n";
	test_vector();
	test_matrix();
	test_square_matrix();
	test_determinant();

	getchar();
	return 0;
}